#pragma once
#include "Scene.h"
#include "Entity.hpp"
#include "Vec2.hpp"
#include "EntityManager.hpp"
#include <string>
#include <set>

class ScenePlay : public Scene
{

private:
	Vec2 winGrid =  Vec2(49, 37);
	EntityManager m_entityManager;

	std::shared_ptr<Entity> player;
	std::set<std::string>	commandList;

	sf::Font tnr;
	void sMovement();
	void sCollision();
	void update()							override;
	void sRender()							override;
	void sDoAction(const Action& action)	override;
	void sOnEnd()							override;

public:
	ScenePlay();
	ScenePlay(Engine* engine);

	void spawnSnake();
	void growSnake();
	void spawnFood();

	const Vec2& getRectGrid(const Vec2& pos, const int rectSize);
};

