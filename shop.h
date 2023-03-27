

#ifndef __SHOP__
#define __SHOP__


class spUpgradeHealth : public idAI {
public:

	CLASS_PROTOTYPE(spUpgradeHealth);

	spUpgradeHealth(void);

	void				Spawn(void);
	void				Think(void);
	void				Save(idSaveGame* savefile) const;
	void				Restore(idRestoreGame* savefile);
	virtual	void		Damage(idEntity* inflictor, idEntity* attacker, const idVec3& dir, const char* damageDefName, const float damageScale, const int location);
	void		passreference(bool* h, bool val);


private:

	int			price;

};

#endif 