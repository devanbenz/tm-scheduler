#pragma once

#include "../include/scheduler.h"

#include "string"
#include <grpcpp/grpcpp.h>
#include "protos/api/v1/task_manager.grpc.pb.h"

enum OutputLocation {
    PATH,
    STDOUT
};

class TaskManager final : public TaskManagerService::Service {
public:
    TaskManager();

    explicit TaskManager(BaseScheduler* sched);

    ~TaskManager() override;

    grpc::Status HealthCheck(::grpc::ServerContext *context, const ::EmptyRequest *request,
                             ::HealthCheckResponse *response) override;

    grpc::Status
    SendTask(::grpc::ServerContext *context, const ::SendTaskRequest *request, ::SendTaskResponse *response) override;

    grpc::Status GetNextTaskFromScheduler(::grpc::ServerContext *context, const ::EmptyRequest *request,
                                          ::GetNextTaskFromSchedulerResponse *response) override;

private:
    BaseScheduler* scheduler_{};
};