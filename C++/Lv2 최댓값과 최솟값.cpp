/********************
최댓값과 최솟값

문제 설명
문자열 s에는 공백으로 구분된 숫자들이 저장되어 있습니다. str에 나타나는 숫자 중 최소값과 최대값을 찾아 이를 "(최소값) (최대값)"형태의 문자열을 반환하는 함수, solution을 완성하세요.
예를들어 s가 "1 2 3 4"라면 "1 4"를 리턴하고, "-1 -2 -3 -4"라면 "-4 -1"을 리턴하면 됩니다.

제한 조건
s에는 둘 이상의 정수가 공백으로 구분되어 있습니다.
********************/

#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    string answer = "";
    
    //string 숫자를 int로 담을 컨테이너
    vector<int> nums;
    string temp = "";
    for(size_t i = 0; i < s.size(); ++i) {
        //공백 발견시 숫자로 변환
        if(s[i] == ' ') {
            nums.push_back(stoi(temp));
            temp = "";
            continue;
        }
        temp += s[i];
    }
    
    nums.push_back(stoi(temp));
    
    int max = nums[0], min = nums[0];
    for(int i = 1; i < nums.size(); ++i) {
        if(nums[i] > max) max = nums[i];
        if(nums[i] < min) min = nums[i];
    }
    
    answer = to_string(min) + " " + to_string(max);
    
    return answer;
}
