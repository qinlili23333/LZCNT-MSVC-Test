#include <intrin.h>
#include <iostream>
#include "InstructionSet.cpp"
#include <chrono>

unsigned lzcnt_on_bsr(unsigned i);
unsigned lzcnt_detect(unsigned i);
unsigned lzcnt_detect_cache(unsigned i);
std::chrono::duration<double, std::milli> measureLzcntExecutionTime(unsigned (*fun)(unsigned i));

bool support_lzcnt;



int main()
{
    volatile unsigned i = 0x0FFF'FFFC;
    support_lzcnt = InstructionSet::LZCNT();
    std::cout << "Support Native LZCNT:"  << support_lzcnt << std::endl;
    auto execution_time = measureLzcntExecutionTime(lzcnt_on_bsr);
    std::cout << "Time taken for 10000000000 executions of lzcnt_on_bsr: "
        << execution_time.count() << " milliseconds" << std::endl;
    execution_time = measureLzcntExecutionTime(lzcnt_detect);
    std::cout << "Time taken for 10000000000 executions of lzcnt_detect: "
        << execution_time.count() << " milliseconds" << std::endl;
    execution_time = measureLzcntExecutionTime(lzcnt_detect_cache);
    std::cout << "Time taken for 10000000000 executions of lzcnt_detect_cache: "
        << execution_time.count() << " milliseconds" << std::endl;


    return 0;
    unsigned lzcnt = __lzcnt(i);
    unsigned lzcnt_bsr = lzcnt_on_bsr(i);

    std::cout <<  " NATIVE LZCNT:" << lzcnt << " LZCNT ON BSR:" << lzcnt_bsr << "\n";
}

// modified from gemini generated code
std::chrono::duration<double, std::milli> measureLzcntExecutionTime(unsigned (*fun)(unsigned i)) {
    const long long num_executions = 10000000000;
    volatile unsigned int result; // Use volatile to prevent optimization
    auto start_time = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < num_executions; ++i) {
        result = fun(1);
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    return end_time - start_time;
}


unsigned lzcnt_on_bsr(unsigned i)
{
    unsigned long bsr;
    _BitScanReverse(&bsr, i);
    return 31-bsr;
}

unsigned lzcnt_detect(unsigned i)
{
    if (InstructionSet::LZCNT()) {
        return __lzcnt(i);
    }
    else {
        return lzcnt_on_bsr(i);
    }
}
unsigned lzcnt_detect_cache(unsigned i)
{
    if (support_lzcnt) {
        return __lzcnt(i);
    }
    else {
        return lzcnt_on_bsr(i);
    }
}