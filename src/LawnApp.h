#pragma once

#include "SexyAppFramework/SexyApp.h"
#ifndef __LAWNAPP_H__
#define __LAWNAPP_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"

#include "Board.h"
#include "PlayerInfo.h"
#include "Reanimator.h"
#include "SeedChooserScreen.h"
#include "ZenGarden.h"

class Board;

namespace Sexy
{
Sexy::Image *IMAGE_BUG_SPRAY;
Sexy::Image *IMAGE_SHOVEL;
Sexy::Image *IMAGE_WATERINGCAN;
Sexy::Image *IMAGE_ZEN_GOLDTOOLRETICLE;
Sexy::Image *IMAGE_WATERINGCANGOLD;
Sexy::Image *IMAGE_FERTILIZER;
Sexy::Image *IMAGE_PHONOGRAPH;
Sexy::Image *IMAGE_CHOCOLATE;
Sexy::Image *IMAGE_ZEN_GARDENGLOVE;
Sexy::Image *IMAGE_TREEFOOD;
Sexy::Image *IMAGE_ZEN_WHEELBARROW;
Sexy::Image *IMAGE_COBCANNON_TARGET;
Sexy::Image *IMAGE_ZEN_MONEYSIGN;
} // namespace Sexy

#ifndef E_ZOMBIE_TYPE
#define E_ZOMBIE_TYPE
enum ZombieType : int
{
    ZOMBIE_INVALID = -1,
    ZOMBIE_NORMAL = 0x0000,
    ZOMBIE_FLAG = 0x0001,
    ZOMBIE_TRAFFIC_CONE = 0x0002,
    ZOMBIE_POLEVAULTER = 0x0003,
    ZOMBIE_PAIL = 0x0004,
    ZOMBIE_NEWSPAPER = 0x0005,
    ZOMBIE_DOOR = 0x0006,
    ZOMBIE_FOOTBALL = 0x0007,
    ZOMBIE_DANCER = 0x0008,
    ZOMBIE_BACKUP_DANCER = 0x0009,
    ZOMBIE_DUCKY_TUBE = 0x000a,
    ZOMBIE_SNORKEL = 0x000b,
    ZOMBIE_ZAMBONI = 0x000c,
    ZOMBIE_BOBSLED = 0x000d,
    ZOMBIE_DOLPHIN_RIDER = 0x000e,
    ZOMBIE_JACK_IN_THE_BOX = 0x000f,
    ZOMBIE_BALLOON = 0x0010,
    ZOMBIE_DIGGER = 0x0011,
    ZOMBIE_POGO = 0x0012,
    ZOMBIE_YETI = 0x0013,
    ZOMBIE_BUNGEE = 0x0014,
    ZOMBIE_LADDER = 0x0015,
    ZOMBIE_CATAPULT = 0x0016,
    ZOMBIE_GARGANTUAR = 0x0017,
    ZOMBIE_IMP = 0x0018,
    ZOMBIE_BOSS = 0x0019,
    ZOMBIE_PEA_HEAD = 0x001a,
    ZOMBIE_WALLNUT_HEAD = 0x001b,
    ZOMBIE_JALAPENO_HEAD = 0x001c,
    ZOMBIE_GATLING_HEAD = 0x001d,
    ZOMBIE_SQUASH_HEAD = 0x001e,
    ZOMBIE_TALLNUT_HEAD = 0x001f,
    ZOMBIE_REDEYE_GARGANTUAR = 0x0020,
    NUM_ZOMBIE_TYPES = 0x0021,
};
#endif

enum AwardType : int
{
    AWARD_FOR_LEVEL = 0x0000,
    AWARD_CREDITS_ZOMBIE_NOTE = 0x0001,
};

