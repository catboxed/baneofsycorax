//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "basehlcombatweapon.h"
#include "NPCevent.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "in_buttons.h"
#include "weapon_ar1.h"
#include "dofweapon.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef MAPBASE
extern acttable_t *GetAR2Acttable();
extern int GetAR2ActtableCount();
#endif

IMPLEMENT_SERVERCLASS_ST(CWeaponAR1, DT_WeaponAR1)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_ar1, CWeaponAR1);
PRECACHE_WEAPON_REGISTER(weapon_ar1);

acttable_t	CWeaponAR1::m_acttable[] =
{
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_AR2, true },
	{ ACT_RELOAD, ACT_RELOAD_AR2, true },
	{ ACT_IDLE, ACT_IDLE_AR2, true },
	{ ACT_IDLE_ANGRY, ACT_IDLE_ANGRY_AR2, false },

	{ ACT_WALK, ACT_WALK_AR2, true },

	// Readiness activities (not aiming)
	{ ACT_IDLE_RELAXED, ACT_IDLE_AR2_RELAXED, false },//never aims
	{ ACT_IDLE_STIMULATED, ACT_IDLE_AR2_STIMULATED, false },
	{ ACT_IDLE_AGITATED, ACT_IDLE_ANGRY_AR2, false },//always aims

	{ ACT_WALK_RELAXED, ACT_WALK_AR2_RELAXED, false },//never aims
	{ ACT_WALK_STIMULATED, ACT_WALK_AR2_STIMULATED, false },
	{ ACT_WALK_AGITATED, ACT_WALK_AIM_AR2, false },//always aims

	{ ACT_RUN_RELAXED, ACT_RUN_AR2_RELAXED, false },//never aims
	{ ACT_RUN_STIMULATED, ACT_RUN_AR2_STIMULATED, false },
	{ ACT_RUN_AGITATED, ACT_RUN_AIM_RIFLE, false },//always aims

	// Readiness activities (aiming)
	{ ACT_IDLE_AIM_RELAXED, ACT_IDLE_AR2_RELAXED, false },//never aims	
	{ ACT_IDLE_AIM_STIMULATED, ACT_IDLE_AIM_AR2_STIMULATED, false },
	{ ACT_IDLE_AIM_AGITATED, ACT_IDLE_ANGRY_AR2, false },//always aims

	{ ACT_WALK_AIM_RELAXED, ACT_WALK_AR2_RELAXED, false },//never aims
	{ ACT_WALK_AIM_STIMULATED, ACT_WALK_AIM_AR2_STIMULATED, false },
	{ ACT_WALK_AIM_AGITATED, ACT_WALK_AIM_AR2, false },//always aims

	{ ACT_RUN_AIM_RELAXED, ACT_RUN_AR2_RELAXED, false },//never aims
	{ ACT_RUN_AIM_STIMULATED, ACT_RUN_AIM_AR2_STIMULATED, false },
	{ ACT_RUN_AIM_AGITATED, ACT_RUN_AIM_RIFLE, false },//always aims
	//End readiness activities

	{ ACT_WALK_AIM, ACT_WALK_AIM_AR2, true },
	{ ACT_WALK_CROUCH, ACT_WALK_CROUCH_RIFLE, true },
	{ ACT_WALK_CROUCH_AIM, ACT_WALK_CROUCH_AIM_RIFLE, true },
	{ ACT_RUN, ACT_RUN_AR2, true },
	{ ACT_RUN_AIM, ACT_RUN_AIM_AR2, true },
	{ ACT_RUN_CROUCH, ACT_RUN_CROUCH_RIFLE, true },
	{ ACT_RUN_CROUCH_AIM, ACT_RUN_CROUCH_AIM_RIFLE, true },
	{ ACT_GESTURE_RANGE_ATTACK1, ACT_GESTURE_RANGE_ATTACK_AR2, false },
	{ ACT_COVER_LOW, ACT_COVER_AR2_LOW, true },
	{ ACT_RANGE_AIM_LOW, ACT_RANGE_AIM_AR2_LOW, false },
	{ ACT_RANGE_ATTACK1_LOW, ACT_RANGE_ATTACK_AR2_LOW, false },
	{ ACT_RELOAD_LOW, ACT_RELOAD_AR2_LOW, false },
	{ ACT_GESTURE_RELOAD, ACT_GESTURE_RELOAD_AR2, true },
	//	{ ACT_RANGE_ATTACK2, ACT_RANGE_ATTACK_AR2_GRENADE, true },

