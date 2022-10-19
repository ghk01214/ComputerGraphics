#include "pch.h"
#include "D3.h"

void D3::OnLoad()
{
	Object::OnLoad();

	_mesh->CreateModel(_shader);
}
