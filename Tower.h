

#ifndef __TOWER__
#define __TOWER__



class rvTower : public idAI {
public:

	CLASS_PROTOTYPE(rvTower);



	void				InitSpawnArgsVariables(void);
	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	static int			maxHealth;
	static int			regenTime;
	static bool			healthRegenEnabled;
	static bool			poisonIvy;
	static int			poisonscale;
	static int			lvl;
	
private:
	int					healthRegen;
	int					healthRegenNextTime;
	

	int					nextWallTraceTime;
	rvAIAction            action;
	float					dynamicProtectionScale;	// value to scale damage by due to dynamic protection
	int						lastDamageDef;
	idVec3					lastDamageDir;
	int						lastDamageLocation;
	int						lastDmgTime;


};


#endif 