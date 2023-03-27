
#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "game/Game_local.h"
#include "Tower.h"

//NOTE: actually a bit of a misnomer, as all Strogg Marine types use this class now...
class playerstuff : public idAI {
public:

	CLASS_PROTOTYPE(playerstuff);

	playerstuff(void);

	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	void				give(idEntity* attacker);
	const char* weapon;

private:

	int			price;
	bool		bought;
};

CLASS_DECLARATION(idAI, playerstuff)
END_CLASS


playerstuff::playerstuff() {
}





void playerstuff::Spawn(void) {

	health = spawnArgs.GetInt("health", "100");
	fl.notarget = true;
	bought =  FALSE;
	price = spawnArgs.GetInt("price", "100");
}

void playerstuff::Think(void) {

	idAI::Think();

}
void playerstuff::Save(idSaveGame* savefile) const {

}

void playerstuff::Restore(idRestoreGame* savefile) {

}

void playerstuff::give(idEntity* attacker)
{
	idPlayer* player;
	idEntity* wp;
	const idDict* weaponDict = NULL;
	int ammo_i;


	player = static_cast<idPlayer*>(attacker);
	
	if (idStr::Icmp(spawnArgs.GetString("item", ""), "health") == 0)
	{
		if ((player->points - price) >= 0)
		{
			player->health = player->inventory.maxHealth;
			player->points -= price;
		}
		else
		{
			player->hud->SetStateString("item", "Not Enough Money");
			player->hud->HandleNamedEvent("itemPickup");
		}
		return;
	}

	if (idStr::Icmp(spawnArgs.GetString("item", ""), "armor") == 0)
	{
		if ((player->points - price) >= 0)
		{
			player->inventory.armor = player->inventory.maxarmor;
			player->points -= price;
		}
		else
		{
			player->hud->SetStateString("item", "Not Enough Money");
			player->hud->HandleNamedEvent("itemPickup");
		}
		return;
	}
	
	if (idStr::Cmpn(spawnArgs.GetString("item", ""), "weapon_", 7) == 0 ) {
		ammo_i = player->inventory.AmmoIndexForWeaponClass(spawnArgs.GetString("item", ""), NULL);
		int i = player->SlotForWeapon(spawnArgs.GetString("item", ""));
		int clip = spawnArgs.GetInt("clipsize");

		if (bought)
		{
			if ((player->points - price) >= 0)
			{
				if (player->inventory.ammo[ammo_i] < (player->inventory.MaxAmmoForAmmoClass(player, rvWeapon::GetAmmoNameForIndex(ammo_i))))
				{
					player->inventory.ammo[ammo_i] = (player->inventory.MaxAmmoForAmmoClass(player, rvWeapon::GetAmmoNameForIndex(ammo_i)) - clip) + player->inventory.clip[i] - 1;
					player->points -= price;
				}
				gameLocal.Printf("clip size  %i\n", clip);
			}
			else
			{
				player->hud->SetStateString("item", "Not Enough Money");
				player->hud->HandleNamedEvent("itemPickup");
			}
			return;
		}
		else
		{ 
			if ((player->points - price) >= 0)
			{
				player->GiveItem(spawnArgs.GetString("item", ""));
				player->inventory.ammo[ammo_i] = player->inventory.MaxAmmoForAmmoClass(player, rvWeapon::GetAmmoNameForIndex(ammo_i));
				player->points -= price;
				bought = TRUE;
				price /= 2;
			}
			else
			{
				player->hud->SetStateString("item", "Not Enough Money");
				player->hud->HandleNamedEvent("itemPickup");
			}
			return;
		}

	}
	gameLocal.Printf("player points: %i\n", player->points);

}


void playerstuff::Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location)
{
	idPlayer* player;

	if (attacker->IsType(idPlayer::GetClassType()))
	{
		give(attacker);

	}


}

 