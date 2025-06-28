// -------------------------  MO's with corrdinate compression -------------------------
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200005;
const int Q = 200005;
const int MAX_VAL = 1000005;
const int SQ = 450;
struct query
{
    int l,r,q_idx,block_idx;
    query(){}
    query(int _l,int _r,int _q_idx)
    {
        l=_l-1,r=_r-1,q_idx=_q_idx,block_idx=_l/SQ;
    }
    bool operator<(const query&y)const{
        if(block_idx!=y.block_idx)
        {
            return block_idx<y.block_idx;
        }
        return r<y.r;
    }
};
int n, q;
int a[N], old_val[N], orig_val[N], f[N];
ll res = 0;
ll q_ans[N];
vector<int> vals;
query queries[N];
void add(int idx) {
    int id = old_val[idx];
    f[id]++;
    if (f[id] == orig_val[id]) res++;
    if (f[id] == orig_val[id] + 1) res--;
}
 
void remove(int idx) {
    int id = old_val[idx];
    if (f[id] == orig_val[id]) res--;
    if (f[id] == orig_val[id] + 1) res++;
    f[id]--;
}

void MO_process()
{
    sort(queries,queries+q);
    int l=1,r=0;
    for(int i=0;i<q;i++)
    {
        while(r<queries[i].r)add(++r);
        while(r>queries[i].r)remove(r--);
        while(l<queries[i].l)remove(l++);
        while(l>queries[i].l)add(--l);
        q_ans[queries[i].q_idx]=res;
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin>>a[i];
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; i++) {
        old_val[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
        orig_val[old_val[i]] = a[i]; 
    }
    for(int i=0;i<q;i++)
    {
        int l,r;cin>>l>>r;
        queries[i]=query(l,r,i);
    }
    MO_process();
    for(int i=0;i<q;i++)
    {
        cout<<q_ans[i]<<'\n';
    }
    return 0;}
