/*
	커맨드 패턴 설명
	커맨드 패턴(Command Pattern)은 행동 패턴 중 하나로,
	요청을 객체로 캡슐화하여 서로 다른 요청들을 매개변수화하고 큐잉, 로깅, 취소 등의 작업을 할 수 있도록 도와줍니다. 
	이 패턴을 사용하면 요청을 발신자와 수신자로 분리할 수 있어 코드의 유연성과 확장성을 높일 수 있습니다.

	구성 요소
	Command 인터페이스: 실행할 명령을 선언합니다.
	Concrete Command: Command 인터페이스를 구현하여 실제로 명령을 실행하는 클래스입니다. 이 클래스는 명령을 수행할 리시버(Receiver)를 포함합니다.
	Receiver: Concrete Command가 명령을 수행할 때 실제로 동작하는 객체입니다.
	Invoker: 명령 객체를 실행시키는 역할을 합니다. 클라이언트의 요청을 받아서 명령을 실행합니다.
	Client: 명령 객체를 생성하고 설정하는 역할을 합니다.
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
					printf("더 이상 명령을 실행할 수 없습니다!\n");
					return;
				}

				_command->OnExecute();

				if (m_bHistroyChange == true)
				{
					// 현재 인덱스부터 끝까지 정리
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
				m_arrCommand[m_nextIdx] = _command; // command 객체 저장
			}
			void Undo()
			{
				if (m_nextIdx < 0)
				{
					printf("취소할 명령이 없습니다!\n");
					return;
				}

				// 최근 명령을 취소하고 인덱스 감소
				m_arrCommand[m_nextIdx]->OnUndo();
				--m_nextIdx;

				m_bHistroyChange = false;
			}

			void Redo()
			{
				if (m_nextIdx > static_cast<int>(m_arrCommand.size()))
				{
					printf("재실행할 명령이 없습니다!\n");
					return;
				}

				// 인덱스를 증가시키고 최근 명령 재실행
				++m_nextIdx;
				m_arrCommand[m_nextIdx]->OnRedo();

				m_bHistroyChange = true;
			}

		private:
			int m_nextIdx = -1;
			bool m_bHistroyChange = false;  // Undo 또는 Redo 중인지 확인
			array<Command*, MAX_COMMAND> m_arrCommand;
		};

		class AttackCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~AttackCommand() = default;

			virtual void OnExecute() override
			{
				printf("공격!\n");
			}
			virtual void OnUndo() override
			{
				printf("공격 취소\n");
			}
			virtual void OnRedo() override
			{
				printf("공격 재실행!\n");
			}				
		};

		class DefendCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~DefendCommand() = default;

			virtual void OnExecute() override
			{
				printf("방어!\n");
			}

			virtual void OnUndo() override
			{
				printf("방어 취소!\n");
			}

			virtual void OnRedo() override
			{
				printf("방어 재실행!\n");
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

			printf("모든 명령을 취소합니다!\n");
			invoker.Undo();
			invoker.Undo();
			invoker.Undo();
			printf("\n");

			printf("공격 명령만 재실행합니다!\n");
			invoker.Redo();
			printf("\n");

			printf("새로 공격 명령을 실행해서 이전 명령 스택을 날립니다!\n");
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