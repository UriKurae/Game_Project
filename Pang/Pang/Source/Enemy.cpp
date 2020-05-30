#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y) 
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) 
	{
		if (App->player->stopTime > 0) {
			if (App->player->stopTime > 40) {
				App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
			}
			
			else if (App->player->stopTime < 30 && App->player->stopTime > 20) {
				App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
			}
			else if (App->player->stopTime < 10 && App->player->stopTime > 0) {
				App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
			}

		}
		else {
			App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		}
		
	}
		
}

void Enemy::OnCollision(Collider* collider)
{
	App->audio->PlayFx(destroyedFx);
}