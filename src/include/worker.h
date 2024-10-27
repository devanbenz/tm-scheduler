#pragma once

#include "protos/api/v1/node.grpc.pb.h"

class WorkerNode final : public Node::Service {
public:
    grpc::Status HealthCheck(::grpc::ServerContext *context, const ::EmptyRequest *request,
                             ::HealthCheckResponse *response) override {

        response->set_message("I'm okay!");

        return ::grpc::Status::OK;
    }

};