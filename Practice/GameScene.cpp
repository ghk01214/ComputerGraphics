#include "pch.h"
#include "Figure.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ Convert::ToUint32(CUBE::LEFT) },
	_cube_face{},
	_tetra_face{},
	_rendered{ 2 }
{
	_object.push_back(new Line{ vec3::zero(), 5.f });
	_object.push_back(new Line{ vec3::zero(), 5.f, false });
	_object.push_back(new Cube{});
	_object.push_back(new Tetraherdon{});

	_object[2]->RotateY(45.f);
	_object[2]->RotateX(30.f);
	_object[3]->RotateY(45.f);
	_object[3]->RotateX(30.f);

	_cube_face.reserve(Convert::ToUint32(CUBE::MAX));
	_tetra_face.reserve(Convert::ToUint32(TETRA::MAX));

#pragma region [CUBE INDEX]
	std::vector<uint32_t> index
	{
		2, 3, 6,
		3, 7, 6
	};
	_cube_face.push_back(index);		// LEFT

	index =
	{
		5, 4, 1,
		4, 0, 1
	};
	_cube_face.push_back(index);		// RIGHT

	index =
	{
		0, 4, 3,
		4, 7, 3
	};
	_cube_face.push_back(index);		// TOP

	index =
	{
		5, 1, 6,
		1, 2, 6
	};
	_cube_face.push_back(index);		// BOTTOM

	index =
	{
		1, 0, 2,
		0, 3, 2
	};
	_cube_face.push_back(index);		// FRONT

	index =
	{
		6, 7, 5,
		7, 4, 5
	};
	_cube_face.push_back(index);		// BACK
#pragma endregion
#pragma region [TETRA INDEX]
	index = { 1, 2, 3 };
	_tetra_face.push_back(index);		// BOTTOM

	index = { 1, 0, 3 };
	_tetra_face.push_back(index);		// FRONT

	index = { 3, 0, 2 };
	_tetra_face.push_back(index);		// LEFT

	index = { 2, 0, 1 };
	_tetra_face.push_back(index);		// RIGHT
#pragma endregion

	_object[2]->SetIndex(&_cube_face[_index]);
	_object[2]->BindIndex();

	std::vector<uint32_t> zero{};
	_object[3]->SetIndex(&zero);
	_object[3]->BindIndex();
}

GameScene::~GameScene()
{
	for (auto& obj : _object)
	{
		delete obj;
	}

	_object.clear();
}

void GameScene::OnLoad()
{
	for (auto& obj : _object)
	{
		obj->OnLoad();
	}
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	auto face{ _cube_face[_index] };

	switch (key)
	{
		case '1':
		{
			_index = Convert::ToUint32(CUBE::LEFT);
			face = _cube_face[_index];
		}
		break;
		case '2':
		{
			_index = Convert::ToUint32(CUBE::RIGHT);
			face = _cube_face[_index];
		}
		break;
		case '3':
		{
			_index = Convert::ToUint32(CUBE::TOP);
			face = _cube_face[_index];
		}
		break;
		case '4':
		{
			_index = Convert::ToUint32(CUBE::BOTTOM);
			face = _cube_face[_index];
		}
		break;
		case '5':
		{
			_index = Convert::ToUint32(CUBE::FRONT);
			face = _cube_face[_index];
		}
		break;
		case '6':
		{
			_index = Convert::ToUint32(CUBE::BACK);
			face = _cube_face[_index];
		}
		break;
		case '7':
		{
			_index = Convert::ToUint32(TETRA::BOTTOM);
			face = _tetra_face[_index];
		}
		break;
		case '8':
		{
			_index = Convert::ToUint32(TETRA::FRONT);
			face = _tetra_face[_index];
		}
		break;
		case '9':
		{
			_index = Convert::ToUint32(TETRA::LEFT);
			face = _tetra_face[_index];
		}
		break;
		case '0':
		{
			_index = Convert::ToUint32(TETRA::RIGHT);
			face = _tetra_face[_index];
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			face = _cube_face[Convert::ToUint32(CUBE::LEFT)];
			
			for (auto& index : _cube_face[Convert::ToUint32(CUBE::RIGHT)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'B': FALLTHROUGH
		case 'b':
		{
			face = _cube_face[Convert::ToUint32(CUBE::TOP)];

			for (auto& index : _cube_face[Convert::ToUint32(CUBE::BOTTOM)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
			face = _cube_face[Convert::ToUint32(CUBE::FRONT)];

			for (auto& index : _cube_face[Convert::ToUint32(CUBE::BACK)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'E': FALLTHROUGH
		case 'e':
		{
			face = _tetra_face[Convert::ToUint32(TETRA::BOTTOM)];

			for (auto& index : _tetra_face[Convert::ToUint32(TETRA::FRONT)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'F': FALLTHROUGH
		case 'f':
		{
			face = _tetra_face[Convert::ToUint32(TETRA::BOTTOM)];

			for (auto& index : _tetra_face[Convert::ToUint32(TETRA::LEFT)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'G': FALLTHROUGH
		case 'g':
		{
			face = _tetra_face[Convert::ToUint32(TETRA::BOTTOM)];

			for (auto& index : _tetra_face[Convert::ToUint32(TETRA::RIGHT)])
			{
				face.push_back(index);
			}
		}
		break;
		case 'Q': FALLTHROUGH
		case 'q':
		break;
		default:
			std::cout << std::format("Keyboard default") << std::endl;
			break;
	}

	std::vector<uint32_t> zero{};

	if (('1' <= key and key <= '6') or
		('A' <= key and key <= 'C') or
		('a' <= key and key <= 'c'))
	{
		_object[2]->SetIndex(&face);
		_object[2]->BindIndex();

		_object[3]->SetIndex(&zero);
		_object[3]->BindIndex();

		_rendered = 2;
	}
	else if (('7' <= key and key <= '9') or
		('E' <= key and key <= 'G') or
		('e' <= key and key <= 'g') or
		key == '0')
	{
		_object[2]->SetIndex(&zero);
		_object[2]->BindIndex();

		_object[3]->SetIndex(&face);
		_object[3]->BindIndex();

		_rendered = 3;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			glutTimerFunc(10, Engine::OnAnimate, 2);
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			glutTimerFunc(10, Engine::OnAnimate, 4);
		}
		break;
		case GLUT_KEY_UP:
		{
			glutTimerFunc(10, Engine::OnAnimate, 3);
		}
		break;
		case GLUT_KEY_DOWN:
		{
			glutTimerFunc(10, Engine::OnAnimate, 9);
		}
		break;
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		
	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

}

void GameScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

	}
}

void GameScene::OnRender()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 
	for (auto& obj : _object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(obj->GetShader());
		CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	if (value % 2 == 0)
	{
		if (value == 2)
			_object[_rendered]->RotateY(1.f);
		else if (value == 4)
			_object[_rendered]->RotateY(-1.f);
	}
	else if (value % 3 == 0)
	{
		if (value == 3)
			_object[_rendered]->RotateX(1.f);
		else if (value == 9)
			_object[_rendered]->RotateX(-1.f);
	}

	glutTimerFunc(10, Engine::OnAnimate, value);
}
