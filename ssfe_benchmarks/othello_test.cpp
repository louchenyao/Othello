#include <gtest/gtest.h>

#include "othello.h"



TEST(Othello, Basic) {
    int n = 100000;
    uint64_t *keys = new uint64_t[n];
    bool *vals = new bool[n];
    for (int i = 0; i < n; i++) {
        keys[i] = i;
        vals[i] = rand()%2;
    }

    // construct the othello
    Othello<uint64_t> o(2, keys, n, true, vals, sizeof(bool));

    // verify
    for (int i = 0; i < n; i++) {
        uint32_t ha, hb;
        EXPECT_EQ(vals[i], (bool)o.query(keys[i], ha, hb));
    }

    delete[] keys;
    delete[] vals;
}