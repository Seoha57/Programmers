/********************
정수 삼각형

문제 설명

        7
      3   8
    8   1   0
  2   7   4   4
4   5   2   6   5

위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

제한사항
삼각형의 높이는 1 이상 500 이하입니다.
삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.
********************/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    for(int i = 1; i < triangle.size(); ++i) {
        //계산값 저장을 위한 temp
        vector<int> temp(triangle[i].size(), 0);
        for(int j = 0; j < triangle[i].size(); ++j) {
            int left_up = 0, right_up = 0;
            int value = triangle[i][j];
            if(j == 0) {
                right_up = triangle[i - 1][0];
            }
            else if(j == triangle[i].size() - 1) {
                left_up = triangle[i - 1][j - 1];
            }
            else {
                left_up = triangle[i - 1][j - 1];
                right_up = triangle[i - 1][j];
            }
            //왼쪽 위와 오른쪽 위의 값 중 큰 값과 자기 자신을 더함
            temp[j] = max(left_up, right_up) + value;
        }
        
        //삼각형 가로행 업데이트
        for(int t = 0; t < temp.size(); ++t) {
            triangle[i][t] = temp[t];
        }
    }
    
    return *max_element(triangle[triangle.size()-1].begin(),
                        triangle[triangle.size()-1].end());
}
