#include "pch.h"
#include "Engine.h"

std::uniform_real_distribution<float> uid{ 0.f, 1.f };

#define RED 1.f, 0.f, 0.f
#define GREEN 0.f, 1.f, 0.f
#define BLUE 0.f, 0.f, 1.f
#define RANDOM uid(dre), uid(dre), uid(dre)
#define WHITE 1.f, 1.f, 1.f
#define BLACK 0.f, 0.f, 0.f

Engine::Engine() :
	_window{ nullptr },
	_start_timer{ false },
	_rect{ -0.5f, 0.5f, 0.5f, -0.5f },
	_back_color{ RANDOM },
	_rect_color{ RANDOM }
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
	glClearColor(WHITE, 1.f);

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(OnKeyboardDownMessage);
	glutKeyboardUpFunc(OnKeyboardUpMessage);
	glutMouseFunc(OnMouseMessage);
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
}

void Engine::Update()
{
	glutMainLoop();
}

void Engine::Render()
{
	glClearColor(inst->_back_color.r, inst->_back_color.g, inst->_back_color.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO : 그리기
	glColor4f(inst->_rect_color.r, inst->_rect_color.g, inst->_rect_color.b, 1.f);
	glRectf(inst->_rect.left, inst->_rect.bottom, inst->_rect.right, inst->_rect.top);

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
			inst->_back_color = { RED };
		}
		break;
		case 'G': FALLTHROUGH
		case 'g':
		{
			inst->_back_color = { GREEN };
		}
		break;
		case 'B': FALLTHROUGH
		case 'b':
		{
			inst->_back_color = { BLUE };
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			inst->_back_color = { RANDOM };
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			inst->_back_color = { WHITE };
		}
		break;
		case 'K': FALLTHROUGH
		case 'k':
		{
			inst->_back_color = { BLACK };
		}
		break;
		case 'T': FALLTHROUGH
		case 't':
		{
			inst->_start_timer = true;
			glutTimerFunc(1, Timer, 1);
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			inst->_start_timer = false;
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
	float x2{ Convert::ToFloat(x) / 400.f - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / 300.f };

	std::cout << y << ", " << y2 << std::endl;

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (inst->_rect.left < x2 and x2 < inst->_rect.right)
			{
				if (inst->_rect.bottom < y2 and y2 < inst->_rect.top)
				{
					inst->_rect_color = { RANDOM };
					glutPostRedisplay();

					return;
				}
			}
			
			inst->_back_color = { RANDOM };
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			int32_t sign{ -1 };

			if (inst->_rect.left < x2 and x2 < inst->_rect.right)
			{
				if (inst->_rect.bottom < y2 and y2 < inst->_rect.top)
					sign = 1;
			}

			inst->_rect.left += -sign * 0.1f;
			inst->_rect.top += -sign * 0.1f;
			inst->_rect.right += sign * 0.1f;
			inst->_rect.bottom += sign * 0.1f;
		}
	}

	glutPostRedisplay();
}

void Engine::Timer(int32_t value)
{
	if (inst->_start_timer == false)
		return;

	inst->_back_color = { RANDOM };
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 1);
}
