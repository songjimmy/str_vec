#pragma once
#include <utility>
#include <memory>
#include <string>
class vec_str
{
public:
	vec_str() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	vec_str(const std::initializer_list<std::string>& L);
	vec_str(const vec_str& V);
	~vec_str();
	vec_str& operator=(const vec_str& V);
	bool empty() { return first_free == elements; }
	size_t size()const { return first_free - elements; }
	size_t capacity()const { return cap - elements; }
	std::string* begin() { return elements; }
	std::string* end() { return first_free; }
	void push_back(std::string str);
	void pop_back();
	void print();
private:
	static std::allocator<std::string> allocator_str;
	std::string* elements;
	std::string* first_free;
	std::string* cap;
	std::pair<std::string* ,std::string* > allocate_n_copy(std::string* ,std::string*);
	void reallocate();//尝试分配大小为两倍的空间，并将原容器中的内容拷贝进去，如果分配不了，抛出一个异常
	void free();//清空所分配的内存空间
	void check() { if (size() == capacity()) reallocate(); }//检查当再插入一个元素时已分配的内存空间够不够
};
	