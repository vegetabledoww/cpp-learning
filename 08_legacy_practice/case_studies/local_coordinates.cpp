/*
局部经纬度与东北天坐标近似转换

教学约定：在基准点附近、小范围、远离极点使用球面局部线性近似。经纬度单位度，距离米；方位角从北顺时针，俯仰角向上为正。转换来回使用同一基准纬度，不适用于跨洲、极区或精密测绘。

样例一：基点(经度0,纬度0,高度0)，目标在正东约111.2米 -> 方位角90度。
样例二：相同经纬度、目标高10米 -> [东0,北0,天10]，俯仰角90度。
来源：lonANDlat/son.cpp:12-41（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double pi = acos(-1.0), earthRadius = 6371393.0;
vector<double> toENU(double lon, double lat, double height, double targetLon, double targetLat,
                     double targetHeight)
{
    double east = (targetLon - lon) * pi / 180 * earthRadius * cos(lat * pi / 180);
    double north = (targetLat - lat) * pi / 180 * earthRadius;
    return {east, north, targetHeight - height};
}
vector<double> fromENU(double lon, double lat, double height, const vector<double> &enu)
{
    return {lon + enu[0] / (earthRadius * cos(lat * pi / 180)) * 180 / pi,
            lat + enu[1] / earthRadius * 180 / pi, height + enu[2]};
}
vector<double> angles(const vector<double> &enu)
{
    double azimuth = atan2(enu[0], enu[1]) * 180 / pi;
    if (azimuth < 0)
        azimuth += 360;
    double elevation = atan2(enu[2], hypot(enu[0], enu[1])) * 180 / pi;
    return {azimuth, elevation};
}
double calcHeight(double baseHeight, double slantDistance, double elevation)
{
    return baseHeight + slantDistance * sin(elevation * pi / 180);
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
    auto east = toENU(0, 0, 0, 0.001, 0, 0);
    fail += check("sample1 east azimuth", angles(east)[0], 90.0);
    cout << "equator east distance expected~111.201786 actual=" << east[0] << '\n';
    fail += check("degree to meter scale", abs(east[0] - 111.201786) < 1e-6, true);
    auto up = toENU(0, 0, 0, 0, 0, 10);
    fail += check("sample2 ENU", up, vector<double>{0, 0, 10});
    fail += check("sample2 elevation", angles(up)[1], 90.0);
    auto enu = toENU(120, 30, 20, 120.001, 30.002, 50);
    fail += check("latitude scaling", abs(enu[0] / east[0] - sqrt(3.0) / 2) < 1e-9, true);
    auto result = fromENU(120, 30, 20, enu);
    cout << "round trip expected=[120.001,30.002,50] actual=[" << result[0] << ',' << result[1]
         << ',' << result[2] << "]\n";
    fail += check("nonzero latitude round trip",
                  abs(result[0] - 120.001) < 1e-9 && abs(result[1] - 30.002) < 1e-9 &&
                      abs(result[2] - 50) < 1e-9,
                  true);
    fail += check("slant height", abs(calcHeight(5, 10, 30) - 10) < 1e-9, true);
    return fail ? 1 : 0;
}

/* 收获点：修正 cos(纬度) 未转弧度及正反转换基准不一致。删除影响验证的随机噪声；斜距用 sin，水平距应配 tan，不能混用。每次转换 O(1)。 */
