#include "../include/api_server.h"

int main() {
    crow::SimpleApp app;
    auto server = ApiServer(app);
    server.start(8080);
    return 0;
}