#include <iostream>
#include <string>

using namespace std;

int solution(int a, int b) 
{
	auto a1 = to_string(a) + to_string(b);
	int answer = max(stoi(a1), 2 * a * b);

	return answer;
}

int main()
{
	int c = solution(2, 91);

	cout << c << endl;

	return 0;
}
