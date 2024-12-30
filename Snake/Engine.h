#pragma once
#include <string>
#include "Scene.h"
#include <SFML/Graphics.hpp>

struct WindowConfig {
	int W, H, FS, FL;
	std::string T;
};

class Scene;

class Engine
{
private:
	WindowConfig winConf;
	sf::RenderWindow m_window;

	std::map<std::string, std::shared_ptr<Scene>> m_sceneMap;
	std::string currentSceneName;

	bool running = true;


	void init(const std::string& config);
	void update();
	void sUserInput();
	
public:
	Engine();
	Engine(const std::string& config);


	void changeScene(const std::string& sceneName, const std::shared_ptr<Scene> scene);
	void quit();
	bool isRunning();
	sf::RenderWindow& window();

	std::shared_ptr<Scene> currentScene();

	void run();
};

