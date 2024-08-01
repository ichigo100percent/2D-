#include <iostream>
#include <memory>
#include <string>
#include <bitset>


using namespace std;
enum State
{
    idle = 0,
    run = 1 << 0,
    attack = 1 << 1,
    both = run | attack
};

class test
{
public:
    test() : state(0) {}

    void set(State s, bool b)
    {
        if (s == both) {
            state.set(0, b); // run
            state.set(1, b); // attack
        }
        else {
            state.set(s == run ? 0 : 1, b);
        }
    }

    bool isSet(State s) const
    {
        if (s == both) {
            return state.test(0) && state.test(1);
        }
        else {
            return state.test(s == run ? 0 : 1);
        }
    }

    std::bitset<2> state;
};

int main()
{
    test t;

    t.set(both, true);

    // 결과 확인을 위한 출력
    std::cout << "State: " << t.state << std::endl;

    if (t.isSet(both)) {
        std::cout << "Both run and attack are set." << std::endl;
    }
    else {
        std::cout << "Both run and attack are not set." << std::endl;
    }

    return 0;
}