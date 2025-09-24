#pragma once

#ifndef __PLANT_H__
#define __PLANT_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GameObject.h"
#include "Zombie.h"

#define MAX_MAGNET_ITEMS 5

class GameObject;
class Zombie;

enum MagnetItemType : int
{
    MAGNET_ITEM_NONE = 0x0000,
    MAGNET_ITEM_PAIL_1 = 0x0001,
    MAGNET_ITEM_PAIL_2 = 0x0002,
    MAGNET_ITEM_PAIL_3 = 0x0003,
    MAGNET_ITEM_FOOTBALL_HELMET_1 = 0x0004,
    MAGNET_ITEM_FOOTBALL_HELMET_2 = 0x0005,
    MAGNET_ITEM_FOOTBALL_HELMET_3 = 0x0006,
    MAGNET_ITEM_DOOR_1 = 0x0007,
    MAGNET_ITEM_DOOR_2 = 0x0008,
    MAGNET_ITEM_DOOR_3 = 0x0009,
    MAGNET_ITEM_POGO_1 = 0x000a,
    MAGNET_ITEM_POGO_2 = 0x000b,
    MAGNET_ITEM_POGO_3 = 0x000c,
    MAGNET_ITEM_JACK_IN_THE_BOX = 0x000d,
    MAGNET_ITEM_LADDER_1 = 0x000e,
    MAGNET_ITEM_LADDER_2 = 0x000f,
    MAGNET_ITEM_LADDER_3 = 0x0010,
    MAGNET_ITEM_LADDER_PLACED = 0x0011,
    MAGNET_ITEM_SILVER_COIN = 0x0012,
    MAGNET_ITEM_GOLD_COIN = 0x0013,
    MAGNET_ITEM_DIAMOND = 0x0014,
    MAGNET_ITEM_PICK_AXE = 0x0015,
};

enum PlantState : int
{
    STATE_NOTREADY = 0x0000,
    STATE_READY = 0x0001,
    STATE_DOINGSPECIAL = 0x0002,
    STATE_SQUASH_LOOK = 0x0003,
    STATE_SQUASH_PRE_LAUNCH = 0x0004,
    STATE_SQUASH_RISING = 0x0005,
    STATE_SQUASH_FALLING = 0x0006,
    STATE_SQUASH_DONE_FALLING = 0x0007,
    STATE_GRAVEBUSTER_LANDING = 0x0008,
    STATE_GRAVEBUSTER_EATING = 0x0009,
    STATE_CHOMPER_BITING = 0x000a,
    STATE_CHOMPER_BITING_GOT_ONE = 0x000b,
    STATE_CHOMPER_BITING_MISSED = 0x000c,
    STATE_CHOMPER_DIGESTING = 0x000d,
    STATE_CHOMPER_SWALLOWING = 0x000e,
    STATE_POTATO_RISING = 0x000f,
    STATE_POTATO_ARMED = 0x0010,
    STATE_POTATO_MASHED = 0x0011,
    STATE_SPIKEWEED_ATTACKING = 0x0012,
    STATE_SPIKEWEED_ATTACKING_2 = 0x0013,
    STATE_SCAREDYSHROOM_LOWERING = 0x0014,
    STATE_SCAREDYSHROOM_SCARED = 0x0015,
    STATE_SCAREDYSHROOM_RAISING = 0x0016,
    STATE_SUNSHROOM_SMALL = 0x0017,
    STATE_SUNSHROOM_GROWING = 0x0018,
    STATE_SUNSHROOM_BIG = 0x0019,
    STATE_MAGNETSHROOM_SUCKING = 0x001a,
    STATE_MAGNETSHROOM_CHARGING = 0x001b,
    STATE_BOWLING_UP = 0x001c,
    STATE_BOWLING_DOWN = 0x001d,
    STATE_CACTUS_LOW = 0x001e,
    STATE_CACTUS_RISING = 0x001f,
    STATE_CACTUS_HIGH = 0x0020,
    STATE_CACTUS_LOWERING = 0x0021,
    STATE_TANGLEKELP_GRABBING = 0x0022,
    STATE_COBCANNON_ARMING = 0x0023,
    STATE_COBCANNON_LOADING = 0x0024,
    STATE_COBCANNON_READY = 0x0025,
    STATE_COBCANNON_FIRING = 0x0026,
    STATE_KERNELPULT_BUTTER = 0x0027,
    STATE_UMBRELLA_TRIGGERED = 0x0028,
    STATE_UMBRELLA_REFLECTING = 0x0029,
    STATE_IMITATER_MORPHING = 0x002a,
    STATE_ZEN_GARDEN_WATERED = 0x002b,
    STATE_ZEN_GARDEN_NEEDY = 0x002c,
    STATE_ZEN_GARDEN_HAPPY = 0x002d,
    STATE_MARIGOLD_ENDING = 0x002e,
    STATE_FLOWERPOT_INVULNERABLE = 0x002f,
    STATE_LILYPAD_INVULNERABLE = 0x0030,
};

