#include "Engine.h"
#include "Engine.h"
#include "pch.h"
#include "Engine.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };
std::uniform_real_distribution<float> uid_coord{ -1.f, 0.8f };
std::uniform_int_distribution<int32_t> uid_rect{ 1, 100 };

#define RED 1.f, 0.f, 0.f
#define GREEN 0.f, 1.f, 0.f
#define BLUE 0.f, 0.f, 1.f
#define RANDOM uid_color(dre), uid_color(dre), uid_color(dre)
#define WHITE 1.f, 1.f, 1.f
#define BLACK 0.f, 0.f, 0.f
#define GRAY 0.5f, 0.5f, 0.5f

enum
{
	MOVE = 0,
	ZIGZAG,
	EXPAND,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

Engine::Engine() :
	_window{ nullptr },
	_rect{}
{
}

Engine::~Engine()
{
}

void Engine::Init(const Window* window)
{
	inst->_window = const_cast<Window*>(window);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - window->width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - window->height) / 2);
	glutInitWindowSize(window->width, window->height);
	glutCreateWindow("GL");

	if (glewInit() != GLEW_OK)
	{
		std::cout << std::format("Unable to initialize GLEW") << std::endl;
		exit(EXIT_FAILURE);
	}

	if (glewIsSupported("GL_VERSION_4_6"))
		std::cout << std::format("GL Version is 4.6") << std::endl;
	else
		std::cout << std::format("GLEW 4.6 not supported") << std::endl;

	glClearDepth(1.f);

	for (int32_t i = 0; i < uid_rect(dre); ++i)
	{
		float left{ uid_coord(dre) };
		float bottom{ uid_coord(dre) };

		inst->_rect.push_back({ left, bottom + 0.2f, left + 0.2f, bottom, RANDOM });
	}

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(OnKeyboardDownMessage);
	glutKeyboardUpFunc(OnKeyboardUpMessage);
	glutMouseFunc(OnMouseMessage);
	glutMotionFunc(OnMouseMotionMessage);
}

void Engine::Init(const Window* window, const std::string& name)
{
	inst->_window = const_cast<Window*>(window);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - window->width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - window->height) / 2);
	glutInitWindowSize(window->width, window->height);
	glutCreateWindow(name.c_str());

	if (glewInit() != GLEW_OK)
	{
		std::cout << std::format("Unable to initialize GLEW") << std::endl;
		exit(EXIT_FAILURE);
	}

	if (glewIsSupported("GL_VERSION_4_6"))
		std::cout << std::format("GL Version is 4.6") << std::endl;
	else
		std::cout << std::format("GLEW 4.6 not supported") << std::endl;

	glClearDepth(1.f);

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(OnKeyboardDownMessage);
	glutKeyboardUpFunc(OnKeyboardUpMessage);
	glutMouseFunc(OnMouseMessage);
	glutMotionFunc(OnMouseMotionMessage);
}

void Engine::Update()
{
	glutMainLoop();
}

void Engine::Render()
{
	glClearColor(GRAY, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO : 그리기
	for (auto& rect : inst->_rect)
	{
		glColor4f(rect.r, rect.g, rect.b, 1.f);
		glRectf(rect.left, rect.bottom, rect.right, rect.top);
	}

	glutSwapBuffers();
}

void Engine::Reshape(int32_t width, int32_t height)
{
	inst->_window->width = Convert::ToUint32(width);
	inst->_window->height = Convert::ToUint32(height);

	glViewport(0, 0, width, height);
}

void Engine::Resize(const Window* window)
{
	inst->_window = const_cast<Window*>(window);

	glutReshapeWindow(window->width, window->height);
}

void Engine::OnKeyboardDownMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'R': FALLTHROUGH
		case 'r':
		{
			inst->_rect.clear();

			for (int32_t i = 0; i < uid_rect(dre); ++i)
			{
				float left{ uid_coord(dre) };
				float bottom{ uid_coord(dre) };

				inst->_rect.push_back({ left, bottom + 0.2f, left + 0.2f, bottom, RANDOM });
			}
		}
		break;
		case 'Q': FALLTHROUGH
		case 'q':
		{
			glutLeaveMainLoop();
		}
		break;
	}

	glutPostRedisplay();
}

void Engine::OnMouseMessage(int32_t button, int32_t state, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (inst->_window->width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (inst->_window->height / 2) };

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			inst->_rect.push_back({ x2 - 0.2f, y2 + 0.2f, x2 + 0.2f, y2 - 0.2f, RANDOM });
		}
	}
	if (state == GLUT_UP)
	{
		inst->_rect.pop_back();
	}

	glutPostRedisplay();
}

void Engine::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (inst->_window->width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (inst->_window->height / 2) };

	auto iter{ inst->_rect.rbegin() };

	iter->left = x2 - 0.2f;
	iter->top = y2 + 0.2f;
	iter->right = x2 + 0.2f;
	iter->bottom = y2 - 0.2f;

	for (auto rect = inst->_rect.begin(); rect != inst->_rect.end(); ++rect)
	{
		if (iter->left < rect->right and rect->right < iter->right)
		{
			if (iter->bottom < rect->top and rect->top < iter->top)
			{
				inst->_rect.erase(rect);
				break;
			}

			if (iter->bottom < rect->bottom and rect->bottom < iter->top)
			{
				inst->_rect.erase(rect);
				break;
			}
		}

		if (iter->left < rect->left and rect->left < iter->right)
		{
			if (iter->bottom < rect->top and rect->top < iter->top)
			{
				inst->_rect.erase(rect);
				break;
			}

			if (iter->bottom < rect->bottom and rect->bottom < iter->top)
			{
				inst->_rect.erase(rect);
				break;
			}
		}
	}

	glutPostRedisplay();
}

void Engine::Timer(int32_t value)
{
	//if (inst->_start_timer == false)
	//	return;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, value);
}
