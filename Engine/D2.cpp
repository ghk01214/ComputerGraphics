﻿#include "pch.h"
#include "D2.h"

void D2::OnLoad()
{
	Object::OnLoad();

	_mesh->CreateVertex2(_shader);
}
