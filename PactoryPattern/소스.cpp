/*
	���丮 ���� (Factory Pattern)

	���丮 ������ ��ü ���� ������ ĸ��ȭ�Ͽ�, ��ü ������ ����ϴ� Ŭ������ ������ �δ� ������ �����Դϴ�.
	�̸� ���� Ŭ���̾�Ʈ �ڵ忡���� ��ü ���� ��Ŀ� ���� ��ü���� ������ �� �ʿ� ���� ��ü�� ������ �� �ֽ��ϴ�. 
	�̴� ��ü ���� ������ �����ϰų� ���ǿ� ���� �ٸ� ������ ��ü�� �����ؾ� �ϴ� ��� �����մϴ�.

	���丮 ������ �ֿ� ������ ������ �����ϴ�:

	��ü ������ å�� �и�: ��ü ���� ������ �� ���� ��� ������ �� �־� ������������ ���˴ϴ�.
	��ü ������ ������: ���ǿ� ���� �پ��� ��ü�� ������ �� �־� Ȯ�强�� �����ϴ�.
	�ڵ� �ߺ� �ּ�ȭ: ��ü ���� ������ �ߺ��� ���� �� �ֽ��ϴ�.
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
		// Interface
		class Character abstract
		{
		public:
			Character() = default;
			virtual ~Character() = default;

			virtual void attack() abstract;
		};

		// Concrete
		class Player : public Character
		{
		public:
			using Character::Character;

			virtual void attack() override
			{
				cout << "player attack" << endl;
			}
		};

		class Enemy : public Character
		{
		public:
			using Character::Character;

			virtual void attack() override
			{
				cout << "Enemy attack" << endl;
			}
		};

		// Factory
		class CharacterFactory
		{
		public:
			static shared_ptr<Character> Create(const string& _type)
			{
				if (_type == "Player")
					return make_shared<Player>();
				if (_type == "Enemy")
					return make_shared<Enemy>();

				return nullptr;
			}
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void test()
		{
			auto player = CharacterFactory::Create("Player");
			if (player)
				player->attack();

			auto enemy = CharacterFactory::Create("Enemy");
			if (enemy)
				enemy->attack();
		}
	}
}

int main()
{
	unit_test::basic::test();

	return 0;
}