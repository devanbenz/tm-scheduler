#pragma once

#include <crow.h>

class ApiServer {
public:
    ApiServer(crow::SimpleApp app): app_(app) {};
    void start(int port);
private:
    void setup_routes();

    crow::SimpleApp app_;
};