#pragma once
#include "Scene.h"
#include "Vec2.hpp"
class ScenePlay : public Scene
{

private:
	void update()							override;
	void sRender()							override;
	void sDoAction(const Action& action)	override;
	void sOnEnd()							override;

public:
	ScenePlay();
	ScenePlay(Engine* engine);

	const Vec2& getRectGrid(const Vec2& pos, const int& rectSize);
};

