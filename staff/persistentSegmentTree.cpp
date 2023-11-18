using namespace std;
typedef    long long      ll;

//persistentSegmentTree
//0-indexed, [l..r]
template<typename V, typename T, typename U>
struct persistentSegmentTree
{
    int n;

    struct treeNode {
        T t;
        U u = U(0);
        int l = -1;
        int r = -1;

        treeNode(const T& t) : t(t) {}
        treeNode() {}
    };
    vector<treeNode> t;
    vector<int> roots;

    int create(const T& v, int ll = -1, int rr = -1, const U& u = U(0))
    {
        int index = t.size();
        auto temp = treeNode(v);
        temp.l = ll;
        temp.r = rr;
        temp.u = u;
        t.pb(temp);
        return index;
    }

    int clone(const treeNode& node)
    {
        return create(node.t, node.l, node.r, node.u);
    }
 
    int push(int v, int tl, int tr)
    {
        if (t[v].u.empty()) return v;
        
        v = clone(t[v]);
        t[v].t += t[v].u;
        if (tl != tr)
        {
            int ll = clone(t[t[v].l]);
            int rr = clone(t[t[v].r]);
            t[ll].u += t[v].u;
            t[rr].u += t[v].u;
            t[v].l = ll;
            t[v].r = rr;
        }
        t[v].u.reset();
        return v;
    }

    int build(const vector<V>& a, int l, int r)
    {
        if (l == r)
            return create(T(a[l], l));
        else 
        {
            int m = (l + r) / 2;
            int ll = build(a, l, m);
            int rr = build(a, m + 1, r);
            return create(t[ll].t + t[rr].t, ll, rr);
        }
    };
 
    persistentSegmentTree(const vector<V>& a)
    {
        n = a.size();
        roots.push_back(build(a, 0, n - 1));
    }
 
    int update(int version, int l, int r, U value)
    {
        int index = update(version, 0, n - 1, l, r, value);
        roots.push_back(index);
        return index;
    }
 
    int update(int v, int tl, int tr, int l, int r, U value) 
    {
        v = push(v, tl, tr);
        if (l > r)
            return v;
        if (tl == l && tr == r)
        {
            t[v].u += value;
            int index = push(v, tl, tr);
            t[v].u.reset();
            return index;
        }
        else 
        {
            int tm = (tl + tr) / 2;
            int ll = update(t[v].l, tl, tm, l, min(r, tm), value);
            int rr = update(t[v].r, tm + 1, tr, max(l, tm + 1), r, value);
            return create(t[ll].t + t[rr].t, ll, rr);
        }
    }

    T get(int version, int l, int r)
    {
        return get(version, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        v = push(v, tl, tr);
        if (l > r) return T();

        if (tl == l && tr == r)
            return t[v].t;
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(t[v].l, tl, tm, l, min(r, tm));
            T right = get(t[v].r, tm + 1, tr, max(l, tm + 1), r);
            return left + right;
        }
    }
};

struct Update {
    ll value = 0;
 
    Update() {}
 
    Update(ll value) : value(value) {}
 
    void operator+=(const Update& b) {
        value += b.value;
    };
 
    Update operator-() {
        return Update(-value);
    };
 
    bool empty() const {
        return value == 0;
    }
 
    void reset() {
        value = 0;
    }
};
 
struct Node 
{
    ll v;
    int pos;
    int l = 1;
 
    Node() : v(0), pos(0) {}
    Node(ll v, int pos) : v(v), pos(pos) {}
    Node(ll v, int pos, int l) : v(v), pos(pos), l(l) {}
 
    Node operator+(const Node& b) const {
        return Node(v + b.v, min(pos, b.pos), l + b.l);
    }
 
    void operator+=(const Update& update) {
        v += update.value * l;
    }
};
