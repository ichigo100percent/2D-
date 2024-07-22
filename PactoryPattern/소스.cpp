/*
	팩토리 패턴 (Factory Pattern)

	팩토리 패턴은 객체 생성 로직을 캡슐화하여, 객체 생성을 담당하는 클래스를 별도로 두는 디자인 패턴입니다.
	이를 통해 클라이언트 코드에서는 객체 생성 방식에 대한 구체적인 사항을 알 필요 없이 객체를 생성할 수 있습니다. 
	이는 객체 생성 과정이 복잡하거나 조건에 따라 다른 종류의 객체를 생성해야 하는 경우 유용합니다.

	팩토리 패턴의 주요 장점은 다음과 같습니다:

	객체 생성의 책임 분리: 객체 생성 로직을 한 곳에 모아 관리할 수 있어 유지보수성이 향상됩니다.
	객체 생성의 유연성: 조건에 따라 다양한 객체를 생성할 수 있어 확장성이 높습니다.
	코드 중복 최소화: 객체 생성 로직의 중복을 줄일 수 있습니다.
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