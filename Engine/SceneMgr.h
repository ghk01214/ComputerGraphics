﻿#pragma once

// NOTE :
// 생성된 scene을 관리하는 manager class
// 

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
public:
	SceneMgr();
	~SceneMgr();

	void AddScene(define::SCENE_TYPE type, Scene* scene);
	void ChangeScene(define::SCENE_TYPE type);
	void LoadScene();

#pragma region [CALLBACK]
	void OnIdleMessage();
	void OnKeyboardMessage(uchar key, int32_t x, int32_t y);
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y);
	void OnKeyboardUpMessage(uchar key, int32_t x, int32_t y);
	void OnSpecialKeyUpMessage(int32_t key, int32_t x, int32_t y);
	void OnMouseMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseMotionMessage(int32_t x, int32_t y);
	void OnMousePassiveMotionMessage(int32_t x, int32_t y);
	void OnAnimate(int32_t index);
	void OnRender();
#pragma endregion

private:
	std::unordered_map<define::SCENE_TYPE, Scene*> _scene;
	define::SCENE_TYPE _current;
};

