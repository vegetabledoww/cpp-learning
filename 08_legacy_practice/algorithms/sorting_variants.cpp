/*
冒泡、插入、非递归快排与桶排序

将整数数组升序排序，对照冒泡、插入和显式栈快排；另对 [0,1) 浮点数组做桶排序。每种算法使用独立输入副本。

样例一：整数 [4,1,3,1,5,2] -> [1,1,2,3,4,5]，重复值保留。
样例二：浮点 [0.5,0.2,0.9,0.1] -> [0.1,0.2,0.5,0.9]，分桶后桶内排序。
来源：order_methods/order.cpp:14-134; Top_K_C++/demo.cpp:11-90（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
using namespace std;

void bubble(vector<int> &nums)
{
    int n = nums.size();
    for (int i = n - 1; i > 0; i--)
    {
        bool flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(nums[j], nums[j + 1]);
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
}

//插入排序
void insertion(vector<int> &nums)
{
    for (int i = 1; i < int(nums.size()); i++)
    {
        int base = nums[i], j = i - 1; //j为插入位置的下标
        while (j >= 0 && nums[j] > base)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = base;
    }
}
void swap(vector<int> &num, int i, int j)
{
    int tmp;
    tmp = num[j];
    num[j] = num[i];
    num[i] = tmp;
}

int partition_s(vector<int> &num, int left, int right)
{
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && num[j] >= num[left]) // 从右往左找小于基准值的数据
        {
            j--;
        }
        while (i < j && num[i] <= num[left])
        {
            i++;
        }
        swap(num, i, j);
    }
    swap(num, i, left);
    return i;
}

void quickSort(vector<int> &num, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int priovt = partition_s(num, left, right); //轴点
    quickSort(num, left, priovt - 1);           //对轴点左侧的数据排序
    quickSort(num, priovt + 1, right);          //对轴点右侧的数据排序
}
//b.非递归快速排序：利用栈来对递归进行手动模拟，非递归而胜似递归
// 显式栈模拟递归调用；不保证比递归更省内存。
void quickSort_not_recursion(vector<int> &num, int left, int right)
{
    stack<int> s;
    if (left < right)
    {
        int boundary = partition_s(num, left, right);
        if (boundary - 1 > left) //确保左分区存在
        {
            //将左分区端点入栈
            s.push(left);
            s.push(boundary - 1);
        }
        if (boundary + 1 < right)
        {
            s.push(boundary + 1);
            s.push(right);
        }
        while (!s.empty())
        {
            //得到某分区的左右边界
            int r = s.top();
            s.pop();
            int l = s.top();
            s.pop();

            boundary = partition_s(num, l, r);
            if (boundary - 1 > l) //确保左分区存在
            {
                //将左分区端点入栈
                s.push(l);
                s.push(boundary - 1);
            }
            if (boundary + 1 < r)
            {
                s.push(boundary + 1);
                s.push(r);
            }
        }
    }
}
void bucketSort(vector<float> &nums)
{
    // 初始化 k = n/2 个桶，预期向每个桶分配 2 个元素
    if (nums.size() < 2)
        return; // 避免空桶访问
    int k = nums.size() / 2;
    vector<vector<float>> buckets(k);
    // 1. 平均分配桶的区间个数，将数组元素分配到各个桶中
    for (float num : nums)
    {
        // 输入数据范围为 [0, 1)，使用 num * k 映射到索引范围 [0, k-1]
        int i = num * k; //整形截断，所以同一个桶中会出现差不多大小的几个元素
        // 将 num 添加进桶 bucket_idx
        buckets[i].push_back(num);
    }
    //2.在桶的内部执行排序：采用内置函数
    for (vector<float> &bucket : buckets)
    {
        // 使用内置排序函数，也可以替换成其他排序算法
        sort(bucket.begin(), bucket.end());
    }
    //3.遍历桶合并结果
    int i = 0;
    for (auto &bucket : buckets)
    {
        for (auto &num : bucket)
        {
            nums[i++] = num;
        }
    }
}

// 本地验证

template <class T> void show(const T &value)
{
    cout << value;
}
template <class T> void show(const vector<T> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i)
            cout << ',';
        show(values[i]);
    }
    cout << ']';
}
template <class T> int check(const char *name, const T &actual, const T &expected)
{
    cout << name << " expected=";
    show(expected);
    cout << " actual=";
    show(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int fail = 0;
    vector<vector<int>> cases = {{4, 1, 3, 1, 5, 2}, {}, {1}, {3, 2, 1}, {2, 2, 2}};
    for (const auto &input : cases)
    {
        auto expected = input;
        sort(expected.begin(), expected.end());
        auto a = input, b = input, c = input;
        bubble(a);
        insertion(b);
        quickSort_not_recursion(c, 0, int(c.size()) - 1);
        fail += check("bubble", a, expected);
        fail += check("insertion", b, expected);
        fail += check("iterative quicksort", c, expected);
    }
    vector<float> f = {0.5f, 0.2f, 0.9f, 0.1f};
    bucketSort(f);
    fail += check("sample2 buckets", f, vector<float>{0.1f, 0.2f, 0.5f, 0.9f});
    vector<float> one = {0.2f};
    bucketSort(one);
    fail += check("single bucket regression", one, vector<float>{0.2f});
    return fail ? 1 : 0;
}

/* 收获点：修复桶数为0的单元素情况，纠正非递归必省空间的说法。冒泡/插入 O(n²) 时间 O(1) 空间；快排平均 O(n log n)、最坏 O(n²)，显式栈最坏 O(n)；桶排序最坏 O(n log n)，空间 O(n)。 */
