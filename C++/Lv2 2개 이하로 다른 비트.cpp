/********************
2개 이하로 다른 비트

문제 설명
양의 정수 x에 대한 함수 f(x)를 다음과 같이 정의합니다.
 - x보다 크고 x와 비트가 1~2개 다른 수들 중에서 제일 작은 수
예를 들어,
 - f(2) = 3 입니다. 다음 표와 같이 2보다 큰 수들 중에서 비트가 다른 지점이 2개 이하이면서 제일 작은 수가 3이기 때문입니다.
   수	비트	        다른 비트의 개수
   2	000...0010	
   3	000...0011	1
 - f(7) = 11 입니다. 다음 표와 같이 7보다 큰 수들 중에서 비트가 다른 지점이 2개 이하이면서 제일 작은 수가 11이기 때문입니다.
   수	비트	        다른 비트의 개수
   7	000...0111	
   8	000...1000	4
   9	000...1001	3
   10	000...1010	3
   11	000...1011	2
정수들이 담긴 배열 numbers가 매개변수로 주어집니다. numbers의 모든 수들에 대하여 각 수의 f 값을 배열에 차례대로 
담아 return 하도록 solution 함수를 완성해주세요.

제한사항
 - 1 ≤ numbers의 길이 ≤ 100,000
 - 0 ≤ numbers의 모든 수 ≤ 1015
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string DecToBin(long long n) {
    string temp = "";
    while(n > 0) {
        temp += to_string(n % 2);
        n /= 2;
    }
    temp += '0';
    reverse(temp.begin(), temp.end());
    return temp;
}

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    
    for(long long n : numbers) {
        string bin_n = DecToBin(n);
        int len = bin_n.length() - 1;
        if(bin_n[len] == '0') {
            answer.push_back(n + 1);
            continue;
        }
        for(int i = len; i >= 0; --i) {
            if(bin_n[i] == '0') {
                bin_n[i] = '1';
                bin_n[i + 1] = '0';
                break;
            }
        }
        long long next = stoll(bin_n, nullptr, 2);
        answer.push_back(next);
    }
    
    return answer;
}



/****************************** 효율성X **********************************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> IntToBinary(long long n) {
    vector<bool> bin;
    
    while(n > 0) {
        bin.push_back(n % 2);
        n /= 2;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

bool CheckDiff(long long n, vector<bool> init) {
    int index = init.size() - 1;
    int cnt = 0;
    while(n > 0) {
        if(index < 0 || n % 2 != init[index])
            cnt++;
        
        n /= 2;
        if(cnt > 2)
            return false;
        index--;
    }
    return cnt <= 2;
}

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    
    for(int i = 0; i < numbers.size(); ++i) {
        vector<bool> binary_n = IntToBinary(numbers[i]);
        long long next = numbers[i];
        while(true) {
            next++;
            if(CheckDiff(next, binary_n)) break;
        }
        answer.push_back(next);
    }
    
    return answer;
}