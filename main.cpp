#include <iostream>
#include <string>
#include <vector>

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


std::string SHA1(std::string message)
{
    // Convert each character in the input message to its binary representation.

    std::vector<bool> messageBits;

    for (char character : message)
    {
        for (int bit = 7; bit >= 0; --bit)
        {
            messageBits.push_back((character & (1 << bit)) != 0);
        }
    }

    // Initial hash values (H0, H1, H2, H3, H4) for SHA-1

    const unsigned int H0_initial = 0x67452301;
    const unsigned int H1_initial = 0xEFCDAB89;
    const unsigned int H2_initial = 0x98BADCFE;
    const unsigned int H3_initial = 0x10325476;
    const unsigned int H4_initial = 0xC3D2E1F0;

    // Constants (K) for each round of SHA-1

    unsigned int K[80];

    for (int i = 0; i <= 79; ++i)
    {
        if (0 <= i && i <= 19) K[i] = 0x5A827999;
        else if (20 <= i && i <= 39) K[i] = 0x6ED9EBA1;
        else if (40 <= i && i <= 59) K[i] = 0x8F1BBCDC;
        else if (60 <= i && i <= 79) K[i] = 0xCA62C1D6;
    }
}


int main()
{
    return 0;
}
