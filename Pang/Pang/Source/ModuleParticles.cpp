#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleTileset.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	name = "PARTICLES";
	
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Balloons/Particles.png");

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1 && c2->type == Collider::Type::BALLOON)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	breakableCollision();
	unbreakableCollision();
	wallCollision();
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}

void ModuleParticles::breakableCollision()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; i++)
	{
		iPoint tile;

		if (particles[i] != nullptr)
		{ 
			tile = { particles[i]->position.x / TILE_SIZE,  particles[i]->position.y / TILE_SIZE };
		}

		if (App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::BREAKABLE && particles[i] != nullptr) {
			App->tileset->changeTile(tile);
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
		else if (App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::BREAKABLE && App->tileset->getTileLevel(tile.y, tile.x + 1).id == ModuleTileset::TileType::EMPTY && particles[i] != nullptr) {
			App->tileset->changeTile(tile);
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
		else if (App->tileset->getTileLevel(tile.y, tile.x + 1).id == ModuleTileset::TileType::BREAKABLE && App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::EMPTY && particles[i] != nullptr) {
			App->tileset->changeTile(tile);
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

void ModuleParticles::unbreakableCollision()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; i++)
	{
		iPoint tile;

		if (particles[i] != nullptr)
		{
			tile = { particles[i]->position.x / TILE_SIZE,  particles[i]->position.y / TILE_SIZE };
		}

		if (App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::UNBREAKABLE && particles[i] != nullptr) {

			delete particles[i];
			particles[i] = nullptr;
			break;

		}
		else if (App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::UNBREAKABLE && App->tileset->getTileLevel(tile.y, tile.x + 1).id == ModuleTileset::TileType::EMPTY && particles[i] != nullptr) {
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
		else if (App->tileset->getTileLevel(tile.y, tile.x + 1).id == ModuleTileset::TileType::UNBREAKABLE && App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::EMPTY && particles[i] != nullptr) {
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

void ModuleParticles::wallCollision()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; i++)
	{
		iPoint tile;

		if (particles[i] != nullptr)
		{
			tile = { particles[i]->position.x / TILE_SIZE,  particles[i]->position.y / TILE_SIZE };
		}

		if (App->tileset->getTileLevel(tile.y, tile.x).id == ModuleTileset::TileType::WALL && App->tileset->getTileLevel(tile.y, tile.x + 1).id == ModuleTileset::TileType::WALL && particles[i] != nullptr) {
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}