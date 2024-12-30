#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
}

ScenePlay::ScenePlay(Engine* engine)
	:Scene(engine)
{
}

const Vec2& ScenePlay::getRectGrid(const Vec2& pos, const int& rectSize)
{
	int halfRect = rectSize / 2;
	return Vec2(((int)(pos.x / rectSize) * rectSize) + halfRect, ((int)(pos.y / rectSize) * rectSize) + halfRect);
}



void ScenePlay::update()
{
	if (!m_paused)
	{

	}
	sRender();
}

void ScenePlay::sRender()
{
	auto& window = m_game->window();

	window.clear(sf::Color::Black);


	sf::RectangleShape rect(sf::Vector2f(16, 16));
	int rectSize = rect.getSize().x;
	rect.setFillColor(sf::Color::Yellow);
	rect.setOrigin(rectSize/2, rectSize/2);

	Vec2 rectPos = getRectGrid(Vec2(65, 15), rectSize);

	rect.setPosition(rectPos.x, rectPos.y);
	window.draw(rect);

}

void ScenePlay::sDoAction(const Action& action)
{
}

void ScenePlay::sOnEnd()
{
}


