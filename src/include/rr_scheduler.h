#pragma once

#include <iostream>

#include "scheduler.h"
#include "stack"
#include "chrono"
#include "rocksdb/db.h"

class RoundRobinScheduler : public BaseScheduler {
public:
    explicit RoundRobinScheduler(rocksdb::DB* db);

    ~RoundRobinScheduler();

    void ScheduleTasks() override;

    void ProcessTask() override;
private:
    std::stack<int> task_queue_;
    std::chrono::duration<double> time_{};
    rocksdb::DB* db_;
};
