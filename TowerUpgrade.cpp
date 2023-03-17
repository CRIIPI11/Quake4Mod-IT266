
#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "game/Game_local.h"
#include "Tower.h"

//NOTE: actually a bit of a misnomer, as all Strogg Marine types use this class now...
class TowerUpgrade : public idAI {
public:

	CLASS_PROTOTYPE(TowerUpgrade);

	TowerUpgrade(void);

	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	void				upgrade(idEntity* attacker, int lvl);



private:

	int			price;

};

CLASS_DECLARATION(idAI, TowerUpgrade)
END_CLASS


TowerUpgrade::TowerUpgrade() {
}

void TowerUpgrade::Spawn(void) {

	health = spawnArgs.GetInt("health", "100");
	fl.takedamage = true;
	fl.solidForTeam = true;
	BecomeSolid();
	fl.notarget = true;
	price = 500;
}

void TowerUpgrade::Think(void) {

	idAI::Think();

}
void TowerUpgrade::Save(idSaveGame* savefile) const {

}

void TowerUpgrade::Restore(idRestoreGame* savefile) {

}


void TowerUpgrade::upgrade(idEntity* attacker, int lvl)
{
	idPlayer* player;
	idEntity* tower;
	int oldhealth;
	int i;

	player = static_cast<idPlayer*>(attacker);
	gameLocal.Printf("player points: %i\n", player->points);
		
	switch (rvTower::lvl)
	{
	case 1:
		rvTower::healthRegenEnabled = TRUE;
		rvTower::lvl = 2;
		player->points -= price;
		gameLocal.Printf("up to lvl 2\n");
		break;
	case 2:
		oldhealth = rvTower::maxHealth;
		rvTower::maxHealth = 1500;
		for (i = 1; i < 6; i++)
		{
			tower = gameLocal.FindEntity(va("tower_%i", i));
			if(tower->health == oldhealth)
			{ 
				tower->health = rvTower::maxHealth;
			}
		}
		rvTower::lvl = 3;
		player->points -= price;
		gameLocal.Printf("up to lvl 3\n");
		break;
	case 3:
		rvTower::poisonIvy = TRUE;
		rvTower::lvl = 4;
		player->points -= price;
		gameLocal.Printf("up to lvl 4\n");
		break;
	case 4:
		rvTower::regenTime /= 2;
		rvTower::poisonscale *= 3;
		rvTower::lvl = 5;
		player->points -= price;
		gameLocal.Printf("up to lvl 5\n");
		break;
	default:
		gameLocal.Printf("Major Level Reached!");
		break;
	}

}

 
void TowerUpgrade::Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location)
{
	idPlayer* player;
	if (!fl.takedamage) {
		return;
	}

	if (attacker->IsType(idPlayer::GetClassType()))
	{
		
		if ((player->points - price) >= 0 )
		{
			upgrade(attacker, rvTower::lvl);
		}
		else
		{
			gameLocal.Printf("can't buy\n");
		}
	}

}


