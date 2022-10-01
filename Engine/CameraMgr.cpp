#include "pch.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraMgr.h"

CameraMgr::CameraMgr() :
	_camera{ std::make_unique<Camera>() },
	_view{ mat4::unit() },
	_projection{ mat4::unit() },
	_pitch{ 0.f },
	_yaw{ -90.f },
	_roll{ 0.f },
	_old_x{ 0 },
	_old_y{ 0 },
	_sensitivity{ 0.f },
	_click{ false },
	_aspect{ 1.f / 1.f }
{
}

CameraMgr::~CameraMgr()
{
}

void CameraMgr::OnLoad()
{
	inst->_camera->Rotate(inst->_pitch, inst->_yaw, inst->_roll);
}

void CameraMgr::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
}

void CameraMgr::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
}

void CameraMgr::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	if (button == GLUT_LEFT_BUTTON)
		inst->_click = true;
}

void CameraMgr::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
}

void CameraMgr::OnMouseMotionMessage(int32_t x, int32_t y)
{
	if (inst->_click)
	{
		inst->_old_x = x;
		inst->_old_y = y;
		inst->_click = false;
	}

	float delta_x{ Convert::ToFloat(x - inst->_old_x) };
	float delta_y{ Convert::ToFloat(inst->_old_y - y) };
	inst->_old_x = x;
	inst->_old_y = y;

	delta_x *= inst->_sensitivity;
	delta_y *= inst->_sensitivity;

	if (delta_x != 0.f)
	{
		inst->_yaw += delta_x;

		if (inst->_yaw > 360.f)
			inst->_yaw -= 360.f;
		if (inst->_yaw < 0.f)
			inst->_yaw += 360.f;
	}

	if (delta_y != 0.f)
	{
		inst->_pitch += delta_y;

		if (inst->_pitch > 89.f)
			inst->_pitch = 89.f;
		if (inst->_pitch < -89.f)
			inst->_pitch = -89.f;
	}

	inst->_camera->Rotate(inst->_pitch, inst->_yaw);
}

void CameraMgr::ViewTransform(std::shared_ptr<Shader> shader)
{
	inst->_view = glm::lookAt(inst->_camera->GetPos(), inst->_camera->GetLook(), inst->_camera->GetUp());

	shader->SetMat4("view", inst->_view);
}

void CameraMgr::ProjectionTransform(std::shared_ptr<Shader> shader)
{
	inst->_projection = glm::perspective(glm::radians(inst->_camera->GetFOV()), inst->_aspect, 1.f, 1000.f);

	shader->SetMat4("projection", inst->_projection);
}
