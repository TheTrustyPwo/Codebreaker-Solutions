#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 200005, M = 998244353;

int n, q, p[MAXN], e[MAXN], t[4*MAXN];
bool marked[4*MAXN];

void build(int idx, int l, int r) {
	if (l == r) { t[idx] = 1; return; }
	int m = (l + r) / 2;
	build(idx * 2, l, m);
	build(idx * 2 + 1, m + 1, r);
	t[idx] = p[r - l];
}

void update(int idx, int l, int r, int a, int b, int v) {
	if (a > b) return;
	if (l == a && r == b) {
		t[idx] = (v * p[r - l]) % M;
		marked[idx] = true;
	} else {
		int m = (l + r) / 2;
		if (marked[idx]) {
			t[idx * 2] = t[idx] / e[r - m];
			t[idx * 2 + 1] = t[idx] / e[m - l + 1];
			marked[idx * 2] = marked[idx * 2 + 1] = true;
			marked[idx] = false;
		}
		update(idx * 2, l, m, a, min(b, m), v);
		update(idx * 2 + 1, m + 1, r, max(a, m + 1), b, v);
		t[idx] = (t[idx * 2] * e[r - m] + t[idx * 2 + 1]) % M;
	}
}

int query() {
	return t[1] % M;
}

int32_t main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> q;
	p[0] = 1; for (int i = 1; i <= n; i++) p[i] = (p[i - 1] * 10 + 1) % M;
	e[0] = 1; for (int i = 1; i <= n; i++) e[i] = (e[i - 1] * 10) % M;
	build(1, 1, n);
	while (q--) {
		int l, r, d; cin >> l >> r >> d;
		update(1, 1, n, l, r, d);
		cout << query() << "\n";
	}
}
