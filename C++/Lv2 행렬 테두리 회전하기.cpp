/********************
행렬 테두리 회전하기

문제 설명
rows x columns 크기인 행렬이 있습니다. 행렬에는 1부터 rows x columns까지의 숫자가 한 줄씩 순서대로 적혀있습니다. 
이 행렬에서 직사각형 모양의 범위를 여러 번 선택해, 테두리 부분에 있는 숫자들을 시계방향으로 회전시키려 합니다. 
각 회전은 (x1, y1, x2, y2)인 정수 4개로 표현하며, 그 의미는 다음과 같습니다.

x1 행 y1 열부터 x2 행 y2 열까지의 영역에 해당하는 직사각형에서 테두리에 있는 숫자들을 한 칸씩 시계방향으로 회전합니다.
다음은 6 x 6 크기 행렬의 예시입니다.

grid_example.png

이 행렬에 (2, 2, 5, 4) 회전을 적용하면, 아래 그림과 같이 2행 2열부터 5행 4열까지 영역의 테두리가 시계방향으로 회전합니다. 
이때, 중앙의 15와 21이 있는 영역은 회전하지 않는 것을 주의하세요.

rotation_example.png

행렬의 세로 길이(행 개수) rows, 가로 길이(열 개수) columns, 그리고 회전들의 목록 queries가 주어질 때, 
각 회전들을 배열에 적용한 뒤, 그 회전에 의해 위치가 바뀐 숫자들 중 가장 작은 숫자들을 순서대로 배열에 담아 
return 하도록 solution 함수를 완성해주세요.

제한사항
 - rows는 2 이상 100 이하인 자연수입니다.
 - columns는 2 이상 100 이하인 자연수입니다.
 - 처음에 행렬에는 가로 방향으로 숫자가 1부터 하나씩 증가하면서 적혀있습니다.
   - 즉, 아무 회전도 하지 않았을 때, i 행 j 열에 있는 숫자는 ((i-1) x columns + j)입니다.
 - queries의 행의 개수(회전의 개수)는 1 이상 10,000 이하입니다.
 - queries의 각 행은 4개의 정수 [x1, y1, x2, y2]입니다.
   - x1 행 y1 열부터 x2 행 y2 열까지 영역의 테두리를 시계방향으로 회전한다는 뜻입니다.
   - 1 ≤ x1 < x2 ≤ rows, 1 ≤ y1 < y2 ≤ columns입니다.
   - 모든 회전은 순서대로 이루어집니다.
   - 예를 들어, 두 번째 회전에 대한 답은 첫 번째 회전을 실행한 다음, 그 상태에서 두 번째 회전을 실행했을 때 이동한 숫자 중 최솟값을 구하면 됩니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//오른쪽, 아래, 왼쪽, 위 (시계방향)
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int helper(vector<vector<int>>& map, vector<int> query) {
    //x1, y1, x2, y2 따로 저장 
    int start_x = query[0] - 1;
    int start_y = query[1] - 1;
    int end_x   = query[2] - 1;
    int end_y   = query[3] - 1;
    
    int d = 0;
    //시작점을 미리 저장
    int prev_num = map[start_x][start_y];
    int min_num = map[start_x][start_y];
    
    //시계방향으로 진행
    int walk_x = start_x + dx[d];
    int walk_y = start_y + dy[d];
    
    bool finish = false;
    while(!finish) {
        //최초 시작점으로 돌아오면 마지막으로 작업 후 종료
        if(walk_x == start_x && walk_y == start_y) 
            finish = true;
        
        //시계방향으로 도는 중 오른쪽으로 이동이 끝났을 때
        if(walk_y == end_y && d == 0)
            d = 1;
        //시계방향으로 도는 중 아래로 이동이 끝났을 떄
        if(walk_x == end_x && d == 1)
            d = 2;
        //시계방향으로 도는 중 왼쪽으로 이동이 끝났을 때
        if(walk_y == start_y && d == 2)
            d = 3;
        
        min_num = min(min_num, map[walk_x][walk_y]);
        //이전 저장값과 현재값 교환
        swap(prev_num, map[walk_x][walk_y]);
        
        //시계방향으로 진행
        walk_x += dx[d];
        walk_y += dy[d];
    }
    //가장 작은 테두리값 반환 
    return min_num;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    
    vector<vector<int>> map(rows, vector<int>(columns));
    int start = 1;
    //맵
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            map[i][j] = start;
            start++;
        }
    }
    
    for(int i = 0; i < queries.size(); ++i) {
        int min = helper(map, queries[i]);
        answer.push_back(min);
    }
    
    return answer;
}