#pragma once

class GameObject;
//class Transform;		// 추가 예정

enum class COMPONENT_TYPE : UINT
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	//LIGHT,
	MONO_BEHAVIOR,
	END
};

class Component
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component() = default;

public:
	virtual void Update() {}
	virtual void Render() {}
	virtual void Bind() {}

private:	
	friend class GameObject;
	void SetGameObject(std::shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

private:
	std::shared_ptr<GameObject> GetGameObject() { return _gameObject.lock(); }
	//std::shared_ptr<GameObject> GetTransform() { return _gameObject.lock()->GetTransform(); }

protected:
	COMPONENT_TYPE				_type;
	std::weak_ptr<GameObject>	_gameObject;
};

