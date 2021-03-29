/********************
소수 찾기

문제 설명
한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.

각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.

제한사항
 - numbers는 길이 1 이상 7 이하인 문자열입니다.
 - numbers는 0~9까지 숫자만으로 이루어져 있습니다.
 - "013"은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.
********************/

import java.util.*;

class Solution {
    public boolean isPrime(int num) {
        if(num == 0 || num == 1) return false;
        
        for(int i = 2; i <= num/2; ++i) {
            if((num % i) == 0) return false;
        }
        return true;
    }
    
    public boolean nextPermutation(int[] nums) {
        if(nums.length <= 1)
            return false;
        
        int a = nums.length - 2;
        //첫번째로 감소하는 숫자 찾기
        while(a >= 0 && nums[a] >= nums[a + 1]) --a;
        
        // 감소하는 숫자가 없으면 permutation 종료
        if(a < 0) return false;
        
        //a보다 큰 숫자 찾기
        int b = nums.length - 1;
        while(nums[a] >= nums[b]) --b;
        swap(nums, a, b);
        
        //a+1에서부터 끝까지 오름차순 정렬
        int start = a + 1;
        int end = nums.length - 1;
        while(start < end) {
            swap(nums, start++, end--);
        }
        
        return true;
    }
    
    private void swap(int[] nums, int a, int b) {
        int temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
    }
        
    public int solution(String numbers) {
        int answer = 0;
        /*String[] str_arr = numbers.split("");
        int[] nums_int = new int[str_arr.length];
        for(int i = 0; i < str_arr.length; i++) {
            nums_int[i] = Integer.parseInt(str_arr[i]);
        }*/
        //int[] nums_int = numbers.chars().map(i->i-'0').toArray();
        
        String[] str_arr = numbers.split("");
        int[] nums_perm_init = new int[str_arr.length];
        for(int i = 0; i < str_arr.length; ++i) {
            nums_perm_init[i] = i;
        }
        
        List<Integer> checkList = new ArrayList<>();
        for(int i = 1; i <= str_arr.length; ++i) {
            int[] nums_perm = Arrays.copyOf(nums_perm_init, nums_perm_init.length);
            do {
                String temp = "";
                //합칠 갯수만큼 더하기
                for(int j = 0; j < i; ++j) {
                    temp += str_arr[nums_perm[j]];
                }
                
                //011, 11 string은 달라 int로 변경
                int num = Integer.parseInt(temp);
                //이미 체크했던 숫자면 패스
                if(!checkList.contains(Integer.valueOf(num))) {
                    if(isPrime(num)) {
                        checkList.add(num);
                        answer++;
                    }
                }
            }while(nextPermutation(nums_perm));
        }
        
        return answer;
    }
}