enum DrawVariation : int
{
    VARIATION_NORMAL = 0x0000,
    VARIATION_IMITATER = 0x0001,
    VARIATION_MARIGOLD_WHITE = 0x0002,
    VARIATION_MARIGOLD_MAGENTA = 0x0003,
    VARIATION_MARIGOLD_ORANGE = 0x0004,
    VARIATION_MARIGOLD_PINK = 0x0005,
    VARIATION_MARIGOLD_LIGHT_BLUE = 0x0006,
    VARIATION_MARIGOLD_RED = 0x0007,
    VARIATION_MARIGOLD_BLUE = 0x0008,
    VARIATION_MARIGOLD_VIOLET = 0x0009,
    VARIATION_MARIGOLD_LAVENDER = 0x000a,
    VARIATION_MARIGOLD_YELLOW = 0x000b,
    VARIATION_MARIGOLD_LIGHT_GREEN = 0x000c,
    VARIATION_ZEN_GARDEN = 0x000d,
    VARIATION_ZEN_GARDEN_WATER = 0x000e,
    VARIATION_SPROUT_NO_FLOWER = 0x000f,
    VARIATION_IMITATER_LESS = 0x0010,
    VARIATION_AQUARIUM = 0x0011,
};

enum PlantWeapon : int
{
    WEAPON_PRIMARY = 0x0000,
    WEAPON_SECONDARY = 0x0001,
};

class MagnetItem
{ /* Size=0x14 */
  /* 0x0000 */ public:
    float mPosX;
  /* 0x0004 */ public:
    float mPosY;
  /* 0x0008 */ public:
    float mDestOffsetX;
  /* 0x000c */ public:
    float mDestOffsetY;
  /* 0x0010 */ public:
    MagnetItemType mItemType;
};

enum PlantSubClass : int
{
    SUBCLASS_NORMAL = 0x0000,
    SUBCLASS_SHOOTER = 0x0001,
};

#ifndef E_SEEDTYPE
#define E_SEEDTYPE
enum SeedType : int
{
    SEED_PEASHOOTER = 0x0000,
    SEED_SUNFLOWER = 0x0001,
    SEED_CHERRYBOMB = 0x0002,
    SEED_WALLNUT = 0x0003,
    SEED_POTATOMINE = 0x0004,
    SEED_SNOWPEA = 0x0005,
    SEED_CHOMPER = 0x0006,
    SEED_REPEATER = 0x0007,
    SEED_PUFFSHROOM = 0x0008,
    SEED_SUNSHROOM = 0x0009,
    SEED_FUMESHROOM = 0x000a,
    SEED_GRAVEBUSTER = 0x000b,
    SEED_HYPNOSHROOM = 0x000c,
    SEED_SCAREDYSHROOM = 0x000d,
    SEED_ICESHROOM = 0x000e,
    SEED_DOOMSHROOM = 0x000f,
    SEED_LILYPAD = 0x0010,
    SEED_SQUASH = 0x0011,
    SEED_THREEPEATER = 0x0012,
    SEED_TANGLEKELP = 0x0013,
    SEED_JALAPENO = 0x0014,
    SEED_SPIKEWEED = 0x0015,
    SEED_TORCHWOOD = 0x0016,
    SEED_TALLNUT = 0x0017,
    SEED_SEASHROOM = 0x0018,
    SEED_PLANTERN = 0x0019,
    SEED_CACTUS = 0x001a,
    SEED_BLOVER = 0x001b,
    SEED_SPLITPEA = 0x001c,
    SEED_STARFRUIT = 0x001d,
    SEED_PUMPKINSHELL = 0x001e,
    SEED_MAGNETSHROOM = 0x001f,
    SEED_CABBAGEPULT = 0x0020,
    SEED_FLOWERPOT = 0x0021,
    SEED_KERNELPULT = 0x0022,
    SEED_INSTANT_COFFEE = 0x0023,
    SEED_GARLIC = 0x0024,
    SEED_UMBRELLA = 0x0025,
    SEED_MARIGOLD = 0x0026,
    SEED_MELONPULT = 0x0027,
    SEED_GATLINGPEA = 0x0028,
    SEED_TWINSUNFLOWER = 0x0029,
    SEED_GLOOMSHROOM = 0x002a,
    SEED_CATTAIL = 0x002b,
    SEED_WINTERMELON = 0x002c,
    SEED_GOLD_MAGNET = 0x002d,
    SEED_SPIKEROCK = 0x002e,
    SEED_COBCANNON = 0x002f,
    SEED_IMITATER = 0x0030,
    SEED_EXPLODE_O_NUT = 0x0031,
    SEED_GIANT_WALLNUT = 0x0032,
    SEED_SPROUT = 0x0033,
    SEED_LEFTPEATER = 0x0034,
    NUM_SEED_TYPES = 0x0035,
    SEED_BEGHOULED_BUTTON_SHUFFLE = 0x0036,
    SEED_BEGHOULED_BUTTON_CRATER = 0x0037,
    SEED_SLOT_MACHINE_SUN = 0x0038,
    SEED_SLOT_MACHINE_DIAMOND = 0x0039,
    SEED_ZOMBIQUARIUM_SNORKLE = 0x003a,
    SEED_ZOMBIQUARIUM_TROPHY = 0x003b,
    SEED_ZOMBIE_NORMAL = 0x003c,
    SEED_ZOMBIE_TRAFFIC_CONE = 0x003d,
    SEED_ZOMBIE_POLEVAULTER = 0x003e,
    SEED_ZOMBIE_PAIL = 0x003f,
    SEED_ZOMBIE_LADDER = 0x0040,
    SEED_ZOMBIE_DIGGER = 0x0041,
    SEED_ZOMBIE_BUNGEE = 0x0042,
    SEED_ZOMBIE_FOOTBALL = 0x0043,
    SEED_ZOMBIE_BALLOON = 0x0044,
    SEED_ZOMBIE_SCREEN_DOOR = 0x0045,
    SEED_ZOMBONI = 0x0046,
    SEED_ZOMBIE_POGO = 0x0047,
    SEED_ZOMBIE_DANCER = 0x0048,
    SEED_ZOMBIE_GARGANTUAR = 0x0049,
    SEED_ZOMBIE_IMP = 0x004a,
    NUM_SEEDS_IN_CHOOSER = 0x0031,
    SEED_NONE = -1,
};
#endif

