#include <string>
#include <vector>

using namespace std;

bool Matching(vector<int> win_nums, int num) {

    for(int i = 0; i < win_nums.size(); ++i) {
        if (win_nums[i] == num)
            return true;
    }
    
    return false;
}

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int max = 0, min = 0;
    for(int i = 0; i < lottos.size(); ++i) {
        if(lottos[i] == 0) {
            max++;
            continue;
        }
        
        if(Matching(win_nums,lottos[i])) {
            max++;
            min++;
        }
    }
    
    max = 7 - max;
    max = max >= 6 ? 6 : max;
    answer.push_back(max);
    min = 7 - min;
    min = min >= 6 ? 6 : min;
    answer.push_back(min);
    
    return answer;
}