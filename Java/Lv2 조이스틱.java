/********************
조이스틱

문제 설명
조이스틱으로 알파벳 이름을 완성하세요. 맨 처음엔 A로만 이루어져 있습니다.
ex) 완성해야 하는 이름이 세 글자면 AAA, 네 글자면 AAAA

조이스틱을 각 방향으로 움직이면 아래와 같습니다.
▲ - 다음 알파벳
▼ - 이전 알파벳 (A에서 아래쪽으로 이동하면 Z로)
◀ - 커서를 왼쪽으로 이동 (첫 번째 위치에서 왼쪽으로 이동하면 마지막 문자에 커서)
▶ - 커서를 오른쪽으로 이동

만들고자 하는 이름 name이 매개변수로 주어질 때, 이름에 대해 조이스틱 조작 횟수의 최솟값을 return 하도록 solution 함수를 만드세요.

제한 사항
 - name은 알파벳 대문자로만 이루어져 있습니다.
 - name의 길이는 1 이상 20 이하입니다.
********************/

import java.lang.*;

class Solution {
    public int UpDown(char alpha) {
        return Math.min(alpha - 'A', 1 + 'Z' - alpha);
    }
    
    public int solution(String name) {
        int answer = 0;
		
        /*************
		case 1 -> 오른쪽으로만 이동               ex) BBBAA
		case 2 -> 왼쪽으로만 이동                 ex) AAABB
		case 3 -> 오른쪽으로 이동 후 왼쪽으로 이동  ex) BBAAAABBBB
		case 4 -> 왼쪽으로 이동 후 오른쪽으로 이동  ex) BBBBAAAABB
		*************/
		
		//오른쪽으로 쭉, 왼쪽으로 쭉, 오른쪽으로 절반, 왼쪽으로 절반
        int left = 0, right = 0, r_half = 0, l_half = 0;
        int size = name.length();
        int mid = size / 2;
              
        answer += UpDown(name.charAt(0));
        for(int i = 1; i < size; ++i) {
            answer += UpDown(name.charAt(i));
            
			
			/*이동한 횟수 계산*/
            if(name.charAt(i) != 'A') {  	   //오른쪽으로 이동 중 A가 아니면
                right = i;               	   //오른쪽 이동횟수 = 현재 인덱스로 업데이트
                if(i <= mid) {           	   
                    r_half = i;          	   //오른쪽으로 이동 중 A가 아닌값의 인덱스가 가운데보다 작으면
                }                        	   //오른쪽 절반 완성하는데 걸리는 이동횟수
            }
            if(name.charAt(size - i) != 'A') { //왼쪽으로 이동 중 A가 아니면
                left = i;                      //왼쪽 이동횟수 = 현재 인덱스로 업데이트
                if(i <= mid) {                 
                    l_half = i;                //왼쪽으로 이동 중 A가 아닌값의 인덱스가 가운데보다 크면
                }                              //왼쪽 절반 완성하는데 걸리는 이동횟수
            }
        }
        
		//min(front, back) -> min(오른쪽으로만 이동, 왼쪽으로만 이동)
		//min(half_f * 2 + half_b, half_b * 2 + half_f) 
		// -> min(오른쪽으로 이동 후 왼쪽으로, 왼쪽으로 이동 후 오른쪽으로 이동)
        answer += Math.min(right, Math.min(left, 
                        Math.min(r_half * 2 + l_half, l_half * 2 + r_half)));
        
        return answer;
    }
}