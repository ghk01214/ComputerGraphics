// stdafx.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#pragma region [MACRO]
#define _DOUBLE_SLASH /##/

#ifdef _DEBUG
#define __D
#define __R _DOUBLE_SLASH
#else
#define __D _DOUBLE_SLASH
#define __R
#endif
#pragma endregion

#pragma region [HEADER]
#pragma region [C++]
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <ranges>
#pragma endregion

#pragma region [CONTAINER]
#include <array>
#include <vector>
//#include <deque>
//#include <list>
//#include <unordered_set>
#include <unordered_map>
#pragma endregion

#pragma region [LIB]
#ifdef _M_X64
#pragma comment(lib, "../Dependencies/lib/freeglut")
#pragma comment(lib, "../Dependencies/lib/glew32")
#pragma comment(lib, "../Dependencies/lib/glew32s")
#else
#pragma comment(lib, "../Dependencies/lib/x86/freeglut")
#pragma comment(lib, "../Dependencies/lib/x86/glew32")
#pragma comment(lib, "../Dependencies/lib/x86/glew32s")
#endif

#pragma region [GL]
#include "../Dependencies/glew.h"
#include "../Dependencies/freeglut.h"
#include "../Dependencies/freeglut_ext.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/ext.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#pragma endregion
#pragma endregion

#endif //PCH_H
