#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <array>
#include <string>

using namespace std;

class Parent
{
public:
	Parent(const std::string& _name) : m_Name(_name) {}

	virtual void Func1()
	{
		cout << "Parent Function" << endl;
	}

protected:
	string m_Name = {};
};

class Child : public Parent 
{
public:
	Child(const string& _name) : Parent(_name) {}

	void Func1() override
	{
		cout << "oveeride Child Function" << endl;
	}
};

class Mgr
{
public:

	template <typename T>
	void Creat(const string& _name)
	{

	}


	map<string, shared_ptr<Parent>> m_List = {};
};

int main()
{
	map<int, string> m;

	array<map<int, string>, 6> arr;

	return 0;
}