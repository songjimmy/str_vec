#include "vec_str.h"
#include "iostream"
std::allocator<std::string> vec_str::allocator_str;
vec_str::vec_str(const std::initializer_list<std::string>& L)
{
	auto new_elements = allocator_str.allocate(L.size());
	std::uninitialized_copy(L.begin(), L.end(), new_elements);
	elements = new_elements;
	first_free = elements + L.size();
	cap = first_free;
}
vec_str::vec_str(const vec_str& V)
{
	auto new_pair = allocate_n_copy(V.elements, V.first_free);
	elements = new_pair.first;
	first_free=cap=new_pair.second;
}
vec_str::~vec_str()
{
	free();
}
vec_str& vec_str::operator=(const vec_str& V)
{
	auto new_pair = allocate_n_copy(V.elements, V.first_free);
	free();
	elements = new_pair.first;
	first_free = cap = new_pair.second;
	return *this;
}
void vec_str::push_back(std::string str)
{
	check();
	allocator_str.construct(first_free, str);
	first_free++;
}

void vec_str::pop_back()
{
	if (!empty()) 
	{
		--first_free;
		allocator_str.destroy(first_free );
	}
}

void vec_str::print()
{
	auto iter = begin();
	while (iter<end())
	{
		std::cout << *iter << "\t";
		++iter;
	}
	std::cout << std::endl;
}

std::pair<std::string*, std::string*> vec_str::allocate_n_copy(std::string* b, std::string* e)
{
	size_t copy_size = e - b;
	auto new_elements = allocator_str.allocate(copy_size);
	return { new_elements,std::uninitialized_copy(b, e, new_elements) };//uninitialized_copy直接再已分配未初始化的内存上构造b,e之间的拷贝
}

void vec_str::reallocate()
{
	size_t new_capacity = capacity() * 2+1;
	auto new_elements=allocator_str.allocate(new_capacity);//分配空间
	//copy elements->first_free to new elements. Return NEW elements and first_free 
	auto iter_new = new_elements;
	auto iter = elements;
	while (iter < first_free)
	{
		allocator_str.construct(iter_new,std::move(*iter));
		++iter_new;
		++iter;
	}
	free();
	elements = new_elements;
	first_free = iter_new;
	cap = elements + new_capacity;
}

void vec_str::free()
{
	if (!empty())
	{
		auto str_ptr = elements;
		while (str_ptr < first_free)
		{
			allocator_str.destroy(str_ptr);
			++str_ptr;
		}
		allocator_str.deallocate(elements, capacity());
	}
	elements = nullptr;
	first_free = nullptr;
	cap = nullptr;
}
