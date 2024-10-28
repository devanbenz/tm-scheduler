#include <pybind11/pybind11.h>
#include <grpcpp/grpcpp.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "../include/grpc_client.h"

class SessionManager {
public:
    static SessionManager& get_instance() {
        static SessionManager instance;
        return instance;
    }

    void set_session_address(const std::string& address) {
        session_address_ = address;
    }

    std::string get_session_address() const {
        return session_address_;
    }

private:
    SessionManager() = default;
    std::string session_address_;
};

grpc::Status healthcheck(const std::string& addr) {
    auto res = SendHealthCheck(addr);
    return res;
}

PYBIND11_MODULE(PyTmSched, m) {
    m.def("healthcheck", &healthcheck, "Send a healthcheck RPC to work node");
    m.def("OpenSession", [](const std::string& input_address) {
        auto& session_manager = SessionManager::get_instance();
        std::stringstream ss;
        std::stringstream address;
        address << input_address << "/health";
        cpr::Response res = cpr::Get(cpr::Url{address.str()});
        if (res.status_code != 200) {
            ss << "Error when opening connection for " << input_address << ": " << res.error.message;
        }

        session_manager.set_session_address(input_address);
        ss << "Opening session for " << session_manager.get_session_address();
        return ss.str();
        },
          "Opens a session to TM Scheduler control plane.");
    m.def("RegisterWorker", [](const std::string& worker_address) {
        auto& session_manager = SessionManager::get_instance();
        if (session_manager.get_session_address().empty()) {
            return "There is no active session. Please use .NewSession(<addr>) to register a new session.";
        }

        auto worker_res = healthcheck(worker_address);
        if (!worker_res.ok()) {
            return "Worker is not healthy.";
        }

        std::stringstream address;

        address << session_manager.get_session_address() << "/api/v1/insert/worker";
        nlohmann::json worker_payload = {{"worker", worker_address}};
        cpr::Response res = cpr::Post(
                cpr::Url{address.str()},
                cpr::Body({worker_payload.dump()})
                );

        return "Added worker.";

    }, "Registers a new worker. Worker must be active prior to adding.");
}