#ifndef E_REANIMATION_TYPE
#define E_REANIMATION_TYPE
enum ReanimationType : int
{
    REANIM_NONE = -1,
    REANIM_LOADBAR_SPROUT = 0x0000,
    REANIM_LOADBAR_ZOMBIEHEAD = 0x0001,
    REANIM_SODROLL = 0x0002,
    REANIM_FINAL_WAVE = 0x0003,
    REANIM_PEASHOOTER = 0x0004,
    REANIM_WALLNUT = 0x0005,
    REANIM_LILYPAD = 0x0006,
    REANIM_SUNFLOWER = 0x0007,
    REANIM_LAWNMOWER = 0x0008,
    REANIM_READYSETPLANT = 0x0009,
    REANIM_CHERRYBOMB = 0x000a,
    REANIM_SQUASH = 0x000b,
    REANIM_DOOMSHROOM = 0x000c,
    REANIM_SNOWPEA = 0x000d,
    REANIM_REPEATER = 0x000e,
    REANIM_SUNSHROOM = 0x000f,
    REANIM_TALLNUT = 0x0010,
    REANIM_FUMESHROOM = 0x0011,
    REANIM_PUFFSHROOM = 0x0012,
    REANIM_HYPNOSHROOM = 0x0013,
    REANIM_CHOMPER = 0x0014,
    REANIM_ZOMBIE = 0x0015,
    REANIM_SUN = 0x0016,
    REANIM_POTATOMINE = 0x0017,
    REANIM_SPIKEWEED = 0x0018,
    REANIM_SPIKEROCK = 0x0019,
    REANIM_THREEPEATER = 0x001a,
    REANIM_MARIGOLD = 0x001b,
    REANIM_ICESHROOM = 0x001c,
    REANIM_ZOMBIE_FOOTBALL = 0x001d,
    REANIM_ZOMBIE_NEWSPAPER = 0x001e,
    REANIM_ZOMBIE_ZAMBONI = 0x001f,
    REANIM_SPLASH = 0x0020,
    REANIM_JALAPENO = 0x0021,
    REANIM_JALAPENO_FIRE = 0x0022,
    REANIM_COIN_SILVER = 0x0023,
    REANIM_ZOMBIE_CHARRED = 0x0024,
    REANIM_ZOMBIE_CHARRED_IMP = 0x0025,
    REANIM_ZOMBIE_CHARRED_DIGGER = 0x0026,
    REANIM_ZOMBIE_CHARRED_ZAMBONI = 0x0027,
    REANIM_ZOMBIE_CHARRED_CATAPULT = 0x0028,
    REANIM_ZOMBIE_CHARRED_GARGANTUAR = 0x0029,
    REANIM_SCRAREYSHROOM = 0x002a,
    REANIM_PUMPKIN = 0x002b,
    REANIM_PLANTERN = 0x002c,
    REANIM_TORCHWOOD = 0x002d,
    REANIM_SPLITPEA = 0x002e,
    REANIM_SEASHROOM = 0x002f,
    REANIM_BLOVER = 0x0030,
    REANIM_FLOWER_POT = 0x0031,
    REANIM_CACTUS = 0x0032,
    REANIM_DANCER = 0x0033,
    REANIM_TANGLEKELP = 0x0034,
    REANIM_STARFRUIT = 0x0035,
    REANIM_POLEVAULTER = 0x0036,
    REANIM_BALLOON = 0x0037,
    REANIM_GARGANTUAR = 0x0038,
    REANIM_IMP = 0x0039,
    REANIM_DIGGER = 0x003a,
    REANIM_DIGGER_DIRT = 0x003b,
    REANIM_ZOMBIE_DOLPHINRIDER = 0x003c,
    REANIM_POGO = 0x003d,
    REANIM_BACKUP_DANCER = 0x003e,
    REANIM_BOBSLED = 0x003f,
    REANIM_JACKINTHEBOX = 0x0040,
    REANIM_SNORKEL = 0x0041,
    REANIM_BUNGEE = 0x0042,
    REANIM_CATAPULT = 0x0043,
    REANIM_LADDER = 0x0044,
    REANIM_PUFF = 0x0045,
    REANIM_SLEEPING = 0x0046,
    REANIM_GRAVE_BUSTER = 0x0047,
    REANIM_ZOMBIES_WON = 0x0048,
    REANIM_MAGNETSHROOM = 0x0049,
    REANIM_BOSS = 0x004a,
    REANIM_CABBAGEPULT = 0x004b,
    REANIM_KERNELPULT = 0x004c,
    REANIM_MELONPULT = 0x004d,
    REANIM_COFFEEBEAN = 0x004e,
    REANIM_UMBRELLALEAF = 0x004f,
    REANIM_GATLINGPEA = 0x0050,
    REANIM_CATTAIL = 0x0051,
    REANIM_GLOOMSHROOM = 0x0052,
    REANIM_BOSS_ICEBALL = 0x0053,
    REANIM_BOSS_FIREBALL = 0x0054,
    REANIM_COBCANNON = 0x0055,
    REANIM_GARLIC = 0x0056,
    REANIM_GOLD_MAGNET = 0x0057,
    REANIM_WINTER_MELON = 0x0058,
    REANIM_TWIN_SUNFLOWER = 0x0059,
    REANIM_POOL_CLEANER = 0x005a,
    REANIM_ROOF_CLEANER = 0x005b,
    REANIM_FIRE_PEA = 0x005c,
    REANIM_IMITATER = 0x005d,
    REANIM_YETI = 0x005e,
    REANIM_BOSS_DRIVER = 0x005f,
    REANIM_LAWN_MOWERED_ZOMBIE = 0x0060,
    REANIM_CRAZY_DAVE = 0x0061,
    REANIM_TEXT_FADE_ON = 0x0062,
    REANIM_HAMMER = 0x0063,
    REANIM_SLOT_MACHINE_HANDLE = 0x0064,
    REANIM_CREDITS_FOOTBALL = 0x0065,
    REANIM_CREDITS_JACKBOX = 0x0066,
    REANIM_SELECTOR_SCREEN = 0x0067,
    REANIM_PORTAL_CIRCLE = 0x0068,
    REANIM_PORTAL_SQUARE = 0x0069,
    REANIM_ZENGARDEN_SPROUT = 0x006a,
    REANIM_ZENGARDEN_WATERINGCAN = 0x006b,
    REANIM_ZENGARDEN_FERTILIZER = 0x006c,
    REANIM_ZENGARDEN_BUGSPRAY = 0x006d,
    REANIM_ZENGARDEN_PHONOGRAPH = 0x006e,
    REANIM_DIAMOND = 0x006f,
    REANIM_ZOMBIE_HAND = 0x0070,
    REANIM_STINKY = 0x0071,
    REANIM_RAKE = 0x0072,
    REANIM_RAIN_CIRCLE = 0x0073,
    REANIM_RAIN_SPLASH = 0x0074,
    REANIM_ZOMBIE_SURPRISE = 0x0075,
    REANIM_COIN_GOLD = 0x0076,
    REANIM_TREE_OF_WISDOM = 0x0077,
    REANIM_TREE_OF_WISDOM_CLOUDS = 0x0078,
    REANIM_TREE_FOOD = 0x0079,
    REANIM_CREDITS_MAIN = 0x007a,
    REANIM_CREDITS_MAIN2 = 0x007b,
    REANIM_CREDITS_MAIN3 = 0x007c,
    REANIM_ZOMBIE_CREDITS_DANCE = 0x007d,
    REANIM_CREDITS_STAGE = 0x007e,
    REANIM_CREDITS_BIGBRAIN = 0x007f,
    REANIM_CREDITS_FLOWER_PETALS = 0x0080,
    REANIM_CREDITS_INFANTRY = 0x0081,
    REANIM_CREDITS_THROAT = 0x0082,
    REANIM_CREDITS_CRAZYDAVE = 0x0083,
    REANIM_CREDITS_BOSSDANCE = 0x0084,
    REANIM_ZOMBIE_CREDITS_SCREEN_DOOR = 0x0085,
    REANIM_ZOMBIE_CREDITS_CONEHEAD = 0x0086,
    REANIM_CREDITS_ZOMBIEARMY1 = 0x0087,
    REANIM_CREDITS_ZOMBIEARMY2 = 0x0088,
    REANIM_CREDITS_TOMBSTONES = 0x0089,
    REANIM_CREDITS_SOLARPOWER = 0x008a,
    REANIM_CREDITS_ANYHOUR = 0x008b,
    REANIM_CREDITS_WEARETHEUNDEAD = 0x008c,
    REANIM_CREDITS_DISCOLIGHTS = 0x008d,
    NUM_REANIMS = 0x008e,
};
#endif

