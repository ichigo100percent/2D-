#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace std;

// Command 인터페이스
class Command
{
public:
    virtual void Execute() = 0;
    virtual ~Command() = default;
};

// Receiver 클래스
class GameCharacter
{
public:
    void MoveUp() { cout << "Character moves up" << endl; }
    void MoveDown() { cout << "Character moves down" << endl; }
    void MoveLeft() { cout << "Character moves left" << endl; }
    void MoveRight() { cout << "Character moves right" << endl; }
    void Attack() { cout << "Character attacks" << endl; }
};

// Concrete Command 클래스
class MoveUpCommand : public Command
{
public:
    explicit MoveUpCommand(shared_ptr<GameCharacter> character) : m_character(character) {}
    void Execute() override { m_character->MoveUp(); }

private:
    shared_ptr<GameCharacter> m_character;
};

class MoveDownCommand : public Command
{
public:
    explicit MoveDownCommand(shared_ptr<GameCharacter> character) : m_character(character) {}
    void Execute() override { m_character->MoveDown(); }

private:
    shared_ptr<GameCharacter> m_character;
};

class MoveLeftCommand : public Command
{
public:
    explicit MoveLeftCommand(shared_ptr<GameCharacter> character) : m_character(character) {}
    void Execute() override { m_character->MoveLeft(); }

private:
    shared_ptr<GameCharacter> m_character;
};

class MoveRightCommand : public Command
{
public:
    explicit MoveRightCommand(shared_ptr<GameCharacter> character) : m_character(character) {}
    void Execute() override { m_character->MoveRight(); }

private:
    shared_ptr<GameCharacter> m_character;
};

class AttackCommand : public Command
{
public:
    explicit AttackCommand(shared_ptr<GameCharacter> character) : m_character(character) {}
    void Execute() override { m_character->Attack(); }

private:
    shared_ptr<GameCharacter> m_character;
};

// Invoker 클래스
class InputHandler
{
public:
    void SetCommand(char input, shared_ptr<Command> command) { m_commands[input] = command; }
    void HandleInput(char input)
    {
        auto it = m_commands.find(input);
        if (it != m_commands.end() && it->second)
            it->second->Execute();
    }

private:
    map<char, shared_ptr<Command>> m_commands;
};

// Client 코드
int main()
{
    shared_ptr<GameCharacter> character = make_shared<GameCharacter>();

    shared_ptr<Command> moveUp = make_shared<MoveUpCommand>(character);
    shared_ptr<Command> moveDown = make_shared<MoveDownCommand>(character);
    shared_ptr<Command> moveLeft = make_shared<MoveLeftCommand>(character);
    shared_ptr<Command> moveRight = make_shared<MoveRightCommand>(character);
    shared_ptr<Command> attack = make_shared<AttackCommand>(character);

    InputHandler inputHandler;
    inputHandler.SetCommand('w', moveUp);
    inputHandler.SetCommand('s', moveDown);
    inputHandler.SetCommand('a', moveLeft);
    inputHandler.SetCommand('d', moveRight);
    inputHandler.SetCommand(' ', attack);

    char input;
    while (true)
    {
        cout << "Enter command (w: up, s: down, a: left, d: right, space: attack, q: quit): ";
        cin >> input;

        if (input == 'q')
            break;

        inputHandler.HandleInput(input);
    }

    return 0;
}