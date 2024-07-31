/*

	빌더 패턴(Builder Pattern)은 객체의 생성 과정을 단계별로 분리하여 복잡한 객체를 단계적으로 생성할 수 있게 하는 생성 패턴 중 하나입니다. 
	빌더 패턴은 특히 객체의 생성 과정이 복잡하고 다양한 조합을 통해 다양한 형태의 객체를 생성해야 할 때 유용합니다. 
	이 패턴은 객체의 생성 과정과 표현 방법을 분리하여 동일한 생성 절차에서 서로 다른 표현을 만들 수 있게 합니다.

	주요 구성 요소
	Builder: 객체를 구성하는 각 부분을 설정하는 인터페이스(혹은 추상 클래스)입니다.
	ConcreteBuilder: Builder 인터페이스를 구현하며, 제품의 부품들을 구체적으로 조립하는 역할을 합니다.
	Product: 최종적으로 생성될 복잡한 객체입니다.
	Director: Builder 인터페이스를 사용하는 객체 생성의 주체입니다. 생성 과정의 순서를 결정합니다.
*/

#include <iostream>
#include <memory>
#include <string>

using namespace std;


namespace unit_test
{
	namespace basic
	{
		class Product
		{
		public:
			void ListParts() const
			{
				cout << "Product parts: ";
				for (size_t i = 0; i < parts.size(); ++i)
				{
					cout << parts[i];
					if (i != parts.size() - 1)
						cout << ", ";
				}
				cout << "\n\n";
			}

			void AddPart(const string& part) { parts.push_back(part); }

		private:
			vector<string> parts;
		};

		class Builder
		{
		public:
			virtual ~Builder() = default;

			virtual void ProducePartA() = 0;
			virtual void ProducePartB() = 0;
			virtual void ProducePartC() = 0;
		};

		class ConcreteBuilder1 : public Builder
		{
		public:
			ConcreteBuilder1() { this->Reset(); }

			void ProducePartA() override { product->AddPart("PartA1"); }
			void ProducePartB() override { product->AddPart("PartB1"); }
			void ProducePartC() override { product->AddPart("PartC1"); }

			void Reset()
			{
				product = make_shared<Product>();
			}

			shared_ptr<Product> GetProduct()
			{
				auto result = product;
				this->Reset();
				return result;
			}

		private:
			shared_ptr<Product> product;
		};

		class Director
		{
		public:
			void SetBuilder(shared_ptr<Builder> _builder) { builder = _builder; }

			void BuildMinimalViableProduct()
			{
				builder->ProducePartA();
			}

			void BuildFullFeaturedProduct()
			{
				builder->ProducePartA();
				builder->ProducePartB();
				builder->ProducePartC();
			}

		private:
			shared_ptr<Builder> builder;
		};
	}
	namespace use_pattern
	{
		// Product 
		class Character
		{
		public:
			Character() = default;
			virtual ~Character() = default;

			void SetName(const string& _name) { name = _name; }
			void SetWeapon(const string& _weapon) { weapon = _weapon; }
			void SetArmor(const string& _armor) { armor = _armor; }

			void ShowCharacter()
			{
				cout << "Name : "   << name   << '\n'
					 << "Weapon : " << weapon << '\n'
					 << "Armor : "  << armor  << '\n';

				cout << '\n';
			}
		private:
			string name;
			string weapon;
			string armor;
		};

		// Builder
		class CharacterBuilder
		{
		public:
			CharacterBuilder() = default;
			virtual ~CharacterBuilder() = default;

			void createNewCharacter() { character = make_unique<Character>(); }
			unique_ptr<Character> getCharacter() { return move(character); }

			virtual void buildName() = 0;
			virtual void buildWeapon() = 0;
			virtual void buildArmor() = 0;

		protected:
			unique_ptr<Character> character = nullptr;
		};

		// ConcreteBuilder
		class WarriorBuilder : public CharacterBuilder
		{
		public:
			virtual void buildName() override
			{
				character->SetName("Warrior");
			}
			virtual void buildWeapon() override
			{
				character->SetWeapon("Sword");
			}
			virtual void buildArmor() override
			{
				character->SetArmor("Shield");
			}
		};

		// ConcreteBuilder
		class MageBuilder : public CharacterBuilder
		{
		public:
			virtual void buildName() override
			{
				character->SetName("Mage");
			}
			virtual void buildWeapon() override
			{
				character->SetWeapon("Staff");
			}
			virtual void buildArmor() override
			{
				character->SetArmor("Robe");
			}
		};

		// Director
		class CharacterDirector
		{
		public:
			void setBuilder(shared_ptr<CharacterBuilder> _builder)
			{
				characterBuilder = _builder;
			}

			unique_ptr<Character> getCharacter() { return characterBuilder->getCharacter(); }

			void constructCharacter()
			{
				characterBuilder->createNewCharacter();
				characterBuilder->buildName();
				characterBuilder->buildWeapon();
				characterBuilder->buildArmor();
			}
		private:
			shared_ptr<CharacterBuilder> characterBuilder = nullptr;
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void test()
		{
			unique_ptr<Director> director = make_unique<Director>();
			auto builder = make_shared<ConcreteBuilder1>();
			director->SetBuilder(builder);

			cout << "Standard basic product:\n";
			director->BuildMinimalViableProduct();
			auto product = builder->GetProduct();
			product->ListParts();

			cout << "Standard full featured product:\n";
			director->BuildFullFeaturedProduct();
			product = builder->GetProduct();
			product->ListParts();

			cout << "Custom product:\n";
			builder->ProducePartA();
			builder->ProducePartC();
			product = builder->GetProduct();
			product->ListParts();
		}
	}
	namespace use_pattern
	{
		void test()
		{
			unique_ptr<CharacterDirector> director = make_unique<CharacterDirector>();
			shared_ptr<WarriorBuilder> warriorBuilder = make_shared<WarriorBuilder>();
			shared_ptr<MageBuilder> mageBuilder = make_shared<MageBuilder>();

			director->setBuilder(warriorBuilder);
			director->constructCharacter();
			auto warrior = director->getCharacter();
			warrior->ShowCharacter();

			director->setBuilder(mageBuilder);
			director->constructCharacter();
			auto mage = director->getCharacter();
			mage->ShowCharacter();
		}
	}
}

int main()
{
	//unit_test::basic::test();
	unit_test::use_pattern::test();
	return 0;
}
