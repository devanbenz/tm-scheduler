#pragma once

enum JobStatus {
    PEND,
    START,
    DONE
};

typedef struct {
    int id;
    int batch_num;
    JobStatus status;
} task_t;

class BaseScheduler {
public:
    virtual void ScheduleTasks() = 0;
    virtual void ProcessTask() = 0;
    virtual ~BaseScheduler() = default;
};