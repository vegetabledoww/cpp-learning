/*
专题：标准库二分查找
任务：在升序整数数组中，返回目标值的 [lower_bound,upper_bound) 下标区间。
没有目标值时，两端相等，代表空区间；它们也对应保持有序的插入位置。
示例一：输入 {1,2,2,2,4}, target=2，输出 [1,4)，出现 3 次。
解释：下标 1 是第一个 >=2 的位置，下标 4 是第一个 >2 的位置。
示例二：输入 {1,2,2,2,4}, target=3，输出 [4,4)，出现 0 次。
解释：第一个 >=3 和 >3 的元素都是下标 4 处的 4。
前提：本示例的数组按升序排列，不能直接对无序数组套用。
*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

pair<int,int> Bounds(const vector<int> &values, int target)
{
    auto left = lower_bound(values.begin(), values.end(), target);
    auto right = upper_bound(values.begin(), values.end(), target);
    // 返回值可以等于 size()，代表 end()，无需解引用就能得到合法边界。
    return {static_cast<int>(left - values.begin()),
            static_cast<int>(right - values.begin())};
}

int Check(const vector<int> &values, int target, int expectedLeft, int expectedRight)
{
    pair<int,int> actual = Bounds(values, target);
    auto range = equal_range(values.begin(), values.end(), target);
    bool found = binary_search(values.begin(), values.end(), target);
    bool passed = actual == make_pair(expectedLeft, expectedRight)
        && range.first - values.begin() == expectedLeft
        && range.second - values.begin() == expectedRight
        && found == (expectedLeft != expectedRight);
    cout << "target=" << target << " expected=[" << expectedLeft << ',' << expectedRight
         << ") actual=[" << actual.first << ',' << actual.second
         << ") found=" << found << " count=" << actual.second - actual.first
         << (passed ? " PASS\n" : " FAIL\n");
    return passed ? 0 : 1;
}

int main()
{
    int failed = 0;
    vector<int> values = {1,2,2,2,4};
    failed += Check(values, 2, 1, 4);
    failed += Check(values, 3, 4, 4);
    failed += Check(values, 0, 0, 0);
    failed += Check(values, 9, 5, 5);
    failed += Check(values, 4, 4, 5);
    failed += Check({}, 1, 0, 0);
    failed += Check({7}, 7, 0, 1);
    failed += Check({2,2,2}, 2, 0, 3);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：lower_bound 找 >=，upper_bound 找 >，二者之差是有序数组中目标出现次数。
binary_search 只返回是否存在，equal_range 一次表达上下边界这一对结果。
vector 上查找 O(log n)、额外空间 O(1)；set/map 优先用成员 lower_bound，
否则通用算法在非随机访问迭代器上可能需要 O(n) 次移动。
*/