enum FoleyType : int
{
    FOLEY_SUN = 0x0000,
    FOLEY_SPLAT = 0x0001,
    FOLEY_LAWNMOWER = 0x0002,
    FOLEY_THROW = 0x0003,
    FOLEY_SPAWN_SUN = 0x0004,
    FOLEY_CHOMP = 0x0005,
    FOLEY_CHOMP_SOFT = 0x0006,
    FOLEY_PLANT = 0x0007,
    FOLEY_USE_SHOVEL = 0x0008,
    FOLEY_DROP = 0x0009,
    FOLEY_BLEEP = 0x000a,
    FOLEY_GROAN = 0x000b,
    FOLEY_BRAINS = 0x000c,
    FOLEY_SUKHBIR = 0x000d,
    FOLEY_JACKINTHEBOX = 0x000e,
    FOLEY_ART_CHALLENGE = 0x000f,
    FOLEY_ZAMBONI = 0x0010,
    FOLEY_THUNDER = 0x0011,
    FOLEY_FROZEN = 0x0012,
    FOLEY_ZOMBIESPLASH = 0x0013,
    FOLEY_BOWLINGIMPACT = 0x0014,
    FOLEY_SQUISH = 0x0015,
    FOLEY_TIRE_POP = 0x0016,
    FOLEY_EXPLOSION = 0x0017,
    FOLEY_SLURP = 0x0018,
    FOLEY_LIMBS_POP = 0x0019,
    FOLEY_POGO_ZOMBIE = 0x001a,
    FOLEY_SNOW_PEA_SPARKLES = 0x001b,
    FOLEY_ZOMBIE_FALLING = 0x001c,
    FOLEY_PUFF = 0x001d,
    FOLEY_FUME = 0x001e,
    FOLEY_COIN = 0x001f,
    FOLEY_KERNEL_SPLAT = 0x0020,
    FOLEY_DIGGER = 0x0021,
    FOLEY_JACK_SURPRISE = 0x0022,
    FOLEY_VASE_BREAKING = 0x0023,
    FOLEY_POOL_CLEANER = 0x0024,
    FOLEY_BASKETBALL = 0x0025,
    FOLEY_IGNITE = 0x0026,
    FOLEY_FIREPEA = 0x0027,
    FOLEY_THUMP = 0x0028,
    FOLEY_SQUASH_HMM = 0x0029,
    FOLEY_MAGNETSHROOM = 0x002a,
    FOLEY_BUTTER = 0x002b,
    FOLEY_BUNGEE_SCREAM = 0x002c,
    FOLEY_BOSS_EXPLOSION_SMALL = 0x002d,
    FOLEY_SHIELD_HIT = 0x002e,
    FOLEY_SWING = 0x002f,
    FOLEY_BONK = 0x0030,
    FOLEY_RAIN = 0x0031,
    FOLEY_DOLPHIN_BEFORE_JUMPING = 0x0032,
    FOLEY_DOLPHIN_APPEARS = 0x0033,
    FOLEY_PLANT_WATER = 0x0034,
    FOLEY_ZOMBIE_ENTERING_WATER = 0x0035,
    FOLEY_GRAVEBUSTERCHOMP = 0x0036,
    FOLEY_CHERRYBOMB = 0x0037,
    FOLEY_JALAPENO_IGNITE = 0x0038,
    FOLEY_REVERSE_EXPLOSION = 0x0039,
    FOLEY_PLASTIC_HIT = 0x003a,
    FOLEY_WINMUSIC = 0x003b,
    FOLEY_BALLOONINFLATE = 0x003c,
    FOLEY_BIGCHOMP = 0x003d,
    FOLEY_MELONIMPACT = 0x003e,
    FOLEY_PLANTGROW = 0x003f,
    FOLEY_SHOOP = 0x0040,
    FOLEY_JUICY = 0x0041,
    FOLEY_NEWSPAPER_RARRGH = 0x0042,
    FOLEY_NEWSPAPER_RIP = 0x0043,
    FOLEY_FLOOP = 0x0044,
    FOLEY_COFFEE = 0x0045,
    FOLEY_LOWGROAN = 0x0046,
    FOLEY_PRIZE = 0x0047,
    FOLEY_YUCK = 0x0048,
    FOLEY_UMBRELLA = 0x0049,
    FOLEY_GRASSSTEP = 0x004a,
    FOLEY_SHOVEL = 0x004b,
    FOLEY_COBLAUNCH = 0x004c,
    FOLEY_WATERING = 0x004d,
    FOLEY_POLEVAULT = 0x004e,
    FOLEY_GRAVESTONE_RUMBLE = 0x004f,
    FOLEY_DIRT_RISE = 0x0050,
    FOLEY_FERTILIZER = 0x0051,
    FOLEY_PORTAL = 0x0052,
    FOLEY_WAKEUP = 0x0053,
    FOLEY_BUGSPRAY = 0x0054,
    FOLEY_SCREAM = 0x0055,
    FOLEY_PAPER = 0x0056,
    FOLEY_MONEYFALLS = 0x0057,
    FOLEY_IMP = 0x0058,
    FOLEY_HYDRAULIC_SHORT = 0x0059,
    FOLEY_HYDRAULIC = 0x005a,
    FOLEY_GARGANTUDEATH = 0x005b,
    FOLEY_CERAMIC = 0x005c,
    FOLEY_BOSSBOULDERATTACK = 0x005d,
    FOLEY_CHIME = 0x005e,
    FOLEY_CRAZYDAVESHORT = 0x005f,
    FOLEY_CRAZYDAVELONG = 0x0060,
    FOLEY_CRAZYDAVEEXTRALONG = 0x0061,
    FOLEY_CRAZYDAVECRAZY = 0x0062,
    FOLEY_PHONOGRAPH = 0x0063,
    FOLEY_DANCER = 0x0064,
    FOLEY_FINALFANFARE = 0x0065,
    FOLEY_CRAZYDAVESCREAM = 0x0066,
    FOLEY_CRAZYDAVESCREAM2 = 0x0067,
    NUM_FOLEY = 0x0068,
};

