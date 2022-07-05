#include "stdafx.h"
#include "pch.h"
#include "Def.h"
#include "LoadPng.h"
#include "Scene.h"

Scene::Scene() :
	verticies{	// vertex
				0.5f, 0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,
				-0.5f, -0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, -0.5f,
				0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, 0.5f, -0.5f,
			
				// color
				1.f, 0.f, 0.f, 1.f,
				0.f, 1.f, 0.f, 1.f,
				0.f, 0.f, 1.f, 1.f,
				1.f, 1.f, 0.f, 1.f,
				1.f, 0.f, 1.f, 1.f,
				0.f, 1.f, 1.f, 1.f,
				1.f, 1.f, 1.f, 1.f,
				0.f, 0.f, 0.f, 1.f, },
	index{ 0, 1, 3,
		   1, 2, 3,
		   0, 1, 4,
		   1, 5, 4,
		   4, 5, 7,
		   5, 6, 7,
		   7, 6, 3,
		   6, 2, 3,
		   0, 4, 3,
		   4, 7, 3,
		   1, 5, 2,
		   5, 6, 2 },
	vertex_num{ 8 },
	aspect{ static_cast<float>(glutGet(GLUT_SCREEN_WIDTH) / glutGet(GLUT_SCREEN_HEIGHT)) },
	mouse{ { false, false, false } }
{
}

Scene::~Scene()
{
	glDisableVertexAttribArray(attrib_position);
	glDisableVertexAttribArray(attrib_color);
}

void Scene::CreateScene()
{
	camera_position = glm::vec3(0.f, 0.f, 1000.f);
	camera_look = glm::vec3(0.f, 0.f, 0.f);
	camera_up = glm::vec3(0.f, 1.f, 0.f);
	view = glm::lookAt(camera_position, camera_look, camera_up);

	//orthographic_projection = glm::ortho(
	//	-static_cast<float>(width) / 2.f, static_cast<float>(width) / 2.f,
	//	-static_cast<float>(height) / 2.f, static_cast<float>(height) / 2.f,
	//	0.0001f, 10000.f);
	//perspective_projection = glm::perspectiveRH(45.f, 1.f, 1.f, 1000.f);
	perspective_projection = glm::perspective(glm::radians(45.f),
											  static_cast<float>(glutGet(GLUT_SCREEN_WIDTH) / glutGet(GLUT_SCREEN_HEIGHT)),
											  1.f,
											  1000.f);

	//projection = orthographic_projection * view;
	//projection = perspective_projection * view;

	model = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));

	shader = CompileShader("Shader/Vertex.glsl", "Shader/Fragment.glsl");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	 
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticies, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index, GL_STATIC_DRAW);

	attrib_position = glGetAttribLocation(shader, "position");
	glEnableVertexAttribArray(attrib_position);
	glVertexAttribPointer(attrib_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	attrib_color = glGetAttribLocation(shader, "in_color");
	glEnableVertexAttribArray(attrib_color);
	glVertexAttribPointer(attrib_color, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(sizeof(GLfloat) * 3 * vertex_num));
}

bool Scene::ReadFile(std::string file_name, std::string* target)
{
	std::ifstream file{ file_name };

	if (file.fail())
	{
		std::cout << file_name << " file loading failed.. \n";
		file.close();

		return false;
	}

	std::string line;

	while (std::getline(file, line))
	{
		target->append(line.c_str());
		target->append("\n");
	}

	return true;
}

