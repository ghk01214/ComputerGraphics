#pragma once
#include <array>
#include <utility>

#define INFINITE 0xffffff

// 링 버퍼
template<typename T>
class ring_iterator
{
private:
	using size_type = size_t;
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;

	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_reference = const value_type&;

public:
	ring_iterator() = default;
	ring_iterator(pointer _p) : _p{ _p } {}

	ring_iterator operator+(int n) const noexcept { return ring_iterator{ _p + n }; }
	ring_iterator operator-(int n) const noexcept { return ring_iterator{ _p - n }; }
	int operator-(const ring_iterator& right) const noexcept { return _p - right._p; }

	ring_iterator& operator++() noexcept { ++_p; return *this; }
	ring_iterator& operator--() noexcept { --_p; return *this; }

	const_reference operator*() const noexcept { return *_p; }
	pointer operator->() const noexcept { return **_p; }

	bool operator==(const ring_iterator& right) noexcept { return _p == right._p; }
	bool operator!=(const ring_iterator& right) noexcept { return _p != right._p; }

	bool operator<(const ring_iterator& right) noexcept { return _p < right._p; }
	bool operator>(const ring_iterator& right) noexcept { return _p > right._p; }

protected:
	pointer _p;
};

template<typename T>
class ring_const_iterator
{
private:
	using size_type = size_t;
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;

	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_reference = const value_type&;

public:
	ring_const_iterator() = default;
	ring_const_iterator(pointer _p) : _p{ _p } {}

	ring_const_iterator operator+(int n) const noexcept { return ring_const_iterator{ _p + n }; }
	ring_const_iterator operator-(int n) const noexcept { return ring_const_iterator{ _p - n }; }
	int operator-(const ring_const_iterator& right) const noexcept { return _p - right._p; }

	ring_const_iterator& operator++() noexcept { ++_p; return *this; }
	ring_const_iterator& operator--() noexcept { --_p; return *this; }

	const_reference operator*() const noexcept { return *_p; }
	pointer operator->() const noexcept { return **this; }

	bool operator==(const ring_const_iterator& right) const noexcept { return _p == right._p; }
	bool operator!=(const ring_const_iterator& right) const noexcept { return _p != right._p; }

	bool operator<(const ring_const_iterator& right) const noexcept { return _p < right._p; }
	bool operator>(const ring_const_iterator& right) const noexcept { return _p > right._p; }

protected:
	pointer _p;
};

template<typename T>
class ring_reverse_iterator
{
private:
	using size_type = size_t;
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;

	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_reference = const value_type&;

public:
	ring_reverse_iterator(pointer _p) : _p{ _p } {}

	ring_reverse_iterator operator+(int n) const noexcept { return ring_reverse_iterator{ _p - n }; }
	ring_reverse_iterator operator-(int n) const noexcept { return ring_reverse_iterator{ _p + n }; }
	int operator-(const ring_reverse_iterator& right) const noexcept { return _p + right._p; }

	const_reference operator*() const noexcept { return *(_p - 1); }
	pointer operator->() const noexcept { return **(_p - 1); }

	ring_reverse_iterator& operator++() noexcept { --_p; return *this; }
	ring_reverse_iterator& operator--() noexcept { ++_p; return *this; }

private:
	pointer _p;
};

template<typename T>
class ring_const_reverse_iterator : public ring_const_iterator<T>
{
private:
	using size_type = size_t;
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;

	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_reference = const value_type&;

public:
	ring_const_reverse_iterator(pointer _p) : _p{ _p } {}

	ring_const_reverse_iterator operator+(int n) const noexcept { return ring_const_reverse_iterator{ _p - n }; }
	ring_const_reverse_iterator operator-(int n) const noexcept { return ring_const_reverse_iterator{ _p + n }; }
	int operator-(const ring_const_reverse_iterator& right) const noexcept { return _p + right._p; }

	const_reference operator*() const noexcept { return *(_p - 1); }
	pointer operator->() const noexcept { return **(_p - 1); }

	ring_const_reverse_iterator& operator++() noexcept { --_p; return *this; }
	ring_const_reverse_iterator& operator--() noexcept { ++_p; return *this; }
private:
	pointer _p;
};

template<typename T>
class ring
{
private:
	using value_type = T;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const pointer;
	using reference = value_type&;
	using const_reference = const reference;

	using iterator = ring_iterator<std::pair<value_type, bool>>;
	using const_iterator = ring_const_iterator<std::pair<value_type, bool>>;
	using reverse_iterator = ring_reverse_iterator<std::pair<value_type, bool>>;
	using const_reverse_iterator = ring_const_reverse_iterator<std::pair<value_type, bool>>;

public:
	ring();
	ring(std::initializer_list<value_type> list);

	constexpr ring& operator=(std::initializer_list<value_type> list);
	constexpr std::pair<value_type, bool>& operator[](size_type pos) { return *(_p + pos); }
	constexpr std::pair<value_type, bool>& operator[](size_type pos) const { return *(_p + pos); }

	bool operator==(const std::pair<value_type, bool>& right);
	bool operator!=(const std::pair<value_type, bool>& right);

	constexpr pointer data() noexcept { return _p; }
	constexpr const pointer data() const noexcept { return _p; }

	constexpr const_reference front() noexcept { return *begin(); }
	constexpr const_reference front() const noexcept { return *cbegin(); }
	constexpr const_reference back() noexcept { return *(--end()); }
	constexpr const_reference back() const noexcept { return *(--cend()); }

	constexpr iterator begin() noexcept { return iterator{ _p }; }
	constexpr iterator end() noexcept { return iterator{ _p + _count }; }
	constexpr reverse_iterator rbegin() noexcept { return reverse_iterator{ _p + _count }; }
	constexpr reverse_iterator rend() noexcept { return reverse_iterator{ _p }; }

	constexpr const_iterator cbegin() const noexcept { return const_iterator{ _p }; }
	constexpr const_iterator cend() const noexcept { return const_iterator{ _p + _count }; }
	constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{ _p + _count }; }
	constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator{ _p }; }

	void push_back(value_type value);
	void push_back(std::initializer_list<value_type> list);

	void push_front(value_type value);
	void push_front(std::initializer_list<value_type> list);

	value_type pop_back();
	value_type pop_front();

	bool empty() const noexcept { return _read_index == _back_write_index; }
	bool is_empty(int i) const noexcept { return _cont[i].second; }
	size_type size() const noexcept { return _count; }
	size_type max_size() const noexcept { return 10; }
	void clear() noexcept;

	void align();

private:
	std::array<std::pair<value_type, bool>, 10> _cont;
	std::pair<value_type, bool>* _p;

	int _count;

	int _front_write_index;
	int _read_index;
	int _back_write_index;
};

#include "ring.hpp"


