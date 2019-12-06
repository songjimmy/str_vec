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
	void reallocate();//���Է����СΪ�����Ŀռ䣬����ԭ�����е����ݿ�����ȥ��������䲻�ˣ��׳�һ���쳣
	void free();//�����������ڴ�ռ�
	void check() { if (size() == capacity()) reallocate(); }//��鵱�ٲ���һ��Ԫ��ʱ�ѷ�����ڴ�ռ乻����
};
	