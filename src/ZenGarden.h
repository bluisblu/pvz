#pragma once

#ifndef __ZENGARDEN_H__
#define __ZENGARDEN_H__

#include "CursorObject.h"

#ifndef E_GRID_ITEM_STATE
#define E_GRID_ITEM_STATE
enum GridItemState : int
{
    GRIDITEM_STATE_NORMAL = 0x0000,
    GRIDITEM_STATE_GRAVESTONE_SPECIAL = 0x0001,
    GRIDITEM_STATE_PORTAL_CLOSED = 0x0002,
    GRIDITEM_STATE_SCARY_POT_QUESTION = 0x0003,
    GRIDITEM_STATE_SCARY_POT_LEAF = 0x0004,
    GRIDITEM_STATE_SCARY_POT_ZOMBIE = 0x0005,
    GRIDITEM_STATE_SQUIRREL_WAITING = 0x0006,
    GRIDITEM_STATE_SQUIRREL_PEEKING = 0x0007,
    GRIDITEM_STATE_SQUIRREL_RUNNING_UP = 0x0008,
    GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN = 0x0009,
    GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT = 0x000a,
    GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT = 0x000b,
    GRIDITEM_STATE_SQUIRREL_CAUGHT = 0x000c,
    GRIDITEM_STATE_SQUIRREL_ZOMBIE = 0x000d,
    GRIDITEM_STATE_ZEN_TOOL_WATERING_CAN = 0x000e,
    GRIDITEM_STATE_ZEN_TOOL_FERTILIZER = 0x000f,
    GRIDITEM_STATE_ZEN_TOOL_BUG_SPRAY = 0x0010,
    GRIDITEM_STATE_ZEN_TOOL_PHONOGRAPH = 0x0011,
    GRIDITEM_STATE_ZEN_TOOL_GOLD_WATERING_CAN = 0x0012,
    GRIDITEM_STINKY_WALKING_LEFT = 0x0013,
    GRIDITEM_STINKY_TURNING_LEFT = 0x0014,
    GRIDITEM_STINKY_WALKING_RIGHT = 0x0015,
    GRIDITEM_STINKY_TURNING_RIGHT = 0x0016,
    GRIDITEM_STINKY_SLEEPING = 0x0017,
    GRIDITEM_STINKY_FALLING_ASLEEP = 0x0018,
    GRIDITEM_STINKY_WAKING_UP = 0x0019,
    GRIDITEM_STATE_RAKE_ATTRACTING = 0x001a,
    GRIDITEM_STATE_RAKE_WAITING = 0x001b,
    GRIDITEM_STATE_RAKE_TRIGGERED = 0x001c,
    GRIDITEM_STATE_BRAIN_SQUISHED = 0x001d,
};
#endif

class ZenGarden
{ /* Size=0xc */
  /* 0x0000 */ public:
    LawnApp *mApp;
  /* 0x0004 */ public:
    Board *mBoard;
  /* 0x0008 */ public:
    GardenType mGardenType;

  public:
    ZenGarden();

  public:
    void ZenGardenInitLevel(bool);

  public:
    void DrawPottedPlantIcon(Sexy::Graphics *, float, float, PottedPlant *);

  public:
    void DrawPottedPlant(Sexy::Graphics *, float, float, PottedPlant *, float, bool);

  public:
    bool IsZenGardenFull(bool);

  public:
    void FindOpenZenGardenSpot(int &, int &);

  public:
    void AddPottedPlant(PottedPlant *);

  public:
    void MouseDownWithTool(int, int, CursorType);

  public:
    void MovePlant(Plant *, int, int);

  public:
    void MouseDownWithMoneySign(Plant *);

  public:
    Plant *PlacePottedPlant(int);

  public:
    float PlantPottedDrawHeightOffset(SeedType, float);

  public:
    int GetPlantSellPrice(Plant *);

  public:
    void ZenGardenUpdate();

  public:
    void MouseDownWithFullWheelBarrow(int, int);

