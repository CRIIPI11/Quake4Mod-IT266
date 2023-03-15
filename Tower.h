

#ifndef __TOWER__
#define __TOWER__


class rvTower : public idAI {
public:

	CLASS_PROTOTYPE(rvTower);

	rvTower(void);

	void				InitSpawnArgsVariables(void);
	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	int					maxHealth;
	int					regenTime;
	bool				healthRegenEnabled;
	bool				poisonIvy;
	int					poisonscale;
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

extern const idEventDef AI_ForcePosture;

#endif /* !__AI_TACTICAL__ */
