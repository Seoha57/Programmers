/********************
네트워크

문제 설명
네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미합니다. 예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어있고, 컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때 컴퓨터 A와 컴퓨터 C도 간접적으로 연결되어 정보를 교환할 수 있습니다. 따라서 컴퓨터 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있습니다.

컴퓨터의 개수 n, 연결에 대한 정보가 담긴 2차원 배열 computers가 매개변수로 주어질 때, 네트워크의 개수를 return 하도록 solution 함수를 작성하시오.

제한사항
 - 컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
 - 각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
 - i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
 - computer[i][i]는 항상 1입니다.
********************/

#include <vector>
#include <queue>

using namespace std;

void helper(const vector<vector<int>>& computers, vector<bool>& visited, int start, 
           int& answer) {
    //모든 컴퓨터를 확인 해봤다면 종료
    if(start == -1) return;
    
    queue<int> q;
    //시작 컴퓨터 추가
    q.push(start);
	//네트워크 갯수 추가
    ++answer;
    
	//연결되어 있는 컴퓨터 탐방
    while(!q.empty()) {
        int com_num = q.front();
        q.pop();
        
        visited[com_num] = true;
        
        for(int i = 0; i < computers[com_num].size(); ++i) {
			//연결되어 있고 한번도 방문하지 않았을 경우에 추가
            if(computers[com_num][i] == 1 && !visited[i]) {
                q.push(i);
            }
        }
    }
    
    int next = -1;
	//방문하지 않았다는 것은 시작 컴퓨터와 연결되어 있지 않다는 뜻
    for(int i = 0; i < visited.size(); ++i) {
        if(visited[i] == false) {
            next = i;
            break;
        }
    }
    
    //방문하지 않은 컴퓨터를 시작점으로 반복시행
    helper(computers, visited, next, answer);
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<bool> visited(n, false);
    
    helper(computers, visited, 0, answer);
    
    return answer;
}

/************************ DFS **************************/
#include <string>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>>& computers, vector<bool>& visited, int from) {
	//시작 컴퓨터 방문 처리
    visited[from] = true;
    
    for(int to = 0; to < computers[from].size(); ++to) {
		//연결이 되어있고 방문하지 않은 컴퓨터일 때,
        if(computers[from][to] == 1 && !visited[to])
            dfs(computers, visited, to);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int network = 0;
    
    vector<bool> visited(n, false);
    for(int com = 0; com < n; ++com) {
		//방문하지 않았으면,
        if(!visited[com]) {
			//네트워크 추가 후 연결된 컴퓨터 찾기
            network++;
            dfs(computers, visited, com);
        }
    }
    
    return network;
}


/*********************** Find-Union ***************************/
#include <vector>
#include <set>

using namespace std;

int FindParent(vector<int>& parent, int x)
{
	if (parent[x] != x)
		parent[x] = FindParent(parent, parent[x]);

	return parent[x];
}

void UnionParent(vector<int>& parent, int a, int b)
{
	a = FindParent(parent, a);
	b = FindParent(parent, b);

	if (a < b)
		parent[b] = a;
	else
		parent[a] = b;
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    vector<int> parent(n, 0);
    for(int i = 0; i < n; ++i)
        parent[i] = i;
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(computers[i][j] && i != j) 
                UnionParent(parent, i, j);
        }
    }
    
    set<int> unions;
    for(int i = 0; i < parent.size(); ++i) {
        int p = FindParent(parent, parent[i]);
        unions.insert(p);
    }
    
    return unions.size();
}