#ifndef NEO_INFO_H
#define NEO_INFO_H

typedef enum
{
    NO_FUSION,
    FUSION_DANCE,
    POTARA
} Fusion_Type;

typedef enum
{
    HEAVY,
    KIAI,
    FLYING_KICKS,
    NO_TECHNIQUE
} Technique;

typedef enum
{
    NO_COUNTER,
    SMASH,
    FEINT,
    THROW
} Counter_Move;

typedef enum
{
    GENERAL_OFFSET = 18,
    MELEE_OFFSET,
    KI_BLAST_OFFSET,
    MOVEMENT_OFFSET,
    NEXT_OFFSET
}ParameterOffset;   // The offsets for the pointers to parameter data in a .pak

typedef enum
{
    GENERAL,
    MELEE,
    KI_BLAST,
    MOVEMENT,
    NEXT
}Parameter; // Currently Known Parameters, this enum should be expanded in the future

#define MAX_GRAVITY 1
#define ROSTER_SIZE 130
#define PAK_FIRST_BYTE 0xFA

#endif
