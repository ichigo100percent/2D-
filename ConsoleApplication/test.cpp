#include "test.h"

#include <iostream>
#include <memory>
#include <string>
#include <bitset>
#include "test.h"

using namespace std;

// 상태 플래그 정의
enum CharacterState {
    STATE_IDLE = 0,
    STATE_RUNNING,
    STATE_JUMPING,
    STATE_ATTACKING,
    STATE_DEFENDING,
    STATE_TOTAL // 상태의 총 개수
};

class Character {
public:
    Character() : state(0) {}

    void setState(CharacterState s, bool value) {
        state.set(s, value);
    }

    bool isState(CharacterState s) const {
        return state.test(s);
    }

    void printState() const {
        std::cout << "Character States: ";
        for (int i = 0; i < STATE_TOTAL; ++i) {
            std::cout << state[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    std::bitset<STATE_TOTAL> state;
};

//int main() {
//    Character character;
//
//    character.setState(STATE_RUNNING, true);
//    character.setState(STATE_JUMPING, true);
//
//    character.printState();
//
//    if (character.isState(STATE_RUNNING)) {
//        std::cout << "Character is running." << std::endl;
//    }
//
//    character.setState(STATE_RUNNING, false);
//    character.printState();
//
//    return 0;
//}