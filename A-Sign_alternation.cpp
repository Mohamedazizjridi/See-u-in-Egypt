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
  item NEUTRAL_ELEMENT=0;
  item merge(item a , item b)
  {
    return a+b;
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
    int first_above(int v, int idx, int x, int lx, int rx) {
      if (values[x] < v || rx<idx) return -1;  
      if (rx - lx == 1) return lx;
      int m = (lx + rx) / 2;
      int res = first_above(v,idx, 2*x+1, lx, m);
      if (res == -1) res = first_above(v,idx, 2*x+2, m, rx);
      return res;
  }
  int first_above(int k ,int idx)
  {
    return first_above(k,idx,0,0,size );
  }
};
signed main(){
  ios::sync_with_stdio(false);
  int n;
  cin>>n;
  segtree stp;
  segtree stip;
  stp.init(n);
  stip.init(n);
  vector<int>a(n,0);
  vector<int>aa(n,0);
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
    aa[i]=a[i];
    if((i+1)%2==0){
      a[i]=-a[i];
    }
    else{
      aa[i]=-aa[i];
    }
  }
  stp.build(a);
  stip.build(aa);
  int m;cin>>m;
  while(m--)
  {
    int op;cin>>op;
    if(op==0)
    {
      int i,v;cin>>i>>v;
      if(i%2==0){
        stp.set(i-1, -v);
        stip.set(i-1,v);
      }
      else{
        stp.set(i-1,v);
         stip.set(i-1, -v);
      }
    }
    else{
      int l ,r;cin>>l>>r;
      if(l%2==0)
      {
        cout<<stip.calc(l-1,r)<<endl;
      }
      else{
        cout<<stp.calc(l-1 , r)<<endl;
      }
    }
  }
  cout<<endl;
  return 0;
}