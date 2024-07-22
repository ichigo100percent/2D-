#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Weapon
{
public:
	Weapon() = default;
	virtual ~Weapon() = default;

	virtual void Attack() abstract;
};

class Sword : public Weapon
{
public:
	using Weapon::Weapon;
	virtual ~Sword() = default;

	virtual void Attack() override
	{
		cout << "Attack use Sword! " << endl;
	}
};

class Bow : public Weapon
{
public:
	using Weapon::Weapon;
	virtual ~Bow() = default;

	virtual void Attack() override
	{
		cout << "Attack use Bow! " << endl;
	}
};

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void Execute() abstract;
	virtual void Undo() abstract;
};

class ChangeWeaponCommand : public Command
{
public:
	ChangeWeaponCommand(shared_ptr<Weapon>& _cur, shared_ptr<Weapon> _new) : m_Current(_cur), m_New(_new) {}

	void Execute() override
	{
		m_Previous = m_Current;
		m_Current = m_New;

		cout << "Weapon Change. " << endl;
	}

	void Undo() override
	{
		m_Current = m_Previous;

		cout << "Weapon Change undone. " << endl;
	}

private:
	shared_ptr<Weapon>& m_Current;
	shared_ptr<Weapon> m_New;
	shared_ptr<Weapon> m_Previous;
};

class AttackCommand : public Command
{
public:
	AttackCommand(shared_ptr<Weapon>& _weapon) : m_CurrentWeapon(_weapon), m_AttackCount(0) {}

	void Execute() override
	{
		m_CurrentWeapon->Attack();
		m_AttackCount++;
	}

	void Undo() override
	{
		if (m_AttackCount > 0)
		{
			cout << "Undoing last Attack. " << endl;
			m_AttackCount--;
		}
		else
		{
			cout << "No attacks to undo. " << endl;
		}
	}

private:
	shared_ptr<Weapon>& m_CurrentWeapon;
	int m_AttackCount;
};

class InputHandler
{
public:

	void SetCommand(char _input, shared_ptr<Command> _comm)
	{
		m_Commands[_input] = _comm;
	}

	void HandleInput(char _input)
	{
		auto find = m_Commands.find(_input);
		if (find != m_Commands.end())
		{
			find->second->Execute();
			m_CommandHistory.push(find->second);
		}
	}

	void UndoLastCommand()
	{
		if (!m_CommandHistory.empty())
		{
			m_CommandHistory.top()->Undo();
			m_CommandHistory.pop();
		}
	}

private:
	unordered_map<char, shared_ptr<Command>> m_Commands = {};
	stack<shared_ptr<Command>> m_CommandHistory = {};
};

int main()
{
	shared_ptr<Weapon> currentWeapon = make_shared<Sword>();
	auto sword = make_shared<Sword>();
	auto bow = make_shared<Bow>();

	auto ChangeToSword = make_shared<ChangeWeaponCommand>(currentWeapon, sword);
	auto ChangeToBow = make_shared<ChangeWeaponCommand>(currentWeapon, bow);
	auto Attack = make_shared<AttackCommand>(currentWeapon);

	InputHandler inputHandler;
	inputHandler.SetCommand('1', ChangeToSword);
	inputHandler.SetCommand('2', ChangeToBow);
	inputHandler.SetCommand('a', Attack);

	vector<char> inputs = { '1', 'a', '2', 'a', 'a', '1' };

	for (auto& input : inputs)
	{
		inputHandler.HandleInput(input);
	}

	cout << "Undo last Command" << endl;
	inputHandler.UndoLastCommand();
	inputHandler.HandleInput('a');

	return 0;
}