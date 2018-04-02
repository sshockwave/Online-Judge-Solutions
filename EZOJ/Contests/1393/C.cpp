#define NDEBUG
#include <bits/stdc++.h>
#include "poly.h"
#define cout cerr
using namespace std;
typedef long long lint;
namespace GROOT{

	const char fin [] = "poly.in";
	const char fout[] = "poly.out";

	const int maxN = 100000 + 7;

	static int mod = 998244353, g = 3;

	inline static int Pow(int a, long long b)
	{
		int t = 1;
		for (/*b %= mod - 1*/; b; b >>= 1, a = 1ll * a * a % mod)
			if (b & 1)
				t = 1ll * t * a % mod;
		return t;
	}

	inline static bool check(int x, int k)
	{
		return (mod - 1) % k == 0 && k != mod - 1 && Pow(x, k) == 1;
	}

	inline static void get_root()
	{
		for (g = 2;; g ++)
		{
			int flag = 1;
			for (int k = 1; 1ll * k * k <= mod; k ++)
				if (check(g, k) || check(g, (mod - 1) / k))
				{
					flag = 0;
					break;
				}
			if (flag)
				return;
		}
	}

}

namespace Polynomial {

	using namespace GROOT;

#define iter(i, n) for (int i = 1; i <= n; ++i)
#define iter0(i, n) for (int i = 0; i < n; ++i)
#define forw(i, a, b) for (int i = a; i <= b; ++i)
#define down(i, a, b) for (int i = b; i >= a; --i)

#define reset(a, l, r) forw(i, l, r) a[i] = 0;
#define NR 401000

	typedef vector<int> Poly;

	inline int pr(int a, int z) {
		int s = 1;
		while (z > 0) {
			if (z % 2 == 1) s = 1ll * s * a % mod;
			a = 1ll * a * a % mod;
			z /= 2;
		}
		return s;
	}

	inline int mod_inv(int a) { return pr(a, mod - 2); }

	void fft(int *a, int n, int ty) {
		for (int i = n >> 1, j = 1, k; j < n - 1; ++j) {
			if (i > j) swap(a[i], a[j]);
			for (k = n >> 1; k <= i; k >>= 1) i ^= k;
			i ^= k;
		}

		for (int m = 2; m <= n; m <<= 1) {
			int h = m >> 1, wm = pr(g, (mod - 1) / m * (ty == +1 ? 1 : (m - 1)));

			for (register int i = 0; i < n; i += m) {
				register int w = 1;
				for (int j = i; j < i + h; ++j) {
					register int u = a[j], v = 1ll * w * a[j + h] % mod;

					a[j] = (u + v) % mod;
					a[j + h] = (u - v + mod) % mod;
					w = 1ll * w * wm % mod;
				}
			}
		}

		if (ty == -1) {
			int iv = mod_inv(n);
			iter0(i, n) a[i] = 1ll * a[i] * iv % mod;
		}
	}

	ostream& operator<<(ostream &output, const Poly &a){  
		output << "[";
		int la = a.size();
		iter0(i, la)
			output << a[i] << (i + 1 == la ? ']' : ',');
		return output;
	}

	void upd(Poly &a) { while (!a.empty() && a.back() == 0) a.pop_back(); }

	inline Poly operator+(const Poly &a, const Poly &b) {
		int la = a.size(), lb = b.size();
		int lc = max(la, lb);
		Poly c(lc);
		iter0(i, lc) c[i] = ((i < la ? a[i] : 0) + (i < lb ? b[i] : 0)) % mod;
		return upd(c), c;
	}
	inline void poly_multo(int a[], int b[], int N) {
		fft(a, N, +1), fft(b, N, +1);
		iter0(i, N) a[i] = 1ll * a[i] * b[i] % mod;
		fft(a, N, -1);
	}

	int ta[NR], tb[NR];

