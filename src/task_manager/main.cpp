#include "../include/rr_scheduler.h"

int main() {
    rocksdb::DB* db;
    auto rr_sched = RoundRobinScheduler(db);
    rr_sched.ScheduleTasks();

    return 0;
}