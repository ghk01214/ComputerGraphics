#include "stdafx.h"
#include "pch.h"
#include "Renderer.h"

std::unique_ptr<Renderer> Renderer::inst{ nullptr };

Renderer::Renderer() :
	width{ 800 },
	height{ 800 },
	current_scene{ std::make_unique<Scene>() }
#pragma region [CONSTRUCTOR]
{
	inst.reset(this);

	x = (glutGet(GLUT_SCREEN_WIDTH) - width) / 2;
	y = (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow("GLFramework");

	//glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	if (glewIsSupported("GL_VERSION_4_6"))
	{
		std::cout << " GL Version is 4.6\n ";
	}
	else
	{
		std::cout << "GLEW 4.6 not supported\n ";
	}

	glClearDepth(1.f);

	Initialize();

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MousePassive);
}
#pragma endregion

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
	current_scene->CreateScene();
}

#pragma region [STATIC FUNCTION]
void Renderer::Idle()
{
	inst->current_scene->OnIdleMessage();
}

void Renderer::Keyboard(GLuchar key, GLint x, GLint y)
{
	inst->current_scene->OnKeyboardMessage(key, x, y);
}

void Renderer::KeyboardUp(GLuchar key, GLint x, GLint y)
{
	inst->current_scene->OnKeyboardUpMessage(key, x, y);
}

void Renderer::SpecialKey(GLint key, GLint x, GLint y)
{
	inst->current_scene->OnKeyboardMessage(key, x, y);
}

void Renderer::SpecialKeyUp(GLint key, GLint x, GLint y)
{
	inst->current_scene->OnKeyboardUpMessage(key, x, y);
}

void Renderer::Mouse(GLint button, GLint state, GLint x, GLint y)
{
	switch (state)
	{
	case GLUT_DOWN:
	{
		inst->current_scene->OnMouseMessage(button, x, y);
	}
	break;
	case GLUT_UP:
	{
		inst->current_scene->OnMouseUpMessage(button, x, y);
	}
	break;
	}
}

void Renderer::MouseMotion(GLint x, GLint y)
{
	inst->current_scene->OnMouseMotionMessage(x, y);
}

void Renderer::MousePassive(GLint x, GLint y)
{
	inst->current_scene->OnMousePassiveMessage(x, y);
}

void Renderer::Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO : scene 렌더링
	inst->current_scene->Render();

	glutSwapBuffers();
}

void Renderer::Reshape(GLint width, GLint height)
{
	inst->width = width;
	inst->height = height;

	glViewport(0, 0, inst->width, inst->height);
}
#pragma endregion

void Renderer::Run()
{
	glutMainLoop();
}