#ifndef E_PARTICLE_SYSTEM_ID
#define E_PARTICLE_SYSTEM_ID
enum ParticleSystemID : int
{
    PARTICLESYSTEMID_NULL = 0x0000,
};
#endif

#ifndef E_REANIMATION_ID
#define E_REANIMATION_ID
enum ReanimationID : int
{
    REANIMATIONID_NULL = 0x0000,
};
#endif

#ifndef E_ZOMBIE_ID
#define E_ZOMBIE_ID
enum ZombieID : int
{
    ZOMBIEID_NULL = 0x0000,
};
#endif

#ifndef E_PARTICLE_EFFECT
#define E_PARTICLE_EFFECT
enum ParticleEffect : int
{
    PARTICLE_NONE = -1,
    PARTICLE_MELONSPLASH = 0x0000,
    PARTICLE_WINTERMELON = 0x0001,
    PARTICLE_FUMECLOUD = 0x0002,
    PARTICLE_POPCORNSPLASH = 0x0003,
    PARTICLE_POWIE = 0x0004,
    PARTICLE_JACKEXPLODE = 0x0005,
    PARTICLE_ZOMBIE_HEAD = 0x0006,
    PARTICLE_ZOMBIE_ARM = 0x0007,
    PARTICLE_ZOMBIE_TRAFFIC_CONE = 0x0008,
    PARTICLE_ZOMBIE_PAIL = 0x0009,
    PARTICLE_ZOMBIE_HELMET = 0x000a,
    PARTICLE_ZOMBIE_FLAG = 0x000b,
    PARTICLE_ZOMBIE_DOOR = 0x000c,
    PARTICLE_ZOMBIE_NEWSPAPER = 0x000d,
    PARTICLE_ZOMBIE_HEADLIGHT = 0x000e,
    PARTICLE_POW = 0x000f,
    PARTICLE_ZOMBIE_POGO = 0x0010,
    PARTICLE_ZOMBIE_NEWSPAPER_HEAD = 0x0011,
    PARTICLE_ZOMBIE_BALLOON_HEAD = 0x0012,
    PARTICLE_SOD_ROLL = 0x0013,
    PARTICLE_GRAVE_STONE_RISE = 0x0014,
    PARTICLE_PLANTING = 0x0015,
    PARTICLE_PLANTING_POOL = 0x0016,
    PARTICLE_ZOMBIE_RISE = 0x0017,
    PARTICLE_GRAVE_BUSTER = 0x0018,
    PARTICLE_GRAVE_BUSTER_DIE = 0x0019,
    PARTICLE_POOL_SPLASH = 0x001a,
    PARTICLE_ICE_SPARKLE = 0x001b,
    PARTICLE_SEED_PACKET = 0x001c,
    PARTICLE_TALL_NUT_BLOCK = 0x001d,
    PARTICLE_DOOM = 0x001e,
    PARTICLE_DIGGER_RISE = 0x001f,
    PARTICLE_DIGGER_TUNNEL = 0x0020,
    PARTICLE_DANCER_RISE = 0x0021,
    PARTICLE_POOL_SPARKLY = 0x0022,
    PARTICLE_WALLNUT_EAT_SMALL = 0x0023,
    PARTICLE_WALLNUT_EAT_LARGE = 0x0024,
    PARTICLE_PEA_SPLAT = 0x0025,
    PARTICLE_SPIKE_SPLAT = 0x0026,
    PARTICLE_BUTTER_SPLAT = 0x0027,
    PARTICLE_CABBAGE_SPLAT = 0x0028,
    PARTICLE_PUFF_SPLAT = 0x0029,
    PARTICLE_STAR_SPLAT = 0x002a,
    PARTICLE_ICE_TRAP = 0x002b,
    PARTICLE_SNOWPEA_SPLAT = 0x002c,
    PARTICLE_SNOWPEA_PUFF = 0x002d,
    PARTICLE_SNOWPEA_TRAIL = 0x002e,
    PARTICLE_LANTERN_SHINE = 0x002f,
    PARTICLE_SEED_PACKET_PICKUP = 0x0030,
    PARTICLE_POTATO_MINE = 0x0031,
    PARTICLE_POTATO_MINE_RISE = 0x0032,
    PARTICLE_PUFFSHROOM_TRAIL = 0x0033,
    PARTICLE_PUFFSHROOM_MUZZLE = 0x0034,
    PARTICLE_SEED_PACKET_FLASH = 0x0035,
    PARTICLE_WHACK_A_ZOMBIE_RISE = 0x0036,
    PARTICLE_ZOMBIE_LADDER = 0x0037,
    PARTICLE_UMBRELLA_REFLECT = 0x0038,
    PARTICLE_SEED_PACKET_PICK = 0x0039,
    PARTICLE_ICE_TRAP_ZOMBIE = 0x003a,
    PARTICLE_ICE_TRAP_RELEASE = 0x003b,
    PARTICLE_ZAMBONI_SMOKE = 0x003c,
    PARTICLE_GLOOMCLOUD = 0x003d,
    PARTICLE_ZOMBIE_POGO_HEAD = 0x003e,
    PARTICLE_ZAMBONI_TIRE = 0x003f,
    PARTICLE_ZAMBONI_EXPLOSION = 0x0040,
    PARTICLE_ZAMBONI_EXPLOSION2 = 0x0041,
    PARTICLE_CATAPULT_EXPLOSION = 0x0042,
    PARTICLE_MOWER_CLOUD = 0x0043,
    PARTICLE_BOSS_ICE_BALL = 0x0044,
    PARTICLE_BLASTMARK = 0x0045,
    PARTICLE_COIN_PICKUP_ARROW = 0x0046,
    PARTICLE_PRESENT_PICKUP = 0x0047,
    PARTICLE_IMITATER_MORPH = 0x0048,
    PARTICLE_MOWERED_ZOMBIE_HEAD = 0x0049,
    PARTICLE_MOWERED_ZOMBIE_ARM = 0x004a,
    PARTICLE_ZOMBIE_HEAD_POOL = 0x004b,
    PARTICLE_ZOMBIE_BOSS_FIREBALL = 0x004c,
    PARTICLE_FIREBALL_DEATH = 0x004d,
    PARTICLE_ICEBALL_DEATH = 0x004e,
    PARTICLE_ICEBALL_TRAIL = 0x004f,
    PARTICLE_FIREBALL_TRAIL = 0x0050,
    PARTICLE_BOSS_EXPLOSION = 0x0051,
    PARTICLE_SCREEN_FLASH = 0x0052,
    PARTICLE_TROPHY_SPARKLE = 0x0053,
    PARTICLE_PORTAL_CIRCLE = 0x0054,
    PARTICLE_PORTAL_SQUARE = 0x0055,
    PARTICLE_POTTED_PLANT_GLOW = 0x0056,
    PARTICLE_POTTED_WATER_PLANT_GLOW = 0x0057,
    PARTICLE_POTTED_ZEN_GLOW = 0x0058,
    PARTICLE_MIND_CONTROL = 0x0059,
    PARTICLE_VASE_SHATTER = 0x005a,
    PARTICLE_VASE_SHATTER_LEAF = 0x005b,
    PARTICLE_VASE_SHATTER_ZOMBIE = 0x005c,
    PARTICLE_AWARD_PICKUP_ARROW = 0x005d,
    PARTICLE_ZOMBIE_SEAWEED = 0x005e,
    PARTICLE_ZOMBIE_MUSTACHE = 0x005f,
    PARTICLE_ZOMBIE_FUTURE_GLASSES = 0x0060,
    PARTICLE_PINATA = 0x0061,
    PARTICLE_DUST_SQUASH = 0x0062,
    PARTICLE_DUST_FOOT = 0x0063,
    PARTICLE_DAISY = 0x0064,
    PARTICLE_CREDIT_STROBE = 0x0065,
    PARTICLE_CREDITS_RAYSWIPE = 0x0066,
    PARTICLE_CREDITS_ZOMBIEHEADWIPE = 0x0067,
    PARTICLE_STARBURST = 0x0068,
    PARTICLE_CREDITS_FOG = 0x0069,
    NUM_PARTICLES = 0x006a,
};
#endif

