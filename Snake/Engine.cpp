#include "Engine.h"
#include <fstream>
#include <iostream>

#include "ScenePlay.h"
Engine::Engine()
{
}

Engine::Engine(const std::string& config)
{
	std::cout << config << std::endl;
	init(config);
}

void Engine::init(const std::string& config)
{
	std::ifstream fin(config);

	while (fin.good())
	{
		std::string token;
		fin >> token >> winConf.W >> winConf.H >> winConf.FL >> winConf.FS >> winConf.T;

	}

	m_window.create(sf::VideoMode(winConf.W, winConf.H), winConf.T, sf::Style::Close);
	std::cout << winConf.FL << " fps" << std::endl;
	m_window.setFramerateLimit(winConf.FL);

	changeScene("PLAY", std::make_shared<ScenePlay>(this));
}

void Engine::changeScene(const std::string& sceneName, const std::shared_ptr<Scene> scene)
{
	currentSceneName = sceneName;
	m_sceneMap[sceneName] = scene;
}

void Engine::quit()
{
	running = false;
	m_window.close();
}

bool Engine::isRunning()
{
	return m_window.isOpen() && running;
}

sf::RenderWindow& Engine::window()
{
	return m_window;
}

std::shared_ptr<Scene> Engine::currentScene()
{
	return m_sceneMap.at(currentSceneName);
}

void Engine::run()
{
	while (isRunning())
	{
		update();
	}
	quit();
}

void Engine::update()
{
	sUserInput();
	currentScene()->update();
	m_window.display();
}

void Engine::sUserInput()
{

	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			quit();
		}
		else if(event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased)
		{

			if (currentScene()->getActionMap().find(event.key.code) ==
				currentScene()->getActionMap().end())
			{
				continue;
			}

			const std::string& actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

			//std::cout << currentScene()->getActionMap().at(event.key.code) << std::endl;
			currentScene()->sDoAction(
				Action(
					currentScene()->getActionMap().at(event.key.code), 
					actionType));

		}
	}
}
