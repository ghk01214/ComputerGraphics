#pragma once
#include "ring.h"

template<typename T>
ring<T>::ring() : _read_index{ 0 }, _back_write_index{ 0 }, _front_write_index{ 0 }, _count{ 0 }
{
	_cont.fill(std::make_pair(T{ INFINITE, INFINITE , INFINITE }, false));
	_p = _cont.data();
}

template<typename T>
ring<T>::ring(std::initializer_list<value_type> list) : _read_index{ 0 }, _back_write_index{ 0 }, _front_write_index{ 0 }, _count{ 0 }
{
	_cont.fill(std::make_pair({ INFINITE, INFINITE , INFINITE }, false));
	_p = _cont.data();

	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		push_back(*iter);
	}
}

template<typename T>
constexpr ring<T>& ring<T>::operator=(std::initializer_list<value_type> list)
{
	auto beg{ begin() };
	auto en{ end() };

	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		if (beg == en)
		{
			do
			{
				push_back(*iter);
				++iter;
			} while (iter != list.end());
		}

		*beg = *iter;
		++beg;
	}

	size_type c{ static_cast<size_type>(en - beg) };

	for (; 0 < c; --c)
	{
		pop_front();
	}
}

template<typename T>
bool ring<T>::operator==(const std::pair<value_type, bool>& right)
{
	for (int i = 0; i < max_size(); ++i)
	{
		if (_cont[i].second == true and right.second == true)
		{
			if (_cont[i].first == right.first)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

template<typename T>
bool ring<T>::operator!=(const std::pair<value_type, bool>& right)
{
	for (int i = 0; i < max_size(); ++i)
	{
		if (_cont[i].second == true and right.second == true)
		{
			if (_cont[i].first == right.first)
				return false;
			else
				return true;
		}
		else
			return true;
	}
}

template<typename T>
void ring<T>::push_back(value_type value)
{
	if (_count == max_size())
		// throw error
		return;

	if (_back_write_index > max_size() - 1)
		_back_write_index = 0;

	_cont[_back_write_index++] = std::make_pair(value, true);

	++_count;
}

template<typename T>
void ring<T>::push_back(std::initializer_list<value_type> list)
{
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		push_back(*iter);
	}
}

template<typename T>
void ring<T>::push_front(value_type value)
{
	if (_count == max_size())
		// throw error
		return;

	int i{ 0 };

	if (_read_index > 0)
	{
		if (_read_index == _front_write_index)
		{
			_front_write_index = 0;
			i = ++_back_write_index;
		}
		else if (_front_write_index == 0)
		{
			_cont[0] = std::make_pair(value, true);
			++_front_write_index;
			++_count;

			return;
		}
		else
		{
			for (i = _front_write_index; i > 0; --i)
			{
				_cont[i] = _cont[i - 1];
			}

			_cont[0] = std::make_pair(value, true);

			++_front_write_index;
			++_count;

			return;
		}
	}
	else if (_read_index == 0)
	{
		i = ++_back_write_index;
	}

	for (; i > 0; --i)
	{
		_cont[i] = _cont[i - 1];
	}

	_cont[0] = std::make_pair(value, true);

	++_count;
}

template<typename T>
void ring<T>::push_front(std::initializer_list<value_type> list)
{
	for (auto iter = --list.end(); iter != list.begin(); --iter)
	{
		push_front(*iter);
	}
}

template<typename T>
ring<T>::value_type ring<T>::pop_back()
{
	if (_count == 0)
		// throw error
		return T{};

	value_type value;

	for (int i = max_size() - 1; i >= 0; --i)
	{
		if (_cont[i].second == true)
		{
			value = _cont[i].first;
			_cont[i] = std::make_pair(T{ INFINITE, INFINITE, INFINITE }, false);
			--_back_write_index;
			--_count;

			break;
		}
	}

	return value;
}

template<typename T>
ring<T>::value_type ring<T>::pop_front()
{
	if (_count == 0)
		// throw error
		return T{};

	value_type value;

	for (int i = 0; i < max_size(); ++i)
	{
		if (_cont[i].second == true)
		{
			value = _cont[i].first;
			_cont[i] = std::make_pair(T{ INFINITE, INFINITE, INFINITE }, false);
			++_read_index;
			--_count;

			break;
		}
	}

	return value;
}

template<typename T>
void ring<T>::clear() noexcept
{
	_cont.fill(std::make_pair(T{ INFINITE, INFINITE , INFINITE }, false));

	_read_index = 0;
	_front_write_index = 0;
	_back_write_index = 0;
	_count = 0;
}

template<typename T>
void ring<T>::align()
{
	std::pair<value_type, bool> temp;

	for (int32 i = 0; i < max_size(); ++i)
	{
		for (int32 j = 0; j < max_size() - 1 - i; ++j)
		{
			if ((_cont[j].second == true && _cont[j + 1].second == false) ||
				(_cont[j].second == false && _cont[j + 1].second == true))
			{
				temp = _cont[j];
				_cont[j] = _cont[j + 1];
				_cont[j + 1] = temp;
			}
		}
	}
}
