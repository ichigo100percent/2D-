/*
	Ŀ�ǵ� ���� ����
	Ŀ�ǵ� ����(Command Pattern)�� �ൿ ���� �� �ϳ���,
	��û�� ��ü�� ĸ��ȭ�Ͽ� ���� �ٸ� ��û���� �Ű�����ȭ�ϰ� ť��, �α�, ��� ���� �۾��� �� �� �ֵ��� �����ݴϴ�. 
	�� ������ ����ϸ� ��û�� �߽��ڿ� �����ڷ� �и��� �� �־� �ڵ��� �������� Ȯ�强�� ���� �� �ֽ��ϴ�.

	���� ���
	Command �������̽�: ������ ����� �����մϴ�.
	Concrete Command: Command �������̽��� �����Ͽ� ������ ����� �����ϴ� Ŭ�����Դϴ�. �� Ŭ������ ����� ������ ���ù�(Receiver)�� �����մϴ�.
	Receiver: Concrete Command�� ����� ������ �� ������ �����ϴ� ��ü�Դϴ�.
	Invoker: ��� ��ü�� �����Ű�� ������ �մϴ�. Ŭ���̾�Ʈ�� ��û�� �޾Ƽ� ����� �����մϴ�.
	Client: ��� ��ü�� �����ϰ� �����ϴ� ������ �մϴ�.
*/

#include <iostream>
#include <memory>
#include <array>
#include <cstdio>

using namespace std;

namespace unin_test
{
	namespace basic
	{
		class Command abstract
		{
		public:
			Command() = default;
			virtual ~Command() = default;

			virtual void Execute() abstract;
		};
		class Invoker
		{
		public:
			Invoker() = default;
			virtual ~Invoker() = default;

			void ReleaseCommand()
			{
				if (m_Command != nullptr)
					delete m_Command;
			}
			void ExecuteCommand()
			{
				m_Command->Execute();
			}
			void SetCommand(Command* _command)
			{
				ReleaseCommand();
				m_Command = _command;
			}

		private:
			Command* m_Command = nullptr;
		};
		class Receiver
		{
		public:
			Receiver() = default;
			virtual ~Receiver() = default;

			void Operation(int _a) { printf("Receiver::Operation()\n"); }
		};
		class ConcreteCommand1 : public Command
		{
		public:
			ConcreteCommand1(Receiver* _receiver, int _a)
			{
				m_Recevier = _receiver;
				int a = _a;
			}

			virtual void Execute() override
			{
				printf("Command1::Execute()\n");
				m_Recevier->Operation(a);
			}

		private:
			Receiver* m_Recevier = nullptr;
			int a = 0;
		};
		class ConcreteCommand2 : public Command
		{
		public:
			ConcreteCommand2() = default;

			virtual void Execute() override
			{
				printf("Command2::Execute()\n");
			}
		};
	}
	namespace use_pattern
	{
		class Command abstract
		{
		public:
			Command() = default;
			virtual ~Command() = default;

			virtual void OnExecute() = 0;
			virtual void OnUndo() = 0;
			virtual void OnRedo() = 0;
		};

		class Invoker
		{
			static const int MAX_COMMAND = 10;
		public:
			Invoker()
			{
				fill(m_arrCommand.begin(), m_arrCommand.end(), nullptr);
			}
			virtual ~Invoker()
			{
				for (int i = 0; i < MAX_COMMAND; i++)
				{
					if (m_arrCommand[i] != nullptr)
						delete m_arrCommand[i];
				}
			}

			void ExecuteCommand(Command* _command)
			{
				if (m_nextIdx >= MAX_COMMAND)
				{
					printf("�� �̻� ����� ������ �� �����ϴ�!\n");
					return;
				}

				_command->OnExecute();

				if (m_bHistroyChange == true)
				{
					// ���� �ε������� ������ ����
					for (int i = (m_nextIdx + 1); i < MAX_COMMAND; i++)
					{
						if (m_arrCommand[i] != nullptr)
						{
							delete m_arrCommand[i];
							m_arrCommand[i] = nullptr;
						}
					}
				}

				++m_nextIdx;
				m_arrCommand[m_nextIdx] = _command; // command ��ü ����
			}
			void Undo()
			{
				if (m_nextIdx < 0)
				{
					printf("����� ����� �����ϴ�!\n");
					return;
				}

				// �ֱ� ����� ����ϰ� �ε��� ����
				m_arrCommand[m_nextIdx]->OnUndo();
				--m_nextIdx;

				m_bHistroyChange = false;
			}

			void Redo()
			{
				if (m_nextIdx > static_cast<int>(m_arrCommand.size()))
				{
					printf("������� ����� �����ϴ�!\n");
					return;
				}

				// �ε����� ������Ű�� �ֱ� ��� �����
				++m_nextIdx;
				m_arrCommand[m_nextIdx]->OnRedo();

				m_bHistroyChange = true;
			}

		private:
			int m_nextIdx = -1;
			bool m_bHistroyChange = false;  // Undo �Ǵ� Redo ������ Ȯ��
			array<Command*, MAX_COMMAND> m_arrCommand;
		};

		class AttackCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~AttackCommand() = default;

			virtual void OnExecute() override
			{
				printf("����!\n");
			}
			virtual void OnUndo() override
			{
				printf("���� ���\n");
			}
			virtual void OnRedo() override
			{
				printf("���� �����!\n");
			}				
		};

		class DefendCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~DefendCommand() = default;

			virtual void OnExecute() override
			{
				printf("���!\n");
			}

			virtual void OnUndo() override
			{
				printf("��� ���!\n");
			}

			virtual void OnRedo() override
			{
				printf("��� �����!\n");
			}
		};
	}
}

namespace unin_test
{
	namespace basic
	{
		void test()
		{
			printf("<Basic Command Pattern Test!>\n\n");

			Invoker invoker;
			invoker.SetCommand(new ConcreteCommand1(new Receiver, 10));
			invoker.ExecuteCommand();

			invoker.SetCommand(new ConcreteCommand2());
			invoker.ExecuteCommand();
			printf("\n");
		}
	}
	namespace use_pattern
	{
		void test()
		{
			printf("<Use Command Pattern Test!>\n\n");

			Invoker invoker;
			invoker.ExecuteCommand(new AttackCommand());
			invoker.ExecuteCommand(new DefendCommand());
			printf("\n");

			printf("��� ����� ����մϴ�!\n");
			invoker.Undo();
			invoker.Undo();
			invoker.Undo();
			printf("\n");

			printf("���� ��ɸ� ������մϴ�!\n");
			invoker.Redo();
			printf("\n");

			printf("���� ���� ����� �����ؼ� ���� ��� ������ �����ϴ�!\n");
			invoker.ExecuteCommand(new AttackCommand());
			printf("\n");
		}
	}
}

// Client
int main()
{
	//unin_test::basic::test();
	unin_test::use_pattern::test();

	return 0;
}