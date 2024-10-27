#include "../include/rr_scheduler.h"

void RoundRobinScheduler::ScheduleTasks() {
    std::string val;
    rocksdb::Status status;

    status = db_->Put(rocksdb::WriteOptions(), "test", "check!");
    assert(status.ok());

    status = db_->Get(rocksdb::ReadOptions(), "test", &val);
    assert(status.ok());
    std::cout << "Got value: " << val << std::endl;
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
