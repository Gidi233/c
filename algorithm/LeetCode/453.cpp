class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n=nums.size();
        int res=0;
        sort(nums.begin(),nums.end());
        for(int i=1;i<n;i++){
            res+=nums[i]-nums[0];
        }
        return res;
    }
};
//��n-1��Ԫ��+1�͵�����һ������Сֵ-1 �������ҵ������е���Сֵ����ÿ��Ԫ������Сֵ�Ĳ���Ӿ��Ǵ�
//��������д�ģ���֪Ϊ�α�ֱ���ҵ���Сֵ�ڴ�ռ���١������ܾ�����Ϊ���˸�������Сֵ�ı�����hhh�� 

class Solution {
public:
  int minMoves(vector<int> &nums) {
    
    int las = *min_element(nums.begin(), nums.end());;
    int ans = 0;
    for (int n : nums) {
      ans += n - las;
    }
    return ans;
  }
};

