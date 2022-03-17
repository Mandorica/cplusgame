#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

void SpriteComponent::Draw(SDL_Render* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// �������� ������ ������ �ʺ�/���̸� ������
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// �������� ��ġ�� �߽����� �簢���� ��ġ
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// ��������Ʈ�� �׸���.
		SDL_RenderCopyEx(renderer,
			mTexture, // �׸� �ؽ�ó
			nullptr, //  �׸� �ؽ�ó�� ����, nullptr�̸� ��ü ����
			&r,      // �׷��� �������� �簢�� ����
			-Math::ToDegrees(mOwner->GetRotation()), //(������ ������ ��ȯ)
			nullptr, // ȸ�� ������
			SDL_FLIP_NONE); //�ø� �ൿ
	}
}
void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// �ؽ�ó�� �ʺ�� ���̸� ����
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}