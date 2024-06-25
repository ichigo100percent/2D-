#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

//template <typename T>
//class Singleton
//{
//public:
//	static T& Instance()
//	{
//		static T ret;
//		return ret;
//	}
//};
//
//template <typename T, typename S>
//class BaseMgr : public Singleton<S>
//{
//public:
//	BaseMgr() {}
//	virtual ~BaseMgr() {}
//
//	void Insert(const int& _num)
//	{
//		m_Map.insert(_num, make_shared<T>());
//	}
//
//	shared_ptr<T> GetPtr(const int& _num)
//	{
//		auto find = m_Map.find(_num);
//
//		if (find == m_Map.end())
//			return nullptr;
//
//		return (*find).second;
//	}
//
//protected:
//		map<int, shared_ptr<T>> m_Map;
//};
//
//class Person
//{
//public:
//	Person() = default;
//	Person(const string& _name) : m_Name(_name) {}
//
//	string GetName() { return m_Name; }
//
//private:
//	string m_Name;
//};
//
//class PersonMgr : public BaseMgr<Person, PersonMgr>
//{
//
//};

class B; // B 클래스가 있다는걸 알림!

class A {
private:
	int adata;
public:
	A(int _data)
	{
		adata = _data;
	}
	void ShowData(B b);

	friend class B;
};

class B {
private:
	int bdata;
public:
	B(int _data)
	{
		bdata = _data;
	}
	void ShowData(A a)
	{
		cout << "a.data: " << a.adata << endl;
	}
	friend class A;
};

void A::ShowData(B b)
{
	cout << "b.data: " << b.bdata << endl;
}
int main()
{
	A a(10);
	B b(20);

	a.ShowData(b);
	b.ShowData(a);
	return 0;
}