#include <grpcpp/grpcpp.h>
#include "string"
#include "../include/worker.h"
#include "protos/api/v1/common.grpc.pb.h"

typedef struct {
    std::string relation;
} submit_task_r;

int SubmitTask(const std::string& addr) {
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Node::NewStub(channel);

    grpc::ClientContext ctx;
    return 0;
}

grpc::Status SendHealthCheck(const std::string& addr) {
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;

    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Node::NewStub(channel);

    EmptyRequest req;
    HealthCheckResponse res;
    grpc::ClientContext ctx;
    grpc::Status status;
    stub->async()->HealthCheck(&ctx, &req, &res, [&mu, &cv, &done, &status](grpc::Status s) {
        status = std::move(s);
        std::lock_guard<std::mutex> lock(mu);
        done = true;
        cv.notify_one();
    });

    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
        cv.wait(lock);
    }

   return status;
}