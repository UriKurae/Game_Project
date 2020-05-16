#include "ModuleScene5.h"

ModuleScene5::ModuleScene5(bool startEnabled) : Module(startEnabled)
{
}

ModuleScene5::~ModuleScene5()
{
}

bool ModuleScene5::Start()
{
	return false;
}

update_status ModuleScene5::Update()
{
	return update_status();
}

update_status ModuleScene5::PostUpdate()
{
	return update_status();
}

bool ModuleScene5::CleanUp()
{
	return false;
}
