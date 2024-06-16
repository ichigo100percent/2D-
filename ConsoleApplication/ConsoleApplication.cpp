#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Person
{
public:
	void SetName(string& _name) { m_Name = _name; }
	string& GetName() { return m_Name; }
	void SetAge(const int& _age) { m_Age = _age; }
	int& GetAge() { return m_Age; }

private:
	string m_Name;
	int m_Age;
};

int main()
{

	Person p1;
	int a = 100;

	p1.SetAge(a);

	return 0;
}