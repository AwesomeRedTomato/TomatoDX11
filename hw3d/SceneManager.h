#pragma once
#include "Scene.h"

class Camera;
class SceneManager
{
	SINGLETON(SceneManager);

public:
	void LoadScene();
	void Update();

	void UpdateImgui();

public:
	std::shared_ptr<Scene> GetActiveScene() { return _activeScene; }
	std::shared_ptr<Scene> LoadTestScene();

private:
	std::shared_ptr<Scene> _activeScene;
};