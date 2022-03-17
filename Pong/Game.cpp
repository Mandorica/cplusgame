#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

void Game::AddActor(Actor* actor)
{
	// Actor을 갱신중이라면 mpendingActors에 Acotr를 추가
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
	// 델타 시간을 계산(1장과 같음)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// 모든 액터 업데이트 하기
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
		mUpdatingActors = false;
	}
	
	// 대기 중인 Actor를 mActors로 이동
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 죽은 Actor를 임시 벡터에 추가
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 죽은 액터 제거(mActors에서 추려낸 액터들)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	// ~Actor 함수가 RemoveActor를 호출하므로 다른 스타일의 루프를 사용하자
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// 정렬된 벡터에서 삽입해야 할 위치를 찾는다.
	// 자신보다 그리기 순서값이 큰 최소 요소
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// 반복자 위치 앞에 요소를 삽입한다.
	mSprites.insert(iter, sprite);
}