#if EXPANDED_HL2_WEAPON_ACTIVITIES
	{ ACT_ARM, ACT_ARM_RIFLE, false },
	{ ACT_DISARM, ACT_DISARM_RIFLE, false },
#endif

#if EXPANDED_HL2_COVER_ACTIVITIES
	{ ACT_RANGE_AIM_MED, ACT_RANGE_AIM_AR2_MED, false },
	{ ACT_RANGE_ATTACK1_MED, ACT_RANGE_ATTACK_AR2_MED, false },

	{ ACT_COVER_WALL_R, ACT_COVER_WALL_R_RIFLE, false },
	{ ACT_COVER_WALL_L, ACT_COVER_WALL_L_RIFLE, false },
	{ ACT_COVER_WALL_LOW_R, ACT_COVER_WALL_LOW_R_RIFLE, false },
	{ ACT_COVER_WALL_LOW_L, ACT_COVER_WALL_LOW_L_RIFLE, false },
#endif

#ifdef MAPBASE
	// HL2:DM activities (for third-person animations in SP)
	{ ACT_HL2MP_IDLE, ACT_HL2MP_IDLE_AR2, false },
	{ ACT_HL2MP_RUN, ACT_HL2MP_RUN_AR2, false },
	{ ACT_HL2MP_IDLE_CROUCH, ACT_HL2MP_IDLE_CROUCH_AR2, false },
	{ ACT_HL2MP_WALK_CROUCH, ACT_HL2MP_WALK_CROUCH_AR2, false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK, ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2, false },
	{ ACT_HL2MP_GESTURE_RELOAD, ACT_HL2MP_GESTURE_RELOAD_AR2, false },
	{ ACT_HL2MP_JUMP, ACT_HL2MP_JUMP_AR2, false },
#if EXPANDED_HL2DM_ACTIVITIES
	{ ACT_HL2MP_WALK, ACT_HL2MP_WALK_AR2, false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK2, ACT_HL2MP_GESTURE_RANGE_ATTACK2_AR2, false },
#endif
#endif
};

IMPLEMENT_ACTTABLE(CWeaponAR1);

//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC(CWeaponAR1)

DEFINE_FIELD(m_ROF, FIELD_INTEGER),

END_DATADESC()

CWeaponAR1::CWeaponAR1()
{
	RateOfFire[0] = 0.1;
	RateOfFire[1] = 0.5;
	RateOfFire[2] = 1.0;

	Damage[0] = 2;
	Damage[1] = 10;
	Damage[2] = 20;

	m_ROF = 0;
}

void CWeaponAR1::Precache(void)
{
	BaseClass::Precache();
}

bool CWeaponAR1::Deploy(void)
{
	//CBaseCombatCharacter *pOwner  = m_hOwner;
	return BaseClass::Deploy();
}


//=========================================================
//=========================================================
void CWeaponAR1::FireBullets(const FireBulletsInfo_t &info)
{
	if (CBasePlayer *pPlayer = ToBasePlayer(GetOwner()))
	{
		pPlayer->FireBullets(info);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Override if we're waiting to release a shot
//-----------------------------------------------------------------------------
bool CWeaponAR1::Reload(void)
{
	EnableDOF();

	return BaseClass::Reload();
}


void CWeaponAR1::SecondaryAttack(void)
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (pPlayer)
	{
		pPlayer->m_nButtons &= ~IN_ATTACK2;
	}

	m_flNextSecondaryAttack = gpGlobals->curtime + 0.1;

	m_ROF += 1;

	if (m_ROF == MAX_SETTINGS)
	{
		m_ROF = 0;
	}
}

//-----------------------------------------------------------------------------
// Purpose: BOF: AR1 viewkick testing
//-----------------------------------------------------------------------------
void CWeaponAR1::AddViewKick(void)
{
#define	EASY_DAMPEN			0.5f
#define	MAX_VERTICAL_KICK	8.0f	//Degrees
#define	SLIDE_LIMIT			5.0f	//Seconds

	//Get the view kick
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

	if (!pPlayer)
		return;

	float flDuration = m_fFireDuration;

	if (g_pGameRules->GetAutoAimMode() == AUTOAIM_ON_CONSOLE)
	{
		// On the 360 (or in any configuration using the 360 aiming scheme), don't let the
		// AR2 progressive into the late, highly inaccurate stages of its kick. Just
		// spoof the time to make it look (to the kicking code) like we haven't been
		// firing for very long.
		flDuration = MIN(flDuration, 0.75f);
	}

	DoMachineGunKick(pPlayer, EASY_DAMPEN, MAX_VERTICAL_KICK, flDuration, SLIDE_LIMIT);
}
