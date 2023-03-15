
#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "game/Game_local.h"
#include "Tower.h"


CLASS_DECLARATION(idAI, rvTower)
END_CLASS

rvTower::rvTower() {

}

void rvTower::Spawn(void) {

	health = spawnArgs.GetInt("health", "100");
	fl.takedamage = true;
	fl.solidForTeam = true;
	BecomeSolid();
	physicsObj.GetClipModel()->Link();

	healthRegenNextTime = 0;
	maxHealth = health;
	regenTime = 3000;
	healthRegen = 15;
	healthRegenEnabled = false;
	poisonIvy = false;
	poisonscale = 1;
}

void rvTower::InitSpawnArgsVariables(void)
{	
}


void rvTower::Think(void) {
	
	idAI::Think();

	//==================Tower Ability============================
	if (health > 0 && health < maxHealth && healthRegenEnabled) {
		if (gameLocal.GetTime() >= healthRegenNextTime) {
			health += healthRegen;
			healthRegenNextTime = gameLocal.GetTime() + regenTime;
		}
	}
	
}


void rvTower::Save(idSaveGame* savefile) const {
	savefile->WriteInt(health);
}


void rvTower::Restore(idRestoreGame* savefile) {
	savefile->ReadInt( health );

}

void rvTower::Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location)
{
	idVec3		kick;
	int			damage;
	idVec3		damage_from;
	float		attackerPushScale;


	if (!fl.takedamage ) {
		return;
	}

	
	if (attacker->IsType(idActor::GetClassType()) && static_cast<idActor*>(attacker)->team == team) {
		return;
	}
	
	//EFFECTS; Could be added later (?) criipi
	/*
	if (damageDef->dict.GetBool("burn")) {
		StartSound("snd_burn", SND_CHANNEL_BODY3, 0, false, NULL);
	}
	else if (damageDef->dict.GetBool("no_air")) {
		if (!armorSave && health > 0) {
			StartSound("snd_airGasp", SND_CHANNEL_ITEM, 0, false, NULL);
		}
	}
	*/

	const idDict* damageDef = gameLocal.FindEntityDefDict(damageDefName, false);
	if (!damageDef) {
		gameLocal.Error("Unknown damageDef '%s'", damageDefName);
	}

	damage = damageDef->GetInt("damage");

	// do the damage
	if (damage > 0) {
		
		if (damage < 1) {
			damage = 1;
		}

		health -= damage;

		GAMELOG_ADD(va("Tower%d_damage_taken", entityNumber), damage);
		GAMELOG_ADD(va("Tower%d_damage_%s", entityNumber, damageDefName), damage);

		
		if (health <= 0) {

			if (health < -999) {
				health = -999;
			}

			lastDmgTime = gameLocal.time;

			Killed(inflictor, attacker, damage, dir, location);

		}
		else {
			// force a blink
			blink_time = 0;

			// let the anim script know we took damage
			Pain(inflictor, attacker, damage, dir, location);
			if (!g_testDeath.GetBool()) {
				lastDmgTime = gameLocal.time;
			}
		}
	}
	
	//==================Tower Ability============================
	if(poisonIvy)
	{ 
		attacker->Damage(inflictor, attacker, dir, damageDefName, poisonscale, location);
	}

	lastDamageDir = dir;
	lastDamageDir.Normalize();
	lastDamageLocation = location;
//	gameLocal.Printf("damage:%i \n",damage);
//	gameLocal.Printf("Damage taken;  Current Life %i\n", health);



}



