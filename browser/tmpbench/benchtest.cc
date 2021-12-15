#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <cstdlib>

std::map<std::string, int> benchmarks;

int main()
{
    benchmarks["./bench1.bin"] = 0;
    benchmarks["./bench2.bin"] = 0;
    benchmarks["./bench3.bin"] = 0;

    for (auto const &[k, v] : benchmarks)
    {
        for (int i = 0; i < 1000; ++i)
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            system((k + " > bench.log").c_str());
            auto t2 = std::chrono::high_resolution_clock::now();

            // subtract the two times to find the time elapsed
            std::printf("Benchmark %s trial #%d: %dms\n", k.c_str(), i + 1, (int)std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
        }
    }
}