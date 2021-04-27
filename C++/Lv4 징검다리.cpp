/********************
징검다리
문제 설명
출발지점부터 distance만큼 떨어진 곳에 도착지점이 있습니다. 그리고 그사이에는 바위들이 놓여있습니다. 바위 중 몇 개를 제거하려고 합니다.
예를 들어, 도착지점이 25만큼 떨어져 있고, 바위가 [2, 14, 11, 21, 17] 지점에 놓여있을 때 바위 2개를 제거하면 출발지점, 도착지점, 
바위 간의 거리가 아래와 같습니다.

제거한 바위의 위치	각 바위 사이의 거리	거리의 최솟값
[21, 17]	    [2, 9, 3, 11]	    2
[2, 21]	        [11, 3, 3, 8]	    3
[2, 11]	        [14, 3, 4, 4]	    3
[11, 21]	    [2, 12, 3, 8]	    2
[2, 14]      	[11, 6, 4, 4]	    4
위에서 구한 거리의 최솟값 중에 가장 큰 값은 4입니다.

출발지점부터 도착지점까지의 거리 distance, 바위들이 있는 위치를 담은 배열 rocks, 제거할 바위의 수 n이 매개변수로 주어질 때, 
바위를 n개 제거한 뒤 각 지점 사이의 거리의 최솟값 중에 가장 큰 값을 return 하도록 solution 함수를 작성해주세요.

제한사항
 - 도착지점까지의 거리 distance는 1 이상 1,000,000,000 이하입니다.
 - 바위는 1개 이상 50,000개 이하가 있습니다.
 - n 은 1 이상 바위의 개수 이하입니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    int nRock = rocks.size();
    if(nRock == n) return distance;
    
    sort(rocks.begin(), rocks.end());
    int start = 1;
    int end = distance;
    
    while(start <= end) {
        int mid = (start + end) / 2;
        int remove = 0;
        int prevIndex = -1;
        for(int i = 0; i <= rocks.size(); ++i) {
            int d = (prevIndex == -1) ? rocks[i] :  
            (i == rocks.size()) ? distance - rocks[i] : rocks[i] - rocks[prevIndex];
            
            if(d < mid)
                remove++;
            else
                prevIndex = i;
        }
        if (remove > n) {
            end = mid - 1;
        } 
        else {
            start = mid + 1;
            answer = max(answer,mid);
        }
    }
    
    return answer;
}

/************************ DFS(타임 아웃) **************************/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int distMin(const vector<int>& rocks, const vector<bool>& used, int count, int dist) {
    int min_dist = 1e9;
    int cnt = 0;
    for(int i = 0; i < used.size() - 1; ++i) {
        if(used[i] == true) continue;
        if(used[i] == false && cnt == 0) {
            min_dist = rocks[i];
            cnt++;
        }
        for(int j = i + 1; j < used.size(); ++j) {
            if(used[j] == false) {
                min_dist = min(min_dist, rocks[j] - rocks[i]);
                cnt++;
                
                if(cnt == (rocks.size() - count))
                    min_dist = min(min_dist, dist - rocks[j]);
                break;
            }
        }
        if(cnt == (rocks.size() - count))
            break;
    }
    
    return min_dist;
}

void dfs(const vector<int>& rocks, vector<bool>& used, int n, int dist,
         int count, int& answer) {
    if(count == n) {
        answer = max(answer, distMin(rocks, used, count, dist));
        return;
    }
    
    for(int i = 0; i < rocks.size(); ++i) {
        if(used[i] == true) continue;
        
        used[i] = true;
        dfs(rocks, used, n, dist, count + 1, answer);
        used[i] = false;
    }
}

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    sort(rocks.begin(), rocks.end());
    vector<bool> used(rocks.size(), false);
    dfs(rocks, used, n, distance, 0, answer);
    
    return answer;
}