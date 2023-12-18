#include <iostream>


template <typename T>

T leftCycleShift(T value, int positions)
{
    const int bit = sizeof(T) * 8;
    return (value << positions) | (value >> (bit - positions));
}

unsigned int nonLinearity(int i, unsigned int B, unsigned int C, unsigned int D)
{
    unsigned int result;

    if (0 <= i && i <= 19)
    {
        result = ( B & C ) | ( ( ~B ) & D );
    }
    else if (20 <= i && i <= 39) 
    {
        result = B ^ C ^ D;
    }
    else if (40 <= i && i <= 59) 
    {
        result = ( B & C ) | ( B & D ) | ( C & D );
    }
    else if (60 <= i && i <= 79) 
    {
        result = B ^ C ^ D;
    }

    return result;
}

int main()
{
    return 0;
}
