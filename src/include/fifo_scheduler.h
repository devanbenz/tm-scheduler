#pragma once

#include "scheduler.h"

template<typename KeyType, typename ValueType>
class FifoScheduler : public BaseScheduler<KeyType, ValueType> {
public:
    ValueType Get() override {
    }

    void Set(KeyType key) override {
    }
private:

};
