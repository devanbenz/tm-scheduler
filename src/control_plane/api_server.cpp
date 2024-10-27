#include "../include/api_server.h"
#include "../include/task_manager.h"

void ApiServer::start(int port) {
    setup_routes();
    app_.port(port).multithreaded().run();
}

void ApiServer::setup_routes() {
    CROW_ROUTE(app_, "/health")([]() {
        return "I'm okay!";
    });

    CROW_ROUTE(app_, "/api/v1/submit_task")
    .methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(crow::status::BAD_REQUEST);
        }
        std::string input =  body["bucket"].s();
        std::string script = body["script"].s();

        return crow::response{};
    });
}
