#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <array>
#include <string>

using namespace std;


std::map<string, int> m;

bool Add(const string& _key, int _obj)
{
	auto find = m.find(_key);

	if (find != m.end())
	{
		cout << "찾음" << endl;
		return true;
	}

	m[_key] = _obj;
	return false;
}


int main()
{
	Add("ㅎㅇ", 1);
	Add("ㅎㅇ", 2);
	return 0;
}