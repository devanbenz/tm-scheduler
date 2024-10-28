#include "../include/rr_scheduler.h"

void RoundRobinScheduler::ScheduleTasks() {
}

void RoundRobinScheduler::ProcessTask() {
}

RoundRobinScheduler::RoundRobinScheduler(rocksdb::DB* db) : db_(db) {
    rocksdb::Options opts;
    opts.create_if_missing = true;
    rocksdb::Status status =
            rocksdb::DB::Open(opts, "/tmp/testdb", &db_);
    assert(status.ok());
}

RoundRobinScheduler::~RoundRobinScheduler() {
    delete db_;
}
