#include "ModuleScene4.h"

ModuleScene4::ModuleScene4(bool startEnabled) : Module(startEnabled)
{
}

ModuleScene4::~ModuleScene4()
{
}

bool ModuleScene4::Start()
{
	return false;
}

update_status ModuleScene4::Update()
{
	return update_status();
}

update_status ModuleScene4::PostUpdate()
{
	return update_status();
}

bool ModuleScene4::CleanUp()
{
	return false;
}
