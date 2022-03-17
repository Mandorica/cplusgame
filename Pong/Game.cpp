#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

void Game::AddActor(Actor* actor)
{
	// Actor�� �������̶�� mpendingActors�� Acotr�� �߰�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::UpdateGame()
{
	// ��Ÿ �ð��� ���(1��� ����)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// ��� ���� ������Ʈ �ϱ�
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
		mUpdatingActors = false;
	}
	
	// ��� ���� Actor�� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���� Actor�� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���� ���� ����(mActors���� �߷��� ���͵�)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	// ~Actor �Լ��� RemoveActor�� ȣ���ϹǷ� �ٸ� ��Ÿ���� ������ �������
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// ���ĵ� ���Ϳ��� �����ؾ� �� ��ġ�� ã�´�.
	// �ڽź��� �׸��� �������� ū �ּ� ���
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �ݺ��� ��ġ �տ� ��Ҹ� �����Ѵ�.
	mSprites.insert(iter, sprite);
}