#pragma once

#include "Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;

	void Initialize();

	static void Idle();
	static void Keyboard(GLuchar key, GLint x, GLint y);
	static void KeyboardUp(GLuchar key, GLint x, GLint y);
	static void SpecialKey(GLint key, GLint x, GLint y);
	static void SpecialKeyUp(GLint key, GLint x, GLint y);
	static void Mouse(GLint button, GLint state, GLint x, GLint y);
	static void MouseMotion(GLint x, GLint y);
	static void MousePassive(GLint x, GLint y);
	static void Render();
	static void Reshape(GLint width, GLint height);

	void Run();

private:
	static std::unique_ptr<Renderer> inst;
	GLint x, y;
	GLint width, height;

	std::unique_ptr<Scene> current_scene;
};
