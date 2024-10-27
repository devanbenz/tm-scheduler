#include "../include/grpc_client.h"
#include <iostream>

int main() {
    std::string rs = SendHealthCheck("0.0.0.0:50051");

    std::cout << rs << std::endl;
}