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

/**Every type of hitstun a melee attack can have.*/
typedef enum
{
    NO_HIT = 1,
    NO_STUN,
    HIT_PRIMARY,
    HIT_SECONDARY,
    SMASH_RIGHT,
    SMASH_LEFT,
    SMASH_NEUTRAL,
    SMASH_DOWN,
    KIAI_CANNON_STUN,
    LIFT_STRIKE_STUN,
    GROUND_SLASH_STUN,
    HEAVY_STUN,
    KNOCKDOWN,
    KNOCKDOWN_KNOCKBACK,
    COMBO_END
} Hitstun;

/**Every type of Visual Effect a melee attack can have.*/
typedef enum
{
    NO_VFX,
    STRIKE_REGULAR_VFX,
    STRIKE_BIG_VFX,
    HEAVY_VFX,
    UNKNOWN_VFX_04,
    UNKNOWN_VFX_05,
    UNKNOWN_VFX_06,
    UNKNOWN_VFX_07,
    CLASH_VFX,
    UNKNOWN_VFX_09,
    UNKNOWN_VFX_0A,
    KIAI_VFX,
    UNKNOWN_VFX_0C,
    LIFT_STRIKE_VFX,
    UNKNOWN_VFX_0E,
    GROUND_SLASH_VFX,
    UNKNOWN_VFX_10
} VFX;

/**Every type of sound a melee attack can make.*/
typedef enum
{
    NO_SFX,
    STRIKE_SFX,
    HEAVY_SFX,
    THROW_SFX,
    LIFT_STRIKE_SFX,
    GIANT_THROW_SFX,
    OOZARU_LANDING_SFX,
    UNKNOWN_SFX_07,
    UNKNOWN_SFX_08,
    GROUND_SLASH_SFX,
    UNKNOWN_SFX_0A,
    UNKNOWN_SFX_0B,
    UNKNOWN_SFX_0C
} SFX;

typedef enum
{
    GUARD,
    GUARD_BREAK,
    COMBO_BREAKER,
    GUARD_IGNORED,
    THROW_TECH,
    NO_GUARD
} GuardEffect;

typedef enum
{
    PLACEHOLDER_2
} CounterEffect;

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
    PARAM_TYPE_INVALID = -1,
    GENERAL,
    MELEE,
    KI_BLAST,
    MOVEMENT,
    NEXT
} ParameterType; // Currently Known Parameters, this enum should be expanded in the future

/**Maximum gravity one can input before jumping becomes impossible.*/
#define MAX_GRAVITY 1
/**The total amount of characters in Tenkaichi 2. (excluding Wii chars)*/
#define ROSTER_SIZE 130
/**The value of the first byte of each Pak file. Used for validity checks.*/
#define PAK_FIRST_BYTE 0xFA
/**The size of the data chunk for each melee attack*/
#define MELEE_ATTACK_SIZE 0x64
/**The size of the data chunk for each ki blast*/
#define KI_BLAST_ATTACK_SIZE 0x38

#endif
