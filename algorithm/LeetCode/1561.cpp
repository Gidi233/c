class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int length = piles.size();
        int rounds = length / 3;
        int coins = 0;
        int index = length - 2;
        for (int i = 0; i < rounds; i++) {
            coins += piles[index];
            index -= 2;
        }
        return coins;
    }
};
//排序删掉最大最小的，取一个最大的（操作太费事了，直接取下标）
//不用一次次操作，小的那n个直接去掉，