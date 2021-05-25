/********************
[3차] 방금그곡

문제 설명
라디오를 자주 듣는 네오는 라디오에서 방금 나왔던 음악이 무슨 음악인지 궁금해질 때가 많다. 
그럴 때 네오는 다음 포털의 '방금그곡' 서비스를 이용하곤 한다. 방금그곡에서는 TV, 라디오 등에서 나온 음악에 관해 제목 등의 정보를 제공하는 서비스이다.

네오는 자신이 기억한 멜로디를 가지고 방금그곡을 이용해 음악을 찾는다. 
그런데 라디오 방송에서는 한 음악을 반복해서 재생할 때도 있어서 네오가 기억하고 있는 멜로디는 음악 끝부분과 처음 부분이 이어서 재생된 멜로디일 수도 있다. 
반대로, 한 음악을 중간에 끊을 경우 원본 음악에는 네오가 기억한 멜로디가 들어있다 해도 그 곡이 네오가 들은 곡이 아닐 수도 있다. 
그렇기 때문에 네오는 기억한 멜로디를 재생 시간과 제공된 악보를 직접 보면서 비교하려고 한다. 다음과 같은 가정을 할 때 네오가 찾으려는 음악의 제목을 구하여라.

 - 방금그곡 서비스에서는 음악 제목, 재생이 시작되고 끝난 시각, 악보를 제공한다.
 - 네오가 기억한 멜로디와 악보에 사용되는 음은 C, C#, D, D#, E, F, F#, G, G#, A, A#, B 12개이다.
 - 각 음은 1분에 1개씩 재생된다. 음악은 반드시 처음부터 재생되며 음악 길이보다 재생된 시간이 길 때는 음악이 끊김 없이 처음부터 반복해서 재생된다. 
   음악 길이보다 재생된 시간이 짧을 때는 처음부터 재생 시간만큼만 재생된다.
 - 음악이 00:00를 넘겨서까지 재생되는 일은 없다.
 - 조건이 일치하는 음악이 여러 개일 때에는 라디오에서 재생된 시간이 제일 긴 음악 제목을 반환한다. 재생된 시간도 같을 경우 먼저 입력된 음악 제목을 반환한다.
 - 조건이 일치하는 음악이 없을 때에는 “(None)”을 반환한다.

입력 형식
입력으로 네오가 기억한 멜로디를 담은 문자열 m과 방송된 곡의 정보를 담고 있는 배열 musicinfos가 주어진다.
 - m은 음 1개 이상 1439개 이하로 구성되어 있다.
 - musicinfos는 100개 이하의 곡 정보를 담고 있는 배열로, 각각의 곡 정보는 음악이 시작한 시각, 끝난 시각, 음악 제목, 악보 정보가 ','로 구분된 문자열이다.
   - 음악의 시작 시각과 끝난 시각은 24시간 HH:MM 형식이다.
   - 음악 제목은 ',' 이외의 출력 가능한 문자로 표현된 길이 1 이상 64 이하의 문자열이다.
   - 악보 정보는 음 1개 이상 1439개 이하로 구성되어 있다.

출력 형식
조건과 일치하는 음악 제목을 출력한다.
********************/


#include <string>
#include <vector>
#include <sstream>

using namespace std;

// C, C#, D, D#, E, F, F#, G, G#, A, A#, B 12개
string solution(string m, vector<string> musicinfos) {
    vector<string> name;  //재생된 곡의 이름
    vector<int> time;     //재생된 시간
    
    //first - 곡의 코드를 다 치는데 걸리는 시간, second - 코드 배열
    vector<pair<int, vector<string>>> codes;
    
    //하나씩 split
    for(int i = 0; i < musicinfos.size(); ++i) {
        vector<string> temp;
        stringstream ss(musicinfos[i]);
        string buff;
        while(getline(ss, buff, ',')) {
            temp.push_back(buff);
        }
        
        //시간 계산
        string h1 = temp[0].substr(0,2); string m1 = temp[0].substr(3,2);
        string h2 = temp[1].substr(0,2); string m2 = temp[1].substr(3,2);
        int ih1 = stoi(h1); int ih2 = stoi(h2); 
        int im1 = stoi(m1); int im2 = stoi(m2);
        int len = (ih2 - ih1)*60 + (im2 - im1);
        
        //코드를 벡터로 하나씩 묶기
        vector<string> t_code;
        for(int c = 0; c < temp[3].size(); ++c) {
            string t = "";
            t += temp[3][c];
            if(temp[3][c + 1] == '#') {
                t += temp[3][c + 1];
                c++;
            }
            t_code.push_back(t);
        }
        int code_len = t_code.size();
        
        //플레이 된 시간만큼 다시 벡터에 저장
        vector<string> t_code2;
        for(int l = 0; l < len; ++l) {
            t_code2.push_back(t_code[l%code_len]);
        }
        
        codes.push_back({code_len, t_code2});
        name.push_back(temp[2]);
        time.push_back(len);
    }
    
    //멜로디 코드 하나씩 따로 저장한 배열
    vector<string> m_split;
    for(int i = 0; i < m.length(); ++i) {
        string m_temp = "";
        m_temp += m[i];
        if(m[i + 1] == '#') {
            m_temp += m[i + 1];
            ++i;
        }
        m_split.push_back(m_temp);
    }
    
    //조건이 일치하는 음악 찾기
    vector<int> pre_ans;
    for(int i = 0; i < codes.size(); ++i) {
        int m_s = 0, c_s = 0;
        bool check = false;
        if(m_split.size() > codes[i].second.size())
            continue;
        while(c_s < codes[i].second.size()) {
            if(m_s >= m_split.size()) {
                pre_ans.push_back(i);
                break;
            }
            
            if(codes[i].second[c_s] == m_split[m_s])
                ++m_s;
            else{
                if(!check) {
                    --c_s;
                    check = true;
                }
                else {
                    check = false;
                }
                m_s = 0;
            }
            ++c_s;
        }
        if(m_s == m_split.size()) 
            pre_ans.push_back(i);
    }
    
    int max_time = 0;
    int index = -1;
    for(int i = 0; i < pre_ans.size(); ++i) {
        if(max_time < time[pre_ans[i]]) {
            max_time = time[pre_ans[i]];
            index = pre_ans[i];
        }
    }
    
    return index != -1 ? name[index] : "(None)";
}