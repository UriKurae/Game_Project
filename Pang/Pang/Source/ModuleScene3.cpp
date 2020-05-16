#include "ModuleScene3.h"

ModuleScene3::ModuleScene3(bool startEnabled) : Module(startEnabled)
{
}

ModuleScene3::~ModuleScene3()
{
}

bool ModuleScene3::Start()
{
	return false;
}

update_status ModuleScene3::Update()
{
	return update_status();
}

update_status ModuleScene3::PostUpdate()
{
	return update_status();
}

bool ModuleScene3::CleanUp()
{
	return false;
}
