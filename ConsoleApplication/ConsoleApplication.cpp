#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <memory>
using namespace std;

class Monster
{
public:
	Monster(const string& _name) : m_Name(_name) {}

	string GetName() { return m_Name; }

protected:
	string m_Name;
};



class Kinght
{
public:
	Kinght() = default;

private:
	weak_ptr<Monster> m_Target;
};

int main()
{	
	

	return 0;
}