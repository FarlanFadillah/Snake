#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
}

ScenePlay::ScenePlay(Engine* engine)
	:Scene(engine)
{
	//std::cout << pos.x << " " << pos.y << std::endl;
	srand((unsigned)time(NULL));
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::W, "UP");


	spawnSnake(Vec2(25, 19));
	spawnFood();
}

void ScenePlay::spawnSnake(const Vec2& pos)
{
	auto snake = m_entityManager.addEntity("snake");

	snake->addComponent<CNode>(pos);

	snake->addComponent<CState>();

	player = snake;
}

void ScenePlay::spawnFood()
{
	// world size 50 x 38	
	int x = std::rand() % 50;
	int y = std::rand() % 38;

	auto food = m_entityManager.addEntity("food");
	food->addComponent<CTransform>(Vec2(x, y));
}

const Vec2& ScenePlay::getRectGrid(const Vec2& pos, const int rectSize)
{
	int halfRect = rectSize / 2;
	if (pos == pos)
	{
		auto result = Vec2((pos.x * rectSize) + halfRect, (pos.y * rectSize) + halfRect);
		//std::cout << result.x << " " << result.y << std::endl;
		//std::cout << pos.x << " " << pos.y << std::endl;
		return result;
	}

	return Vec2(((int)(pos.x / rectSize) * rectSize) + halfRect, ((int)(pos.y / rectSize) * rectSize) + halfRect);
}



void ScenePlay::sMovement()
{
	if (currentFrame % 15 != 0) return;
	auto& node = player->getComponent<CNode>();
	auto& state = player->getComponent<CState>();
	auto& body = node.body;
	for (int i = node.body.size()-1; i >= 0; i--)
	{
		auto& currentElement = body.at(i);
		if (i != 0)
		{
			auto front = body.at(i - 1);
			currentElement += front - currentElement;
		}
		else
		{
			if (state.state == "up")
			{
				currentElement.y--;
			}
			else if (state.state == "down")
			{
				currentElement.y++;
			}
			else if (state.state == "left")
			{
				currentElement.x--;
			}
			else if (state.state == "right")
			{
				currentElement.x++;
			}
		}

	}
}

void ScenePlay::sCollision()
{
	auto& node = player->getComponent<CNode>();
	auto& body = node.body;
	auto& head = body.at(0);
	

	// collision for food
	for (auto& f : m_entityManager.getEntities("food"))
	{
		auto& ctf = f->getComponent<CTransform>();

		if (ctf.pos == head)
		{
			f->destroy();
			auto& tail = body.back();
			auto& tailprev = body.at(body.size() - 2);

			Vec2 newPos(tailprev - tail);
			newPos += tail;

			node.body.push_back(Vec2(newPos));
			spawnFood();
		}

		
	}

	//collision with the body it self
	



	//collision with frame bound

}

void ScenePlay::update()
{
	if (!m_paused)
	{
		m_entityManager.update();
		sCollision();
		sMovement();
	}
	sRender();
	currentFrame++;
}

void ScenePlay::sRender()
{
	auto& window = m_game->window();

	window.clear(sf::Color::Black);


	/*sf::RectangleShape rect(sf::Vector2f(16, 16));
	int rectSize = rect.getSize().x;
	rect.setFillColor(sf::Color::Yellow);
	rect.setOrigin(rectSize/2, rectSize/2);

	Vec2 rectPos = getRectGrid(Vec2(65, 15), rectSize);

	rect.setPosition(rectPos.x, rectPos.y);
	window.draw(rect);*/


	// draw snake
	{
		for (auto& e : m_entityManager.getEntities("snake"))
		{
			auto& node = e->getComponent<CNode>();
			auto body = node.body;
			for (int i = 0; i < node.body.size(); i++)
			{
				auto element = body.at(i);

				sf::RectangleShape rect(sf::Vector2f(16, 16)); 
				auto& pos = getRectGrid(element, 16);
				auto size = rect.getSize().x;
				rect.setFillColor(sf::Color::Blue);
				rect.setOrigin(size / 2, size / 2);
				rect.setPosition(pos.x, pos.y);

				window.draw(rect);
			}
		}
	}

	for (auto& e : m_entityManager.getEntities("food"))
	{
		auto& pos = e->getComponent<CTransform>();
		auto _pos = getRectGrid(pos.pos, 16);
		sf::RectangleShape rect(sf::Vector2f(16, 16));
		auto size = rect.getSize().x;
		rect.setFillColor(sf::Color::Yellow);
		rect.setOrigin(size/2, size/2);
		rect.setPosition(_pos.x, _pos.y);

		window.draw(rect);
	}

}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		auto& playerState = player->getComponent<CState>();
		if (action.name() == "UP")
		{
			if (playerState.state == "down") return;
			playerState.state = "up";
		}
		else if (action.name() == "DOWN")
		{
			if (playerState.state == "up") return;
			playerState.state = "down";
		}
		else if (action.name() == "LEFT")
		{
			if (playerState.state == "right") return;
			playerState.state = "left";
		}
		else if (action.name() == "RIGHT")
		{
			if (playerState.state == "left") return;
			playerState.state = "right";
		}
	}
	else if(action.type() == "END")
	{

	}
}

void ScenePlay::sOnEnd()
{
}


