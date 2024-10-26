#pragma once

template<typename KeyType, typename ValueType>
class BaseScheduler {
public:
    virtual ValueType Get();
    virtual void Set(KeyType key);
};