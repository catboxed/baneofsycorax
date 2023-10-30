//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Projectile shot from the AR2 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//

#ifndef	WEAPONAR1_H
#define	WEAPONAR1_H

#include "basehlcombatweapon.h"

//=========================================================
//=========================================================
class CWeaponAR1 : public CHLMachineGun
{
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CWeaponAR1, CHLMachineGun);

	DECLARE_SERVERCLASS();

#define DAMAGE_PER_SECOND 10

#define MAX_SETTINGS	3

	float RateOfFire[MAX_SETTINGS];
	float Damage[MAX_SETTINGS];

	CWeaponAR1();

	int m_ROF;

	void	Precache(void);
	bool	Deploy(void);

	bool	Reload(void);
	void	AddViewKick(void);

	float GetFireRate(void) { return RateOfFire[m_ROF]; }

	int CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	void SecondaryAttack(void);

	virtual void FireBullets(const FireBulletsInfo_t &info);

	virtual const Vector& GetBulletSpread(void)
	{
		static const Vector cone = VECTOR_CONE_4DEGREES;
		return cone;
	}

	void Operator_HandleAnimEvent(animevent_t *pEvent, CBaseCombatCharacter *pOperator)
	{
		switch (pEvent->event)
		{
		case EVENT_WEAPON_AR1:
		{
			Vector vecShootOrigin, vecShootDir;
			vecShootOrigin = pOperator->Weapon_ShootPosition();

			CAI_BaseNPC *npc = pOperator->MyNPCPointer();
			ASSERT(npc != NULL);

			vecShootDir = npc->GetActualShootTrajectory(vecShootOrigin);

			WeaponSound(SINGLE_NPC);
			pOperator->FireBullets(1, vecShootOrigin, vecShootDir, VECTOR_CONE_PRECALCULATED, MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 2);
			pOperator->DoMuzzleFlash();
		}
		break;
		default:
			CBaseCombatWeapon::Operator_HandleAnimEvent(pEvent, pOperator);
			break;
		}
	}

	DECLARE_ACTTABLE();
};

#endif

