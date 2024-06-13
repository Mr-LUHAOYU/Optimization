#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<string> vs;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<pdd> vpdd;
typedef vector<vd> vvd;
#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
template<class T> bool chmax(T &a, T b) {
    if (a >= b) return false;
    a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
    if (a <= b) return false;
    a = b; return true;
}
#define FOR(i, s, e, t) for ((i) = (s); (i) < (e); (i) += (t)) 
#define REP(i, e) for (int i = 0; i < (e); ++i) 
#define REP1(i, s, e) for (int i = (s); i < (e); ++i)
#define REP2(i, s, e) for (int i = (s); i <= (e); ++i)
#define REPS(i, s, l) for (int i = (s); i < (s + l); ++i)
#define RREP(i, e) for (int i = (e); i >= 0; --i)
#define RREP1(i, e, s) for (int i = (e); i >= (s); --i)
#define DL while (true)
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
ll inf = 1e18;
db eps = 1e-7;
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);
template<class T> void print(vector<T> &v, bool withSize = false) {
    if (withSize) cout << v.size() << endl;
    REP(i, v.size()) cout << v[i] << " "; 
    cout << endl;
}
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int __FAST_IO__ = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();

#define TESTS int t; cin >> t; while (t--)
#define TEST

const int N = 1e3 + 10;
int n, m, k, ms, me, s[N], e[N], id[N << 2];
db z, ans[N << 2], a[N << 2][N];
bool r[N];

void pivot(int l, int e) {
    swap(id[n + l], id[e]);
    
    db t(a[l][e]); a[l][e] = 1.0;
    REP2(i, 1, n) a[l][i] /= t;
    REP2(i, 0, m) if (i != l && fabs(a[i][e]) > eps) {
        db t(a[i][e]); a[i][e] = 0.0;
        REP2(j, 0, n) a[i][j] -= t * a[l][j];
    }
}

void simplex() {
    DL {
        int e(0), l(0);
        db mx(eps);
        REP2(i, 1, n) if (a[0][i] > mx) mx = a[0][i], e = i;
        
        if (!e) return;
        
        db mn(1e18);
        REP2(i, 1, m) if (a[i][e] > eps && a[i][0] / a[i][e] < mn)
    		mn = a[i][0] / a[i][e], l = i;
        
        pivot(l, e);
    }
}

void matrix() {
	REP2(i, 1, n) {
        r[i] = ((i - 1) % k + 1 <= me);
        z += (r[i] ? s[i] : e[i]);
        a[0][i] = (e[i] - s[i]) * (r[i] ? 1 : -1);
        a[i][0] = 1.0, a[i][i] = 1.0;
    }
    
    m = n;
    
    REP2(i, 1, n - k + 1) {
        ++m, a[m][0] = -ms;
        REPS(j, i, k) a[m][j] = -1.0;
        ++m, a[m][0] = k - me;
        REPS(j, i, k) a[m][j] = 1.0;
    }
        
    REP2(i, 1, n) if (r[i]) REP2(j, n + 1, m)
        a[j][0] -= a[j][i], a[j][i] = -a[j][i];
}

void solve() {
    scanf("%d%d%d%d",&n, &k, &ms, &me);
    REP2(i, 1, n) scanf("%d", &s[i]);    
    REP2(i, 1, n) scanf("%d", &e[i]);
    matrix(); REP2(i, 1, n) id[i] = i;
    simplex(); REP2(i, 1, m) ans[id[n + i]] = a[i][0];
    printf("%.lf\n", z - a[0][0]);
    REP2(i, 1, n) putchar(((fabs(ans[i]) > eps) ^ r[i]) ? 'S' : 'E');
    putchar('\n');
}

int main(int argc, char *argv[]) {
	TEST {
		solve();
	}
	return 0;
}