/*
题目：多窗口事件分发系统（根据用户代码与示例整理的学习题）

屏幕有 1000 行、1000 列，可点击坐标为 0 <= row,col < 1000。
窗口左上角为 (row,col)，width 表示横向列数，height 表示纵向行数。
窗口覆盖 [row,row+height) × [col,col+width)，上、左边界包含，下、右边界不包含。
多个窗口可以重叠，点击只分发给覆盖该点且层级最高的一个窗口。

实现 MultiWindowSys 的接口：
1. MultiWindowSys()：初始化空系统。
2. CreateWindow(id,row,col,width,height)：ID 已存在返回 false，系统不变；
   否则创建窗口并置顶，返回 true。沿用用户示例：允许部分或完全离屏创建。
3. DestroyWindow(id)：删除该窗口并返回 true；不存在返回 false。
   其余窗口的位置和相对层级不变，删除后该 ID 可以重新使用。
4. MoveWindow(id,dstRow,dstCol)：只改变左上角，尺寸不变。
   ID 不存在，或新位置与屏幕没有正面积交集，返回 false，系统不变；
   否则移动并置顶，返回 true。若仍与屏幕相交，移动到原位置也成功并置顶。
5. DispatchClickEvent(row,col)：返回命中的最高层窗口 ID，并将该窗口置顶。
   没有命中返回 -1，系统不变。本学习版补充约定：屏幕外点击同样返回 -1。

输入约定：ID 为非负 int，width 和 height 为正 int，坐标可为负数；
不额外处理非法尺寸。边界加法可能超过 int，使用 long long 计算。
成功创建、移动和命中点击的总次数保证在 long long 范围内。

示例一（一个新系统，按顺序调用）：
CreateWindow(1,0,0,100,100)       -> true
CreateWindow(2,50,50,100,100)     -> true
CreateWindow(3,75,75,100,100)     -> true
CreateWindow(1,10,10,50,50)       -> false
DispatchClickEvent(80,80)        -> 3
MoveWindow(1,900,900)            -> true
MoveWindow(1,2000,2000)          -> false
DispatchClickEvent(950,950)      -> 1
解释：新建的窗口 3 在重叠区域最上方；窗口 1 第二次移动失败，仍在 (900,900)。

示例二（另一个新系统，按顺序调用）：
CreateWindow(1,0,0,100,100)       -> true
CreateWindow(2,50,50,100,100)     -> true
CreateWindow(3,75,75,100,100)     -> true
DispatchClickEvent(10,10)        -> 1
DispatchClickEvent(80,80)        -> 1
DestroyWindow(1)                 -> true
DispatchClickEvent(80,80)        -> 3
解释：(10,10) 只有窗口 1 覆盖。点中它后，其层级必须超过所有窗口，
而不只是超过当前位置的候选窗口；删除后露出的最高层窗口为 3。
*/
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class MultiWindowSys
{
private:
    struct window
    {
        int id;
        int row;
        int col;
        int width;
        int height;
        long long layer;
    };

    vector<window> w;
    long long maxLayer;

    // 判断窗口是否有部分面积在屏幕内，不要求整个窗口都在屏幕内。
    bool IsOnScreen(const window &win) const
    {
        // 先提升类型再相加，避免正 int 的坐标与尺寸相加溢出。
        long long right = 1LL * win.col + win.width;
        long long bottom = 1LL * win.row + win.height;
        if (right <= 0 || bottom <= 0)
            return false;
        if (win.col >= 1000 || win.row >= 1000)
            return false;
        return true;
    }

    bool contain(const window &win, int row, int col) const
    {
        return row >= win.row && row < 1LL * win.row + win.height &&
               col >= win.col && col < 1LL * win.col + win.width;
    }

public:
    MultiWindowSys() : maxLayer(0) {}

    bool CreateWindow(int id, int row, int col, int width, int height)
    {
        for (const auto &win : w)
        {
            if (win.id == id)
                return false;
        }
        ++maxLayer;
        w.push_back({id, row, col, width, height, maxLayer});
        return true;
    }

    bool DestroyWindow(int id)
    {
        for (auto it = w.begin(); it != w.end(); ++it)
        {
            if (it->id == id)
            {
                w.erase(it);
                return true; // erase 后不再访问这个迭代器。
            }
        }
        return false;
    }

    bool MoveWindow(int id, int dstRow, int dstCol)
    {
        for (auto &win : w)
        {
            if (win.id == id)
            {
                window tmp = win;
                tmp.row = dstRow;
                tmp.col = dstCol;
                // 先检查副本。失败不能改变原窗口的位置或层级。
                if (!IsOnScreen(tmp))
                    return false;
                win = tmp;
                win.layer = ++maxLayer;
                return true;
            }
        }
        return false; // 修复原稿中 ID 不存在时缺少返回值。
    }

    int DispatchClickEvent(int row, int col)
    {
        // 屏幕外不是可接收点击的位置，即使某个窗口延伸到了那里。
        if (row < 0 || row >= 1000 || col < 0 || col >= 1000)
            return -1;

        window *topwindow = nullptr;
        long long highestLayer = -1; // 只记录本次命中候选的最高层。
        for (auto &win : w)
        {
            if (contain(win, row, col) && win.layer > highestLayer)
            {
                highestLayer = win.layer;
                topwindow = &win;
            }
        }
        if (topwindow == nullptr)
            return -1;

        // 必须使用成员 maxLayer。不能只给命中窗口原来的层级加 1。
        topwindow->layer = ++maxLayer;
        return topwindow->id;
    }
};

