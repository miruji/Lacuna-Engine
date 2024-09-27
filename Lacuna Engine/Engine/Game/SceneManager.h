#pragma once
#include <iostream>
#include <vector>

#include "../Type/mi.h"

#include "Scene.h"

namespace LE
{
	class SceneManager
	{
	private:
		std::vector<Scene> scenes;

	public:
		mi currentScene = -1; // -1 = undefined

		SceneManager();
		~SceneManager();

		void addScene(Log& l, const std::string name);
		Scene& getScene(const size_t num);
		Scene& getScene(const std::string name);
		Scene& getCurrentScene();

		size_t getScenesSize();
		void clearScenes();

		void nextScene(const size_t num);
		void nextScene(const std::string name);
	};
}