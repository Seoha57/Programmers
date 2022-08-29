#include <string>
#include <vector>

using namespace std;

int reverse(vector<int> b) {
    int answer = 0;
    int c = 1;
    for(int i = 0; i < b.size(); ++i) {
        answer += (b[i] * c);
        c *= 3;
    }
    return answer;
}

vector<int> make(int n, int e, int digit) {
    vector<int> b;
    while(digit >= 0) {
        if(e * 2 <= n) {
            b.push_back(2);
            n -= (e * 2);
        }
        else if(e <= n) {
            b.push_back(1);
            n -= e;
        }
        else
            b.push_back(0);
        
        e /= 3;
        --digit;
    }
    return b;
}

int solution(int n) {
    if(n == 1) return 1;
    else if (n == 2) return 2;
    
    int e = 1;
    int digit = 0;
    
    while(e < n) {
        e *= 3;
        digit++;
        if(e > n) {
            e /= 3;
            digit--;
            break;
        }
    }
    
    return reverse(make(n, e, digit));
}