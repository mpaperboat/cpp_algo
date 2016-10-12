int n,nx,ny,m;
int link[MaxN],lx[MaxN],ly[MaxN],slack[MaxN]; 
int visx[MaxN],visy[MaxN],w[MaxN][MaxN];

bool DFS(int x) {
	visx[x] = 1;
	for (int y = 1;y <= ny;y++) {
		if (visy[y]) continue;
		int t = lx[x] + ly[y] - w[x][y];
		if (t == 0) {
			visy[y] = 1;
			if (link[y] == -1 || DFS(link[y])) {
				link[y] = x;
				return true;
			}
		}
		else if (slack[y] > t) slack[y] = t;
	}
	return false;
}
void KM() {
	int i,j;
	memset (link,-1,sizeof(link));
	memset (ly,0,sizeof(ly));
	for (i = 1;i <= nx;i ++) for (j = 1,lx[i] = -INF;j <= ny;j ++)
		if (w[i][j] > lx[i]) lx[i] = w[i][j];

	for (int x = 1;x <= nx;x ++) {
		for (i = 1;i <= ny;i++) slack[i] = INF;
		while (1) {
			memset (visx,0,sizeof(visx));
			memset (visy,0,sizeof(visy));
			if (DFS(x)) break;  
			int d = INF;
			for (i = 1;i <= ny;i ++) if (!visy[i]&&d > slack[i]) d = slack[i];
			for (i = 1;i <= nx;i ++) if (visx[i]) lx[i] -= d;
			for (i = 1;i <= ny;i ++) 
				if (visy[i]) ly[i] += d;
				else slack[i] -= d;
		}
	}
}


#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long s64;

const int BufferSize = 1 << 16;

char buffer[BufferSize];
char *head, *tail;

inline char nextChar()
{
	if (head == tail)
	{
		int l = fread(buffer, 1, BufferSize, stdin);
		tail = (head = buffer) + l;
	}
	return *head++;
}

inline int getint()
{
	char c;
	while ((c = nextChar()) < '0' || c > '9');

	int res = c - '0';
	while ((c = nextChar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

namespace Writer
{
	const int BufferSize = 2000;

	char buffer[BufferSize];
	char *tail = buffer;

	inline void putint(int x)
	{
		if (x == 0)
			*tail++ = '0';
		else
		{
			char s[10], *t = s;
			while (x != 0)
				*t++ = x % 10 + '0', x /= 10;
			while (t-- != s)
				*tail++ = *t;
		}
		*tail++ = '\n';
	}

	inline void final()
	{
		fwrite(buffer, 1, tail - buffer, stdout);
	}
};

inline void relax(int &a, const int &b)
{
	if (b > a)
		a = b;
}
inline void tense(int &a, const int &b)
{
	if (b < a)
		a = b;
}

const int MaxNL = 405;
const int MaxNR = 405;
const int INF = 0x3f3f3f3f;

int m, nL, nR, nVer;
int mat[MaxNL][MaxNR];

s64 tot_weight;
int mateL[MaxNL];
int mateR[MaxNR];
int labL[MaxNL];
int labR[MaxNR];
int faR[MaxNR];

int slackR[MaxNR];
int slackRV[MaxNR];

bool bookL[MaxNL];
bool bookR[MaxNR];

int q_n, q[MaxNL];

inline void augment(int v)
{
	while (v)
	{
		int nv = mateL[faR[v]];
		mateL[faR[v]] = v;
		mateR[v] = faR[v];
		v = nv;
	}
}

inline bool on_found_edge(const int &u, const int &v)
{
	bookR[v] = true;
	faR[v] = u;

	int nv = mateR[v];
	if (!nv)
	{
		augment(v);
		return true;
	}
	else
	{
		bookL[nv] = true;
		q[++q_n] = nv;
	}
	return false;
}

inline void match(const int &sv)
{
	for (int u = 1; u <= nVer; ++u)
		bookL[u] = false;
	for (int v = 1; v <= nVer; ++v)
	{
		bookR[v] = false;
		slackRV[v] = faR[v] = 0;
		slackR[v] = INF;
	}

	bookL[q[q_n = 1] = sv] = true;
	while (true)
	{
		for (int i = 1; i <= q_n; ++i)
		{
			int u = q[i];
			for (int v = 1; v <= nVer; ++v)
				if (!bookR[v])
				{
					int d = labL[u] + labR[v] - mat[u][v];
					if (!d)
					{
						if (on_found_edge(u, v))
							return;
					}
					else if (d < slackR[v])
					{
						slackR[v] = d;
						slackRV[v] = u;
					}
				}
		}

		int delta = INF;
		for (int v = 1; v <= nVer; ++v)
			if (!bookR[v])
				tense(delta, slackR[v]);
		for (int u = 1; u <= nVer; ++u)
			if (bookL[u])
				labL[u] -= delta;
		for (int v = 1; v <= nVer; ++v)
		{
			if (bookR[v])
				labR[v] += delta;
			else if (slackR[v] != INF)
				slackR[v] -= delta;
		}

		q_n = 0;
		for (int v = 1; v <= nVer; ++v)
			if (!bookR[v] && !slackR[v])
			{
				if (on_found_edge(slackRV[v], v))
					return;
			}
	}
}

inline void calc_max_weight_match()
{
	for (int u = 1; u <= nL; ++u)
		match(u);

	tot_weight = 0ll;
	for (int u = 1; u <= nL; ++u)
		tot_weight += labL[u];
	for (int v = 1; v <= nR; ++v)
		tot_weight += labR[v];
}

int main()
{
	nL = getint(), nR = getint(), m = getint();
	nVer = max(nL, nR);

	while (m--)
	{
		int u = getint(), v = getint();
		relax(labL[u], mat[u][v] = getint());
	}

	calc_max_weight_match();

	printf("%lld\n", tot_weight);
	for (int u = 1; u <= nL; ++u)
		Writer::putint(mat[u][mateL[u]] ? mateL[u] : 0);

	Writer::final();
	return 0;
}