#ifndef E_PLANT_ORDER
#define E_PLANT_ORDER
enum PLANT_ORDER : int
{
    PLANT_ORDER_LILYPAD = 0x0000,
    PLANT_ORDER_NORMAL = 0x0001,
    PLANT_ORDER_PUMPKIN = 0x0002,
    PLANT_ORDER_FLYER = 0x0003,
    PLANT_ORDER_CHERRYBOMB = 0x0004,
};
#endif

class PlantDefinition
{ /* Size=0x24 */
  /* 0x0000 */ public:
    SeedType mSeedType;
  /* 0x0004 */ public:
    Sexy::Image **mPlantImage;
  /* 0x0008 */ public:
    ReanimationType mReanimationType;
  /* 0x000c */ public:
    int mPacketIndex;
  /* 0x0010 */ public:
    int mSeedCost;
  /* 0x0014 */ public:
    int mRefreshTime;
  /* 0x0018 */ public:
    PlantSubClass mSubClass;
  /* 0x001c */ public:
    int mLaunchRate;
  /* 0x0020 */ public:
    const char *mPlantName;
};

class Plant : public GameObject
{   /* Size=0x148 */
    /* 0x0000: fields for GameObject */
  /* 0x0024 */ public:
    SeedType mSeedType;
  /* 0x0028 */ public:
    int mPlantCol;
  /* 0x002c */ public:
    int mAnimCounter;
  /* 0x0030 */ public:
    bool mAnimPing;
    char pad_0x31[3];
  /* 0x0034 */ public:
    int mFrame;
  /* 0x0038 */ public:
    int mFrameLength;
  /* 0x003c */ public:
    int mNumFrames;
  /* 0x0040 */ public:
    PlantState mState;
  /* 0x0044 */ public:
    bool mDead;
  /* 0x0045 */ public:
    bool mSquished;
    char pad_0x46[2];
  /* 0x0048 */ public:
    int mPlantHealth;
  /* 0x004c */ public:
    int mPlantMaxHealth;
  /* 0x0050 */ public:
    int mSubclass;
  /* 0x0054 */ public:
    int mDisappearCountdown;
  /* 0x0058 */ public:
    int mDoSpecialCountdown;
  /* 0x005c */ public:
    int mStateCountdown;
  /* 0x0060 */ public:
    int mLaunchCounter;
  /* 0x0064 */ public:
    int mLaunchRate;
  /* 0x0068 */ public:
    // Sexy::TRect<int> mPlantRect;
    int mPlantRect[0x4];
  /* 0x0078 */ public:
    // Sexy::TRect<int> mPlantAttackRect;
    int mPlantAttackRect[0x4];
  /* 0x0088 */ public:
    int mTargetX;
  /* 0x008c */ public:
    int mTargetY;
  /* 0x0090 */ public:
    int mStartRow;
  /* 0x0094 */ public:
    ParticleSystemID mParticleID;
  /* 0x0098 */ public:
    int mShootingCounter;
  /* 0x009c */ public:
    ReanimationID mBodyReanimID;
  /* 0x00a0 */ public:
    ReanimationID mHeadReanimID;
  /* 0x00a4 */ public:
    ReanimationID mHeadReanimID2;
  /* 0x00a8 */ public:
    ReanimationID mHeadReanimID3;
  /* 0x00ac */ public:
    ReanimationID mBlinkReanimID;
  /* 0x00b0 */ public:
    ReanimationID mLightReanimID;
  /* 0x00b4 */ public:
    ReanimationID mSleepingReanimID;
  /* 0x00b8 */ public:
    int mBlinkCountdown;
  /* 0x00bc */ public:
    int mRecentlyEatenCountdown;
  /* 0x00c0 */ public:
    int mEatenFlashCountdown;
  /* 0x00c4 */ public:
    int mBeghouledFlashCountdown;
  /* 0x00c8 */ public:
    float mShakeOffsetX;
  /* 0x00cc */ public:
    float mShakeOffsetY;
  /* 0x00d0 */ public:
    MagnetItem mMagnetItems[5];
  /* 0x0134 */ public:
    ZombieID mTargetZombieID;
  /* 0x0138 */ public:
    int mWakeUpCounter;
  /* 0x013c */ public:
    bool mIsAsleep;
  /* 0x013d */ public:
    bool mIsOnBoard;
  /* 0x013e */ public:
    bool mIsOnBungee;
  /* 0x013f */ public:
    bool mHighlighted;
  /* 0x0140 */ public:
    SeedType mImitaterType;
  /* 0x0144 */ public:
    int mPottedPlantIndex;

