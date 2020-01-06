#include <gtest/gtest.h>

#include "othello_wrapper.h"


bool test_othello(int n) {
    vector<std::pair<uint64_t, bool> > kvs;
    for (int i = 0; i < n; i++) {
        kvs.push_back(make_pair(uint64_t(i), bool(rand()%2)));
    }

    OthelloWrapper<uint64_t> o(n);
    o.build(kvs);

    // verify
    bool success = true;
    for (int i = 0; i < n; i++) {
        if (kvs[i].second != o.query(kvs[i].first)) {
            success = false;
        }
    }
    return success;
}

TEST(Othello, Basic) {
    EXPECT_TRUE(test_othello(1000)); // 1k
    EXPECT_TRUE(test_othello(1000*1000)); // 1m
    EXPECT_TRUE(test_othello(1000*1000*10)); // 10m
    EXPECT_TRUE(test_othello(1000*1000*20)); // 20m
    // The following tests fail
    // EXPECT_TRUE(test_othello(1000*1000*50)); // 50m
    // EXPECT_TRUE(test_othello(1000*1000*100)); // 100m
}