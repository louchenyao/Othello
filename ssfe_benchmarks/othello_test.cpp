#include <gtest/gtest.h>

#include "othello_wrapper.h"



TEST(Othello, Basic) {
    int n = 100000;
    vector<std::pair<uint64_t, bool> > kvs;
    for (int i = 0; i < n; i++) {
        kvs.push_back(make_pair(uint64_t(i), bool(rand()%2)));
    }

    OthelloWrapper<uint64_t> o(n);
    o.build(kvs);

    // verify
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(kvs[i].second, o.query(kvs[i].first));
    }
}