  public:
    void PlantInitialize(int, int, SeedType, SeedType);

  public:
    void Update();

  public:
    void Animate();

  public:
    void Draw(Sexy::Graphics *);

  public:
    void MouseDown(int, int, int);

  public:
    void DoSpecial();

  public:
    void Fire(Zombie *, int, PlantWeapon);

  public:
    Zombie *FindTargetZombie(int, PlantWeapon);

  public:
    void Die();

  public:
    void UpdateProductionPlant();

  public:
    void UpdateShooter();

  public:
    bool FindTargetAndFire(int, PlantWeapon);

  public:
    void LaunchThreepeater();

  public:
    void UpdateAbilities();

  public:
    void Squish();

  public:
    void DoRowAreaDamage(int, unsigned int);

  public:
    int GetDamageRangeFlags(PlantWeapon);

  public:
    /* Sexy::TRect<int> */ int GetPlantRect();

  public:
    /* Sexy::TRect<int> */ int GetPlantAttackRect(PlantWeapon);

  public:
    Zombie *FindSquashTarget();

  public:
    void UpdateSquash();

  public:
    bool NotOnGround();

  public:
    void DoSquashDamage();

  public:
    void BurnRow(int);

  public:
    void IceZombies();

  public:
    void BlowAwayFliers(int, int);

