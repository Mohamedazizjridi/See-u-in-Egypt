struct DSU {
    vector<int> parent, sz;
    DSU(int n): parent(n), sz(n,1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x){ return parent[x]==x ? x : parent[x]=find(parent[x]); }
    bool join(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a; sz[a]+=sz[b]; return true;
    }
};