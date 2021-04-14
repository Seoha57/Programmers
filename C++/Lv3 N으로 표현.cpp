/********************
N으로 표현

문제 설명
아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.
이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법 중 N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

제한사항
 - N은 1 이상 9 이하입니다.
 - number는 1 이상 32,000 이하입니다.
 - 수식에는 괄호와 사칙연산만 가능하며 나누기 연산에서 나머지는 무시합니다.
 - 최솟값이 8보다 크면 -1을 return 합니다.
********************/

#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(int N, int number) {
    int answer = 1;
    if(N == number) return answer;
    answer++;
    
    vector<set<int>> poss(9);
    poss[answer - 1].insert(N);
    string s = to_string(N);
    for(int i = 2; i < 9; ++i) {
        s += to_string(N);
        int n = stoi(s);
        if(n == number) return i;
		
        poss[i].insert(n);
    }
    
    while(answer <= 8) {
        for(int b = answer - 1; b > 0; --b) {
            for(auto base : poss[b]) {
                for(auto num : poss[answer - b]) {
                    if(num == 0) continue;
                    //더하기
                    int plus = base + num;
                    if(plus == number) return answer;
                    poss[answer].insert(plus);

                    //빼기
                    int minus = base - num;
                    if(minus == number) return answer;
                    poss[answer].insert(minus);
                    
                    //곱하기
                    int multi = base * num;
                    if(multi == number) return answer;
                    poss[answer].insert(multi);
                    
                    //나누기
                    int divde = base / num;
                    if(divde == number) return answer;
                    poss[answer].insert(divde);
                }
            }
        }
        answer++;
    }
    
    return -1;
}