#pragma once

class GameObject;
class Transform;		// 추가 예정

enum class COMPONENT_TYPE
{
	TRANSFORM,
	MESH_RENDERER,
	//CAMERA,
	//LIGHT,
	MONO_BEHAVIOR,
};

class Component
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component() = default;

public:
	virtual void Update() {}

private:	
	friend class GameObject;
	void SetGameObject(std::shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

private:
	std::shared_ptr<GameObject> GetGameObject() { return _gameObject.lock(); }
	// 추가예정
	//std::shared_ptr<GameObjct> GetTransform() { return _gameObject.lock()->GetTransform; }

protected:
	COMPONENT_TYPE				_type;
	std::weak_ptr<GameObject>	_gameObject;
};

