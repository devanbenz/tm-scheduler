#include <grpcpp/grpcpp.h>
#include "absl/strings/str_format.h"
#include "../include/worker.h"

int main() {
    std::string server_addr = absl::StrFormat("0.0.0.0:%d", 50051);
    WorkerNode worker;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&worker);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_addr << std::endl;

    server->Wait();

    return 0;
}