// 本地测试：bool 返回值用 1/0 展示；失败时 main 返回非零退出码。
int CheckResult(const char *name, int actual, int expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;

    cout << "===== 示例一与用户原始操作序列 =====\n";
    MultiWindowSys sys;
    failed += CheckResult("创建1", sys.CreateWindow(1, 0, 0, 100, 100), true);
    failed += CheckResult("创建2", sys.CreateWindow(2, 50, 50, 100, 100), true);
    failed += CheckResult("创建3", sys.CreateWindow(3, 75, 75, 100, 100), true);
    failed += CheckResult("重复ID", sys.CreateWindow(1, 10, 10, 50, 50), false);
    failed += CheckResult("重叠区域命中3", sys.DispatchClickEvent(80, 80), 3);
    failed += CheckResult("移动到屏幕边缘", sys.MoveWindow(1, 900, 900), true);
    failed += CheckResult("拒绝完全离屏移动", sys.MoveWindow(1, 2000, 2000), false);
    failed += CheckResult("失败后位置不变", sys.DispatchClickEvent(950, 950), 1);
    failed += CheckResult("允许部分离屏创建", sys.CreateWindow(4, -50, -50, 100, 100), true);
    failed += CheckResult("允许完全离屏创建", sys.CreateWindow(5, -200, -200, 100, 100), true);
    failed += CheckResult("部分离屏窗口仍可命中", sys.DispatchClickEvent(0, 0), 4);
    failed += CheckResult("空白处点击", sys.DispatchClickEvent(500, 500), -1);
    failed += CheckResult("删除2", sys.DestroyWindow(2), true);
    failed += CheckResult("删除不存在ID", sys.DestroyWindow(99), false);
    failed += CheckResult("移动不存在ID", sys.MoveWindow(99, 0, 0), false);
    failed += CheckResult("完全离屏窗口移回屏幕", sys.MoveWindow(5, 0, 0), true);
    failed += CheckResult("移回后置顶", sys.DispatchClickEvent(0, 0), 5);

    cout << "\n===== 示例二：点击低层窗口必须全局置顶 =====\n";
    MultiWindowSys layers;
    failed += CheckResult("创建低层1", layers.CreateWindow(1, 0, 0, 100, 100), true);
    failed += CheckResult("创建中层2", layers.CreateWindow(2, 50, 50, 100, 100), true);
    failed += CheckResult("创建高层3", layers.CreateWindow(3, 75, 75, 100, 100), true);
    failed += CheckResult("只命中1的区域", layers.DispatchClickEvent(10, 10), 1);
    failed += CheckResult("1必须高于未命中的3", layers.DispatchClickEvent(80, 80), 1);
    failed += CheckResult("删除置顶的1", layers.DestroyWindow(1), true);
    failed += CheckResult("删除后露出3", layers.DispatchClickEvent(80, 80), 3);
    failed += CheckResult("重复点击仍命中3", layers.DispatchClickEvent(80, 80), 3);
    failed += CheckResult("删除后重用ID", layers.CreateWindow(1, 75, 75, 100, 100), true);
    failed += CheckResult("新建应高于多次点击的3", layers.DispatchClickEvent(80, 80), 1);
    failed += CheckResult("移动2并置顶", layers.MoveWindow(2, 75, 75), true);
    failed += CheckResult("移动后的重叠次序", layers.DispatchClickEvent(80, 80), 2);
    failed += CheckResult("原位置移动也成功", layers.MoveWindow(3, 75, 75), true);
    failed += CheckResult("原位置移动同样置顶", layers.DispatchClickEvent(80, 80), 3);

    cout << "\n===== 失败操作不得改变状态 =====\n";
    MultiWindowSys unchanged;
    failed += CheckResult("创建底层", unchanged.CreateWindow(1, 0, 0, 20, 20), true);
    failed += CheckResult("创建顶层", unchanged.CreateWindow(2, 0, 0, 20, 20), true);
    failed += CheckResult("重复创建不移动旧窗口", unchanged.CreateWindow(1, 500, 500, 10, 10), false);
    failed += CheckResult("重复创建不应置顶", unchanged.DispatchClickEvent(1, 1), 2);
    failed += CheckResult("重复创建未产生新位置", unchanged.DispatchClickEvent(500, 500), -1);
    failed += CheckResult("底层移动失败", unchanged.MoveWindow(1, 1000, 1000), false);
    failed += CheckResult("移动失败不应置顶", unchanged.DispatchClickEvent(1, 1), 2);
    failed += CheckResult("空白点击不改变层级", unchanged.DispatchClickEvent(500, 500), -1);
    failed += CheckResult("删除不存在窗口", unchanged.DestroyWindow(9), false);
    failed += CheckResult("失败操作后仍命中2", unchanged.DispatchClickEvent(1, 1), 2);
    failed += CheckResult("移走顶层", unchanged.MoveWindow(2, 100, 100), true);
    failed += CheckResult("底层原位置仍保留", unchanged.DispatchClickEvent(1, 1), 1);

    cout << "\n===== 行列、尺寸和半开区间 =====\n";
    MultiWindowSys rectangle;
    failed += CheckResult("非正方形窗口", rectangle.CreateWindow(0, 10, 20, 30, 5), true);
    failed += CheckResult("左上角包含", rectangle.DispatchClickEvent(10, 20), 0);
    failed += CheckResult("最后一个内部点", rectangle.DispatchClickEvent(14, 49), 0);
    failed += CheckResult("下边界不包含", rectangle.DispatchClickEvent(15, 20), -1);
    failed += CheckResult("右边界不包含", rectangle.DispatchClickEvent(10, 50), -1);
    failed += CheckResult("上方不包含", rectangle.DispatchClickEvent(9, 20), -1);
    failed += CheckResult("左侧不包含", rectangle.DispatchClickEvent(10, 19), -1);
    failed += CheckResult("移动非正方形", rectangle.MoveWindow(0, 100, 200), true);
    failed += CheckResult("移动后尺寸保持", rectangle.DispatchClickEvent(104, 229), 0);
    failed += CheckResult("旧位置不再命中", rectangle.DispatchClickEvent(10, 20), -1);

    cout << "\n===== 屏幕相交与屏幕外点击 =====\n";
    MultiWindowSys edges;
    failed += CheckResult("创建边界测试窗口", edges.CreateWindow(1, 0, 0, 100, 100), true);
    failed += CheckResult("底边恰好为0无交集", edges.MoveWindow(1, -100, 0), false);
    failed += CheckResult("右边恰好为0无交集", edges.MoveWindow(1, 0, -100), false);
    failed += CheckResult("顶边1000无交集", edges.MoveWindow(1, 1000, 0), false);
    failed += CheckResult("左边1000无交集", edges.MoveWindow(1, 0, 1000), false);
    failed += CheckResult("只有一个像素相交仍成功", edges.MoveWindow(1, -99, -99), true);
    failed += CheckResult("可见像素命中", edges.DispatchClickEvent(0, 0), 1);
    failed += CheckResult("负行点击拒绝", edges.DispatchClickEvent(-1, 0), -1);
    failed += CheckResult("负列点击拒绝", edges.DispatchClickEvent(0, -1), -1);
    failed += CheckResult("右下角部分相交", edges.MoveWindow(1, 999, 999), true);
    failed += CheckResult("屏幕最后一个像素", edges.DispatchClickEvent(999, 999), 1);
    failed += CheckResult("行1000虽在窗口内也拒绝", edges.DispatchClickEvent(1000, 999), -1);
    failed += CheckResult("列1000虽在窗口内也拒绝", edges.DispatchClickEvent(999, 1000), -1);

    cout << "\n===== 大数边界与独立实例 =====\n";
    MultiWindowSys large;
    failed += CheckResult("创建大尺寸窗口", large.CreateWindow(1, 1, 1, INT_MAX, INT_MAX), true);
    failed += CheckResult("边界相加超过int仍命中", large.DispatchClickEvent(999, 999), 1);
    failed += CheckResult("相交判断也需宽整数", large.MoveWindow(1, 2, 2), true);
    MultiWindowSys empty;
    failed += CheckResult("新系统独立且为空", empty.DispatchClickEvent(10, 10), -1);
    failed += CheckResult("空系统删除", empty.DestroyWindow(1), false);
    failed += CheckResult("空系统移动", empty.MoveWindow(1, 0, 0), false);
    failed += CheckResult("删除最后窗口", large.DestroyWindow(1), true);
    failed += CheckResult("删除后不再命中", large.DispatchClickEvent(999, 999), -1);

    cout << "\nfailed=" << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 层级是持久状态：创建、移动、点击置顶共用同一个成员 maxLayer。
   highestLayer 只是本次查询的局部结果，两者不要同名，也不要混用。
2. 屏幕相交和点在窗口内是两种不同判断，均注意右、下边界不包含。
3. 先检查移动副本，再修改真实状态，失败操作自然保留旧位置与层级。
4. topwindow 指向 vector 内的窗口；本函数期间不插入、删除窗口，所以指针有效。
   不要把该指针长期保存到对象中，因为后续 vector 扩容或删除可能让它失效。
5. 当前有 W 个窗口：创建、销毁、移动、点击的时间均为 O(W)，
   系统存储空间 O(W)，除 vector 扩容外每次操作只需 O(1) 辅助空间。
*/
