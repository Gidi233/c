class Solution {
 public:
  int rand10() {
    int a, b, idx;
    while (true) {
      a = rand7();
      b = rand7();
      idx = b + (a - 1) * 7;
      if (idx <= 40) {
        return 1 + (idx - 1) % 10;
      }
      a = idx - 40;
      b = rand7();
      // get uniform dist from 1 - 63
      idx = b + (a - 1) * 7;
      if (idx <= 60) {
        return 1 + (idx - 1) % 10;
      }
      a = idx - 60;
      b = rand7();
      // get uniform dist from 1 - 21
      idx = b + (a - 1) * 7;
      if (idx <= 20) {
        return 1 + (idx - 1) % 10;
      }
    }
  }
};
// 数学 等概率，不符合等概率的要舍去，让不符合的尽量少