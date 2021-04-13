/********************
주식가격

문제 설명
초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.

제한사항
 - prices의 각 가격은 1 이상 10,000 이하인 자연수입니다.
 - prices의 길이는 2 이상 100,000 이하입니다.
********************/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size(), 0);
    
    for(size_t i = 0; i < answer.size(); ++i) {
        for(size_t j = i + 1; j < prices.size(); ++j) {
            //1초 더해줌
            ++answer[i];
            
            //가격이 떨어지면 멈춤
            if(prices[i] > prices[j])
                break;
        }
    }
    
    return answer;
}