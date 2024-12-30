#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(Engine* engine)
	:m_game(engine)
{
}

const ActionMap& Scene::getActionMap() const
{
	return m_actionMap;
}

Engine* Scene::gameEngine()
{
	return m_game;
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
	m_actionMap[inputKey] = actionName;
}

void Scene::setPaused(bool paused)
{
	m_paused = true;
}
