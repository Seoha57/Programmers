/********************
소수 찾기

문제 설명
한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.

각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.

제한사항
 - numbers는 길이 1 이상 7 이하인 문자열입니다.
 - numbers는 0~9까지 숫자만으로 이루어져 있습니다.
 - "013"은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool IsPrime(int n) {
    if(n == 0 || n == 1) return false;
    
    for(int i = 2; i <= n / 2; ++i) {
        if(n % i == 0) return false;
    }
    return true;
}

int solution(string numbers) {
    int answer = 0;
    
    vector<bool> list(1e7, false);
    vector<int> indices;
    for(size_t i = 0; i < numbers.size(); ++i)
        indices.push_back(i);
    
    for(size_t i = 1; i <= numbers.size(); ++i) {
        do {
            string s_num = "";
            for(int j = 0; j < i; ++j) 
                s_num += numbers[indices[j]];
            
            int num = stoi(s_num);
            
            if(list[num]) continue;
            
            list[num] = true;
            if(IsPrime(num)) answer++;
            
        }while(next_permutation(indices.begin(), indices.end()));
        sort(indices.begin(), indices.end());
    }
        
    return answer;
}