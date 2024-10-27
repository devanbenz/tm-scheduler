#include "../include/task_manager.h"

TaskManager::TaskManager(BaseScheduler *sched) : scheduler_(std::move(sched)) {}

TaskManager::~TaskManager() {
    delete scheduler_;
}

grpc::Status TaskManager::HealthCheck(::grpc::ServerContext *context, const ::EmptyRequest *request,
                                      ::HealthCheckResponse *response) {
    response->set_message("I'm okay!");

    return ::grpc::Status::OK;
}

grpc::Status
TaskManager::SendTask(::grpc::ServerContext *context, const ::SendTaskRequest *request, ::SendTaskResponse *response) {
    return Service::SendTask(context, request, response);
}

grpc::Status TaskManager::GetNextTaskFromScheduler(::grpc::ServerContext *context, const ::EmptyRequest *request,
                                                   ::GetNextTaskFromSchedulerResponse *response) {
    return Service::GetNextTaskFromScheduler(context, request, response);
}

TaskManager::TaskManager() {}
