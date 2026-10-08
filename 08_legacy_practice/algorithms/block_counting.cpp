/*
固定长度数据块去重与计数

恢复练习：按 blk>=1 将数组依次分块，最后不足一块也保留。相同块合并，并按首次出现顺序输出各块，紧随该块附加出现次数。

样例一：[1,2,3,4,1,2],blk=2 -> [1,2,2,3,4,1]，块 [1,2] 两次，[3,4] 一次。
样例二：[1,2,1],blk=2 -> [1,2,1,1,1]，块 [1,2] 与短块 [1] 不同。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:317-358（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> countBlocks(const vector<int> &nums, int blk)
{
    map<vector<int>, int> indices;
    vector<vector<int>> blocks;
    vector<int> counts;
    for (int i = 0; i < int(nums.size()); i += blk)
    {
        vector<int> block(nums.begin() + i, nums.begin() + min(i + blk, int(nums.size())));
        auto it = indices.find(block);
        if (it == indices.end())
        {
            indices[block] = blocks.size();
            blocks.push_back(block);
            counts.push_back(1);
        }
        else
            ++counts[it->second];
    }
    vector<int> ans;
    for (size_t i = 0; i < blocks.size(); ++i)
    {
        ans.insert(ans.end(), blocks[i].begin(), blocks[i].end());
        ans.push_back(counts[i]);
    }
    return ans;
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
    fail += check("sample1", countBlocks({1, 2, 3, 4, 1, 2}, 2), vector<int>{1, 2, 2, 3, 4, 1});
    fail += check("sample2", countBlocks({1, 2, 1}, 2), vector<int>{1, 2, 1, 1, 1});
    fail += check("empty", countBlocks({}, 2), vector<int>{});
    fail += check("first appearance", countBlocks({9, 8, 1, 2, 9, 8}, 2),
                  vector<int>{9, 8, 2, 1, 2, 1});
    return fail ? 1 : 0;
}

/* 收获点：保留 map 以块为键；另存首次遇到的顺序，去掉原来为恢复该顺序做的额外排序。最坏 O(n log 块数)，空间 O(n)。 */
