﻿#include "pch.h"
#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() :
	_vao{},
	_vertex_vbo{},
	_normal_vbo{},
	_texture_vbo{},
	_color_vbo{},
	_ibo{}
{
}

Mesh::~Mesh()
{
}

void Mesh::CreateBuffer()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vertex_vbo);
	glGenBuffers(1, &_normal_vbo);
	glGenBuffers(1, &_texture_vbo);
	glGenBuffers(1, &_color_vbo);
	glGenBuffers(1, &_ibo);
}

void Mesh::BindVAO()
{
	glBindVertexArray(_vao);
}

void Mesh::CreateVertex(std::shared_ptr<Shader> _shader)
{
	BindVAO();

	CreateVBO(_vertex_vbo, &_vertex, _shader, "v_pos", 3);
	CreateVBO(_color_vbo, &_color, _shader, "v_color", 4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, &_index);
}

void Mesh::SetUp(std::shared_ptr<Shader> _shader, std::vector<Vertex> verticies, std::vector<uint32_t> index)
{
	BindVAO();

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_vbo);
	InputAttrib(_shader, "pos", 3, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _color_vbo);
	InputAttrib(_shader, "color", 3, offsetof(Vertex, color));
	//InputAttrib(_shader, "normal", 3, offsetof(Vertex, normal));
	//InputAttrib(_shader, "tex", 3, offsetof(Vertex, tex));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, &_index);
}

template<typename T> requires requires {  std::is_arithmetic_v<T>; std::is_class_v<T>; }
void Mesh::CreateVBO(uint32_t vbo, const std::vector<T>* cont, std::shared_ptr<Shader> _shader, const std::string& name, uint32_t count)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, cont);

	int32_t attrib{ glGetAttribLocation(_shader->ID(), name.c_str()) };
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, count, GL_FLOAT, GL_FALSE, 0, 0);
}

void Mesh::InputAttrib(std::shared_ptr<Shader> _shader, const std::string& name, uint32_t count, int32_t offset)
{
	int32_t attrib{ glGetAttribLocation(_shader->ID(), name.c_str()) };
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, count, GL_FLOAT, GL_FALSE, sizeof(Vertex), Convert::ToPointer<void*>(offset));
}

template<typename T>
void Mesh::glBufferData(uint32_t target, const std::vector<T>* cont)
{
	::glBufferData(target, cont->size() * sizeof(T), cont->data(), GL_STATIC_DRAW);
}