#pragma once

#include "othello/othello.h"

template <class keyType>
class OthelloWrapper {
   public:
    OthelloWrapper() = default;
    OthelloWrapper(int max_capacity) { init(max_capacity); }
    ~OthelloWrapper() { clear(); }

    void init(int max_capacity) { (void)max_capacity; }

    void build(const std::vector<std::pair<keyType, bool>> &kvs) {
        assert(o_ == nullptr);

        int n = kvs.size();
        keyType *keys = new keyType[n];
        bool *vals = new bool[n];

        for (int i = 0; i < n; i++) {
            keys[i] = kvs[i].first;
            vals[i] = kvs[i].second;
        }

        o_ = new Othello<keyType>(2, keys, n, true, vals, sizeof(bool));

        delete[] keys;
        delete[] vals;
    }

    void clear() {
        if (o_ != nullptr) {
            delete o_;
            o_ = nullptr;
        }
    }

    bool query(keyType key) {
        uint32_t ha, hb;
        return (bool)o_->query(key, ha, hb);
    }

   private:
    Othello<keyType> *o_ = nullptr;
};