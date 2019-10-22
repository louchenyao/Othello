#include <benchmark/benchmark.h>

#include "othello/othello.h"

struct Data {
    uint64_t *keys;
    bool *vals;

    Data(int n) {
        keys = new uint64_t[n];
        vals = new bool[n];
        for (int i = 0; i < n; i++) {
            keys[i] = i;
            vals[i] = rand() % 2;
        }
    }
    ~Data() {
        delete[] keys;
        delete[] vals;
    }
};

static void BM_othello_build(benchmark::State& state) {
    Data d(state.range(0));

    for (auto _ : state) {
        Othello<uint64_t> o(2, d.keys, state.range(0), true, d.vals, sizeof(bool));
        uint32_t ha, hb;
        benchmark::DoNotOptimize(o.query(1, ha, hb));
    }

    state.SetItemsProcessed(int64_t(state.iterations()) *
                            int64_t(state.range(0)));
}

static void BM_othello_query(benchmark::State& state) {
    Data d(state.range(0));

    // construct the othello
    Othello<uint64_t> o(2, d.keys, state.range(0), true, d.vals, sizeof(bool));

    // benchmark
    int i = 0;
    for (auto _ : state) {
        uint32_t ha, hb;
        benchmark::DoNotOptimize(o.query(i, ha, hb));
        i = i + 1;
        if (i == state.range(0)) {
            i = 0;
        }
    }
}

BENCHMARK(BM_othello_query)->Arg(10 * 1000)->Arg(100 * 1000)->Arg(1000 * 1000)->Arg(2 * 1000 * 1000);
BENCHMARK(BM_othello_build)->Arg(10 * 1000)->Arg(100 * 1000)->Arg(1000 * 1000)->Arg(2 * 1000 * 1000);