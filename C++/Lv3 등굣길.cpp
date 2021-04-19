/********************
등굣길

문제 설명
계속되는 폭우로 일부 지역이 물에 잠겼습니다. 물에 잠기지 않은 지역을 통해 학교를 가려고 합니다. 집에서 학교까지 가는 길은 m x n 크기의 격자모양으로 나타낼 수 있습니다.

아래 그림은 m = 4, n = 3 인 경우입니다.

가장 왼쪽 위, 즉 집이 있는 곳의 좌표는 (1, 1)로 나타내고 가장 오른쪽 아래, 즉 학교가 있는 곳의 좌표는 (m, n)으로 나타냅니다.

격자의 크기 m, n과 물이 잠긴 지역의 좌표를 담은 2차원 배열 puddles이 매개변수로 주어집니다. 오른쪽과 아래쪽으로만 움직여 집에서 학교까지 갈 수 있는 최단경로의 개수를 1,000,000,007로 나눈 나머지를 return 하도록 solution 함수를 작성해주세요.

제한사항
 - 격자의 크기 m, n은 1 이상 100 이하인 자연수입니다.
 - m과 n이 모두 1인 경우는 입력으로 주어지지 않습니다.
 - 물에 잠긴 지역은 0개 이상 10개 이하입니다.
 - 집과 학교가 물에 잠긴 경우는 입력으로 주어지지 않습니다.
********************/

/************************ DFS(효율성x) **************************/
#include <string>
#include <vector>

using namespace std;

int temp = 0;

void dfs(const vector<vector<int>>& map, vector<vector<bool>>& visited,
         int m, int n, int x, int y, int& answer) {
    if(x < 1 || x > n || y < 1 || y > m) 
        return;
    
    if(x == n && y == m) {
        ++answer;
        if(answer == 1000000007) {
            temp++;
            answer = temp;
        }
        return;
    }
    
    if(map[x][y] == 1 || visited[x][y] == true)
        return;
    
    visited[x][y] = true;
    dfs(map, visited, m, n, x + 1, y, answer);
    dfs(map, visited, m, n, x, y + 1, answer);
    visited[x][y] = false;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    vector<vector<int>> map(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i < puddles.size(); ++i) {
        map[puddles[i][1]][puddles[i][0]] = 1;
    }
    
    int start_x = 1, start_y = 1;
    
    vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, false));
    dfs(map, visited, m, n, start_x, start_y, answer);
    
    return answer;
}


/************************ DP **************************/
#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    
    vector<vector<int>> map(n + 1, vector<int>(m + 1, 1));
    for(int i = 0; i < puddles.size(); ++i) {
        map[puddles[i][1]][puddles[i][0]] = 0;
    }
    
    for(int row = 1; row <= n; ++row) {
        for(int col = 1; col <= m; ++col) {
            if(row - 1 <= 0 && col - 1 <= 0)
                continue;
            
            if(map[row][col] == 0) continue;
            
            if(row - 1 <= 0 && col - 1 > 0)
                map[row][col] = map[row][col - 1] % 1000000007;
            else if(row - 1 > 0 && col - 1 <= 0)
                map[row][col] = map[row - 1][col] % 1000000007;
            else
                map[row][col] = (map[row - 1][col] + map[row][col - 1]) % 1000000007;
        }
    }
    
    return map[n][m];
}
