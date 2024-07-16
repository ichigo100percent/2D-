/*
	���� ���� (State Pattern)
	���� ������ ��ü�� ���¿� ���� �� ��ü�� �ൿ�� ������ �� �ֵ��� �ϴ� ������ �����Դϴ�.
	��, ��ü�� ���� ���°� �ٲ� ���� ��ü�� �ൿ�� �޶����� �մϴ�.
	���� ������ �ַ� ���� ���(state machine)�� ���õ� ������ �ذ��ϴ� �� ���˴ϴ�.

	���� ������ �ֿ� ��Ҵ� ������ �����ϴ�:

	State �������̽�: ���º��� �ൿ�� �����ϴ� �������̽��Դϴ�.
	ConcreteState Ŭ������: State �������̽��� �����ϴ� ��ü���� ���� Ŭ�������Դϴ�.
	Context Ŭ����: ���¿� ���� �ൿ�� �����ϴ� Ŭ�����Դϴ�. ���� ���¸� �����ϰ�, ���� ��ȯ�� �����մϴ�.
*/
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class State abstract
{
public:
    State() = default;
    virtual ~State() = default;

    virtual void Update() abstract;
};

class Monster : public enable_shared_from_this<Monster>
{
public:
    Monster() {}
    ~Monster() { ReleaseState(); }

    void ReleaseState()
    {
        if (m_State != nullptr)
            m_State.reset();
    }

    void Init();
    void Update()
    {
        if (m_State)
            m_State->Update();
    }

    void ChangeState(shared_ptr<State> _state)
    {
        ReleaseState();
        m_State = _state;
    }

    int GetAttackDamage() const { return m_AttackDamage; }

private:
    int m_AttackDamage = 10;
    shared_ptr<State> m_State = nullptr;
};

class MonsterState : public State
{
public:
    explicit MonsterState(shared_ptr<Monster> _monster) : m_Monster(_monster) {}
    virtual ~MonsterState() = default;

    virtual void Update() override {}

    shared_ptr<Monster> GetMonster() { return m_Monster.lock(); }

private:
    weak_ptr<Monster> m_Monster;
};

class MonsterIdleState : public MonsterState
{
public:
    using MonsterState::MonsterState;
    virtual ~MonsterIdleState() = default;

    virtual void Update() override;
};

class MonsterChaseState : public MonsterState
{
public:
    using MonsterState::MonsterState;
    virtual ~MonsterChaseState() = default;

    virtual void Update() override;
};

class MonsterAttackState : public MonsterState
{
public:
    using MonsterState::MonsterState;
    virtual ~MonsterAttackState() = default;

    virtual void Update() override;
};


int main()
{
    shared_ptr<Monster> monster = make_shared<Monster>();
    monster->Init();
    monster->Update();
    monster->Update();
    monster->Update();

    return 0;
}

void Monster::Init()
{
    m_State = make_shared<MonsterIdleState>(shared_from_this());
}

void MonsterIdleState::Update()
{
    cout << "���Ͱ� ���� �����Դϴ�!" << endl;
    cout << "���Ͱ� ���ѱ� �����մϴ�!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterChaseState>(GetMonster()));
}

void MonsterChaseState::Update()
{
    cout << "���Ͱ� ���Ѵ� ���Դϴ�!" << endl;
    cout << "���Ͱ� �����ϱ� �����մϴ�!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterAttackState>(GetMonster()));
}

void MonsterAttackState::Update()
{
    cout << "������ �������� " << GetMonster()->GetAttackDamage() << "��ŭ�� ���ظ� �Ծ����ϴ�!" << endl;
    cout << "������ �������κ��� ������ϴ�!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterIdleState>(GetMonster()));
}