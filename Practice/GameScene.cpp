#include "pch.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

enum
{
	NONE = 0,
	BODY = NONE,
	HEAD,
	NOSE,
	LEFT_ARM,
	RIGHT_ARM,
	LEFT_LEG,
	RIGHT_LEG,
	MAX
};

GameScene::GameScene() :
	_camera{ std::make_unique<Camera>(glm::vec3{ 0.f, 0.f, 4.f }) },
	_robot{},
	_stage{},
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_direction{ DIRECTION::BACK },
	_camera_angle{ 0.f },
	_gravity{ 9.8f },
	_jump_speed{ 0.f },
	_jump_pos{ 0.f },
	_delta_time{ 0.f },
	_old_time{ glutGet(GLUT_ELAPSED_TIME) }
{
	CreateRobot();
	CreateStage();
}

GameScene::~GameScene()
{
	OnRelease();
}

void GameScene::OnLoad()
{
	for (auto& obj : _robot)
	{
		obj->OnLoad();

		glm::vec3 color{ RAND_COLOR };
		obj->GetShader()->SetVec3("f_color", glm::value_ptr(color));
	}

	_stage[0]->OnLoad();
	glm::vec3 color{ RAND_COLOR };
	_stage[0]->GetShader()->SetVec3("f_color", glm::value_ptr(color));

	for (auto iter = ++_stage.begin(); iter != _stage.end(); ++iter)
	{
		(*iter)->OnLoad();
	}
}

void GameScene::OnRelease()
{
	for (auto& obj : _robot)
	{
		delete obj;
	}

	for (auto& obj : _stage)
	{
		delete obj;
	}

	_robot.clear();
	_stage.clear();
}

void GameScene::OnIdleMessage()
{
	int32_t time{ glutGet(GLUT_ELAPSED_TIME) };

	_delta_time = Convert::ToFloat((time - _old_time)) / 1000.f;
	_old_time = time;
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'O': FALLTHROUGH
		case 'o':
		{
			_stage.back()->Move(vec3::up(0.1f));
		}
		break;
		case 'W': FALLTHROUGH
		case 'w': FALLTHROUGH
		case 'A': FALLTHROUGH
		case 'a': FALLTHROUGH
		case 'S': FALLTHROUGH
		case 's': FALLTHROUGH
		case 'D': FALLTHROUGH
		case 'd':
		{
			MoveRobot(key);
		}
		break;
		case 'J': FALLTHROUGH
		case 'j':
		{
			_stop_animation = false;
			_jump_speed = 4.f;
			_jump_pos = _robot[BODY]->GetPos().y;

			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'Y': FALLTHROUGH
		case 'y':
		{
			Orbit();
		}
		break;
		case 'I': FALLTHROUGH
		case 'i':
		{
			Reset();
		}
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	_camera->OnSpecialKeyMessage(key, x, y, 0.1f);
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		_click = true;
	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (_click)
	{
		_old_x = x;
		_old_y = y;
		_click = false;
	}

	float delta_x{ Convert::ToFloat(x - _old_x) };
	float delta_y{ Convert::ToFloat(_old_y - y) };
	_old_x = x;
	_old_y = y;

	_camera->OnMouseMotionMessage(delta_x, delta_y);
}

void GameScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
	}
}

void GameScene::OnRender()
{
	glClearColor(GRAY, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderObject(&_robot);
	RenderObject(&_stage);
}

void GameScene::ViewProjection(std::shared_ptr<Shader>& shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", glm::value_ptr(view));
	shader->SetMat4("projection", glm::value_ptr(projection));
}

void GameScene::CreateRobot()
{
	// body
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.4f, 0.6f, 0.4f });

	// head
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.2f, 0.25f, 0.2f });
	_robot.back()->Move(vec3::up(0.425f));

	// nose
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.04f, 0.07f, 0.04f });
	_robot.back()->Move(glm::vec3{ 0.f, 0.4f, 0.12f });

	// left arm
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.05f, 0.3f, 0.05f });
	_robot.back()->RotateZ(-40.f);
	_robot.back()->Move(vec3::left(0.27f));

	// right arm
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.05f, 0.3f, 0.05f });
	_robot.back()->RotateZ(40.f);
	_robot.back()->Move(vec3::right(0.27f));

	// left leg
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.05f, 0.3f, 0.05f });
	_robot.back()->Move(glm::vec3{ 0.1f, -0.45f, 0.f });

	// right leg
	_robot.push_back(new Cube{});
	_robot.back()->Scale(glm::vec3{ 0.05f, 0.3f, 0.05f });
	_robot.back()->Move(glm::vec3{ -0.1f, -0.45f, 0.f });

	for (auto& obj : _robot)
	{
		obj->Move(vec3::down(0.4f));
	}

	//for (auto& obj : _robot)
	//{
	//	obj->Transform();
	//}

	//_jump_pos = _robot[BODY]->GetPos().y;
}

