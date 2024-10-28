#pragma once

#include <rocksdb/db.h>
#include <memory>

template<typename KeyType, typename ValueType>
class MetadataStore {
public:
    MetadataStore();

    ~MetadataStore();

    void Set(KeyType key, ValueType val);

    ValueType Get(KeyType key);
private:
    std::shared_ptr<rocksdb::DB> db_;
};

template<typename KeyType, typename ValueType>
ValueType MetadataStore<KeyType, ValueType>::Get(KeyType key) {
    ValueType val;
    rocksdb::Status status = db_->Get(rocksdb::ReadOptions(), key, &val);
    assert(status.ok());

    return val;
}

template<typename KeyType, typename ValueType>
void MetadataStore<KeyType, ValueType>::Set(KeyType key, ValueType val) {
    rocksdb::Status status = db_->Put(rocksdb::WriteOptions(), key, val);
    assert(status.ok());
}

template<typename KeyType, typename ValueType>
MetadataStore<KeyType, ValueType>::~MetadataStore() {
    db_->Close();
}

template<typename KeyType, typename ValueType>
MetadataStore<KeyType, ValueType>::MetadataStore() {
    rocksdb::DB* db;
    rocksdb::Options opts;
    opts.create_if_missing = true;
    rocksdb::Status status =
            rocksdb::DB::Open(opts, "/tmp/tm_sched_meta_test", &db);
    assert(status.ok());

    db_ = std::shared_ptr<rocksdb::DB>(db, [](rocksdb::DB *ptr) {
        if (ptr) ptr->Close();
        delete ptr;
    });
}
