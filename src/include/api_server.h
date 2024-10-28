#pragma once

#include <crow.h>

class ApiServer {
public:
    explicit ApiServer(crow::SimpleApp app): app_(app) {};

    void start(int port);

    void register_health_routes();

    void register_worker_routes();
private:
    crow::SimpleApp app_;
};


