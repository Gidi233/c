class Solution {
public:
    int binaryGap(int n) {
        int ans=0,ci=0,flag=0;
        while(n>0){
            if(n&1){//=n%2
                flag=1;
                ans=max(ans,ci);
                ci=1;
            }
            else{
                if(flag==1) ci++;
            }
            n>>=1;
        }
        return ans;
    }
};

//记录经过0的ci数

class Solution {
public:
    int binaryGap(int n) {
        int last = -1, ans = 0;
        for (int i = 0; n; ++i) {
            if (n & 1) {
                if (last != -1) {
                    ans = max(ans, i - last);
                }
                last = i;
            }
            n >>= 1;
        }
        return ans;
    }
};

//记录上一个1的位置