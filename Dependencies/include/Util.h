﻿#pragma once

template<typename T>
concept IsPrimary = requires
{
	std::is_arithmetic_v<T>;
	std::is_enum_v<T>;
};

template<typename T>
concept IsPointer = requires
{
	std::is_pointer_v<T>;
	std::is_member_pointer_v<T>;
	not std::is_null_pointer_v<T>;
};

namespace Util
{
	template<class T>
	bool CheckSame(T& container, int index_0, int index_1, int count);
	bool ReadFile(const std::string& path, std::string* blob);
	std::string ReadFile(const std::string& path);
	bool ReadModel(const std::string& path, std::vector<float>* vertex, std::vector<float>* normal, std::vector<float>* texture, std::vector<uint32_t>* index, int32_t* vertex_num, int32_t* index_num);

	template<typename T> requires std::is_floating_point_v<T>
	inline bool IsEqual(T a, T b) { return std::abs(a - b) < 0.000001f or std::abs(b - a) < 0.000001f; }

	template<typename T> requires IsPointer<T>
	inline void ReleasePtr(T pointer)
	{
		delete pointer;
		pointer = nullptr;
	}

	template<typename T> requires requires { IsPointer<T>; std::is_array_v<T>; }
	inline void ReleasePtr(T pointer)
	{
		for (int32_t i = 0; i < _countof(pointer); ++i)
		{
			delete pointer[i];
			pointer[i] = nullptr;
		}

		delete[] pointer;
		pointer = nullptr;
	}
}

namespace Convert
{
	template<typename T, typename U> requires IsPrimary<T>
	inline T ChangeTo(U value) { return static_cast<T>(value); }

	template<typename T, typename U>
	inline T* ToPointer(U pointer) { return reinterpret_cast<T*>(pointer); }

#pragma region [CHAR]
	template<typename T> requires IsPrimary<T>
	inline char ToChar(T value) { return static_cast<char>(value); }
	template<typename T> requires IsPrimary<T>
	inline unsigned char ToUchar(T value) { return static_cast<unsigned char>(value); }

	template<typename T> requires IsPointer<T>
	inline char* ToCharP(T value) { return reinterpret_cast<char*>(value); }
	template<typename T> requires IsPointer<T>
	inline unsigned char* ToUcharP(T value) { return reinterpret_cast<unsigned char*>(value); }
#pragma endregion

#pragma region [INT8]
	template<typename T> requires IsPrimary<T>
	inline int8_t ToInt8(T value) { return static_cast<int8_t>(value); }
	template<typename T> requires IsPrimary<T>
	inline uint8_t ToUint8(T value) { return static_cast<uint8_t>(value); }

	template<typename T> requires IsPointer<T>
	inline int8_t* ToInt8P(T value) { return reinterpret_cast<int8_t*>(value); }
	template<typename T> requires IsPointer<T>
	inline uint8_t* ToUint8P(T value) { return reinterpret_cast<uint8_t*>(value); }
#pragma endregion

#pragma region [INT16]
	template<typename T> requires IsPrimary<T>
	inline int16_t ToInt16(T value) { return static_cast<int16_t>(value); }
	template<typename T> requires IsPrimary<T>
	inline uint16_t ToUint16(T value) { return static_cast<uint16_t>(value); }

	template<typename T> requires IsPointer<T>
	inline int16_t* ToInt16P(T value) { return reinterpret_cast<int16_t*>(value); }
	template<typename T> requires IsPointer<T>
	inline uint16_t* ToUint16P(T value) { return reinterpret_cast<uint16_t*>(value); }
#pragma endregion

#pragma region [INT32]
	template<typename T> requires IsPrimary<T>
	inline int32_t ToInt32(T value) { return static_cast<int32_t>(value); }
	template<typename T> requires IsPrimary<T>
	inline uint32_t ToUint32(T value) { return static_cast<uint32_t>(value); }

	template<typename T> requires IsPointer<T>
	inline int32_t* ToInt32P(T value) { return reinterpret_cast<int32_t*>(value); }
	template<typename T> requires IsPointer<T>
	inline uint32_t* ToUint32P(T value) { return reinterpret_cast<uint32_t*>(value); }
#pragma endregion

#pragma region [INT64]
	template<typename T> requires IsPrimary<T>
	inline int64_t ToInt64(T value) { return static_cast<int64_t>(value); }
	template<typename T> requires IsPrimary<T>
	inline uint64_t ToUint64(T value) { return static_cast<uint64_t>(value); }

	template<typename T> requires IsPointer<T>
	inline int64_t* ToInt64P(T value) { return reinterpret_cast<int64_t*>(value); }
	template<typename T> requires IsPointer<T>
	inline uint64_t* ToUint64P(T value) { return reinterpret_cast<uint64_t*>(value); }
#pragma endregion

#pragma region [FLOAT]
	template<typename T> requires IsPrimary<T>
	inline float ToFloat(T value) { return static_cast<float>(value); }
	template<typename T> requires IsPrimary<T>
	inline double ToDouble(T value) { return static_cast<double>(value); }

	template<typename T> requires IsPointer<T>
	inline float* ToFloatP(T value) { return reinterpret_cast<float*>(value); }
	template<typename T> requires IsPointer<T>
	inline double* ToDoubleP(T value) { return reinterpret_cast<double*>(value); }
#pragma endregion
}
