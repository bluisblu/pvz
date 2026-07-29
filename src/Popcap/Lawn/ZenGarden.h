#ifndef __ZENGARDEN_H__
#define __ZENGARDEN_H__

#include "CursorObject.h"
#include "GridItem.h"
#include "Plant.h"

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
