#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool OddOrEven(int num) {
    
}

int solution(int left, int right) {
    int answer = 0;
    
    for(int i = left; i <= right; ++i) {
        int half = sqrt(i);
        
        if(pow(half,2) != i)
            answer += i;
        else
            answer -= i;
    }
    
    return answer;
}