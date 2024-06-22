#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <memory>

using namespace std;

class Test
{
public:
	bool test(Test& _a)
	{
		return true;
	}

};

int main()
{
	Test t1;
	auto t2 = make_shared<Test>();

	t1.test(*t2.get());

	return 0;
}