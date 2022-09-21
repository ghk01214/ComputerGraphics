#include "pch.h"
#include "Engine.h"

std::uniform_real_distribution<float> uid{ 0.f, 1.f };

#define RED 1.f, 0.f, 0.f
#define GREEN 0.f, 1.f, 0.f
#define BLUE 0.f, 0.f, 1.f
#define RANDOM uid(dre), uid(dre), uid(dre)
#define WHITE 1.f, 1.f, 1.f
#define BLACK 0.f, 0.f, 0.f
#define GRAY 0.5f, 0.5f, 0.5f

Engine::Engine() :
	_window{ nullptr },
	_start_timer{ false },
	_rect{},
	_move_rect{ -1 }
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

	inst->_rect.push_back({ -0.1f, 0.1f, 0.1f, -0.1f, RANDOM });

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
		case 'A': FALLTHROUGH
		case 'a':
		{
			if (inst->_rect.size() < 5)
				inst->_rect.push_back({ -0.1f, 0.1f, 0.1f, -0.1f, RANDOM });
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

void Engine::OnKeyboardUpMessage(uchar key, int32_t x, int32_t y)
{
}

void Engine::OnMouseMessage(int32_t button, int32_t state, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (inst->_window->width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (inst->_window->height / 2) };

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			for (auto iter = inst->_rect.rbegin(); iter != inst->_rect.rend(); ++iter)
			{
				if (iter->left <= x2 and x2 <= iter->right)
				{
					if (iter->bottom <= y2 and y2 <= iter->top)
					{
						inst->_move_rect = std::distance(iter, --inst->_rect.rend());
						break;
					}
				}
			}
		}
	}
	else if (state == GLUT_UP)
	{
		inst->_move_rect = -1;
	}

	glutPostRedisplay();
}

void Engine::OnMouseMotionMessage(int32_t x, int32_t y)
{
	if (inst->_move_rect == -1)
		return;

	float x2{ Convert::ToFloat(x) / (inst->_window->width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (inst->_window->height / 2) };

	auto iter{ inst->_rect.begin() };
	std::advance(iter, inst->_move_rect);

	iter->left = x2 - 0.1f;
	iter->top = y2 + 0.1f;
	iter->right = x2 + 0.1f;
	iter->bottom = y2 - 0.1f;

	glutPostRedisplay();
}

void Engine::Timer(int32_t value)
{
	
}
