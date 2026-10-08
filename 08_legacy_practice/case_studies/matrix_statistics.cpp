/*
矩阵转置、乘法与样本协方差

每行一个观测样本，每列一个变量。样本协方差 C[i][j]=各样本中心化后第i、j变量乘积之和/(样本数-1)，要求矩形矩阵、至少两个样本、至少一个变量。另提供普通矩阵转置和乘法，维度必须兼容。

样例一：样本 [[1,2],[3,4]] -> 协方差 [[2,2],[2,2]]，两行与均值之差分别为[-1,-1]、[1,1]。
样例二：单变量样本 [[1],[2],[3]] -> [[1]]，就是无偏样本方差。
来源：Char/main.cpp:173-222; cov_Matrix/main.cpp:4-30（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

using Matrix = vector<vector<double>>;
void rectangular(const Matrix &a)
{
    if (a.empty() || a[0].empty())
        throw invalid_argument("empty matrix");
    for (const auto &row : a)
        if (row.size() != a[0].size())
            throw invalid_argument("ragged matrix");
}
Matrix transpose(const Matrix &a)
{
    rectangular(a);
    Matrix b(a[0].size(), vector<double>(a.size()));
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < a[0].size(); ++j)
            b[j][i] = a[i][j];
    return b;
}
Matrix multiply(const Matrix &a, const Matrix &b)
{
    rectangular(a);
    rectangular(b);
    if (a[0].size() != b.size())
        throw invalid_argument("incompatible dimensions");
    Matrix out(a.size(), vector<double>(b[0].size()));
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < b[0].size(); ++j)
            for (size_t k = 0; k < b.size(); ++k)
                out[i][j] += a[i][k] * b[k][j];
    return out;
}
Matrix covariance(Matrix samples)
{
    rectangular(samples);
    if (samples.size() < 2)
        throw invalid_argument("need two samples");
    vector<double> mean(samples[0].size());
    for (const auto &row : samples)
        for (size_t j = 0; j < mean.size(); ++j)
            mean[j] += row[j];
    for (double &x : mean)
        x /= samples.size();
    for (auto &row : samples)
        for (size_t j = 0; j < mean.size(); ++j)
            row[j] -= mean[j];
    Matrix result = multiply(transpose(samples), samples);
    for (auto &row : result)
        for (double &x : row)
            x /= samples.size() - 1;
    return result;
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
    fail += check("sample1", covariance({{1, 2}, {3, 4}}), Matrix{{2, 2}, {2, 2}});
    fail += check("sample2", covariance({{1}, {2}, {3}}), Matrix{{1}});
    fail += check("rectangular product", multiply({{1, 2, 3}}, {{1}, {2}, {3}}), Matrix{{14}});
    fail += check("constant data", covariance({{2, 2}, {2, 2}}), Matrix{{0, 0}, {0, 0}});
    bool rejected = false;
    try
    {
        covariance({{1, 2}});
    }
    catch (const invalid_argument &)
    {
        rejected = true;
    }
    fail += check("one sample rejected", rejected, true);
    return fail ? 1 : 0;
}

/* 收获点：纠正原稿把一个标量序列的中心化外积当变量协方差矩阵；单变量多样本只能得到1x1协方差。转置 O(np)，协方差 O(np²)，空间 O(np+p²)。 */
