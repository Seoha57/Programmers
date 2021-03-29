/********************
N개의 최소공배수

문제 설명
두 수의 최소공배수(Least Common Multiple)란 입력된 두 수의 배수 중 공통이 되는 가장 작은 숫자를 의미합니다. 예를 들어 2와 7의 최소공배수는 14가 됩니다. 정의를 확장해서, n개의 수의 최소공배수는 n 개의 수들의 배수 중 공통이 되는 가장 작은 숫자가 됩니다. n개의 숫자를 담은 배열 arr이 입력되었을 때 이 수들의 최소공배수를 반환하는 함수, solution을 완성해 주세요.

제한 사항
arr은 길이 1이상, 15이하인 배열입니다.
arr의 원소는 100 이하인 자연수입니다.
********************/

#include <string>
#include <vector>
#include <queue>

using namespace std;

/*최대공약수*/
int GCD(int a, int b) {
    /* 루프형
	while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
	return a;
	*/
	
	//recursive
    if(b == 0)
        return a;
    return GCD(b, a%b);
}

/*최소공배수*/
int LCM(int a, int b) {
    return a * b / GCD(a,b);
}

int solution(vector<int> arr) { 
    //작은 수 부터 하기 위하여 priority queue 사용
    priority_queue<int> num;
    for(int i = 0; i < arr.size(); ++i)
        num.push(arr[i]);
    
    while(num.size() >= 2) {
        //작은 수 두개 뽑기
        int num1 = num.top();
        num.pop();
        int num2 = num.top();
        num.pop();
        
		//최소공배수 구하고 queue에 넣기
        num.push(LCM(num1, num2));
    }
    
    return num.top();
}