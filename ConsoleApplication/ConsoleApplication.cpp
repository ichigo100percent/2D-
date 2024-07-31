#include <iostream>
#include <thread>
#include <vector>

// 비원자적 카운터 변수
int counter = 0;

// 카운터 증가 함수
void increment(int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        ++counter; // 비원자적 증감 연산
    }
}

int main() {
    const int num_threads = 10;
    const int num_iterations = 10000;

    std::vector<std::thread> threads;

    // 여러 스레드를 생성하여 카운터를 증가시킴
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(increment, num_iterations));
    }

    // 모든 스레드가 종료될 때까지 대기
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value (without atomic): " << counter << std::endl;

    return 0;
}