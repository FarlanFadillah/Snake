#pragma once
#include "Scene.h"
#include "Entity.hpp"
#include "Vec2.hpp"
#include "EntityManager.hpp"
#include <string>

class ScenePlay : public Scene
{

private:
	EntityManager m_entityManager;

	std::shared_ptr<Entity> player;

	void sMovement();
	void sCollision();
	void update()							override;
	void sRender()							override;
	void sDoAction(const Action& action)	override;
	void sOnEnd()							override;

public:
	ScenePlay();
	ScenePlay(Engine* engine);

	void spawnSnake(const Vec2& pos);
	void spawnFood();

	const Vec2& getRectGrid(const Vec2& pos, const int rectSize);
};

