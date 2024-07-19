/*
	������ ����(Observer Pattern)�� ��ü ���� ���α׷��ֿ��� �θ� ���Ǵ� ������ ���� �� �ϳ��Դϴ�.
	������ �� ��ü�� ���°� ����Ǿ��� �� �� ��ü�� �����ϴ� �ٸ� ��ü�鿡�� �ڵ����� �˸��� ������ ������Ʈ�� �����ϴ� ����� �����մϴ�.
	�ַ� �̺�Ʈ �ڵ鸵 �ý����̳� ��-��-��Ʈ�ѷ�(MVC) �������� ���˴ϴ�.

	������ ������ ���� ���
	Subject (����): ���¸� ������ ������, ���� ���� �� �������鿡�� �˸��� �����ϴ�.
	Observer (������): ������ ���� ��ȭ�� �����ϰ�, ������ �˸��� ���� �� ������Ʈ �޼��带 ȣ��޾� ������ �����մϴ�.
	ConcreteSubject (��ü���� ����): ������ ��ü���� ����ü��, �������� ����ϰų� �����ϴ� �޼��带 �����մϴ�.
	ConcreteObserver (��ü���� ������): �������� ��ü���� ����ü��, ������ ���°� ����Ǿ��� �� ������Ʈ �޼��带 ���� �˸��� �޽��ϴ�.

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

namespace unit_test
{
	namespace basic
	{
		class Observer abstract
		{
		public:
			virtual void OnEvent(const string& _msg) abstract;
		};

		class Subject
		{
		public:
			void Attach(shared_ptr<Observer> _observer)
			{
				m_Observers.push_back(_observer);
			}

			void Detach(shared_ptr<Observer> _observer)
			{
				m_Observers.erase(remove(begin(m_Observers), end(m_Observers), _observer), m_Observers.end());
			}

			void Notify()
			{
				for (auto& observer : m_Observers)
					observer->OnEvent(m_Message);
			}

			void CreateMessage(const string& _message)
			{
				m_Message = _message;
				Notify();
			}

		private:
			string m_Message = {};
			vector<shared_ptr<Observer>> m_Observers = {};
		};

		class ConcreteObserver : public Observer, public enable_shared_from_this<ConcreteObserver>
		{
		public:
			ConcreteObserver(const string& _name, shared_ptr<Subject> _subject)
				: m_Name(_name), m_Subject(_subject)
			{
			}
			~ConcreteObserver()
			{
				if (auto subject = m_Subject.lock())
				{
					subject->Detach(shared_from_this());
				}
			}
			void Init()
			{
				auto subject = m_Subject.lock();

				subject->Attach(shared_from_this());
			}
			void OnEvent(const string& _message) override
			{
				cout << "Observer Name : " << m_Name << " received message : " << _message << endl;
			}

		private:
			string m_Name;
			weak_ptr<Subject> m_Subject;
		};
	}

	namespace use_pattern
	{
		class Player;

		class IPlayerObserver abstract
		{
		public:
			IPlayerObserver() = default;
			virtual ~IPlayerObserver() = default;

			virtual void OnEvent(shared_ptr<Player> _player) abstract;
		};

		class MonsterSpawner : public IPlayerObserver
		{
		public:
			virtual void OnEvent(shared_ptr<Player> _player) override
			{
				cout << "MonsterSpawner::OnEvent() �Լ� ȣ��" << endl;
			}
		};

		class QuestMgr : public IPlayerObserver
		{
		public:
			virtual void OnEvent(shared_ptr<Player> _player) override
			{
				cout << "QuestMgr::OnEvent() �Լ� ȣ��" << endl;
			}
		};

		class AchievementMgr : public IPlayerObserver
		{
		public:
			virtual void OnEvent(shared_ptr<Player> _player) override
			{
				cout << "AchievementMgr::OnEvent() �Լ� ȣ��" << endl;
			}
		};

		class Player : public enable_shared_from_this<Player>
		{
		public:
			Player(const string& _name) : name(_name) {}

			void Attach(shared_ptr<IPlayerObserver> _observer)
			{
				if (_observer == nullptr)
					return;

				m_Observers.push_back(_observer);
			}

			void Detach(shared_ptr<IPlayerObserver> _observer)
			{
				auto iter = find(begin(m_Observers), end(m_Observers), _observer);

				if (iter == m_Observers.end())
					return;

				m_Observers.erase(iter);
			}

			void Notify()
			{
				for (auto& observer : m_Observers)
					observer->OnEvent(shared_from_this());
			}

			void EnterBossRoom()
			{
				Notify();
			}

			vector<shared_ptr<IPlayerObserver>> m_Observers = {};
			string name = {};
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void test()
		{
			shared_ptr<Subject> subject = make_shared<Subject>();
			auto observer1 = make_shared<ConcreteObserver>("Observer1", subject);
			observer1->Init();
			auto observer2 = make_shared<ConcreteObserver>("Observer2", subject);
			observer2->Init();

			subject->CreateMessage("Hello Observer!");
			subject->CreateMessage("Observer Pattern in C++");
		}
	}
	namespace use_pattern
	{
		void test()
		{
			shared_ptr<Player> player = make_shared<Player>("���");

			player->Attach(make_shared<MonsterSpawner>());
			player->Attach(make_shared<QuestMgr>());
			player->Attach(make_shared<AchievementMgr>());

			player->EnterBossRoom();
		}
	}
}

int main()
{
	//unit_test::basic::test();
	unit_test::use_pattern::test();
	return 0;
}


