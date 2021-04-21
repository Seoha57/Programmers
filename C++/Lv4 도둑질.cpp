/********************
도둑질

문제 설명
도둑이 어느 마을을 털 계획을 하고 있습니다. 이 마을의 모든 집들은 동그랗게 배치되어 있습니다.

각 집들은 서로 인접한 집들과 방범장치가 연결되어 있기 때문에 인접한 두 집을 털면 경보가 울립니다.

각 집에 있는 돈이 담긴 배열 money가 주어질 때, 도둑이 훔칠 수 있는 돈의 최댓값을 return 하도록 solution 함수를 작성하세요.

제한사항
 - 이 마을에 있는 집은 3개 이상 1,000,000개 이하입니다.
 - money 배열의 각 원소는 0 이상 1,000 이하인 정수입니다.
********************/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> money) {
    //첫번째 집 시작
    vector<int> stolen1(money.size(), money[0]);
    //두번째 집 시작
    vector<int> stolen2(money.size(), money[1]);
    stolen2[0] = 0;
    
    for(int i = 2; i < money.size(); ++i) {
        stolen1[i] = max(stolen1[i - 1], money[i] + stolen1[i - 2]);
        stolen2[i] = max(stolen2[i - 1], money[i] + stolen2[i - 2]);
    }
    
    stolen1[money.size() - 1] -= min(stolen1[money.size() - 1], money[0]);
    
    return max(*max_element(stolen1.begin(), stolen1.end()), 
              *max_element(stolen2.begin(), stolen2.end()));
}