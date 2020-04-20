#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Items&Weapons/Harpoon4.png");

	/*//Harpoon shot particle
	harpoonShot[0].anim.PushBack({ 4, 53, 9, 34 });
	harpoonShot[1].anim.PushBack({ 21, 51, 9, 36 });
	harpoonShot[2].anim.PushBack({ 38, 49, 9, 38 });
	harpoonShot[3].anim.PushBack({ 55, 46, 9, 41 });
	harpoonShot[4].anim.PushBack({ 72, 44, 9, 43 });
	harpoonShot[5].anim.PushBack({ 89, 42, 9, 45 });
	harpoonShot[6].anim.PushBack({ 106, 40, 9, 47 });
	harpoonShot[7].anim.PushBack({ 123, 37, 9, 50 });
	harpoonShot[8].anim.PushBack({ 140, 35, 9, 52 });
	harpoonShot[9].anim.PushBack({ 157, 33, 9, 54 });
	harpoonShot[10].anim.PushBack({ 174, 31, 9, 56 });
	harpoonShot[11].anim.PushBack({ 191, 28, 9, 59 });
	harpoonShot[12].anim.PushBack({ 208, 26, 9, 61 });
	harpoonShot[13].anim.PushBack({ 225, 24, 9, 63 });
	harpoonShot[14].anim.PushBack({ 242, 22, 9, 65 });
	harpoonShot[15].anim.PushBack({ 259, 19, 9, 68 });
	harpoonShot[16].anim.PushBack({ 276, 17, 9, 70 });
	harpoonShot[17].anim.PushBack({ 293, 15, 9, 72 });
	harpoonShot[18].anim.PushBack({ 310, 13, 9, 74 });
	harpoonShot[19].anim.PushBack({ 327, 10, 9, 77 });
	harpoonShot[20].anim.PushBack({ 344, 8, 9, 79 });
	harpoonShot[21].anim.PushBack({ 361, 6, 9, 81 });
	harpoonShot[22].anim.PushBack({ 378, 4, 9, 83 });
	harpoonShot->anim.speed = 0.1f;*/



	// Explosion particle
	/*explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;*/

	/*laser.anim.PushBack({ 232, 103, 16, 12 });
	laser.anim.PushBack({ 249, 103, 16, 12 });
	laser.speed.x = 5;
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;*/

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
		if (particles[i] != nullptr && particles[i]->collider == c1)
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}