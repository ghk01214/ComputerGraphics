#include "pch.h"
#include "Engine.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };
std::uniform_real_distribution<float> uid_size{ 0.f, 0.3f };

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
	_start_move{ false },
	_start_zigzag{ false },
	_start_expand{ false },
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
	for (auto& [origin, info] : inst->_rect)
	{
		glColor4f(info.rect.r, info.rect.g, info.rect.b, 1.f);
		glRectf(info.rect.left, info.rect.bottom, info.rect.right, info.rect.top);
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
			inst->_start_move = !inst->_start_move;
			glutTimerFunc(10, Move, MOVE);
		}
		break;
		case 'I': FALLTHROUGH
		case 'i':
		{
			inst->_start_zigzag = !inst->_start_zigzag;
			glutTimerFunc(10, ZigZag, ZIGZAG);
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
			inst->_start_expand = !inst->_start_expand;
			glutTimerFunc(10, Expand, EXPAND);
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			inst->_start_move = false;
			inst->_start_zigzag = false;
			inst->_start_expand = false;
		}
		break;
		case 'M': FALLTHROUGH
		case 'm':
		{
			for (auto& [origin, info] : inst->_rect)
			{
				info.rect = origin;
				info.direction = UP;
				info.expand = true;
			}
		}
		break;
		case 'R': FALLTHROUGH
		case 'r':
		{
			inst->_rect.clear();
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
			if (inst->_rect.size() < 5)
			{
				Rect temp{ x2 - 0.1f, y2 + 0.1f, x2 + 0.1f, y2 - 0.1f, RANDOM };
				Info info{ temp, uid_size(dre), UP, true };

				inst->_rect.push_back(std::make_pair(temp, info));
			}
		}
	}

	glutPostRedisplay();
}

void Engine::OnMouseMotionMessage(int32_t x, int32_t y)
{


	glutPostRedisplay();
}

void Engine::Timer(int32_t value)
{
	//if (inst->_start_timer == false)
	//	return;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, value);
}

void Engine::Move(int32_t value)
{
	if (inst->_start_move == false)
		return;

	for (auto& [rect, info] : inst->_rect)
	{
		switch (info.direction)
		{
			case LEFT:
			{
				info.rect.left -= 0.01f;
				info.rect.top += 0.01f;
				info.rect.right -= 0.01f;
				info.rect.bottom += 0.01f;
			}
			break;
			case RIGHT:
			{
				info.rect.left += 0.01f;
				info.rect.top -= 0.01f;
				info.rect.right += 0.01f;
				info.rect.bottom -= 0.01f;
			}
			break;
			case UP:
			{
				info.rect.left += 0.01f;
				info.rect.top += 0.01f;
				info.rect.right += 0.01f;
				info.rect.bottom += 0.01f;
			}
			break;
			case DOWN:
			{
				info.rect.left -= 0.01f;
				info.rect.top -= 0.01f;
				info.rect.right -= 0.01f;
				info.rect.bottom -= 0.01f;
			}
			break;
		}

		if (info.rect.left <= -1.f)
			info.direction = UP;

		if (info.rect.right >= 1.f)
			info.direction = DOWN;

		if (info.rect.top >= 1.f)
			info.direction = RIGHT;

		if (info.rect.bottom <= -1.f)
			info.direction = LEFT;
	}

	glutPostRedisplay();
	glutTimerFunc(10, Move, value);
}

void Engine::ZigZag(int32_t value)
{
	if (inst->_start_zigzag == false)
		return;

	glutPostRedisplay();
	glutTimerFunc(100, ZigZag, value);
}

void Engine::Expand(int32_t value)
{
	if (inst->_start_expand == false)
		return;



	for (auto& [origin, info] : inst->_rect)
	{
		float sign{ 1 };
		float diff{ info.rect.right - info.rect.left };

		if (diff >= info.size * 2 + 0.2f)
			info.expand = false;
		else if (diff <= 0.2f)
			info.expand = true;

		if (info.expand == false)
			sign = -1;

		info.rect.left -= sign * 0.01f;
		info.rect.top += sign * 0.01f;
		info.rect.right += sign * 0.01f;
		info.rect.bottom -= sign * 0.01f;
	}

	glutPostRedisplay();
	glutTimerFunc(10, Expand, value);
}
