#include <iostream>


template <typename T>

T leftCycleShift(T value, int positions)
{
    const int bit = sizeof(T) * 8;
    return (value << positions) | (value >> (bit - positions));
}

int main()
{
    return 0;
}
