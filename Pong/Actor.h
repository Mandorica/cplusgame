#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	// ������ ���¸� �����ϴµ� ����.
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	// ������&�Ҹ���
	Actor(class Game* game);
	virtual ~Actor();
	// Game���� ȣ���ϴ� Update �Լ� ( ���� �Լ� �ƴ� )
	void Update(float deltaTime);
	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ ( ���� �Լ� �ƴ�)
	void UpdateComponents(float deltaTime);
	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ� ( �������̵� ���� )
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	// ...

	//������Ʈ �߰�/����
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private :
	// ������ ����
	State mState;
	// ��ȯ
	Vector2 mPosition; // ������ �߽���
	float mScale; // ������ ���� (100%�� ��� 1.0f)
	float mRotation; // ȸ�� ���� ( ���� )
	// �� ���Ͱ� ������ ������Ʈ��
	std::vector<class Component*> mComponents;
	class Game* mGame;


};