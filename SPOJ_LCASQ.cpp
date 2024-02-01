#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,q,salto[20][maxn],d[maxn],cnt,u,v,cha,c;
vector<int> a[maxn];
void dfs(int u, int par){
    salto[0][u]=par;
    
    for(int i=1;i<=18;i++) {
        salto[i][u]=salto[i-1][salto[i-1][u]];//pre-procesamiento del binary lifting
    }

    for(auto v:a[u]){
        if(v==par) continue;//si es el padre ya no sigue el dfs por ahi
        d[v]=d[u]+1;//calcula la distacia de los nodos al vértice del árbol
        dfs(v,u);
    }
    return;
}
int lca(int u, int v){

    if(d[u]<d[v])swap(v,u);//hago que u sea igual o más profundo que v

    int dist=d[u]-d[v];
    for(int i=18;i>=0;i--){
        if((dist>>i)&1)
            u=salto[i][u];//doy saltos 
    }
    if(u==v) return u;
    for(int i=18;i>=0;i--){
        if(salto[i][u]!=salto[i][v]){
        //el ancestro tiene que ser diferente para dar el salto
            u=salto[i][u];
            v=salto[i][v];
        }
    }
    return salto[0][u];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++){
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1,0);
	cin>>q;
    while(q--){
        cin>>u>>v>>c;
        cha=lca(u,v);//calcula el vértice lca de u y v
		int dista_u_v=d[u]+d[v]-2*d[cha];

        if(dista_u_v<=c){
			cout<<v<<"\n";
		}else{
			if(c>d[u]-d[cha]){//salto desde v 
				for(int i=18;i>=0;i--){
        			if((dista_u_v-c>>i)&1)
            			v=salto[i][v];
    			}
				cout<<v<<"\n";
			}else{//salto desde u 
				for(int i=18;i>=0;i--){
        			if((c>>i)&1)
            			u=salto[i][u];
    			}
				cout<<u<<"\n";
			}
		}
    }
    return 0;
}