void GameScene::CreateStage()
{
	glm::vec3 scale_offset{ 3.f };
	float move_offset{ 1.5f };

	_stage.push_back(new Cube{});
	_stage.back()->Scale(glm::vec3{ 0.5f, 0.3f, 0.5f });
	_stage.back()->Move(glm::vec3{ -0.7f, -0.85f, 1.f });

	_stage.push_back(new Rect{});
	_stage.back()->Scale(scale_offset);
	_stage.back()->RotateY(90.f);
	_stage.back()->Move(vec3::left(move_offset));

	_stage.push_back(new Rect{});
	_stage.back()->Scale(scale_offset);
	_stage.back()->RotateY(90.f);
	_stage.back()->Move(vec3::right(move_offset));

	_stage.push_back(new Rect{});
	_stage.back()->Scale(scale_offset);
	_stage.back()->RotateX(90.f);
	_stage.back()->Move(vec3::up(move_offset));

	_stage.push_back(new Rect{});
	_stage.back()->Scale(scale_offset);
	_stage.back()->RotateX(90.f);
	_stage.back()->Move(vec3::down(move_offset));

	_stage.push_back(new Rect{});
	_stage.back()->Scale(scale_offset);
	_stage.back()->Move(vec3::front(move_offset));

	//_stage.push_back(new Rect{});
	//_stage.back()->Scale(scale_offset);
	//_stage.back()->Move(vec3::back(move_offset));

	for (auto iter = ++_stage.begin(); iter != _stage.end(); ++iter)
	{
		(*iter)->Move(vec3::up(0.5f));
	}
}

void GameScene::RenderObject(std::vector<Object*>* object)
{
	for (auto& obj : *object)
	{
		auto shader{ obj->GetShader() };

		shader->Use();
		obj->BindVAO();

		obj->Transform();
		ViewProjection(shader);

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::MoveRobot(uchar key)
{
	float angle{ 0.f };
	auto pos{ _robot[BODY]->GetPos() };
	auto move_offset{ vec3::zero() };

	switch (key)
	{
		case 'W': FALLTHROUGH
		case 'w':
		{
			if (_direction == DIRECTION::LEFT)
				angle = -90.f;
			else if (_direction == DIRECTION::RIGHT)
				angle = 90.f;
			else if (_direction == DIRECTION::BACK)
				angle = 180.f;

			for (auto& obj : _robot)
			{
				obj->Move(-pos);
				obj->RotateY(angle);
				obj->Move(pos);
			}

			_direction = DIRECTION::FRONT;
			move_offset = vec3::front(0.1f);
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			if (_direction == DIRECTION::RIGHT)
				angle = 180.f;
			else if (_direction == DIRECTION::FRONT)
				angle = 90.f;
			else if (_direction == DIRECTION::BACK)
				angle = -90.f;

			for (auto& obj : _robot)
			{
				obj->Move(-pos);
				obj->RotateY(angle);
				obj->Move(pos);
			}

			_direction = DIRECTION::LEFT;
			move_offset = vec3::left(0.1f);
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			if (_direction == DIRECTION::LEFT)
				angle = 90.f;
			else if (_direction == DIRECTION::RIGHT)
				angle = -90.f;
			else if (_direction == DIRECTION::FRONT)
				angle = 180.f;

			for (auto& obj : _robot)
			{
				obj->Move(-pos);
				obj->RotateY(angle);
				obj->Move(pos);
			}

			_direction = DIRECTION::BACK;
			move_offset = vec3::back(0.1f);
		}
		break;
		case 'D': FALLTHROUGH
		case 'd':
		{
			if (_direction == DIRECTION::LEFT)
				angle = 180.f;
			else if (_direction == DIRECTION::FRONT)
				angle = -90.f;
			else if (_direction == DIRECTION::BACK)
				angle = 90.f;

			for (auto& obj : _robot)
			{
				obj->Move(-pos);
				obj->RotateY(angle);
				obj->Move(pos);
			}

			_direction = DIRECTION::RIGHT;
			move_offset = vec3::right(0.1f);
		}
		break;
	}

	for (auto& obj : _robot)
	{
		obj->Move(move_offset);
	}

	auto new_pos{ _robot[BODY]->GetPos() };
	auto new_move_offset{ vec3::zero() };

	if (new_pos.x < -1.5f)
		new_move_offset = vec3::right(3.f);
	else if (new_pos.x > 1.5f)
		new_move_offset = vec3::left(3.f);
	else if (new_pos.z > 1.5f)
		new_move_offset = vec3::front(3.f);
	else if (new_pos.z < -1.5f)
		new_move_offset = vec3::back(3.f);

	for (auto& obj : _robot)
	{
		obj->Move(new_move_offset);
	}
}

void GameScene::Jump()
{
	auto pos{ _robot[BODY]->GetPos().y };

	if (pos < _jump_pos)
	{
		_stop_animation = true;

		for (auto& obj : _robot)
		{
			obj->Move(vec3::up(_jump_pos - pos));
		}

		return;
	}

	for (auto& obj : _robot)
	{
		obj->Move(vec3::up(_jump_speed * _delta_time * 2.f));
	}

	_jump_speed -= _gravity * _delta_time * 2.f;
}

void GameScene::Orbit()
{
	auto pos{ _camera->GetPos() };
	float radius{ Convert::ToFloat(std::sqrt((pos.x * pos.x) + (pos.z * pos.z))) };
	float x{ std::sin(_camera_angle) * radius };
	float z{ std::cos(_camera_angle) * radius };

	_camera->RotateY(1.f);
	_camera->SetPos(x, pos.y, z);

	_camera_angle -= 0.0175f;
}

void GameScene::Reset()
{
	OnRelease();

	_camera = std::make_unique<Camera>(glm::vec3{ 0.f, 0.f, 4.f });
	_camera_angle = 0.f;

	CreateRobot();
	CreateStage();

	OnLoad();
}

void GameScene::OnAnimate(int32_t value)
{
	Jump();

	if (_stop_animation == false)
	{
		glutTimerFunc(10, Engine::OnAnimate, value);
	}
}
