#include<bits/stdc++.h>
using namespace std;
#define  int   long long 
// struct item{
//   int v, idx;
// };
typedef int item;
struct segtree{
  int size;
  vector<item>values;
  item NEUTRAL_ELEMENT=INT_MIN;
  item merge(item a , item b)
  {
    return max(a,b);
  }
  item single(int v)
  {
    return v;
    // if(v>0) return{v,v,v,v};
    // return {0,0,0,v};
  }
  void init(int n)
  {
    size=1;
    while(size<n) size*=2;
    values.resize(2*size);
  }
  void build(vector<int>&a,int x ,int lx, int rx)
  {
    if(rx-lx==1)
    {
      if(lx<(int)a.size())
      {
        values[x]=single(a[lx]);
      }
      return;
    }
    int m=(lx + rx)/2;
    build(a,2*x+1,lx,m);
    build(a,2*x+2,m,rx);
    values[x]=merge(values[2*x+1],values[2*x+2]);
   
  }
  void build(vector<int>&a)
  {
      build(a,0,0,size);
  }
  void set(int i, int v, int x , int lx ,int rx)
  {
    if(rx-lx==1)
    {
      values[x]=single(v);
      return;
    }
    int m=(lx + rx)/2;
    if(i<m)
    {
      set(i,v,2*x+1,lx ,m);
    }
    else{
       set(i,v,2*x+2,m ,rx);
    }
    values[x]=merge(values[2*x+1],values[2*x+2]);
  }
  void set(int i, int v)
  {
    set(i,v,0,0,size);
  }
  item calc(int l, int r ,int x ,int lx ,int rx)
  {
    if(lx>=r || l>=rx) return NEUTRAL_ELEMENT;
    if(lx>=l && rx<=r) return values[x];
    int m=(lx+rx)/2;
    item s1=calc(l,r,2*x+1,lx,m);
    item s2=calc(l,r,2*x+2,m,rx);
    return merge(s1,s2);
  }
  item calc(int l , int r)
  {
    return calc(l,r,0,0,size);
  }
  
  int find(int k ,int x, int lx, int rx)
  {
    if(rx-lx==1)
    {
      return lx;
    }
    int m=(lx+rx)/2;
    int sl=values[2*x+1];
    if(k<sl)
    {
      return find(k,2*x+1,lx,m);
    }
    else{
      return find(k-sl,2*x+2,m,rx);
    }
  }
    int find(int k)
    {
      return find(k,0,0,size);
    }
    int first_above(int v, int x, int lx, int rx) {
      if (values[x] < v) return -1;  
      if (rx - lx == 1) return lx;
      int m = (lx + rx) / 2;
      int res = first_above(v, 2*x+1, lx, m);
      if (res == -1) res = first_above(v, 2*x+2, m, rx);
      return res;
  }
  int first_above(int k)
  {
    return first_above(k,0,0,size );
  }
};
signed main(){
  ios::sync_with_stdio(false);
  int n,m;
  cin>>n>>m;
  segtree st;
  st.init(n);
  vector<int>a(n);
  for(int i=0;i<n;i++)
  {
   cin>>a[i];
  }
  st.build(a);
  while(m--)
  {
    int op;cin>>op;
    if(op==1)
    {
      int i;cin>>i;
      int v;cin>>v;
      st.set(i,v);
    }
    else{
      int k;cin>>k;
      cout<<st.first_above(k)<<endl;;
    }
  }
}