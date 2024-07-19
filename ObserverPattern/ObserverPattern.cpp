/*
	옵저버 패턴(Observer Pattern)은 객체 지향 프로그래밍에서 널리 사용되는 디자인 패턴 중 하나입니다.
	패턴은 한 객체의 상태가 변경되었을 때 그 객체에 의존하는 다른 객체들에게 자동으로 알림을 보내고 업데이트를 수행하는 방법을 제공합니다.
	주로 이벤트 핸들링 시스템이나 모델-뷰-컨트롤러(MVC) 구조에서 사용됩니다.

	옵저버 패턴의 구성 요소
	Subject (주제): 상태를 가지고 있으며, 상태 변경 시 옵저버들에게 알림을 보냅니다.
	Observer (옵저버): 주제의 상태 변화를 감지하고, 주제가 알림을 보낼 때 업데이트 메서드를 호출받아 동작을 수행합니다.
	ConcreteSubject (구체적인 주제): 주제의 구체적인 구현체로, 옵저버를 등록하거나 제거하는 메서드를 구현합니다.
	ConcreteObserver (구체적인 옵저버): 옵저버의 구체적인 구현체로, 주제의 상태가 변경되었을 때 업데이트 메서드를 통해 알림을 받습니다.

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
				cout << "MonsterSpawner::OnEvent() 함수 호출" << endl;
			}
		};

		class QuestMgr : public IPlayerObserver
		{
		public:
			virtual void OnEvent(shared_ptr<Player> _player) override
			{
				cout << "QuestMgr::OnEvent() 함수 호출" << endl;
			}
		};

		class AchievementMgr : public IPlayerObserver
		{
		public:
			virtual void OnEvent(shared_ptr<Player> _player) override
			{
				cout << "AchievementMgr::OnEvent() 함수 호출" << endl;
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
			shared_ptr<Player> player = make_shared<Player>("용사");

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


