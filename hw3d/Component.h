#pragma once

class GameObject;
class Transform;

enum class COMPONENT_TYPE : UINT
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	LIGHT,
	MONO_BEHAVIOR,
	END
};

class Component
{
public:
	Component(COMPONENT_TYPE type) : _type(type) {}
	virtual ~Component() = default;

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}

public:
	COMPONENT_TYPE GetType() { return _type; }

private:	
	friend class GameObject;
	void SetGameObject(std::shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

public:
	std::shared_ptr<GameObject> GetGameObject();
	std::shared_ptr<Transform> GetTransform();

protected:
	COMPONENT_TYPE				_type;
	std::weak_ptr<GameObject>	_gameObject;
};

