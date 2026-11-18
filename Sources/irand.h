#pragma once

#include <cstdint>

#define RANDa 1664525
#define RANDc 1013904223

class IRand
{
    uint32_t _RND { 0 };

public:
    int irand()
    {
        _RND = (_RND * RANDa) + RANDc;
        return _RND >> 16;
    }
};
