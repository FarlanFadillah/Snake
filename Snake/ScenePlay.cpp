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
	registerAction(sf::Keyboard::Add, "GROW");


	spawnSnake();
	spawnFood();

	tnr.loadFromFile("res/fonts/Times_New_Roman.ttf");
}

void ScenePlay::spawnSnake()
{
	auto snake = m_entityManager.addEntity("snake");

	snake->addComponent<CNode>(Vec2(25, 19));

	snake->addComponent<CState>();

	player = snake;
}

void ScenePlay::growSnake()
{
	auto& body = player->getComponent<CNode>().body;
	auto& tail = body.back();
	auto& tailprev = body.at(body.size() - 2);

	Vec2 newPos(tail - tailprev);
	newPos += tail;

	body.push_back(Vec2(newPos)); 
}

void ScenePlay::spawnFood()
{
	// world size 50 x 38	
	int x = std::rand() % 49;
	int y = std::rand() % 37;

	Vec2 pos(x, y);

	for (auto& e : player->getComponent<CNode>().body)
	{
		if (e == pos)
		{
			spawnFood();
			return;
		}
	}

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
	if (currentFrame % 5 != 0) return;
	auto& node = player->getComponent<CNode>();
	auto& state = player->getComponent<CState>();
	auto& body = node.body;

	if (!commandList.empty())
	{
		state.state = *commandList.begin();
		commandList.erase(commandList.begin());
	}

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
	auto& head = body.front();
	//collision with frame bound
	if (head.x < 0) head.x = winGrid.x;
	else if (head.x > winGrid.x) head.x = 0;
	else if (head.y < 0) head.y = winGrid.y;
	else if (head.y > winGrid.y) head.y = 0;
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
			growSnake();
			spawnFood();
		}

		
	}

	//collision with the body it self
	for (int i = 1; i < body.size(); i++)
	{
		if (head == body.at(i))
		{
			player->destroy();
			spawnSnake();
		}
	}



	
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

	Vec2 rectPos = getRectGrid(winGrid, rectSize);

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

	// draw food
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

	// draw score
	auto& body = player->getComponent<CNode>().body;
	sf::Text text;
	text.setFont(tnr);
	std::cout << body.size() << std::endl;
	text.setString(std::to_string(body.size()-2));
	text.setFillColor(sf::Color::White);
	text.setPosition(100, 100);

	window.draw(text);
}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		auto& playerState = player->getComponent<CState>();
		if (action.name() == "UP")
		{
			if (playerState.state == "down") return;
			commandList.insert("up");
			//playerState.state = "up";
		}
		else if (action.name() == "DOWN")
		{
			if (playerState.state == "up") return;
			commandList.insert("down");
			//playerState.state = "down";
		}
		else if (action.name() == "LEFT")
		{
			if (playerState.state == "right") return;
			commandList.insert("left");
			//playerState.state = "left";
		}
		else if (action.name() == "RIGHT")
		{
			if (playerState.state == "left") return;
			commandList.insert("right");
			//playerState.state = "right";
		}
		else if (action.name() == "GROW")
		{
			growSnake();
		}
	}
	else if(action.type() == "END")
	{

	}
}

void ScenePlay::sOnEnd()
{
}