#ifndef E_BOARD_RESULT
#define E_BOARD_RESULT
enum BoardResult : int
{
    BOARDRESULT_NONE = 0x0000,
    BOARDRESULT_WON = 0x0001,
    BOARDRESULT_LOST = 0x0002,
    BOARDRESULT_RESTART = 0x0003,
    BOARDRESULT_QUIT = 0x0004,
    BOARDRESULT_QUIT_APP = 0x0005,
    BOARDRESULT_CHEAT = 0x0006,
};
#endif

#ifndef E_REANIMATION_ID
#define E_REANIMATION_ID
enum ReanimationID : int
{
    REANIMATIONID_NULL = 0x0000,
};
#endif

#ifndef E_PARTICLE_SYSTEM_ID
#define E_PARTICLE_SYSTEM_ID
enum ParticleSystemID : int
{
    PARTICLESYSTEMID_NULL = 0x0000,
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

#ifndef E_CRAZY_DAVE_STATE
#define E_CRAZY_DAVE_STATE
enum CrazyDaveState : int
{
    CRAZY_DAVE_OFF = 0x0000,
    CRAZY_DAVE_ENTERING = 0x0001,
    CRAZY_DAVE_LEAVING = 0x0002,
    CRAZY_DAVE_IDLING = 0x0003,
    CRAZY_DAVE_TALKING = 0x0004,
    CRAZY_DAVE_HANDING_TALKING = 0x0005,
    CRAZY_DAVE_HANDING_IDLING = 0x0006,
};
#endif

enum GameScenes : int
{
    SCENE_LOADING = 0x0000,
    SCENE_MENU = 0x0001,
    SCENE_LEVEL_INTRO = 0x0002,
    SCENE_PLAYING = 0x0003,
    SCENE_ZOMBIES_WON = 0x0004,
    SCENE_AWARD = 0x0005,
    SCENE_CREDIT = 0x0006,
    SCENE_CHALLENGE = 0x0007,
};

enum ChallengePage : int
{
    CHALLENGE_PAGE_SURVIVAL = 0x0000,
    CHALLENGE_PAGE_CHALLENGE = 0x0001,
    CHALLENGE_PAGE_LIMBO = 0x0002,
    CHALLENGE_PAGE_PUZZLE = 0x0003,
    MAX_CHALLANGE_PAGES = 0x0004,
};

#ifndef E_GAME_MODE
#define E_GAME_MODE
enum GameMode : int
{
    GAMEMODE_ADVENTURE = 0x0000,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_1 = 0x0001,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_2 = 0x0002,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_3 = 0x0003,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_4 = 0x0004,
    GAMEMODE_SURVIVAL_NORMAL_STAGE_5 = 0x0005,
    GAMEMODE_SURVIVAL_HARD_STAGE_1 = 0x0006,
    GAMEMODE_SURVIVAL_HARD_STAGE_2 = 0x0007,
    GAMEMODE_SURVIVAL_HARD_STAGE_3 = 0x0008,
    GAMEMODE_SURVIVAL_HARD_STAGE_4 = 0x0009,
    GAMEMODE_SURVIVAL_HARD_STAGE_5 = 0x000a,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_1 = 0x000b,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_2 = 0x000c,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_3 = 0x000d,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_4 = 0x000e,
    GAMEMODE_SURVIVAL_ENDLESS_STAGE_5 = 0x000f,
    GAMEMODE_CHALLENGE_WAR_AND_PEAS = 0x0010,
    GAMEMODE_CHALLENGE_WALLNUT_BOWLING = 0x0011,
    GAMEMODE_CHALLENGE_SLOT_MACHINE = 0x0012,
    GAMEMODE_CHALLENGE_RAINING_SEEDS = 0x0013,
    GAMEMODE_CHALLENGE_BEGHOULED = 0x0014,
    GAMEMODE_CHALLENGE_INVISIGHOUL = 0x0015,
    GAMEMODE_CHALLENGE_SEEING_STARS = 0x0016,
    GAMEMODE_CHALLENGE_ZOMBIQUARIUM = 0x0017,
    GAMEMODE_CHALLENGE_BEGHOULED_TWIST = 0x0018,
    GAMEMODE_CHALLENGE_LITTLE_TROUBLE = 0x0019,
    GAMEMODE_CHALLENGE_PORTAL_COMBAT = 0x001a,
    GAMEMODE_CHALLENGE_COLUMN = 0x001b,
    GAMEMODE_CHALLENGE_BOBSLED_BONANZA = 0x001c,
    GAMEMODE_CHALLENGE_SPEED = 0x001d,
    GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE = 0x001e,
    GAMEMODE_CHALLENGE_LAST_STAND = 0x001f,
    GAMEMODE_CHALLENGE_WAR_AND_PEAS_2 = 0x0020,
    GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2 = 0x0021,
    GAMEMODE_CHALLENGE_POGO_PARTY = 0x0022,
    GAMEMODE_CHALLENGE_FINAL_BOSS = 0x0023,
    GAMEMODE_CHALLENGE_ART_CHALLENGE_1 = 0x0024,
    GAMEMODE_CHALLENGE_SUNNY_DAY = 0x0025,
    GAMEMODE_CHALLENGE_RESODDED = 0x0026,
    GAMEMODE_CHALLENGE_BIG_TIME = 0x0027,
    GAMEMODE_CHALLENGE_ART_CHALLENGE_2 = 0x0028,
    GAMEMODE_CHALLENGE_AIR_RAID = 0x0029,
    GAMEMODE_CHALLENGE_ICE = 0x002a,
    GAMEMODE_CHALLENGE_ZEN_GARDEN = 0x002b,
    GAMEMODE_CHALLENGE_HIGH_GRAVITY = 0x002c,
    GAMEMODE_CHALLENGE_GRAVE_DANGER = 0x002d,
    GAMEMODE_CHALLENGE_SHOVEL = 0x002e,
    GAMEMODE_CHALLENGE_STORMY_NIGHT = 0x002f,
    GAMEMODE_CHALLENGE_BUNGEE_BLITZ = 0x0030,
    GAMEMODE_CHALLENGE_SQUIRREL = 0x0031,
    GAMEMODE_TREE_OF_WISDOM = 0x0032,
    GAMEMODE_SCARY_POTTER_1 = 0x0033,
    GAMEMODE_SCARY_POTTER_2 = 0x0034,
    GAMEMODE_SCARY_POTTER_3 = 0x0035,
    GAMEMODE_SCARY_POTTER_4 = 0x0036,
    GAMEMODE_SCARY_POTTER_5 = 0x0037,
    GAMEMODE_SCARY_POTTER_6 = 0x0038,
    GAMEMODE_SCARY_POTTER_7 = 0x0039,
    GAMEMODE_SCARY_POTTER_8 = 0x003a,
    GAMEMODE_SCARY_POTTER_9 = 0x003b,
    GAMEMODE_SCARY_POTTER_ENDLESS = 0x003c,
    GAMEMODE_PUZZLE_I_ZOMBIE_1 = 0x003d,
    GAMEMODE_PUZZLE_I_ZOMBIE_2 = 0x003e,
    GAMEMODE_PUZZLE_I_ZOMBIE_3 = 0x003f,
    GAMEMODE_PUZZLE_I_ZOMBIE_4 = 0x0040,
    GAMEMODE_PUZZLE_I_ZOMBIE_5 = 0x0041,
    GAMEMODE_PUZZLE_I_ZOMBIE_6 = 0x0042,
    GAMEMODE_PUZZLE_I_ZOMBIE_7 = 0x0043,
    GAMEMODE_PUZZLE_I_ZOMBIE_8 = 0x0044,
    GAMEMODE_PUZZLE_I_ZOMBIE_9 = 0x0045,
    GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS = 0x0046,
    NUM_GAME_MODES = 0x0047,
};
#endif

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

class LawnApp : public Sexy::SexyApp
{   /* Size=0x8c0 */
    /* 0x0000: fields for Sexy::SexyApp */
  public:
    // char unk_0[8];
  /* 0x0768 */ public:
    Board *mBoard;
  /* 0x076c */ public:
    /* TitleScreen * */ int mTitleScreen;
  /* 0x0770 */ public:
    GameSelector *mGameSelector;
  /* 0x0774 */ public:
    SeedChooserScreen *mSeedChooserScreen;
  /* 0x0778 */ public:
    /* AwardScreen * */ int mAwardScreen;
  /* 0x077c */ public:
    /* CreditScreen * */ int mCreditScreen;
  /* 0x0780 */ public:
    /* ChallengeScreen * */ int mChallengeScreen;
  /* 0x0784 */ public:
    /* TodFoley * */ int mSoundSystem;
  /* 0x0788 */ public:
    // std::list<Sexy::ButtonWidget *, std::allocator<Sexy::ButtonWidget *>> mControlButtonList;
    char unk_788[0xc];
  /* 0x0794 */ public:
    // std::list<Sexy::Image *, std::allocator<Sexy::Image *>> mCreatedImageList;
    char unk_794[0xc];
  /* 0x07a0 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mReferId;
  /* 0x07bc */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mRegisterLink;
  /* 0x07d8 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mMod;
  /* 0x07f4 */ public:
    bool mRegisterResourcesLoaded;
  /* 0x07f5 */ public:
    bool mTodCheatKeys;
  /* 0x07f8 */ public:
    GameMode mGameMode;
  /* 0x07fc */ public:
    GameScenes mGameScene;
  /* 0x0800 */ public:
    bool mLoadingZombiesThreadCompleted;
  /* 0x0801 */ public:
    bool mFirstTimeGameSelector;
  /* 0x0804 */ public:
    int mGamesPlayed;
  /* 0x0808 */ public:
    int mMaxExecutions;
  /* 0x080c */ public:
    int mMaxPlays;
  /* 0x0810 */ public:
    int mMaxTime;
  /* 0x0814 */ public:
    bool mEasyPlantingCheat;
  /* 0x0818 */ public:
    /* PoolEffect * */ int mPoolEffect;
  /* 0x081c */ public:
    ZenGarden *mZenGarden;
  /* 0x0820 */ public:
    /* EffectSystem * */ int mEffectSystem;
  /* 0x0824 */ public:
    /* ReanimatorCache * */ int mReanimatorCache;
  /* 0x0828 */ public:
    /* ProfileMgr * */ int mProfileMgr;
  /* 0x082c */ public:
    PlayerInfo *mPlayerInfo;
  /* 0x0830 */ public:
    /* LevelStats * */ int mLastLevelStats;
  /* 0x0834 */ public:
    bool mCloseRequest;
  /* 0x0838 */ public:
    int mAppCounter;
  /* 0x083c */ public:
    /* Music * */ int mMusic;
  /* 0x0840 */ public:
    ReanimationID mCrazyDaveReanimID;
  /* 0x0844 */ public:
    CrazyDaveState mCrazyDaveState;
  /* 0x0848 */ public:
    int mCrazyDaveBlinkCounter;
  /* 0x084c */ public:
    ReanimationID mCrazyDaveBlinkReanimID;
  /* 0x0850 */ public:
    int mCrazyDaveMessageIndex;
  /* 0x0854 */ public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> mCrazyDaveMessageText;
  /* 0x0870 */ public:
    int mAppRandSeed;
  /* 0x0874 */ public:
    /* HICON__ * */ int mBigArrowCursor;
  /* 0x0878 */ public:
    /* PopDRMComm * */ int mDRM;
  /* 0x087c */ public:
    int mSessionID;
  /* 0x0880 */ public:
    int mPlayTimeActiveSession;
  /* 0x0884 */ public:
    int mPlayTimeInactiveSession;
  /* 0x0888 */ public:
    BoardResult mBoardResult;
  /* 0x088c */ public:
    bool mKilledYetiAndRestarted;
  /* 0x0890 */ public:
    /* TypingCheck * */ int mKonamiCheck;
  /* 0x0894 */ public:
    /* TypingCheck * */ int mMustacheCheck;
  /* 0x0898 */ public:
    /* TypingCheck * */ int mMoustacheCheck;
  /* 0x089c */ public:
    /* TypingCheck * */ int mSuperMowerCheck;
  /* 0x08a0 */ public:
    /* TypingCheck * */ int mSuperMowerCheck2;
  /* 0x08a4 */ public:
    /* TypingCheck * */ int mFutureCheck;
  /* 0x08a8 */ public:
    /* TypingCheck * */ int mPinataCheck;
  /* 0x08ac */ public:
    /* TypingCheck * */ int mDaisyCheck;
  /* 0x08b0 */ public:
    /* TypingCheck * */ int mSukhbirCheck;
  /* 0x08b4 */ public:
    bool mMustacheMode;
  /* 0x08b5 */ public:
    bool mSuperMowerMode;
  /* 0x08b6 */ public:
    bool mFutureMode;
  /* 0x08b7 */ public:
    bool mPinataMode;
  /* 0x08b8 */ public:
    bool mDaisyMode;
  /* 0x08b9 */ public:
    bool mSukhbirMode;

