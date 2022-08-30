#ifndef NEO_INFO_H
#define NEO_INFO_H

/**Every Fusion Type.*/
typedef enum
{
    NO_FUSION,
    FUSION_DANCE,
    POTARA
} Fusion_Type;

/**Every Rushing Technique.*/
typedef enum
{
    HEAVY,
    KIAI,
    FLYING_KICKS,
    NO_TECHNIQUE
} Technique;

/**Every move that can be triggered by a counter.*/
typedef enum
{
    NO_COUNTER,
    SMASH,
    FEINT,
    THROW,
    SWAY
} Counter_Move;

/**Offset to get the pointer to the real offset in the file.*/
typedef enum
{
    GENERAL_OFFSET = 18,
    MELEE_OFFSET,
    KI_BLAST_OFFSET,
    MOVEMENT_OFFSET,
    NEXT_OFFSET
}ParameterOffset;   // The offsets for the pointers to parameter data in a .pak

/**Every currently known Parameter Type.*/
typedef enum
{
    GENERAL,
    MELEE,
    KI_BLAST,
    MOVEMENT,
    NEXT
} ParameterType; // Currently Known Parameters, this enum should be expanded in the future

/**Maximum gravity one can input before jumping becomes impossible.*/
#define MAX_GRAVITY 1
/**The total amounf of characters in Tenkaichi 2.*/
#define ROSTER_SIZE 130
/**The value of the first byte of each Pak file. Used for validity checks.*/
#define PAK_FIRST_BYTE 0xFA

#endif
