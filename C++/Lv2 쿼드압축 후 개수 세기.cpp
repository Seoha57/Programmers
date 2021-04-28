/********************
쿼드압축 후 개수 세기

문제 설명
0과 1로 이루어진 2n x 2n 크기의 2차원 정수 배열 arr이 있습니다. 당신은 이 arr을 쿼드 트리와 
같은 방식으로 압축하고자 합니다. 구체적인 방식은 다음과 같습니다.

당신이 압축하고자 하는 특정 영역을 S라고 정의합니다.
만약 S 내부에 있는 모든 수가 같은 값이라면, S를 해당 수 하나로 압축시킵니다.
그렇지 않다면, S를 정확히 4개의 균일한 정사각형 영역(입출력 예를 참고해주시기 바랍니다.)으로 쪼갠 뒤, 
각 정사각형 영역에 대해 같은 방식의 압축을 시도합니다.
arr이 매개변수로 주어집니다. 위와 같은 방식으로 arr을 압축했을 때, 배열에 최종적으로 남는 0의 개수와 1의 
개수를 배열에 담아서 return 하도록 solution 함수를 완성해주세요.

제한사항
 - arr의 행의 개수는 1 이상 1024 이하이며, 2의 거듭 제곱수 형태를 하고 있습니다. 즉, arr의 
   행의 개수는 1, 2, 4, 8, ..., 1024 중 하나입니다.
 - arr의 각 행의 길이는 arr의 행의 개수와 같습니다. 즉, arr은 정사각형 배열입니다.
 - arr의 각 행에 있는 모든 값은 0 또는 1 입니다.
********************/

#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> QUAD;

bool quadCheck(QUAD quad) {
    //같은 숫자로만 이루어졌는지 체크
    int n = quad[0][0];
    for(int i = 0; i < quad.size(); ++i) {
        for(int j = 0; j < quad[i].size(); ++j) {
            if(n != quad[i][j])
                return false;
        }
    }
    return true;
}

void helper(QUAD arr, vector<int>& answer) {
    int x_half = arr[0].size() / 2;
    int y_half = arr.size() / 2;
    
    vector<QUAD> newQ;
    int start_x[4] = {0, x_half, 0, x_half};
    int start_y[4] = {0, 0, y_half, y_half};
    int end_x[4] = {x_half, x_half * 2, x_half, x_half * 2};
    int end_y[4] = {y_half, y_half, y_half * 2, y_half * 2};
    
    //쿼드 나누기
    for(int i = 0; i < 4; ++i) {
        QUAD q;
        for(int y = start_y[i]; y < end_y[i]; ++y) {
            vector<int> row;
            for(int x = start_x[i]; x < end_x[i]; ++x) {
                row.push_back(arr[y][x]);
            }
            q.push_back(row);
        }
        newQ.push_back(q);
    }
    
    //같은 수로만 이루어진 쿼드면 합치고 갯수 더하기
    //다른 숫자 있으면 다시 진행
    for(int i = 0; i < newQ.size(); ++i) {
        if(!quadCheck(newQ[i]))
            helper(newQ[i], answer);
        else
            answer[newQ[i][0][0]]++;
    }
    
    return;
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer(2, 0);
    if(quadCheck(arr)) {
        ++answer[arr[0][0]];
        return answer;
    }
    
    helper(arr, answer);
    
    return answer;
}