  public:
    void MouseDownWithEmptyWheelBarrow(Plant *);

  public:
    void GotoNextGarden();

  public:
    PottedPlant *GetPottedPlantInWheelbarrow();

  public:
    void RemovePottedPlant(Plant *);

  public:
    /*SpecialGridPlacement * */ int GetSpecialGridPlacements(int &);

  public:
    int PixelToGridX(int, int);

  public:
    int PixelToGridY(int, int);

  public:
    int GridToPixelX(int, int);

  public:
    int GridToPixelY(int, int);

  public:
    void DrawBackdrop(Sexy::Graphics *);

  public:
    bool MouseDownZenGarden(int, int, int, HitResult *);

  public:
    void PlantFulfillNeed(Plant *);

  public:
    void PlantWatered(Plant *);

  public:
    PottedPlantNeed GetPlantsNeed(PottedPlant *);

  public:
    void MouseDownWithFeedingTool(int, int, CursorType);

  public:
    void DrawPlantOverlay(Sexy::Graphics *, Plant *);

  public:
    PottedPlant *PottedPlantFromIndex(int);

  public:
    bool WasPlantNeedFulfilledToday(PottedPlant *);

  public:
    void PottedPlantUpdate(Plant *);

  public:
    void AddHappyEffect(Plant *);

  public:
    void RemoveHappyEffect(Plant *);

  public:
    void PlantUpdateProduction(Plant *);

  public:
    bool CanDropPottedPlantLoot();

  public:
    void ShowTutorialArrowOnWateringCan();

  public:
    bool PlantsNeedWater();

  public:
    void ZenGardenStart();

  public:
    void UpdatePlantEffectState(Plant *);

  public:
    void ZenToolUpdate(/* GridItem * */ int);

  public:
    void DoFeedingTool(int, int, GridItemState);

  public:
    void AddStinky();

  public:
    void StinkyUpdate(/* GridItem * */ int);

  public:
    void OpenStore();

  public:
    /* GridItem * */ int GetStinky();

  public:
    void StinkyPickGoal(/* GridItem * */ int);

  public:
    bool PlantShouldRefreshNeed(PottedPlant *);

  public:
    void PlantFertilized(Plant *);

  public:
    bool WasPlantFertilizedInLastHour(PottedPlant *);

  public:
    void SetupForZenTutorial();

  public:
    bool HasPurchasedStinky();

  public:
    int CountPlantsNeedingFertilizer();

  public:
    bool AllPlantsHaveBeenFertilized();

  public:
    void WakeStinky();

  public:
    bool ShouldStinkyBeAwake();

  public:
    bool IsStinkySleeping();

  public:
    SeedType PickRandomSeedType();

  public:
    void StinkyWakeUp(/* GridItem * */ int);

  public:
    void StinkyStartFallingAsleep(/* GridItem * */ int);

  public:
    void StinkyFinishFallingAsleep(/* GridItem * */ int, int);

  public:
    void AdvanceCrazyDaveDialog();

  public:
    void LeaveGarden();

  public:
    bool CanDropChocolate();

  public:
    void FeedChocolateToPlant(Plant *);

  public:
    bool PlantHighOnChocolate(PottedPlant *);

  public:
    bool PlantCanHaveChocolate(Plant *);

  public:
    void SetPlantAnimSpeed(Plant *);

  public:
    void UpdateStinkyMotionTrail(/* GridItem * */ int, bool);

  public:
    void ResetPlantTimers(PottedPlant *);

  public:
    void ResetStinkyTimers();

  public:
    void UpdatePlantNeeds();

  public:
    void RefreshPlantNeeds(PottedPlant *);

  public:
    void PlantSetLaunchCounter(Plant *);

  public:
    int PlantGetMinutesSinceHappy(Plant *);

  public:
    bool IsStinkyHighOnChocolate();

  public:
    void StinkyAnimRateUpdate(/* GridItem * */ int);

  public:
    bool PlantCanBeWatered(Plant *);
};

#endif