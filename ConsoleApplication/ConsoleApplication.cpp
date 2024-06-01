#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(string n_str) {
    string answer = to_string(stoi(n_str));
    return answer;
}

class Test
{
public:
    void T1() { cout << "Hellow World"; }
};

class Test2 : public Test
{
public:
    void T2() { Test::T1(); }
};

int main()
{
   

    return 0;
}