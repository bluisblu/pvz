#pragma once

#ifndef __ZENGARDEN_H__
#define __ZENGARDEN_H__

#include "CursorObject.h"
#include "GridItem.h"

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
public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Board *mBoard;
    /* 0x0008 */ GardenType mGardenType;
public:
    ZenGarden();
    void ZenGardenInitLevel(bool);
    void DrawPottedPlantIcon(Sexy::Graphics *, float, float, PottedPlant *);
    void DrawPottedPlant(Sexy::Graphics *, float, float, PottedPlant *, float, bool);
    bool IsZenGardenFull(bool);
    void FindOpenZenGardenSpot(int &, int &);
    void AddPottedPlant(PottedPlant *);
    void MouseDownWithTool(int, int, CursorType);
    void MovePlant(Plant *, int, int);
    void MouseDownWithMoneySign(Plant *);
    Plant *PlacePottedPlant(int);
    float PlantPottedDrawHeightOffset(SeedType, float);
    int GetPlantSellPrice(Plant *);
    void ZenGardenUpdate();
    void MouseDownWithFullWheelBarrow(int, int);
    void MouseDownWithEmptyWheelBarrow(Plant *);
    void GotoNextGarden();
    PottedPlant *GetPottedPlantInWheelbarrow();
    void RemovePottedPlant(Plant *);
    /*SpecialGridPlacement * */ void *GetSpecialGridPlacements(int &);
    int PixelToGridX(int, int);
    int PixelToGridY(int, int);
    int GridToPixelX(int, int);
    int GridToPixelY(int, int);
    void DrawBackdrop(Sexy::Graphics *);
    bool MouseDownZenGarden(int, int, int, HitResult *);
    void PlantFulfillNeed(Plant *);
    void PlantWatered(Plant *);
    PottedPlantNeed GetPlantsNeed(PottedPlant *);
    void MouseDownWithFeedingTool(int, int, CursorType);
    void DrawPlantOverlay(Sexy::Graphics *, Plant *);
    PottedPlant *PottedPlantFromIndex(int);
    bool WasPlantNeedFulfilledToday(PottedPlant *);
    void PottedPlantUpdate(Plant *);
    void AddHappyEffect(Plant *);
    void RemoveHappyEffect(Plant *);
    void PlantUpdateProduction(Plant *);
    bool CanDropPottedPlantLoot();
    void ShowTutorialArrowOnWateringCan();
    bool PlantsNeedWater();
    void ZenGardenStart();
    void UpdatePlantEffectState(Plant *);
    void ZenToolUpdate(GridItem *);
    void DoFeedingTool(int, int, GridItemState);
    void AddStinky();
    void StinkyUpdate(GridItem *);
    void OpenStore();
    GridItem *GetStinky();
    void StinkyPickGoal(GridItem *);
    bool PlantShouldRefreshNeed(PottedPlant *);
    void PlantFertilized(Plant *);
    bool WasPlantFertilizedInLastHour(PottedPlant *);
    void SetupForZenTutorial();
    bool HasPurchasedStinky();
    int CountPlantsNeedingFertilizer();
    bool AllPlantsHaveBeenFertilized();
    void WakeStinky();
    bool ShouldStinkyBeAwake();
    bool IsStinkySleeping();
    SeedType PickRandomSeedType();
    void StinkyWakeUp(GridItem *);
    void StinkyStartFallingAsleep(GridItem *);
    void StinkyFinishFallingAsleep(GridItem *, int);
    void AdvanceCrazyDaveDialog();
    void LeaveGarden();
    bool CanDropChocolate();
    void FeedChocolateToPlant(Plant *);
    bool PlantHighOnChocolate(PottedPlant *);
    bool PlantCanHaveChocolate(Plant *);
    void SetPlantAnimSpeed(Plant *);
    void UpdateStinkyMotionTrail(GridItem *, bool);
    void ResetPlantTimers(PottedPlant *);
    void ResetStinkyTimers();
    void UpdatePlantNeeds();
    void RefreshPlantNeeds(PottedPlant *);
    void PlantSetLaunchCounter(Plant *);
    int PlantGetMinutesSinceHappy(Plant *);
    bool IsStinkyHighOnChocolate();
    void StinkyAnimRateUpdate(GridItem *);
    bool PlantCanBeWatered(Plant *);
};

#endif
