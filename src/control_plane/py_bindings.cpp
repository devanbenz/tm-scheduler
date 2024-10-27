#include <pybind11/pybind11.h>
#include "../include/grpc_client.h"


std::string healthcheck(const std::string& addr) {
    std::string res = SendHealthCheck(addr);
    return res;
}

void register_worker(const std::string& addr) {

}

PYBIND11_MODULE(PyTmSched, m) {
    m.def("healthcheck", &healthcheck, "Send a healthcheck RPC to work node");
}