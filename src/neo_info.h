#ifndef NEO_INFO_H
#define NEO_INFO_H

/**Offset to get the pointer to the real offset in the file.*/
typedef enum
{
    PARAM_OFFSET_GENERAL = 18,
    PARAM_OFFSET_MELEE,
    PARAM_OFFSET_KI_BLAST,
    PARAM_OFFSET_MOVEMENT,
    PARAM_OFFSET_NEXT
}ParameterOffset;   // The offsets for the pointers to parameter data in a .pak

/**Every currently known Parameter Type.*/
typedef enum
{
    PARAM_TYPE_INVALID = -1,
    PARAM_TYPE_GENERAL,
    PARAM_TYPE_MELEE,
    PARAM_TYPE_KI_BLAST,
    PARAM_TYPE_MOVEMENT,
    PARAM_TYPE_NEXT
} ParameterType; // Currently Known Parameters, this enum should be expanded in the future

/**Maximum gravity one can input before jumping becomes impossible.*/
#define MAX_GRAVITY 1
/**The total amount of characters in Tenkaichi 2. (excluding Wii chars)*/
#define ROSTER_SIZE 136
/**The value of the first byte of each Pak file. Used for validity checks.*/
#define PAK_FIRST_BYTE 0xFA
/**The size of the data chunk for each melee attack*/
#define MELEE_ATTACK_SIZE 0x64
/**The size of the data chunk for each ki blast*/
#define KI_BLAST_ATTACK_SIZE 0x38

#endif
