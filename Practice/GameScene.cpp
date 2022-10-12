#include "pch.h"
#include "Triangle.h"
#include "CameraMgr.h"
#include "GameScene.h"

enum
{
	NONE = 0,
	C_LEFT,
	C_TOP,
	C_RIGHT,
	C_BOTTOM,
	CC_LEFT,
	CC_TOP,
	CC_RIGHT,
	CC_BOTTOM,
	MAX
};

extern Window window;
std::uniform_int_distribution<int32_t> uid_time{ 1, 4 };
std::uniform_real_distribution<float> uid_posx{ -1.f, 1.f };
std::uniform_real_distribution<float> uid_posy{ -1.f, -0.5f };

std::shared_ptr<GameScene> GameScene::_inst{ nullptr };

GameScene::GameScene() :
	_camera{},
	_tri{},
	_index{},
	_type{ GL_TRIANGLES },
	_info{}
{
	_tri.push_back(new Triangle{ glm::vec3{ uid_posx(dre), uid_posy(dre), 0.f} });
	_tri.push_back(new Triangle{ glm::vec3{ uid_posx(dre), uid_posy(dre), 0.f} });
	_tri.push_back(new Triangle{ glm::vec3{ uid_posx(dre), uid_posy(dre), 0.f} });
	_tri.push_back(new Triangle{ glm::vec3{ uid_posx(dre), uid_posy(dre), 0.f} });

	_inst.reset(this);
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	for (int32_t i = 0; i < _tri.size(); ++i)
	{
		_tri[i]->OnLoad();

		if (uid_time(dre) % 2 == 0)
			_info.insert(std::make_pair(_tri[i], std::make_pair(uid_time(dre), C_LEFT)));
		else
			_info.insert(std::make_pair(_tri[i], std::make_pair(uid_time(dre), CC_RIGHT)));


		glutTimerFunc(_info[_tri[i]].first * 10, Animate, i);
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

		_tri[_index++]->Teleport(x2, y2, 0.f);
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& tri : _tri)
	{
		tri->GetShader()->Use();
		tri->BindVAO();

		tri->Transform();
		//CameraMgr::ViewTransform(tri->GetShader());
		//CameraMgr::ProjectionTransform(tri->GetShader());

		glDrawElements(_type, tri->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::Animate(int32_t value)
{
	_inst->Moving(value);
	glutTimerFunc(_inst->_info[_inst->_tri[value]].first * 10, Animate, value);
}

void GameScene::Moving(int32_t index)
{
	auto triangle{ dynamic_cast<Triangle*>(_tri[index]) };
	int32_t angle{ (Convert::ToInt32(triangle->GetAngle().z) / 90) % 4 };

	switch (_info[triangle].second)
	{
		case C_LEFT:
		{
			if (triangle->GetPos().x < -0.9f)
			{
				_info[triangle].second = C_TOP;
				triangle->SetPos(glm::vec3{ -0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(-90.f);

				break;
			}

			if (triangle->GetPos().y > 0.9f)
			{
				_info[triangle].second = C_RIGHT;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, 0.9f, 0.f });
				triangle->RotateZ(-180.f);

				break;
			}

			triangle->Move(-0.01f, 0.01f, 0.f);
		}
		break;
		case C_TOP:
		{
			if (triangle->GetPos().y > 0.9f)
			{
				_info[triangle].second = C_RIGHT;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, 0.9f, 0.f });
				triangle->RotateZ(-90.f);

				break;
			}

			if (triangle->GetPos().x > 0.9f)
			{
				_info[triangle].second = C_BOTTOM;
				triangle->SetPos(glm::vec3{ 0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(-180.f);

				break;
			}

			triangle->Move(0.01f, 0.01f, 0.f);
		}
		break;
		case C_RIGHT:
		{
			if (triangle->GetPos().x > 0.9f)
			{
				_info[triangle].second = C_BOTTOM;
				triangle->SetPos(glm::vec3{ 0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(-90.f);

				break;
			}

			if (triangle->GetPos().y < -0.9f)
			{
				_info[triangle].second = C_LEFT;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, -0.9f, 0.f });
				triangle->RotateZ(-180.f);

				break;
			}

			triangle->Move(0.01f, -0.01f, 0.f);
		}
		break;
		case C_BOTTOM:
		{
			if (triangle->GetPos().y < -0.9f)
			{
				_info[triangle].second = C_LEFT;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, -0.9f, 0.f });
				triangle->RotateZ(-90.f);

				break;
			}

			if (triangle->GetPos().x < -0.9f)
			{
				_info[triangle].second = C_TOP;
				triangle->SetPos(glm::vec3{ -0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(-180.f);

				break;
			}

			triangle->Move(-0.01f, -0.01f, 0.f);
		}
		break;
		case CC_LEFT:
		{
			if (triangle->GetPos().y > 0.9f)
			{
				_info[triangle].second = CC_BOTTOM;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, 0.9f, 0.f });
				triangle->RotateZ(90.f);

				break;
			}

			if (triangle->GetPos().x < -0.9f)
			{
				_info[triangle].second = CC_RIGHT;
				triangle->SetPos(glm::vec3{ -0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(180.f);

				break;
			}

			triangle->Move(-0.01f, 0.01f, 0.f);
		}
		break;
		case CC_TOP:
		{
			if (triangle->GetPos().x > 0.9f)
			{
				_info[triangle].second = CC_LEFT;
				triangle->SetPos(glm::vec3{ 0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(90.f);

				break;
			}

			if (triangle->GetPos().y > 0.9f)
			{
				_info[triangle].second = CC_BOTTOM;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, 0.9f, 0.f });
				triangle->RotateZ(180.f);

				break;
			}

			triangle->Move(0.01f, 0.01f, 0.f);
		}
		break;
		case CC_RIGHT:
		{
			if (triangle->GetPos().y < -0.9f)
			{
				_info[triangle].second = CC_TOP;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, -0.9f, 0.f });
				triangle->RotateZ(90.f);

				break;
			}

			if (triangle->GetPos().x > 0.9f)
			{
				_info[triangle].second = CC_LEFT;
				triangle->SetPos(glm::vec3{ 0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(180.f);

				break;
			}

			triangle->Move(0.01f, -0.01f, 0.f);
		}
		break;
		case CC_BOTTOM:
		{
			if (triangle->GetPos().x < -0.9f)
			{
				_info[triangle].second = CC_RIGHT;
				triangle->SetPos(glm::vec3{ -0.9f, triangle->GetPos().y, 0.f });
				triangle->RotateZ(90.f);

				break;
			}

			if (triangle->GetPos().y < -0.9f)
			{
				_info[triangle].second = CC_TOP;
				triangle->SetPos(glm::vec3{ triangle->GetPos().x, -0.9f, 0.f });
				triangle->RotateZ(180.f);

				break;
			}

			triangle->Move(-0.01f, -0.01f, 0.f);
		}
		break;
	}

	triangle->GetMesh()->SetUp(triangle->GetShader());
	//std::cout << triangle->GetPos().x << ", " << triangle->GetPos().y << std::endl;

	glutPostRedisplay();
}
