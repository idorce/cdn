//----------------------------------------------------------------------------//
// A. Volunteer recruitment

// Description
// Suppose you will recruit a group of volunteers for a coming event. It is estimated that this event will take N days to complete, and the i(th) day needs at least Ai volunteers. The number of kinds of volunteers is M. The volunteers of i(th) kind can volunteer from the Si day to the Fi day and the recruit fee is Ci. In order to do his job well, you hope to recruit enough volunteers with least money. Please give an optimal plan.

// note: i(th) means the ordinal of this number is i

// Input
// The first line presents two integers: N, M. The second line contains N nonnegative integers presenting the numbers of volunteers each day needs. Each of the other lines contain three integers: Si, Fi, Ci

// note: You can recruit each kind of volunteers as many as possible.

// Output
// Just a number meaning the total money of your optimal plan.

// Sample Input
// 3 3
// 2 3 4
// 1 2 2
// 2 3 5
// 3 3 2

// Sample Output
// 14

// Hint
// 1<=N<=200, 1<=M<=1000, 题目中所有数据不超过2^31-1

// ZS Zeng：他把等式约束建模为节点，变量建模为边，构建了一个网络，然后求解最小费用最大流。
// https://www.byvoid.com/zhs/blog/noi-2008-employee
//----------------------------------------------------------------------------//

#include <iostream>
using namespace std;

//----------------------------------------------------------------------------//
// [WD Xu]
#include <cmath>

namespace Simplex {
// s.t. AX≤B
// MAX CX
const int maxn = 1010;
const int maxm = 10010;
const double eps = 1E-9;
const double inf = 1E18;
int n, m;
double a[maxm][maxn], b[maxm], c[maxn], v;
void pivot(int l, int e) {
    // l: 替入变量所在方程号; e：替出变量
    // 处理这一个约束方程的所有系数以及常数。
    b[l] /= a[l][e];
    for (int j = 1; j <= n; j++) {
        // 移项
        if (j != e)
            a[l][j] /= a[l][e];
    }
    a[l][e] = 1 / a[l][e];
    // 更新其余约束方程的表示和系数值。
    for (int i = 1; i <= m; i++) {
        if (i != l && fabs(a[i][e]) > 0) {
            b[i] -= a[i][e] * b[l];
            for (int j = 1; j <= n; j++) {
                // 更新参数表示
                if (j != e)
                    a[i][j] -= a[i][e] * a[l][j];
            }
            a[i][e] = -a[i][e] * a[l][e];
        }
    }
    // 更新目标值和目标方程参数
    v += c[e] * b[l];
    for (int j = 1; j <= n; j++) {
        if (j != e)
            c[j] -= c[e] * a[l][j];
    }
    c[e] = -c[e] * a[l][e];
}
double simplex() {
    while (1) {
        int e = 0, l = 0;
        /*
        从优化目标中选择替出变量，因为是MAX目标，
        当所有系数都<0时，我们只能让那个变量为0才能得到最优解，
        于是我们选系数>0的。
        （如果是MIN为目标，我们选的是系数<0的，理由同上）
        同时根据bland规则，选id最小的那个。
        */
        for (e = 1; e <= n; e++) {
            if (c[e] > eps)
                break;
        }
        // 找不到替出变量，说明系数都<0了。
        if (e == n + 1)
            return v;
        double mn = inf;
        for (int i = 1; i <= m; i++) {
            // 选择替入变量的约束方程，要保证替出变量的系数>0，否则同号的话替入替出没有意义。
            // 选一个替出变量系数>0的所在约束方程，这样一变换位置就和替出变量异号了。
            // 同时，根据bland规则，选约束最紧的那个。
            if (a[i][e] > eps && mn > b[i] / a[i][e]) {
                mn = b[i] / a[i][e];
                l = i;
            }
        }
        // 选不到替入变量的行，而存在替出变量，说明无解
        if (mn == inf)
            return inf;
        // 进行替换操作
        pivot(l, e);
    }
}
}  // namespace Simplex
//----------------------------------------------------------------------------//

int main() {
    ios::sync_with_stdio(false);

    int n, m, s, f;
    cin >> n >> m;
    Simplex::n = n;
    Simplex::m = m;
    for (int i = 1; i <= n; ++i) cin >> Simplex::c[i];
    for (int i = 1; i <= m; ++i) {
        cin >> s >> f >> Simplex::b[i];
        for (int j = s; j <= f; ++j) Simplex::a[i][j] = 1;
    }
    cout << (int)(Simplex::simplex()) << endl;

    return 0;
}