  public:
    LawnApp(const LawnApp &);

  public:
    LawnApp();

  public:
    virtual ~LawnApp();

  public:
    bool KillNewOptionsDialog();

  public:
    virtual void GotFocus();

  public:
    virtual void LostFocus();

  public:
    virtual void InitHook();

  public:
    virtual void WriteToRegistry();

  public:
    virtual void ReadFromRegistry();

  public:
    virtual void LoadingThreadProc();

  public:
    virtual void LoadingCompleted();

  public:
    virtual void LoadingThreadCompleted();

  public:
    virtual void URLOpenFailed(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    virtual void URLOpenSucceeded(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    virtual bool OpenURL(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, bool);

  public:
    virtual bool DebugKeyDown(int);

  public:
    virtual void HandleCmdLineParam(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                    const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void ConfirmQuit();

  public:
    void ConfirmCheckForUpdates();

  public:
    void CheckForUpdates();

  public:
    void DoUserDialog();

  public:
    void FinishUserDialog(bool);

  public:
    void DoCreateUserDialog();

  public:
    void DoCheatDialog();

  public:
    void FinishCheatDialog(bool);

  public:
    void FinishCreateUserDialog(bool);

  public:
    void DoConfirmDeleteUserDialog(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void FinishConfirmDeleteUserDialog(bool);

  public:
    void DoRenameUserDialog(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void FinishRenameUserDialog(bool);

  public:
    void FinishNameError(int);

  public:
    void FinishRestartConfirmDialog();

  public:
    void DoConfirmSellDialog(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void DoConfirmPurchaseDialog(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void FinishTimesUpDialog();

  public:
    void KillBoard();

  public:
    void MakeNewBoard();

  public:
    void StartPlaying();

  public:
    bool TryLoadGame();

  public:
    void NewGame();

  public:
    void PreNewGame(GameMode, bool);

  public:
    void ShowGameSelector();

  public:
    void KillGameSelector();

  public:
    void ShowAwardScreen(AwardType);

  public:
    void KillAwardScreen();

  public:
    void ShowSeedChooserScreen();

  public:
    void KillSeedChooserScreen();

  public:
    void DoHighScoreDialog();

  public:
    void DoBackToMain();

  public:
    void DoConfirmBackToMain();

  public:
    void DoNewOptions(bool);

  public:
    void DoRegister();

  public:
    void DoRegisterError();

  public:
    bool CanDoRegisterDialog();

  public:
    bool WriteCurrentUserConfig();

  public:
    void DoNeedRegisterDialog();

  public:
    void DoContinueDialog();

  public:
    void DoPauseDialog();

  public:
    void FinishModelessDialogs();

  public:
    virtual Sexy::Dialog *DoDialog(int, bool,
                                   const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                   const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                   const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, int);

  public:
    Sexy::Dialog *DoDialogDelay(int, bool,
                                const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, int);

  public:
    virtual void Shutdown();

  public:
    virtual void Init();

  public:
    virtual void Start();

  public:
    virtual Sexy::Dialog *NewDialog(int, bool,
                                    const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                    const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &,
                                    const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &, int);

  public:
    virtual bool KillDialog(int);

  public:
    virtual void ModalOpen();

  public:
    virtual void ModalClose();

  public:
    virtual void PreDisplayHook();

  public:
    virtual bool ChangeDirHook(const char *);

  public:
    bool NeedRegister();

  public:
    void UpdateRegisterInfo();

  public:
    virtual void ButtonPress(int);

  public:
    virtual void ButtonDepress(int);

  public:
    virtual void UpdateFrames();

  public:
    virtual bool UpdateApp();

  public:
    bool IsAdventureMode();

  public:
    bool IsSurvivalMode();

  public:
    bool IsContinuousChallenge();

  public:
    bool IsArtChallenge();

  public:
    bool NeedPauseGame();

  public:
    virtual void ShowResourceError(bool);

  public:
    void ToggleSlowMo();

  public:
    void ToggleFastMo();

  public:
    void PlayFoley(FoleyType);

  public:
    void FastLoad(GameMode);

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetStageString(int);

  public:
    void KillChallengeScreen();

  public:
    void ShowChallengeScreen(ChallengePage);

  public:
    const /* ChallengeDefinition & */ int GetCurrentChallengeDef();

  public:
    void CheckForGameEnd();

  public:
    virtual void CloseRequestAsync();

  public:
    bool IsChallengeWithoutSeedBank();

  public:
    /* AlmanacDialog * */ int DoAlmanacDialog(SeedType, ZombieType);

  public:
    bool KillAlmanacDialog();

  public:
    int GetSeedsAvailable();

  public:
    Reanimation *AddReanimation(float, float, int, ReanimationType);

  public:
    /* TodParticleSystem * */ int AddTodParticle(float, float, int, ParticleEffect);

  public:
    /* ParticleSystemID */ int ParticleGetID(/* TodParticleSystem * */ int);

  public:
    /* TodParticleSystem * */ int ParticleGet(/* ParticleSystemID */ int);

  public:
    /* TodParticleSystem * */ int ParticleTryToGet(/* ParticleSystemID */ int);

  public:
    ReanimationID ReanimationGetID(Reanimation *);

  public:
    Reanimation *ReanimationGet(ReanimationID);

  public:
    Reanimation *ReanimationTryToGet(ReanimationID);

  public:
    void RemoveReanimation(ReanimationID);

  public:
    void RemoveParticle(ParticleSystemID);

  public:
    /* StoreScreen * */ int ShowStoreScreen();

  public:
    void KillStoreScreen();

  public:
    bool HasSeedType(SeedType);

  public:
    void EndLevel();

  public:
    bool IsIceDemo();

  public:
    bool IsShovelLevel();

  public:
    bool IsWallnutBowlingLevel();

  public:
    bool IsMiniBossLevel();

  public:
    bool IsSlotMachineLevel();

  public:
    bool IsLittleTroubleLevel();

  public:
    bool IsStormyNightLevel();

  public:
    bool IsFinalBossLevel();

  public:
    bool IsBungeeBlitzLevel();

  public:
    SeedType GetAwardSeedForLevel(int);

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetCrazyDaveText(int);

  public:
    bool CanShowAlmanac();

  public:
    bool IsNight();

  public:
    bool CanShowStore();

  public:
    bool HasBeatenChallenge(GameMode);

  public:
    PottedPlant *GetPottedPlantByIndex(int);

  public:
    bool IsSurvivalNormal(GameMode);

  public:
    bool IsSurvivalHard(GameMode);

  public:
    bool IsSurvivalEndless(GameMode);

  public:
    bool HasFinishedAdventure();

  public:
    bool IsFirstTimeAdventureMode();

  public:
    bool CanSpawnYetis();

  public:
    void CrazyDaveEnter();

  public:
    void UpdateCrazyDave();

  public:
    void CrazyDaveTalkIndex(int);

  public:
    void CrazyDaveTalkMessage(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &);

  public:
    void CrazyDaveLeave();

  public:
    void DrawCrazyDave(/* Sexy::Graphics * */ int);

  public:
    void CrazyDaveDie();

  public:
    void CrazyDaveStopTalking();

  public:
    void PreloadForUser();

  public:
    int GetNumPreloadingTasks();

  public:
    int LawnMessageBox(int, const char *, const char *, const char *, const char *, int);

  public:
    virtual void EnforceCursor();

  public:
    void ShowCreditScreen();

  public:
    void KillCreditScreen();

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> Pluralize(int, const char *, const char *);

  public:
    int GetNumTrophies(ChallengePage);

  public:
    bool EarnedGoldTrophy();

  public:
    bool IsRegistered();

  public:
    bool IsExpired();

  public:
    bool IsDRMConnected();

  public:
    bool IsScaryPotterLevel();

  public:
    bool IsEndlessScaryPotter(GameMode);

  public:
    bool IsSquirrelLevel();

  public:
    bool IsIZombieLevel();

  public:
    bool CanShowZenGarden();

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetMoneyString(int);

  public:
    bool AdvanceCrazyDaveText();

  public:
    bool IsWhackAZombieLevel();

  public:
    void BetaSubmit(bool);

  public:
    void BetaRecordLevelStats();

  public:
    void UpdatePlayTimeStats();

  public:
    void BetaAddFile(std::list<std::basic_string<char, std::char_traits<char>, std::allocator<char>>,
                               std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &,
                     std::basic_string<char, std::char_traits<char>, std::allocator<char>>,
                     std::basic_string<char, std::char_traits<char>, std::allocator<char>>);

  public:
    bool CanPauseNow();

  public:
    bool IsPuzzleMode();

  public:
    bool IsChallengeMode();

  public:
    bool IsEndlessIZombie(GameMode);

  public:
    void CrazyDaveDoneHanding();

  public:
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetCurrentLevelName();

  public:
    int TrophiesNeedForGoldSunflower();

  public:
    int GetCurrentChallengeIndex();

  public:
    void LoadGroup(const char *, const int);

  public:
    void TraceLoadGroup(const char *, int, int, int);

  public:
    void CrazyDaveStopSound();

  public:
    LawnApp &operator=(const LawnApp &);
};

LawnApp *gLawnApp;

#endif // __LAWNAPP_H__