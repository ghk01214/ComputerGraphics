#pragma once

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};

struct Color
{
	float r, g, b;
};

class Engine : public Singleton<Engine>
{
public:
	Engine();
	~Engine();

	void Init(const Window* window);
	void Init(const Window* window, const std::string& name);
	void Update();
	static void Render();

	static void Reshape(int32_t width, int32_t height);
	void Resize(const Window* window);

	static void OnKeyboardDownMessage(uchar key, int32_t x, int32_t y);
	static void OnKeyboardUpMessage(uchar key, int32_t x, int32_t y);
	static void OnMouseMessage(int32_t button, int32_t state, int32_t x, int32_t y);
	static void Timer(int32_t value);

private:
	Window* _window;
	bool _start_timer;
	Rect _rect;
	Color _back_color;
	Color _rect_color;
};