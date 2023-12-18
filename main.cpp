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
        result = (B & C) | ((~B) & D);
    }
    else if (20 <= i && i <= 39)
    {
        result = B ^ C ^ D;
    }
    else if (40 <= i && i <= 59)
    {
        result = (B & C) | (B & D) | (C & D);
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

    unsigned int H0_initial = 0x67452301;
    unsigned int H1_initial = 0xEFCDAB89;
    unsigned int H2_initial = 0x98BADCFE;
    unsigned int H3_initial = 0x10325476;
    unsigned int H4_initial = 0xC3D2E1F0;


    // Constants (K) for each round of SHA-1

    unsigned int K[80];

    for (int i = 0; i <= 79; ++i)
    {
        if (0 <= i && i <= 19) K[i] = 0x5A827999;
        else if (20 <= i && i <= 39) K[i] = 0x6ED9EBA1;
        else if (40 <= i && i <= 59) K[i] = 0x8F1BBCDC;
        else if (60 <= i && i <= 79) K[i] = 0xCA62C1D6;
    }


    // Calculating the length of message in bits using long long type to accommodate the 64-bit length of the message

    long long messageLength = messageBits.size();

    // Variable is used to ensure that only the first bit in the padding is set to '1', and subsequent bits are set to '0'

    bool appendOne = true;

    // Padding the Message to Achieve 448 Bits : 

    while (messageBits.size() % 512 != 448)
    {
        if (appendOne)
        {
            messageBits.push_back(true);
            appendOne = false;
        }
        else
        {
            messageBits.push_back(false);
        }
    }


    // Appending the Original Message Length : 

    for (int i = 63; i >= 0; --i)
    {

        // By appending LL to the literal 1, it specifies that the literal should be treated as a long long.

        messageBits.push_back((messageLength & (1LL << i)) != 0);
    }


    for (int i = 0; i < messageBits.size(); i += 512)
    {

        // Initialize hash values for this block

        unsigned int A = H0_initial;
        unsigned int B = H1_initial;
        unsigned int C = H2_initial;
        unsigned int D = H3_initial;
        unsigned int E = H4_initial;


        // Prepare the message block W for processing

        unsigned int W[80] = { 0 };
        int k = 0;

        // Iterate over the 512-bit block, dividing it into 16 32-bit words (W[0] to W[15])

        for (int j = i; j < i + 512; j += 32)
        {
            int p = 0;

            for (int z = j; z < j + 32; ++z)
            {

                // Assemble each 32-bit word from 32 bits of the message block

                W[k] |= (static_cast<unsigned int>(messageBits[z]) << p);
                ++p;
            }

            ++k;
        }

        // Extend the 16 words to 80 words

        for (int j = 16; j <= 79; ++j)
        {
            W[j] = leftCycleShift(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
        }


        // Main computation loop for the SHA-1 algorithm

        for (int j = 0; j <= 79; ++j)
        {
            unsigned int TEMP = leftCycleShift(A, 5) + nonLinearity(j, B, C, D) + E + W[j] + K[j];
            E = D;
            D = C;
            C = leftCycleShift(B, 30);
            B = A;
            A = TEMP;
        }


        // Update hash values with the results of this block

        H0_initial += A;
        H1_initial += B;
        H2_initial += C;
        H3_initial += D;
        H4_initial += E;
    }

    char result[41];
    sprintf_s(result, "%08x%08x%08x%08x%08x", H0_initial, H1_initial, H2_initial, H3_initial, H4_initial);
    return std::string(result);
}


int main()
{
    std::string S = "abcd";
    std::cout << SHA1(S) << std::endl;

    return 0;
}
