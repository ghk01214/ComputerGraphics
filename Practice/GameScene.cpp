#include "pch.h"
#include "Triangle.h"
#include "CameraMgr.h"
#include "GameScene.h"

enum
{
	NONE = 0,
	C_LT,
	C_RT,
	C_LB,
	C_RB,
	CC_LT,
	CC_RT,
	CC_LB,
	CC_RB,
	MAX
};

extern Window window;
std::uniform_int_distribution<int32_t> uid_direction{ C_LT, CC_RB };
std::uniform_int_distribution<int32_t> uid_time{ 1, 4 };

std::shared_ptr<GameScene> GameScene::_inst{ nullptr };

GameScene::GameScene() :
	_camera{},
	_tri{},
	_index{},
	_type{ GL_TRIANGLES }
{
	_tri.push_back(Triangle{ glm::vec3{ -0.5f, 0.5f, 0.f } });
	_tri.push_back(Triangle{ glm::vec3{ 0.5f, 0.5f, 0.f } });
	_tri.push_back(Triangle{ glm::vec3{ 0.5f, -0.5f, 0.f } });
	_tri.push_back(Triangle{ glm::vec3{ -0.5f, -0.5f, 0.f } });

	_inst.reset(this);
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	for (int32_t i = 0; i < _tri.size(); ++i)
	{
		_tri[i].OnLoad();
	}
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'A': FALLTHROUGH
		case 'a':
			_type = GL_LINE_LOOP;
			break;
		case 'B': FALLTHROUGH
		case 'b':
			_type = GL_TRIANGLES;
			break;
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		if (_index >= _tri.size())
			_index = 0;

		_tri[_index++].Teleport(x2, y2, 0.f);
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& tri : _tri)
	{
		tri.BindVAO();

		tri.Transform();
		//CameraMgr::ViewTransform(tri.GetShader());
		//CameraMgr::ProjectionTransform(tri.GetShader());

		glDrawElements(_type, tri.GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}
