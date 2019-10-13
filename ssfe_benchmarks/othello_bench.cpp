#include <benchmark/benchmark.h>

#include "othello.h"

static void BM_othello_query(benchmark::State& state) {
    uint64_t *keys = new uint64_t[state.range(0)];
    bool *vals = new bool[state.range(0)];
    for (int i = 0; i < state.range(0); i++) {
        keys[i] = i;
        vals[i] = rand()%2;
    }

    // construct the othello
    Othello<uint64_t> o(2, keys, state.range(0), true, vals, sizeof(bool));

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

    delete[] keys;
    delete[] vals;
}

BENCHMARK(BM_othello_query)->Arg(10 * 1000)->Arg(100 * 1000)->Arg(1000 * 1000)->Arg(2 * 1000 * 1000);