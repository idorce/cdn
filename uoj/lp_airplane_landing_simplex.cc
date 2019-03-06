//----------------------------------------------------------------------------//
// B. Airplane Landing Problem

// Problem Description
// With human lives at stake, an air traffic controller has to schedule the airplanes that are landing at an airport in order to avoid airplane collision. Each airplane i
//  has a time window [si,ti]
//  during which it can safely land. You must compute the exact time of landing for each airplane that respects these time windows. Furthermore, the airplane landings should be stretched out as much as possible so that the minimum time gap between successive landings is as large as possible.

// For example, if the time window of landing three airplanes are [10:00-11:00], [11:20-11:40], [12:00-12:20], and they land at 10:00, 11:20, 12:20 respectively, then the smallest gap is 60 minutes, which occurs between the last two airplanes.

// Given 5 time windows, denoted as [s1,t1],[s2,t2],⋯,[s5,t5]
//  satisfying 0<=s1<t1<s2<t2<⋯<s5<t5<=24
// . You are required to give the exact landing time of each airplane, in which the smallest gap between successive landings is maximized.

// Notice:

// Make sure that each airplane lands as early as possible.

// Input
// 10 numbers(type is float32) s1,t1,s2,t2,⋯,s5,t5
// , satisfying 0<=s1<t1<s2<t2<⋯<s5<t5<=24
// .

// Output
// 5 numbers(type is float32) l1,l2,⋯,l5
// , with accuracy of two decimal digits.

// Sample Input
// 1 2 3 4 5 6 7 8 9 10

// Sample Output
// 1.00 3.25 5.50 7.75 10.00
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// Simplex. [Euryale_] CSDN. Modified for submission.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;
#define maxn 50
const double eps = 1e-8, inf = 1e15;
int n, m, id[maxn * 2];
double a[maxn][maxn];  //a[i][j]:i表第几条约束 j表第几个元素
double ans[maxn];
double myabs(double x) { return x > 0 ? x : -x; }
//a[0][i] -> ci 目标函数中第i个元素系数
//a[i][0] -> bi 第i条约束中的常数
//a[i][j] -> Aij 第i条约束中第j个元素的系数
//最大化 sigma(ci*xi),i∈N
//约束 xj=bj-sigma(aji*xi) ,j∈B

//转轴
void pivot(int l, int e)
//替入变量xe∈非基本变量(1~n)  替出变量xl∈基本变量(n+1~n+m)
{
    int tt = id[n + l];
    id[n + l] = id[e];
    id[e] = tt;
    int i, j;
    double t = a[l][e];
    a[l][e] = 1;
    for (j = 0; j <= n; j++) a[l][j] /= t;
    //重写其它等式：
    for (i = 0; i <= m; i++)
        if (i != l && myabs(a[i][e]) > eps) {
            t = a[i][e];
            a[i][e] = 0;
            for (j = 0; j <= n; j++)
                a[i][j] -= a[l][j] * t;
        }
}

//初始化
//方法一：引入一个辅助线性规划 要求最大化-x0
//约束为 xj=bj-sigma(aji*xi)+x0 ,j∈B然后用x0替换bj为负的约束
//下面的是方法二：
bool initialize() {
    while (1) {
        int i, j, e = 0, l = 0;
        for (i = 1; i <= m; i++)
            if (a[i][0] < -eps && (!l || (rand() & 1))) l = i;
        if (!l) break;
        for (j = 1; j <= n; j++)
            if (a[l][j] < -eps && (!e || (rand() & 1))) e = j;
        if (!e) {
            printf("Infeasible\n");
            return 0;
        }
        pivot(l, e);
        //在bi为负的时候，把所有基变量设为0不是一组合法的初始解
        //所以选择一个bi为负的基变量x[i+n]
        //然后在该约束右边找一个系数为正(即原系数为负)的非基变量进行转轴操作
        //如果没有系数为正显然就无解了
    }
    return 1;
}

//最优化
bool simplex() {
    int i, j;
    while (1) {
        int l = 0, e = 0;
        double minn = inf;
        for (j = 1; j <= n; j++)
            if (a[0][j] > eps) {
                e = j;
                break;
            }
        if (!e) break;
        //如果目标变量ci都小于0 那么最优解就是非基变量都为0
        for (i = 1; i <= m; i++)
            if (a[i][e] > eps && a[i][0] / a[i][e] < minn)
                minn = a[i][0] / a[i][e], l = i;
        //在所有的式子中找出包含当前选中项（系数不为0）且最紧的一项
        if (!l) {
            printf("Unbounded\n");
            return 0;
        }
        //如果所有的a[i][e]都小于0，说明最优值正无穷
        pivot(l, e);
    }
    return 1;
}
//----------------------------------------------------------------------------//

int main() {
    srand(time(0));
    int type, i, j;

    double s, t;
    n = 6, m = 3 * n - 4, type = 1;
    a[0][n] = 1;
    for (int i = 1; i <= n - 1; ++i) {
        cin >> s >> t;
        a[i * 2 - 1][i] = 1, a[i * 2 - 1][0] = t;
        a[i * 2][i] = -1, a[i * 2][0] = -s;
        if (i < n - 1) {
            a[i + 2 * n - 2][i] = 1;
            a[i + 2 * n - 2][i + 1] = -1;
            a[i + 2 * n - 2][n] = 1;
        }
    }

    //n个变量 m条约束

    for (i = 1; i <= n; i++) id[i] = i;
    if (initialize() && simplex()) {
        // printf("%.8lf\n", -a[0][0]);
        if (type) {
            for (i = 1; i <= m; i++) ans[id[n + i]] = a[i][0];
            for (i = 1; i <= n - 2; i++) printf("%.2lf ", ans[i]);
            printf("%.2lf", ans[n - 1]);
        }
    }
    return 0;
}