  public:
    void UpdateGraveBuster();

  public:
    /* TodParticleSystem * */ int AddAttachedParticle(int, int, int, ParticleEffect);

  public:
    void GetPeaHeadOffset(int &, int &);

  public:
    bool MakesSun();

  public:
    void KillAllPlantsNearDoom();

  public:
    bool IsOnHighGround();

  public:
    void UpdateTorchwood();

  public:
    void LaunchStarFruit();

  public:
    bool FindStarFruitTarget();

  public:
    void UpdateChomper();

  public:
    void DoBlink();

  public:
    void UpdateBlink();

  public:
    void PlayBodyReanim(const char *, ReanimLoopType, int, float);

  public:
    void UpdateMagnetShroom();

  public:
    MagnetItem *GetFreeMagnetItem();

  public:
    void DrawMagnetItems(Sexy::Graphics *);

  public:
    void UpdateDoomShroom();

  public:
    void UpdateIceShroom();

  public:
    void UpdatePotato();

  public:
    int CalcRenderOrder();

  public:
    void AnimateNuts();

  public:
    void SetSleeping(bool);

  public:
    void UpdateShooting();

  public:
    void DrawShadow(Sexy::Graphics *, float, float);

  public:
    void UpdateScaredyShroom();

  public:
    int DistanceToClosestZombie();

