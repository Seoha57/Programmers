#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> UniqueReport(vector<string> report) {
    vector<string> new_report;
    sort(report.begin(), report.end());
    string s = report[0];
    new_report.push_back(s);
    for(int i = 1; i < report.size(); ++i) {
        if(s.compare(report[i]) == 0)
            continue;
        
        s = report[i];
        new_report.push_back(s);
    }
    
    return new_report;
}

vector<string> SplitReport(string s) {
    vector<string> r;
    size_t leng = s.length();
    for(int i = 0; i < s.length(); ++i) {
        if(s[i] ==' ') {
            
            string first = s.substr(0, i);
            string second = s.substr(i + 1, leng - i);
            
            r.push_back(first);
            r.push_back(second);
            
            break;
        }
    }
    
    return r;
}

vector<int> CountReported(vector<string> id_list, vector<string> report) {
    vector<int> reported(id_list.size());
    for(int i = 0; i < report.size(); ++i) {
        vector<string> r = SplitReport(report[i]);
        
        for(int j = 0; j < id_list.size(); ++j) {
            if(id_list[j].compare(r[1]) == 0) {
                ++reported[j];
                break;
            }
        }
    }
    
    return reported;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size());
    vector<string> new_report = UniqueReport(report);
    
    vector<int> reported = CountReported(id_list, new_report);
    
    for(int i = 0; i < new_report.size(); ++i) {
        vector<string> r = SplitReport(new_report[i]);
        
        auto r1 = find(id_list.begin(), id_list.end(), r[0]);
        auto r2 = find(id_list.begin(), id_list.end(), r[1]);
        
        if(reported[r2-id_list.begin()] >= k)
            ++answer[r1-id_list.begin()];
    }
    
    return answer;
}