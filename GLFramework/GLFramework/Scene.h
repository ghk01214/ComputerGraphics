#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	GLvoid CreateScene();
private:
	GLbool ReadFile(std::string file_name, std::string* target);
	GLvoid AddShader(GLuint shader_program, std::string text, GLuint type);
	GLuint CompileShader(std::string vertex, std::string fragment);

	//GLuint CreatePngTexture(std::string file_name, GLuint type);
public:
	GLvoid OnIdleMessage();
	template<typename T>
	GLvoid OnKeyboardMessage(T key, GLint x, GLint y);
	template<typename T>
	GLvoid OnKeyboardUpMessage(T key, GLint x, GLint y);
	GLvoid OnMouseMessage(GLint state, GLint x, GLint y);
	GLvoid OnMouseUpMessage(GLint state, GLint x, GLint y);
	GLvoid OnMouseMotionMessage(GLint x, GLint y);
	GLvoid OnMousePassiveMessage(GLint x, GLint y);

	GLvoid WorldTransform();
	GLvoid ViewTransform();
	GLvoid ProjectionTransform();

	GLvoid Render();

private:
	template<typename T>
	inline GLvoid glBufferData(GLenum target, const std::vector<T>& v, GLenum usage);

	GLvoid ChangeMouseState(GLint button);

private:
	GLuint shader;

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<GLfloat> verticies;
	std::vector<GLuint> index;

	GLint vertex_num;
	GLint color_num;

#pragma region [ATTRIBUTE]
	GLint attrib_position;
	GLint attrib_color;
#pragma endregion

#pragma region [UNIFORM]
	GLint uni_model;
	GLint uni_view;
	GLint uni_projection;
#pragma endregion

#pragma region [CAMERA]
	glm::vec3 camera_position;
	glm::vec3 camera_look;
	glm::vec3 camera_up;
#pragma endregion

#pragma region [MATRIX]
	glm::mat4 orthographic_projection;
	glm::mat4 perspective_projection;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
#pragma endregion

	GLfloat aspect;

	std::array<GLbool, 3> mouse;
};

template<typename T>
inline void Scene::glBufferData(GLenum target, const std::vector<T>& v, GLenum usage)
{
	::glBufferData(target, v.size() * sizeof(T), v.data(), usage);
}
