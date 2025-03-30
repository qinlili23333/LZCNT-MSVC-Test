#include <intrin.h>
#include <iostream>

int main()
{
    volatile unsigned i = 0x0FFF'FFFC;


    unsigned long bsr;
    _BitScanReverse(&bsr, i);
    unsigned lzcnt = __lzcnt(i);

    std::cout <<    " BSR:" << bsr << " LZCNT:" << lzcnt << "\n";
}