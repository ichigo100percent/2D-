#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Entity
{
public:
	Entity() = default;
	Entity(const string& _name)
		: m_Name(_name)
	{
	}

	string GetName() { return m_Name; }

protected:
	string m_Name;
};

class Object : public Entity
{
public:
	Object(const string& _name = {})
		: Entity(_name)
	{

	}

private:
};

int main()
{
	Object obj;

	cout << obj.GetName();
	return 0;
}