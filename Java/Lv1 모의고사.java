/********************
모의고사

문제 설명
수포자는 수학을 포기한 사람의 준말입니다. 수포자 삼인방은 모의고사에 수학 문제를 전부 찍으려 합니다. 수포자는 1번 문제부터 마지막 문제까지 다음과 같이 찍습니다.

1번 수포자가 찍는 방식: 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, ...
2번 수포자가 찍는 방식: 2, 1, 2, 3, 2, 4, 2, 5, 2, 1, 2, 3, 2, 4, 2, 5, ...
3번 수포자가 찍는 방식: 3, 3, 1, 1, 2, 2, 4, 4, 5, 5, 3, 3, 1, 1, 2, 2, 4, 4, 5, 5, ...

1번 문제부터 마지막 문제까지의 정답이 순서대로 들은 배열 answers가 주어졌을 때, 가장 많은 문제를 맞힌 사람이 누구인지 배열에 담아 return 하도록 solution 함수를 작성해주세요.

제한 조건
시험은 최대 10,000 문제로 구성되어있습니다.
문제의 정답은 1, 2, 3, 4, 5중 하나입니다.
가장 높은 점수를 받은 사람이 여럿일 경우, return하는 값을 오름차순 정렬해주세요.
********************/

import java.util.*;
import javafx.util.*;

class Solution {
    public int[] solution(int[] answers) {        
        int[] no1 = {1,2,3,4,5};
        int[] no2 = {2,1,2,3,2,4,2,5};
        int[] no3 = {3,3,1,1,2,2,4,4,5,5};
        
        int[] correct = new int[3];
        
        for(int i = 0; i < answers.length; ++i) {
            if(no1[i%5] == answers[i])
                ++correct[0];
            
            if(no2[i%8] == answers[i])
                ++correct[1];
            
            if(no3[i%10] == answers[i])
                ++correct[2];
        }
        
        //key - index, value - num of correct
        Deque<Pair<Integer, Integer>> high = new ArrayDeque<Pair<Integer, Integer>>();
        Pair<Integer, Integer> temp = new Pair<Integer, Integer>(1, correct[0]);
        high.add(temp);
        for(int i = 1; i < 3; ++i) {
            temp = new Pair<Integer, Integer>(i + 1, correct[i]);
            for(Pair list : high) {
                int num_correct = (int)list.getValue();
                if(num_correct < correct[i]) {
                    high.clear();
                    high.add(temp);
                }
                else if(num_correct == correct[i]) {
                    high.add(temp);
                    break;
                }
            }
        }
        
        int[] answer = new int[high.size()];
        int index = 0;
        for(Pair list : high) {
            answer[index] = (int)list.getKey();
            index++;
        }
        
        return answer;
        
        //다른 사람의 풀이
        /*int maxScore = Math.max(correct[0], Math.max(correct[1], correct[2]));
        ArrayList<Integer> list = new ArrayList<>();
        if(maxScore == correct[0]) {list.add(1);}
        if(maxScore == correct[1]) {list.add(2);}
        if(maxScore == correct[2]) {list.add(3);}
        return list.stream().filter(i->i!=null).mapToInt(i->i.intValue()).toArray();*/
    }
}