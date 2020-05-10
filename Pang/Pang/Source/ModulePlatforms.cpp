#include "ModulePlatforms.h"


ModulePlatforms::ModulePlatforms(bool startEnabled): Module (startEnabled)
{

}

bool ModulePlatforms::Start()
{
	return false;
}

update_status ModulePlatforms::Update()
{
	return update_status();
}

update_status ModulePlatforms::PostUpdate()
{
	return update_status();
}

void ModulePlatforms::OnCollision(Collider* c1, Collider* c2)
{
}




