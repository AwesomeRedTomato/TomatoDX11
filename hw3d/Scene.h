#pragma once

class GameObject;

class Scene
{
public:
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void UpdateImGui();

public:
	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

	std::vector<std::shared_ptr<GameObject>>& GetGameObject() { return _gameObjects; }

private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
};

