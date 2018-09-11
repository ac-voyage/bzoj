/**
 * BZOJ 1014
 * [JSOI2008] 火星人prefix
 * by Abreto<m@abreto.net>.
 **/
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define MAXL    100100

struct strhash
{
    const static ull p = 233ull;
    ull x[MAXL];
    strhash(void)
    {
        x[0] = 1ull;
        for (int i = 1; i < MAXL; i++)
            x[i] = x[i - 1] * p;
    }
    ull operator[](const unsigned &pos) const { return x[pos]; }
}xP;

struct node
{
    node *f, *ch[2];
    char c;
    int sz; ull h;
    node(node *fa = NULL, node *lc = NULL, node *rc = NULL, char cc = 0)
    {
        f = fa;
        ch[0] = lc; ch[1] = rc;
        c = cc;
        maintain();
    }
    inline void maintain(void)
    {
        int lsz = 0, rsz = 0;
        ull lh = 0ull, rh = 0ull;
        if (ch[0]) { lsz = ch[0]->sz; lh = ch[0]->h; }
        if (ch[1]) { rsz = ch[1]->sz; rh = ch[1]->h; }
        sz = lsz + rsz + 1;
        h = lh * strhash::p + c;
        h = h * xP[rsz] + rh;
    }
    inline int szof(const int d) const { return ch[d] ? ch[d]->sz : 0; }
    inline int which(void)
    {
        if (NULL == f) return 0;
        return (f->ch[1] == this);  /* f[which()] == this */
    }
    inline node *setf(node *fa, int d = 0)
    {
        f = fa;
        if (f) { f->ch[d] = this; f->maintain(); }
        return f;
    }
    inline node *setc(node *son, int d = 0)
    {
        ch[d] = son;
        if (son) son->f = this;
        maintain();
        return this;
    }
    /* rotate this to its fater, return this. */
    inline node *rotate(void)
    {
        if (f != NULL)
        {
            node *ff = f->f;
            int d = which(), fd = f->which();
            setc(f->setc(ch[d ^ 1], d), d ^ 1);
            setf(ff, fd);
        }
        return this;
    }
    /* splay this to child of target */
    inline node *splay(node * const target = NULL)
    {
        while (f != target)
        {
            if (target != f->f)
            {
                ( (which() == f->which()) ? f : this )->rotate();
            }
            rotate();
        }
        return this;
    }
    /* 0-based rank */
    inline node *get_k_th(unsigned k)
    {
        node *p = this;
        int rank;
        while (k != (rank = (p->szof(0))))
        {
            if (k < rank) { p = p->ch[0]; }
            else { k -= (rank + 1); p = p->ch[1]; }
        }
        return p->splay(f);
    }
}nodes[MAXL];

inline node *newnode(node *fa = NULL, char cc = 0, node *lc = NULL, node *rc = NULL)
{
    static int top = 0;
    nodes[top] = node(fa, lc, rc, cc);
    return (nodes + (top++));
}

inline node *insert(node *&root, unsigned k, char c)
{
    root = root->get_k_th(k);
    root->setc(root->ch[1]->get_k_th(0), 1);
    root->ch[1]->setc(newnode(root->ch[1], c), 0);
    root = root->ch[1]->ch[0]->splay(root->f);
    return root;
}

inline node *replace(node *&root, unsigned k, char c)
{
    root = root->get_k_th(k);
    root->c = c;
    root->maintain();
    return root;
}

inline ull hashp(node *&root, unsigned i)
{
    root = root->get_k_th(i);
    ull lh = root->ch[0] ? root->ch[0]->h : 0ull;
    return lh * strhash::p + root->c;
}
inline ull myhash(node *&root, unsigned l, unsigned r)
{
    ull hr = hashp(root, r);
    ull hlm1 = hashp(root, l - 1);
    return hr - hlm1 * xP[r - l + 1];
}

int n;
char s[MAXL];
node *rt;

node *build(node *fa = NULL, int l = 0, int r = n + 1)
{
    if (r < l) return NULL;
    if (l == r) return newnode(fa, s[l]);
    int mid = (l + r) >> 1;
    node *ret = newnode(fa, s[mid]);
    ret->setc(build(ret, l, mid - 1), 0);
    ret->setc(build(ret, mid + 1, r), 1);
    ret->maintain();
    return ret;
}

inline bool check(unsigned x, unsigned y, unsigned len)
{
    ull h1 = myhash(rt, x, x + len - 1);
    ull h2 = myhash(rt, y, y + len - 1);
    return (h1 == h2);
}

int main(void)
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    rt = build();
    int m; scanf("%d", &m);
    while (m--)
    {
        char com[4];
        scanf("%s", com);
        if ('Q' == com[0])
        {
            static int x, y;
            scanf("%d%d", &x, &y);
            if (x > y) swap(x, y);
            int l = 0, r = n - y + 1;
            while (l < r)
            {
                int mid = ((l + r) >> 1) + 1;
                if (check(x, y, mid)) l = mid;
                else r = mid - 1;
            }
            printf("%d\n", l);
        } else {
            static int x;
            static char ch[4];
            scanf("%d%s", &x, ch);
            if ('R' == com[0])
            {
                rt = replace(rt, x, ch[0]);
            } else {
                assert('I' == com[0]);
                rt = insert(rt, x, ch[0]);
                n++;
            }
        }
    }
    return 0;
}
