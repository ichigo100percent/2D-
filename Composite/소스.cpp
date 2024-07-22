/*
	������Ʈ ������ ��ü�� Ʈ�� ������ �����Ͽ� ���� ��ü�� ���� ��ü�� �����ϰ� �ٷ�� ���� ���Ǵ� ������ ������ �����Դϴ�. 
	�� ������ ����ϸ� Ŭ���̾�Ʈ�� ���� ��ü�� ��ü�� ������ �����ϰ� ó���� �� �ֽ��ϴ�.

	�ֿ� ���� ��Ҵ� ������ �����ϴ�:

	Component (���� ���): ���� �������̽���, ���� ��ü�� ���� ��ü�� �����ؾ� �ϴ� �������̽��� �����մϴ�.
	Leaf (��): ���� �۾��� �����ϴ� ���� ��ü�� ��Ÿ���ϴ�.
	Composite (����ü): �ٸ� ���� ��ҵ��� �ڽ����� ������ �� �ִ� ���� ��ü�� ��Ÿ���ϴ�.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

namespace unit_test
{
	namespace basic
	{
		class Component abstract
		{
		public:
			Component() = default;
			virtual ~Component() = default;

			virtual void Execute() abstract;
		};

		class Composite : public Component
		{
		public:
			using Component::Component;
			virtual ~Composite() = default;

			virtual void Execute() override
			{
				for (auto& comp : m_Components)
				{
					if (comp)
						comp->Execute();
				}
			}

			void add(shared_ptr<Component> _comp)
			{
				m_Components.push_back(_comp);
			}
			void remove(shared_ptr<Component> _comp)
			{
				auto iter = find(m_Components.begin(), m_Components.end(), _comp);

				if (iter != m_Components.end())
					m_Components.erase(iter);
			}
			shared_ptr<Component> GetComponent(int idx)
			{
				if (idx >= 0 && idx < m_Components.size())
					return m_Components[idx];

				return nullptr;
			}
		private:
			vector<shared_ptr<Component>> m_Components = {};
		};

		class Leaf : public Component
		{
		public:
			using Component::Component;
			virtual ~Leaf() = default;

			virtual void Execute() override
			{
				// �ּ� �� ���
				cout << this << endl;
			}
		};
	}

	namespace use_pattern
	{
		// Component
		class Object abstract
		{
		public:
			Object(const string& _name) : m_Name(_name) {}
			virtual ~Object() = default;

			virtual void Execute() abstract;
			const string& GetName() const { return m_Name; }

		private:
			string m_Name = {};
		};

		// Leaf 
		class Tree : public Object
		{
		public:
			using Object::Object;
			virtual ~Tree() = default;

			virtual void Execute() override
			{
				cout << "���� �߿��� " << GetName() << "ó��! " << endl;
			}
		};

		class Car : public Object
		{
		public:
			using Object::Object;
			virtual ~Car() = default;

			virtual void Execute() override
			{
				cout << "�� �߿��� " << GetName() << "ó��! " << endl;
			}
		};

		// Composite
		class ObjectGroup final : public Object
		{
		public:
			using Object::Object;
			virtual ~ObjectGroup() = default;

			void add(shared_ptr<Object> _obj)
			{
				if (_obj)
					m_Objects.push_back(_obj);
			}
			void remove(shared_ptr<Object> _obj)
			{
				auto find = std::find(m_Objects.begin(), m_Objects.end(), _obj);

				if (find != m_Objects.end())
					m_Objects.erase(find);
			}
			void Execute() override
			{
				for (auto& obj : m_Objects)
				{
					obj->Execute();
				}
			}
			shared_ptr<Object> GetObject(int _idx)
			{
				if (_idx >= 0 && m_Objects.size() > _idx)
					return m_Objects[_idx];

				return nullptr;
			}
		private:
			vector<shared_ptr<Object>> m_Objects = {};
		};
	}
}


namespace unit_test
{
	namespace basic
	{
		void test()
		{
			Composite main;
			main.add(make_shared<Leaf>());
			main.add(make_shared<Leaf>());
			main.add(make_shared<Leaf>());
			main.Execute();
			cout << '\n';

			auto iter = main.GetComponent(0);
			cout << iter << endl;
			cout << '\n';

			shared_ptr<Composite> sub = make_shared<Composite>();
			sub->add(make_shared<Leaf>());
			sub->add(make_shared<Leaf>());
			sub->Execute();
			cout << '\n';

			main.add(sub);
			main.Execute();
			cout << '\n';

			main.remove(main.GetComponent(0));
			main.Execute();
		}
	}
	namespace use_pattern
	{
		void test()
		{
			shared_ptr<ObjectGroup> main = make_shared<ObjectGroup>("main");
			main->add(make_shared<Car>("����"));
			main->add(make_shared<Tree>("�ҳ���"));
			main->add(make_shared<Tree>("�볪��"));

			main->Execute();
		}
	}

}

int main()
{
	//unit_test::basic::test();
	unit_test::use_pattern::test();

	return 0;
}