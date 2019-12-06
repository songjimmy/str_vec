#include "vec_str.h"
#include <iostream>
using namespace std;
int main()
{
	vec_str v_s;
	size_t i = 0;
	while (i<1000)
	{
		v_s.push_back(to_string(i));
		//cout << "size " << v_s.size() << " capacity " << v_s.capacity() << endl;
		i++;
	}
	auto v_c = v_s;
	vec_str v_cc;
	v_cc = v_s;
	v_cc = v_cc;
	std::string str("1234"), str2("2345");
	vec_str v_l{ str,str2,"1234",{'1','2'} };
	cout << "size " << v_s.size() << " capacity " << v_s.capacity() << endl;
	cout << "size " << v_c.size() << " capacity " << v_c.capacity() << endl;
	cout << "size " << v_cc.size() << " capacity " << v_cc.capacity() << endl;
	cout << "size " << v_l.size() << " capacity " << v_l.capacity() << endl;
	v_cc.push_back("1");
	cout << "size " << v_cc.size() << " capacity " << v_cc.capacity() << endl;
	while (!v_cc.empty())
	{
		v_cc.pop_back();
		//cout << "size " << v_s.size() << " capacity " << v_s.capacity() << endl;
	}
	v_s.print();
	v_c.print();
	v_cc.print();
	

}