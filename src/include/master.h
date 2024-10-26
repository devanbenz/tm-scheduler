#pragma

#include <iostream>
#include <grpcpp/grpcpp.h>
#include "protos/api/v1/master.pb.h"
#include "protos/api/v1/master.grpc.pb.h"


class MasterNodeImp : public MasterNode::Service {
public:
    grpc::Status HealthCheck(::grpc::ServerContext *context, const ::EmptyRequest *request,
                             ::HealthCheckResponse *response) override {
        std::cout << "Called healthcheck\n";
        response->set_message("OK!");

        return grpc::Status::OK;
    }
};
