#pragma once

class GameObject;

class Scene
{
public:
	void Start();
	void Update();
	void LateUpdate();

	void Render();

public:
	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
};

