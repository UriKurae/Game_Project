#include "ModuleScene6.h"

ModuleScene6::ModuleScene6(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 6";
}

ModuleScene6::~ModuleScene6()
{
}

bool ModuleScene6::Start()
{
	return false;
}

update_status ModuleScene6::Update()
{
	return update_status();
}

update_status ModuleScene6::PostUpdate()
{
	return update_status();
}

bool ModuleScene6::CleanUp()
{
	return false;
}
