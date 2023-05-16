class Solution {

public:

    int maximizeWin(vector<int> &prizePositions, int k) {

        int left = 0,ans=0,j=0,n = prizePositions.size(), max0=0,max1=0,num[n + 1],pre[n+1];
        pre[0]=0;
        num[0] = 0;

        // for(int right=0;right<n;right++){
        //     if(prizePositions[right+1]!=prizePositions[right]){
        //             num[prizePositions[right+1]]=right+1;
        //     }
        //     else continue;想用num数组记录每一个变化的下标，更新pre，right循环找完，left就可以直接移动
        for (int right = 0; right < n; right++) {

            while (prizePositions[right] - prizePositions[left] > k) ++left;

            ans = max(ans, right - left + 1 + pre[left]);

            pre[right + 1] = max(pre[right], right - left + 1);

        }

        }
        return ans;
};
//pre记录到这一位之前的一段线段的最大值
