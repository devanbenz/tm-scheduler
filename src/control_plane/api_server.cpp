#include "../include/api_server.h"
#include "../include/metadata.h"
#include <iostream>

void ApiServer::start(int port) {
    register_health_routes();
    register_worker_routes();
    app_.port(port).multithreaded().run();
}

void ApiServer::register_worker_routes() {
    CROW_ROUTE(app_, "/api/v1/insert/worker")
            .methods("POST"_method)
                    ([](const crow::request& req) {
                        auto metadata = MetadataStore<std::string, std::string>();
                        auto body = crow::json::load(req.body);
                        if (!body) {
                            return crow::response(crow::status::BAD_REQUEST);
                        }
                        std::string worker_address = body["worker"].s();
                        metadata.Set("worker", worker_address);
                        return crow::response(crow::status::OK);
                    });
}

void ApiServer::register_health_routes() {
    CROW_ROUTE(app_, "/health")([]() {
        return "I'm okay!";
    });
}