	Poly operator*(const Poly &a, const Poly &b) {
		int la = a.size(), lb = b.size();

		Poly c(la + lb - 1);

		if (la + lb <= 100) {
			iter0(i, la) iter0(j, lb) c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % mod;
		} else {
			int N;
			for (N = 1; N < la + lb; N <<= 1);
			iter0(i, N) {
				ta[i] = (i < la ? a[i] : 0);
				tb[i] = (i < lb ? b[i] : 0);
			}
			poly_multo(ta, tb, N);
			iter0(i, la + lb - 1) c[i] = ta[i];
		}
		return upd(c), c;
	}
	int ccc = 0;
	int ti[NR];

	void poly_inv(int *f, int *inv, int n) {
		if (n == 0) {
			inv[0] = mod_inv(f[0]);
			return;
		}
		poly_inv(f, inv, n / 2);
		static int t[140000];
		int N = 1;
		for (; N <= n * 2; N <<= 1);
		iter0(i, N) t[i] = i <= n ? f[i] : 0; reset(inv, n / 2 + 1, N);
		fft(inv, N, +1); fft(t, N, +1);
		iter0(i, N) inv[i] = (2 + mod - 1ll * inv[i] * t[i] % mod) * inv[i] % mod;
		fft(inv, N, -1);
	}

	void poly_mod(int *a, int *b, int *c, int n, int m) {
		if (n < m) {
			iter0(i, m) c[i] = i <= n ? a[i] : 0;
			return;
		}
		static int f[140000], g[140000];
		if (n < 100) {
			int invb = mod_inv(b[m]);
			memcpy(f, a, sizeof(int) * (n + 1));
			down(i, n, m) {
				int t = 1ll * f[i] * invb % mod;
				forw(j, 0, m) (f[i - j] += mod - 1ll * t * b[m - j] % mod) %= mod;
			}
			memcpy(c, f, sizeof(int) * m);
			return;
		}

		int N;
		for (N = 1; N <= max(n, 2 * (n - m)) + 10; N <<= 1);
		reset(g, 0, N);

		forw(i, 0, n - m) f[i] = i <= m ? b[m - i] : 0; reset(f, n - m + 1, N);
		poly_inv(f, g, n - m); reset(g, n - m + 1, N);
		forw(i, 0, n - m) f[i] = a[n - i];
		poly_multo(g, f, N);
		reset(g, n - m + 1, N);
		reverse(g, g + n - m + 1);
		forw(i, 0, m) f[i] = b[i]; reset(f, m + 1, N);
		poly_multo(f, g, N);
		iter0(i, m) c[i] = (a[i] + mod - f[i]) % mod;
	}
	int tr[NR];

	Poly operator%(const Poly &a, const Poly &b) {

		int la = a.size(), lb = b.size(), N;
		Poly c(lb);
		for (N = 1; N < la + lb; N <<= 1);
		iter0(i, N) {
			ta[i] = (i < la ? a[i] : 0);
			tb[i] = (i < lb ? b[i] : 0);
		}
		poly_mod(ta, tb, tr, la - 1, lb - 1);

		iter0(i, lb) c[i] = tr[i];
		iter0(i, N) tr[i] = 0;
		upd(c);

		return c;
	}
	Poly t[NR], tt[NR];
	int tsz, lc[NR], rc[NR];


	void init(int &x, int l, int r, const int a[]) {
		x = ++tsz;
		if (l == r) {
			t[x] = { (mod - a[l]) % mod, 1 };
			return;
		}
		int mid = (l + r) / 2;
		init(lc[x], l, mid, a);
		init(rc[x], mid + 1, r, a);
		t[x] = t[lc[x]] * t[rc[x]];
	}

	int eval(const Poly &A, int x) {
		int p = 1, res = 0;
		for (auto it = A.begin(); it != A.end(); ++it) {
			res = (res + 1ll * p * *it) % mod;
			p = 1ll * p * x % mod;
		}
		return res;
	}

	int pp[NR];

