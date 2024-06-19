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

using namespace std;

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

class Resource
{
public:
    virtual void Load(const string& _name) = 0;
};

template <class T, class S>
class BaseMgr : public Singleton<S>
{
protected:
    shared_ptr<T> GetPtr(const string& _name)
    {
        auto iter = m_List.find(_name);
        if (iter != m_List.end())
            return iter->second;

        return nullptr;
    }

    virtual shared_ptr<T> Load(const string& _name)
    {
        auto findData = GetPtr(_name);
        if (findData != nullptr)
            return findData;

        auto newData = make_shared<T>(_name);
        m_List.insert(make_pair(_name, newData));

        return newData;
    }

protected:
    BaseMgr() {}
    virtual ~BaseMgr() {}

protected:
    map<string, shared_ptr<T>> m_List;
};

class Person : public Resource
{
public:
    Person(const string& _name) : m_Name(_name) {}

    void Load(const string& _name) override
    {
        m_Name = _name;
    }

public:
    string m_Name;
};

class PersonMgr : public BaseMgr<Person, PersonMgr>
{
    friend class Singleton<PersonMgr>;

public:
    shared_ptr<Person> LoadPerson(const string& _name)
    {
        return Load(_name);
    }

private:
    PersonMgr() {}
};

int main()
{
    auto& personMgr = PersonMgr::Instance();
    auto person1 = personMgr.LoadPerson("John Doe");

    cout << "Loaded person: " << person1->m_Name << endl;

    return 0;
}