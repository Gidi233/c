#include <bits/stdc++.h>
using namespace std;
unsigned long num = 0;
int quickselect(vector<int> &nums, int l, int r, int k)
{
    if (l == r)
        return nums[k];
    int partition = nums[(rand() % (r - l + 1)) + l], i = l, j = r;
    while (i < j)
    {
        while (i < j && nums[j] >= partition)
            j--;
        swap(nums[i], nums[j]);
        num++;
        while (i < j && nums[i] <= partition)
            i++;
        swap(nums[i], nums[j]);
        num++;
    }
    if (k == j)
        return nums[k];
    else if (k < j)
        return quickselect(nums, l, j - 1, k);
    else
        return quickselect(nums, j + 1, r, k);
}
// 我拿快排改的 swap的次数差不多 但我要跑5秒，官方的一瞬间？？？
// 原因在大量相同数据时官方写法中用do while，每次左右指针都会向中间移动，会有二分的效果 nlogn
// 而我写的会一次性让左指针移到右指针（或相反）导致冒泡的效率 n方
// 以下为官方
int quickselect(vector<int> &nums, int l, int r, int k)
{
    if (l == r)
        return nums[k];
    int partition = nums[l], i = l - 1, j = r + 1;
    while (i < j)
    {
        do
            i++;
        while (nums[i] < partition);
        do
            j--;
        while (nums[j] > partition);
        if (i < j)
            swap(nums[i], nums[j]);
    }
    if (k <= j)
        return quickselect(nums, l, j, k);
    else
        return quickselect(nums, j + 1, r, k);
}
int findKthLargest(vector<int> &nums, int k)
{
    int n = nums.size();
    return quickselect(nums, 0, n - 1, n - k);
}

class Solution
{
public:
    void maxHeapify(vector<int> &a, int i, int heapSize)
    {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest])
        {
            largest = l;
        }
        if (r < heapSize && a[r] > a[largest])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int> &a, int heapSize)
    {
        for (int i = heapSize / 2; i >= 0; --i)
        {
            maxHeapify(a, i, heapSize);
        }
    }

    int findKthLargest(vector<int> &nums, int k)
    {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i)
        {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};
// 堆排序