  public:
    void UpdateSpikeweed();

  public:
    void MagnetShroomAttactItem(Zombie *);

  public:
    void UpdateSunShroom();

  public:
    void UpdateBowling();

  public:
    void AnimatePumpkin();

  public:
    void UpdateBlover();

  public:
    void UpdateCactus();

  public:
    void StarFruitFire();

  public:
    void UpdateTanglekelp();

  public:
    /* Reanimation * */ int AttachBlinkAnim(/* Reanimation * */ int);

  public:
    void UpdateReanimColor();

  public:
    bool IsUpgradableTo(SeedType);

  public:
    bool IsPartOfUpgradableTo(SeedType);

  public:
    void UpdateCobCannon();

  public:
    void CobCannonFire(int, int);

  public:
    void UpdateGoldMagnetShroom();

  public:
    bool IsOnBoard();

  public:
    void RemoveEffects();

  public:
    void UpdateCoffeeBean();

  public:
    void UpdateUmbrella();

  public:
    void EndBlink();

  public:
    void AnimateGarlic();

  public:
    /* Coin * */ int FindGoldMagnetTarget();

  public:
    void SpikeweedAttack();

  public:
    void ImitaterMorph();

  public:
    void UpdateImitater();

  public:
    void UpdateReanim();

  public:
    void SpikeRockTakeDamage();

  public:
    bool IsSpiky();

  public:
    bool IsInPlay();

  public:
    void UpdateNeedsFood();

  public:
    void PlayIdleAnim(float);

  public:
    void UpdateFlowerPot();

  public:
    void UpdateLilypad();

  public:
    void GoldMagnetFindTargets();

  public:
    bool IsAGoldMagnetAboutToSuck();

  public:
    bool DrawMagnetItemsOnTop();

  public:
    Plant(const Plant &);

  public:
    Plant();

  public:
    static Sexy::Image *GetImage(SeedType);

  public:
    static int GetCost(SeedType, SeedType);

  public:
    static std::string GetNameString(SeedType, SeedType);

  public:
    static std::string GetToolTip(SeedType);

  public:
    static int GetRefreshTime(SeedType, SeedType);

  public:
    static bool IsNocturnal(SeedType);

  public:
    static bool IsAquatic(SeedType);

  public:
    static bool IsFlying(SeedType);

  public:
    static bool IsUpgrade(SeedType);

  public:
    static void DrawSeedType(Sexy::Graphics *, SeedType, SeedType, DrawVariation, float, float);

  public:
    static void PreloadPlantResources(SeedType);
};

enum GardenType : int
{
    GARDEN_MAIN = 0x0000,
    GARDEN_MUSHROOM = 0x0001,
    GARDEN_WHEELBARROW = 0x0002,
    GARDEN_AQUARIUM = 0x0003,
};

enum PottedPlantAge : int
{
    PLANTAGE_SPROUT = 0x0000,
    PLANTAGE_SMALL = 0x0001,
    PLANTAGE_MEDIUM = 0x0002,
    PLANTAGE_FULL = 0x0003,
};

enum PottedPlantNeed : int
{
    PLANTNEED_NONE = 0x0000,
    PLANTNEED_WATER = 0x0001,
    PLANTNEED_FERTILIZER = 0x0002,
    PLANTNEED_BUGSPRAY = 0x0003,
    PLANTNEED_PHONOGRAPH = 0x0004,
};

class PottedPlant
{ /* Size=0x58 */
  /* 0x0000 */ public:
    SeedType mSeedType;
  /* 0x0004 */ public:
    GardenType mWhichZenGarden;
  /* 0x0008 */ public:
    int mX;
  /* 0x000c */ public:
    int mY;
  /* 0x0010 */ public:
    int mFacing;
    // char pad_0x14[4];
  /* 0x0018 */ public:
    long long mLastWateredTime;
  /* 0x0020 */ public:
    DrawVariation mDrawVariation;
  /* 0x0024 */ public:
    PottedPlantAge mPlantAge;
  /* 0x0028 */ public:
    int mTimesFed;
  /* 0x002c */ public:
    int mFeedingsPerGrow;
  /* 0x0030 */ public:
    PottedPlantNeed mPlantNeed;
    // char pad_0x34[4];
  /* 0x0038 */ public:
    long long mLastNeedFulfilledTime;
  /* 0x0040 */ public:
    long long mLastFertilizedTime;
  /* 0x0048 */ public:
    long long mLastChocolateTime;
  /* 0x0050 */ public:
    int mFutureAttribute[1];
    char pad_0x54[4];

  public:
    void InitializePottedPlant(SeedType);
};

PlantDefinition const &GetPlantDefinition(SeedType seedType) // placeholder
{
    static PlantDefinition invalidPlant;
    return invalidPlant;
}

#endif // __PLANT_H__