void Scene::AddShader(GLuint shader_program, std::string text, GLuint type)
{
	GLuint shader{ glCreateShader(type) };

	if (shader == 0)
	{
		std::cerr << "Error creating shader type " << type << "\n";
	}

	GLchar* p{ text.data() };
	GLint length{ static_cast<GLint>(text.length()) };

	glShaderSource(shader, 1, &p, &length);
	glCompileShader(shader);

	GLint success{ 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (not success)
	{
		GLchar log[1024]{ 0 };

		glGetShaderInfoLog(shader, 1024, NULL, log);

		std::cerr << "Error compiling shader type " << type << ": '" << log << "'\n";
	}

	glAttachShader(shader_program, shader);
}

GLuint Scene::CompileShader(std::string vertex, std::string fragment)
{
	GLuint shader_program{ glCreateProgram() };

	if (shader_program == 0)
	{
		std::cerr << "Error creating shader program\n";
	}

	std::string vs, fs;

	if (not ReadFile(vertex, &vs))
	{
		std::cerr << "Error compiling vertex shader\n";
		return -1;
	}

	if (not ReadFile(fragment, &fs))
	{
		std::cerr << "Error compiling fragment shader\n";
		return -1;
	}

	AddShader(shader_program, vs, GL_VERTEX_SHADER);
	AddShader(shader_program, fs, GL_FRAGMENT_SHADER);

	GLint success{ 0 };
	GLchar log[1024]{ 0 };

	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

	if (not success)
	{
		glGetShaderInfoLog(shader_program, 1024, NULL, log);

		std::cerr << vertex << ", " << fragment << " Error linking shader program\n" << log;

		return -1;
	}

	glValidateProgram(shader_program);
	glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &success);

	if (not success)
	{
		glGetShaderInfoLog(shader_program, 1024, NULL, log);

		std::cerr << vertex << ", " << fragment << " Error vailidating shader program\n" << log;

		return -1;
	}

	glUseProgram(shader_program);

	std::cout << vertex << ", " << fragment << " Shader comiling is done.\n";

	return shader_program;
}

//GLuint Scene::CreatePngTexture(std::string file_name, GLuint type)
//{
//	std::vector<unsigned char> image;
//	unsigned int width, height;
//	unsigned int error{ lodepng::decode(image, width, height, file_name) };
//
//	if (error != 0)
//	{
//		lodepng_error_text(error);
//		assert(error == 0);
//
//		return -1;
//	}
//
//	GLuint texture;
//	glGenTextures(1, &texture);
//
//	glBindTexture(type, texture);
//	glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
//
//	return texture;
//}

GLvoid Scene::OnIdleMessage()
{
}

template<typename T>
GLvoid Scene::OnKeyboardMessage(T key, GLint x, GLint y)
{
	// GLUT_KEY_F1 ~ GLUT_KEY_F12
	// GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	// GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	// GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	// glutGetModifiers() -> return GLUT_ACTIVE_CTRL, GLUT_ACTIVE_ALT, GLUT_ACTIVE_SHIFT
	switch (key)
	{

	}
}

template<typename T>
GLvoid Scene::OnKeyboardUpMessage(T key, GLint x, GLint y)
{
	switch (key)
	{

	}
}

GLvoid Scene::OnMouseMessage(GLint state, GLint x, GLint y)
{
	switch (state)
	{
	case GLUT_LEFT_BUTTON: [[fallthrough]];
	case GLUT_RIGHT_BUTTON: [[fallthrough]];
	case GLUT_MIDDLE_BUTTON:
	{
		ChangeMouseState(state);
	}
	break;
	}
}

GLvoid Scene::OnMouseUpMessage(GLint state, GLint x, GLint y)
{
	switch (state)
	{
	case GLUT_LEFT_BUTTON: [[fallthrough]];
	case GLUT_RIGHT_BUTTON: [[fallthrough]];
	case GLUT_MIDDLE_BUTTON:
	{
		ChangeMouseState(state);
	}
	break;
	}
}

GLvoid Scene::ChangeMouseState(GLint button)
{
	mouse[button] = !mouse[button];
}

GLvoid Scene::OnMouseMotionMessage(GLint x, GLint y)
{
	if (mouse[GLUT_LEFT_BUTTON])
	{

	}
	else if (mouse[GLUT_RIGHT_BUTTON])
	{

	}
	else if (mouse[GLUT_MIDDLE_BUTTON])
	{

	}
}

GLvoid Scene::OnMousePassiveMessage(GLint x, GLint y)
{
}

void Scene::WorldTransform()
{
	glm::mat4 rotate{ glm::mat4{1.f} };
	glm::mat4 rotate2{ glm::mat4{1.f} };

	rotate = glm::rotate(rotate, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
	rotate2 = glm::rotate(rotate2, glm::radians(-30.f), glm::vec3(1.f, 0.f, 0.f));

	model = rotate2 * rotate;

	uni_model = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(uni_model, 1, GL_FALSE, glm::value_ptr(model));
}

void Scene::ViewTransform()
{
	view = glm::lookAt(camera_position, camera_look, camera_up);
	
	uni_view = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(uni_view, 1, GL_FALSE, glm::value_ptr(model));
}

void Scene::ProjectionTransform()
{
}

void Scene::Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader);
	glBindVertexArray(vao);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CW);

	WorldTransform();
	ViewTransform();
	ProjectionTransform();

	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glutSwapBuffers();
}
