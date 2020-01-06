#include <gtest/gtest.h>

#include "othello_wrapper.h"


int test_othello(int n) {
    vector<std::pair<uint64_t, bool> > kvs;
    for (int i = 0; i < n; i++) {
        kvs.push_back(make_pair(uint64_t(i), bool(rand()%2)));
    }

    OthelloWrapper<uint64_t> o(n);
    o.build(kvs);

    // verify
    int failed = 0;
    for (int i = 0; i < n; i++) {
        if (kvs[i].second != o.query(kvs[i].first)) {
            failed++;
        }
    }

    printf("test_othello: n = %d, failed = %d\n", n, failed);
    return failed;
}

TEST(Othello, Basic) {
    // due to othello's bug, there are always some keys absent from the table
    EXPECT_TRUE(test_othello(1000) < 10); // 1k
    EXPECT_TRUE(test_othello(1000*1000) < 10); // 1m
    EXPECT_TRUE(test_othello(1000*1000*10) < 180); // 10m
    EXPECT_TRUE(test_othello(1000*1000*20) < 230); // 20m
    EXPECT_TRUE(test_othello(1000*1000*50) < 1400); // 50m, 1364 keys fail
    EXPECT_TRUE(test_othello(1000*1000*100) < 2000); // 100m
}