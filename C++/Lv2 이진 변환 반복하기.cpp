/********************
이진 변환 반복하기

문제 설명
0과 1로 이루어진 어떤 문자열 x에 대한 이진 변환을 다음과 같이 정의합니다.

x의 모든 0을 제거합니다.
x의 길이를 c라고 하면, x를 "c를 2진법으로 표현한 문자열"로 바꿉니다.
예를 들어, x = "0111010"이라면, x에 이진 변환을 가하면 x = "0111010" -> "1111" -> "100" 이 됩니다.

0과 1로 이루어진 문자열 s가 매개변수로 주어집니다. s가 "1"이 될 때까지 계속해서 s에 이진 변환을 가했을 때,
이진 변환의 횟수와 변환 과정에서 제거된 모든 0의 개수를 각각 배열에 담아 return 하도록 solution 함수를 완성해주세요.

제한사항
 - s의 길이는 1 이상 150,000 이하입니다.
 - s에는 '1'이 최소 하나 이상 포함되어 있습니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> convertToBinary(int x) {
    vector<int> xToBinary;
    
    while(x != 0) {
        xToBinary.push_back(x%2);
        x /= 2;
    }
    reverse(xToBinary.begin(), xToBinary.end());
    return xToBinary;
}

void helper(vector<int> x, vector<int>& answer){
    if(x.size() == 1 && x[0] == 1) return;
    
    ++answer[0];
    vector<int> removed;
    int cnt = 0;
    for(int i = 0; i < x.size(); ++i) {
        if(x[i] == 0) {
            cnt++;
            continue;
        }
        removed.push_back(x[i]);
    }
    answer[1] += cnt;
    
	//1만 남을 때 까지 반복
    return helper(convertToBinary(removed.size()), answer);
}

vector<int> solution(string s) {
	//[0] - 횟수, [1] - 지운 0 갯수
    vector<int> answer(2, 0);
    
    vector<int> x;
    for(int i = 0; i < s.length(); ++i) {
        x.push_back(s[i] - '0');
    }
    
    helper(x, answer);
    
    return answer;
}