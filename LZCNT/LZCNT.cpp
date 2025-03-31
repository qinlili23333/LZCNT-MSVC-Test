#include <intrin.h>
#include <iostream>
#include <chrono>

unsigned lzcnt_on_bsr(unsigned i);
unsigned lzcnt_on_bsr64(unsigned long i);
unsigned lzcnt_on_bsr64_sim(unsigned long i);
std::chrono::duration<double, std::milli> measureLzcntExecutionTime(unsigned (*fun)(unsigned i));

bool support_lzcnt;



int main()
{
    volatile unsigned i = 0x0FFF'FFFC;
    

    unsigned lzcnt = _lzcnt_u32(i);
    unsigned lzcnt_bsr = lzcnt_on_bsr(i);

    std::cout << " NATIVE LZCNT:" << lzcnt << " LZCNT ON BSR:" << lzcnt_bsr << "\n";


    volatile unsigned long i2 = 0x0;


    unsigned lzcnt64 = __lzcnt64(i2);
    unsigned lzcnt_bsr64 = lzcnt_on_bsr64(i2);

    std::cout << " NATIVE LZCNT64:" << lzcnt64 << " LZCNT64 ON BSR:" << lzcnt_bsr64 << "\n";

    return 0;
}


unsigned lzcnt_on_bsr(unsigned i)
{
    unsigned long bsr;
    _BitScanReverse(&bsr, i);
    return 31-bsr;
}
unsigned lzcnt_on_bsr64(unsigned long i)
{
    unsigned long bsr;
    _BitScanReverse64(&bsr, i);
    return 63 - bsr;
}
unsigned lzcnt_on_bsr64_sim(unsigned long i)
{
    unsigned long bsr;
    if (_BitScanReverse(&bsr, i >> 32))
        bsr += 32;
    else
        _BitScanReverse(&bsr, i & 0xffffffff);
    return 63 - bsr;
}
