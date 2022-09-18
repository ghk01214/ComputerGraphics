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
	_start_timer{ false }
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// TODO : 그리기

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
			glClearColor(RED, 1.f);
		}
		break;
		case 'G': FALLTHROUGH
		case 'g':
		{
			glClearColor(GREEN, 1.f);
		}
		break;
		case 'B': FALLTHROUGH
		case 'b':
		{
			glClearColor(BLUE, 1.f);
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			glClearColor(RANDOM, 1.f);
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			glClearColor(WHITE, 1.f);
		}
		break;
		case 'K': FALLTHROUGH
		case 'k':
		{
			glClearColor(BLACK, 1.f);
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
}

void Engine::Timer(int32_t value)
{
	if (inst->_start_timer == false)
		return;

	glClearColor(RANDOM, 1.f);
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 1);
}
