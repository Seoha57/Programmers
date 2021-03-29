/********************
가장 큰 수

문제 설명
0 또는 양의 정수가 주어졌을 때, 정수를 이어 붙여 만들 수 있는 가장 큰 수를 알아내 주세요.

예를 들어, 주어진 정수가 [6, 10, 2]라면 [6102, 6210, 1062, 1026, 2610, 2106]를 만들 수 있고, 이중 가장 큰 수는 6210입니다.

0 또는 양의 정수가 담긴 배열 numbers가 매개변수로 주어질 때, 순서를 재배치하여 만들 수 있는 가장 큰 수를 문자열로 바꾸어 return 하도록 solution 함수를 작성해주세요.

제한 사항
 - numbers의 길이는 1 이상 100,000 이하입니다.
 - numbers의 원소는 0 이상 1,000 이하입니다.
 - 정답이 너무 클 수 있으니 문자열로 바꾸어 return 합니다.
********************/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(const string& a, const string& b) {
    return (a + b > b + a);
}

/*bool myCompare(const string& a, const string& b) {
    int a_size = a.size();
    int b_size = b.size();
    
    if(a_size == b_size)
        return a > b;
    else {
        if(a[0] != b[0])
            return a > b;
        else {
            string temp1 = a + b;
            string temp2 = b + a;
            return temp1 > temp2;
        }
    }
}*/

string solution(vector<int> numbers) {
    string answer = "";
    
    vector<string> num_str(numbers.size());
    for(size_t i = 0; i < numbers.size(); ++i)
        num_str[i] += to_string(numbers[i]);
    
    sort(num_str.begin(), num_str.end(), compare);
    
    for(int i = 0; i < num_str.size(); ++i)
        answer += num_str[i];
    
    if (answer[0] == '0')
        answer = "0";
    
    return answer;
}