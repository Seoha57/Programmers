/********************
여행경로

문제 설명
주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 "ICN" 공항에서 출발합니다.

항공권 정보가 담긴 2차원 배열 tickets가 매개변수로 주어질 때, 방문하는 공항 경로를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

제한사항
 - 모든 공항은 알파벳 대문자 3글자로 이루어집니다.
 - 주어진 공항 수는 3개 이상 10,000개 이하입니다.
 - tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
 - 주어진 항공권은 모두 사용해야 합니다.
 - 만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
 - 모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int max_count = 0;

void dfs(const vector<vector<string>>& tickets, vector<string>& temp, 
         vector<bool>& visited, string start, int count, int max_count,
         vector<string>& answer) {
    if(count == max_count) {
        //모든 도시 다 돌았으면 정답에 복사
        answer = temp;
        return;
    }
    
    for(int i = 0; i < tickets.size(); ++i) {
        if(tickets[i][0] == start && visited[i] == false) {
            visited[i] = true;
            temp.push_back(tickets[i][1]);
            dfs(tickets, temp, visited, tickets[i][1], count + 1, max_count, answer);
            visited[i] = false;
            temp.pop_back();
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
	//asc로 정렬 할 경우 같은 결론을 가진 더 큰 알파벳이 오버로딩 되므로 desc로 정렬
    sort(tickets.begin(), tickets.end(), greater<vector<string>>());
    
    int max_count = tickets.size();
    vector<bool> visited(max_count, false);
    //방문한 도시 임시 저장을 위한 temp
    vector<string> temp;
    //출발도시 미리 추가
    string start = "ICN";
    temp.push_back(start);
    
    dfs(tickets, temp, visited, start, 0, max_count, answer);
    
    return answer;
}