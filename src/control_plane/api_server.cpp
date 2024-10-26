#include "../include/api_server.h"

void ApiServer::start(int port) {
    setup_routes();
    app_.port(port).multithreaded().run();
}

void ApiServer::setup_routes() {
    CROW_ROUTE(app_, "/health")([]() {
        return "I'm okay!";
    });
}
