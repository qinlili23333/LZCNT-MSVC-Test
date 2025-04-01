#include <intrin.h>
#include <iostream>
#include <chrono>

unsigned tzcnt_on_bsf(unsigned i);
unsigned tzcnt_on_bsf64(unsigned long i);

bool support_tzcnt;



int main()
{
#ifdef __LZCNT__
    std::cout << " LZCNT defined" << "\n";
#else
    std::cout << " LZCNT undefined" << "\n";
#endif

#ifdef __AVX2__
    std::cout << " AVX2 defined" << "\n";
#else
    std::cout << " AVX2 undefined" << "\n";
#endif
    volatile unsigned i = 0x0;
    

    unsigned tzcnt = _tzcnt_u32(i);
    unsigned tzcnt_bsf = tzcnt_on_bsf(i);

    std::cout << " NATIVE TZCNT:" << tzcnt << " TZCNT ON BSR:" << tzcnt_bsf << "\n";


    volatile unsigned long i2 = 0x0;


    unsigned tzcnt64 = _tzcnt_u64(i2);
    unsigned tzcnt_bsf64 = tzcnt_on_bsf64(i2);

    std::cout << " NATIVE TZCNT64:" << tzcnt64 << " TZCNT64 ON BSR:" << tzcnt_bsf64 << "\n";

    return 0;
}


unsigned tzcnt_on_bsf(unsigned i)
{
    unsigned long bsf;
    _BitScanForward(&bsf, i);
    return bsf;
}
unsigned tzcnt_on_bsf64(unsigned long i)
{
    unsigned long bsf;
    _BitScanForward64(&bsf, i);
    return bsf;
}
