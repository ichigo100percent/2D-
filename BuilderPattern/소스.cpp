/*

	���� ����(Builder Pattern)�� ��ü�� ���� ������ �ܰ躰�� �и��Ͽ� ������ ��ü�� �ܰ������� ������ �� �ְ� �ϴ� ���� ���� �� �ϳ��Դϴ�. 
	���� ������ Ư�� ��ü�� ���� ������ �����ϰ� �پ��� ������ ���� �پ��� ������ ��ü�� �����ؾ� �� �� �����մϴ�. 
	�� ������ ��ü�� ���� ������ ǥ�� ����� �и��Ͽ� ������ ���� �������� ���� �ٸ� ǥ���� ���� �� �ְ� �մϴ�.

	�ֿ� ���� ���
	Builder: ��ü�� �����ϴ� �� �κ��� �����ϴ� �������̽�(Ȥ�� �߻� Ŭ����)�Դϴ�.
	ConcreteBuilder: Builder �������̽��� �����ϸ�, ��ǰ�� ��ǰ���� ��ü������ �����ϴ� ������ �մϴ�.
	Product: ���������� ������ ������ ��ü�Դϴ�.
	Director: Builder �������̽��� ����ϴ� ��ü ������ ��ü�Դϴ�. ���� ������ ������ �����մϴ�.
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
