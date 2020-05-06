#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
public:
	Module(bool startEnabled);


	//Called at the beginning of the application execution
	virtual bool Init();

	//Called when the module is activated
	//By now we will consider all modules to be permanently active
	virtual bool Start();

	//Called at the beginning of each application loop
	virtual update_status PreUpdate();

	//Called at the middle of each application loop
	virtual update_status Update();

	//Called at the end of each application loop
	virtual update_status PostUpdate();

	//Called at the end of the application
	virtual bool CleanUp();

	//Called when two colliders are intersecting
	//and the module is registered as the listener
	virtual void OnCollision(Collider* c1, Collider* c2);

	//Enable and disable variables
	void Enable();

	void Disable();

	inline bool IsEnabled() const { return isEnabled; }

	const char* name = "None";

	//ResourcesInfo
	uint activeFonts = 0;
	uint totalFonts = 0;

	uint activeTextures = 0;
	uint totalTextures = 0;

	uint activeColliders = 0;
	uint totalColliders = 0;

	uint activeFx = 0;
	uint totalFx = 0;

private:
	bool isEnabled = true;
};

#endif // __MODULE_H__