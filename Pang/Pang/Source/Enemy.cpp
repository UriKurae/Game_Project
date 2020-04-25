#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (circularCollider != nullptr)
		circularCollider->pendingToDelete = true;
}

const CircularCollider* Enemy::GetCircularCollider() const
{
	return circularCollider;
}

const Collider* Enemy::GetRectCollider() const
{
	return rectCollider;
}
void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (circularCollider != nullptr)
		circularCollider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	App->audio->PlayFx(destroyedFx);
}