
#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "game/Game_local.h"
#include "Tower.h"

//NOTE: actually a bit of a misnomer, as all Strogg Marine types use this class now...
class playerabilities : public idAI {
public:

	CLASS_PROTOTYPE(playerabilities);

	playerabilities(void);

	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	void				upgrade(idEntity* attacker, int lvl);
private:

	int			price;
};

CLASS_DECLARATION(idAI, playerabilities)
END_CLASS


playerabilities::playerabilities() {
}

void playerabilities::Spawn(void) {

	health = spawnArgs.GetInt("health", "100");
	fl.notarget = true;
	price = spawnArgs.GetInt("price", "100");
}

void playerabilities::Think(void) {

	idAI::Think();

}
void playerabilities::Save(idSaveGame* savefile) const {

}

void playerabilities::Restore(idRestoreGame* savefile) {

}

void playerabilities::upgrade(idEntity* attacker, int lvl)
{
	idPlayer* player;

	player = static_cast<idPlayer*>(attacker);
	gameLocal.Printf("player points: %i\n", player->points);

	switch (player->lvl)
	{
	case 1:
		player->inventory.maxarmor *= 2;
		player->inventory.armor = player->inventory.maxarmor;
		player->lvl = 2;
		player->points -= price;
		gameLocal.Printf("up to lvl 2\n");
		break;
	case 2:
		player->inventory.maxHealth *= 2;
		player->health = player->inventory.maxHealth;
		player->lvl = 3;
		player->points -= price;
		gameLocal.Printf("up to lvl 3\n");
		break;
	case 3:
		player->damagescale = 2;
		player->lvl = 4;
		player->points -= price;
		gameLocal.Printf("up to lvl 3\n");
		break;
	default:
		gameLocal.Printf("Major Level Reached!");
		break;
	}
	return;
}

void playerabilities::Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location)
{
	idPlayer* player;

	if (attacker->IsType(idPlayer::GetClassType()))
	{
		player = static_cast<idPlayer*>(attacker);

		if ((player->points - price) >= 0)
		{
			upgrade(attacker, player->lvl);
		}
		else
		{
			gameLocal.Printf("can't buy\n");
		}
	}


}

