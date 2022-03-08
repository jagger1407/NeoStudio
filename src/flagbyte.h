#ifndef FLAGBYTE_H
#define FLAGBYTE_H

/**
 * Class to Read and Write specific bits in a byte
 * Note: bit order is 76543210
 */
class FlagByte
{
public:
    /**Returns wanted bit out of byte.*/
    static bool Bit(char byte, unsigned char bit)
    {
        return (byte >> bit) & 0x01;
    }
    /**Sets wanted bit out of byte.*/
    static void SetBit(char *byte, unsigned char bit, bool newValue)
    {
        if (newValue == true) *byte = *byte | (0x01 << bit);
        else *byte = *byte & ~(0x01 << bit);
    }
};

#endif // FLAGBYTE_H
