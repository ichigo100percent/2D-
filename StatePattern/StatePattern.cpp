/*
	상태 패턴 (State Pattern)
	상태 패턴은 객체의 상태에 따라 그 객체의 행동을 변경할 수 있도록 하는 디자인 패턴입니다.
	즉, 객체의 내부 상태가 바뀜에 따라 객체의 행동이 달라지게 합니다.
	상태 패턴은 주로 상태 기계(state machine)와 관련된 문제를 해결하는 데 사용됩니다.

	상태 패턴의 주요 요소는 다음과 같습니다:

	State 인터페이스: 상태별로 행동을 정의하는 인터페이스입니다.
	ConcreteState 클래스들: State 인터페이스를 구현하는 구체적인 상태 클래스들입니다.
	Context 클래스: 상태에 따라 행동을 수행하는 클래스입니다. 현재 상태를 저장하고, 상태 전환을 관리합니다.
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
    cout << "몬스터가 보통 상태입니다!" << endl;
    cout << "몬스터가 뒤쫓기 시작합니다!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterChaseState>(GetMonster()));
}

void MonsterChaseState::Update()
{
    cout << "몬스터가 뒤쫓는 중입니다!" << endl;
    cout << "몬스터가 공격하기 시작합니다!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterAttackState>(GetMonster()));
}

void MonsterAttackState::Update()
{
    cout << "몬스터의 공격으로 " << GetMonster()->GetAttackDamage() << "만큼의 피해를 입었습니다!" << endl;
    cout << "몬스터의 공격으로부터 벗어났습니다!" << endl;
    GetMonster()->ChangeState(make_shared<MonsterIdleState>(GetMonster()));
}