	Poly D(const Poly &a) {
		int la = a.size();
		Poly c(la - 1);
		iter(i, la - 1) c[i - 1] = 1ll * i * a[i] % mod;
		return c;
	}

	void s2(int x, int l, int r, const Poly &f, const int qX[], int ans[]) {
		if (f.size() < 1000 || r - l + 1 <= 200) {
			forw(i, l, r) pp[i] = 1;
			for (auto it = f.begin(); it != f.end(); ++it) {
				forw(i, l, r) {
					ans[i] = (ans[i] + 1ll * pp[i] * *it) % mod;
					pp[i] = 1ll * pp[i] * qX[i] % mod;
				}
			}
			return;
		}

		int mid = (l + r) / 2;
		s2(lc[x], l, mid, f % t[lc[x]], qX, ans);
		s2(rc[x], mid + 1, r, f % t[rc[x]], qX, ans);
	}
	int root;

	void evaluation(const Poly &f, bool inited, const int qX[], int ans[], int m) {
		if (!inited) {
			tsz = 0;
			init(root, 1, m, qX);
		}
		s2(root, 1, m, f, qX, ans);

	}

	int px[NR], py[NR], Q[NR], n, m;

	Poly s1(int x, int l, int r) {
		if (l == r) {
			Poly tmp = { (int) (1ll * py[l] * mod_inv(Q[l]) % mod) };
			return tmp;
		}
		int mid = (l + r) / 2;
		Poly L = s1(lc[x], l, mid), R = s1(rc[x], mid + 1, r);
		return L * t[rc[x]] + R * t[lc[x]];
	}

	Poly interpolation(int m){//put it in (px, py)
		tsz=0;
		init(root,1,m,px);
		Poly f;
		for(int i=1,ti=t[root].size();i<ti;i++){
			f.push_back((lint)t[root][i]*i%mod);
		}
		evaluation(f,true,px,Q,m);
		return s1(root,1,m);
	}

}

const int &O=GROOT::mod;
using GROOT::g;
inline int fpow(int x,int n,const int O=::O){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int n,m,t;
namespace Log{
	unordered_map<int,int>m;
	int rt;
	inline void init(){
		rt=sqrtl(O-1);
		int w=1,wn=fpow(g,rt);
		for(int i=0;i<O-1;i+=rt,w=(lint)w*wn%O){
			m[w]=i;
		}
	}
	inline int bsgs(int w){
		for(int j=0;j<rt;j++,w=(lint)w*g%O){
			unordered_map<int,int>::iterator it=m.find(w);
			if(it!=m.end())return (it->second+O-1-j)%(O-1);
		}
		return -1;
	}
}
int init(int l, int r, int n, int P) {
	GROOT::mod=P,::n=n;
	GROOT::get_root();
	Log::init();
	t=Log::bsgs(m=max(2,l));
	assert(fpow(g,t)==m);
	return m;
}
const int N=60010;
lint x[N];
inline int lb(int x){
	return x&-x;
}
void solve(int *A, int *B) {
	const int c=n+1+(n&1),totn=c+n+1;
	const lint totO=(lint)O*(O-1);
	{//get x
		int q=lb(O-1),p=(O-1)/q;
		int invc=fpow(c,(q>>1)-1,q);
		int xs=0;
		for(lint x1=0;xs<totn;x1++){//mod O-1
			lint x2=Polynomial::px[++xs]=fpow(g,x1*t%q*invc%q*p%(O-1));//mod O
			x[xs]=x1*p*O-x2*(O-1);
			if(x[xs]<0){
				x[xs]=(x[xs]%totO+totO)%totO;
			}
			assert(fpow(m,x[xs]%(O-1))==fpow(x[xs]%O,c));
		}
	}
	get(totn,x,Polynomial::py);
	Polynomial::Poly f=Polynomial::interpolation(totn);
	f.resize(totn-1);
	for(int i=0;i<=n;i++){
		A[i]=f[i],B[i]=f[i+c];
	}
}
