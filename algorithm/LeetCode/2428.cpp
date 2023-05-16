class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
        int max1=0,m=grid.size(),n;
        int sum[155][155]={};
        for(int i=0;i<m;i++){
            n=grid[i].size();
            for(int j=1;j<=n;j++){
                    sum[i][j]= grid[i][j-1]+sum[i][j-1];
                }
            cout<<endl;
        }
        int res=0;
        for(int i=0;i<m-2;i++){
            n=grid[i].size();
            for(int j=1;j<=n-2;j++){
                res=sum[i][j+2]-sum[i][j-1]+grid[i+1][j]+sum[i+2][j+2]-sum[i+2][j-1];
                max1=max(res,max1);
            }
        }
        return max1;
    }
};
//先用前缀和处理注意从sum[][1]开始，sum[][0]=0;
//但好像数据范围太小了 跟直接枚举没什么区别