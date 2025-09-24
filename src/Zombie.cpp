#include "Zombie.h"

void Zombie::SetupDoorArms(Reanimation *aReanim, bool theShow)
{
    int aArmGroup = RENDER_GROUP_NORMAL;
    int aDoorGroup = RENDER_GROUP_HIDDEN;
    if (theShow)
    {
        // Assembly says aArmGroup = ebx (aDoorGroup) instead of -1
        // but I can't get it to match, but it seems like an
        // optimization anyway.
        aArmGroup = RENDER_GROUP_HIDDEN;
        aDoorGroup = RENDER_GROUP_NORMAL;
    }

    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_hand", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_lower", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_upper", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("anim_innerarm", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor_hand", aDoorGroup);
}

void Zombie::SetupReanimLayers(Reanimation *aReanim, ZombieType theZombieType)
{
    aReanim->AssignRenderGroupToPrefix("anim_cone", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_bucket", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_flag", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_duckytube", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_tongue", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_mustache", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_hand", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_lower", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_upper", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("anim_innerarm", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor_hand", RENDER_GROUP_HIDDEN);

    // Yes, if-else matches better than a switch statement here
    if (theZombieType == ZOMBIE_TRAFFIC_CONE)
    {
        aReanim->AssignRenderGroupToPrefix("anim_cone", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToPrefix("anim_hair", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_PAIL)
    {
        aReanim->AssignRenderGroupToPrefix("anim_bucket", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToPrefix("anim_hair", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_DOOR)
    {
        Zombie::SetupDoorArms(aReanim, 1);
    }
    else if (theZombieType == ZOMBIE_NEWSPAPER)
    {
        aReanim->AssignRenderGroupToPrefix("Zombie_paper_paper", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_FLAG)
    {
        aReanim->AssignRenderGroupToPrefix("anim_innerarm", RENDER_GROUP_HIDDEN);
        aReanim->AssignRenderGroupToTrack("Zombie_flaghand", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToTrack("Zombie_innerarm_screendoor", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToTrack("Zombie_flag", RENDER_GROUP_NORMAL);
    }
    else if (theZombieType == ZOMBIE_DUCKY_TUBE)
    {
        aReanim->AssignRenderGroupToPrefix("Zombie_duckytube", RENDER_GROUP_NORMAL);
    }
}

bool Zombie::IsBouncingPogo()
{
    if (mZombiePhase >= ZombiePhase::PHASE_POGO_BOUNCING && mZombiePhase <= ZombiePhase::PHASE_POGO_FORWARD_BOUNCE_7)
        return true;

    return false;
}