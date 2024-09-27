#include "SceneManager.h"

LE::SceneManager::SceneManager()
{
}
LE::SceneManager::~SceneManager()
{
}
void LE::SceneManager::addScene(Log& l, const std::string name)
{
	if (currentScene == -1)
		currentScene = 0;

	scenes.emplace_back( name );
}
LE::Scene& LE::SceneManager::getScene(const size_t num)
{
	return scenes[num];
}
LE::Scene& LE::SceneManager::getScene(const std::string name)
{
	//for (size_t i = 0; i < scenes.size(); i++)
	//if (scenes[i].name == name)
	//	return getScene(i);

	//auto l = for_el(i, 0, i < scenes.size(), i++, scenes[i].name == name, NULL);
	//if (currentScene == -1)
	//	return getScene(l);
	return getScene( for_el(i, 0, i < scenes.size(), i++, scenes[i].name == name, i) );
}
LE::Scene& LE::SceneManager::getCurrentScene()
{
	return getScene(currentScene);
}
size_t LE::SceneManager::getScenesSize()
{
	return scenes.size();
}
void LE::SceneManager::clearScenes()
{
	scenes.clear();
}
void LE::SceneManager::nextScene(const size_t num)
{
	if (currentScene != -1)
		currentScene = num;
}
void LE::SceneManager::nextScene(const std::string name)
{
	//for (size_t i = 0; i < scenes.size(); i++)
	//if (scenes[i].name == name)
	//	nextScene(i);

	auto l = for_el(i, 0, i < scenes.size(), i++, scenes[i].name == name, i);
	if (l) nextScene(l);
}