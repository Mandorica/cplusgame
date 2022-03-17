#include "AnimSpriteComponent.h"
#include "Math.h"

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// ������ ����Ʈ�� ��Ÿ �ð��� �������
		// ���� ������ ����
		mCurrFrame += mAnimFPS * deltaTime;

		// �ִϸ��̼� �ؽ�ó ���� �ʰ��ϸ� ���� �������� �����Ѵ�.
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		// ���� �ؽ�ó�� ����
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}