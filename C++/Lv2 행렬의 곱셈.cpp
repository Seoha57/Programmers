/********************
행렬의 곱셈

문제 설명
2차원 행렬 arr1과 arr2를 입력받아, arr1에 arr2를 곱한 결과를 반환하는 함수, solution을 완성해주세요.

제한 조건
 - 행렬 arr1, arr2의 행과 열의 길이는 2 이상 100 이하입니다.
 - 행렬 arr1, arr2의 원소는 -10 이상 20 이하인 자연수입니다.
 - 곱할 수 있는 배열만 주어집니다.
********************/

#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer(arr1.size(), vector<int>(arr2[0].size(), 0));
    
    for(int i = 0; i < answer.size(); ++i) {
        for(int j = 0; j < answer[i].size(); ++j) {
            int index = 0;
            while(index < arr1[i].size()) {
                answer[i][j] += (arr1[i][index] * arr2[index][j]);
                index++;
            }
        }
    }
    
    return answer;
}