#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
    T i=0;char c;
    while(!isdigit(c=getchar())&&c!='-');
    bool flag=c=='-';
    flag?(c=getchar()):0;
    while(i=i*10-'0'+c,isdigit(c=getchar()));
    return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
    if(a<b){
        a=b;
    }
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
    if(a>b){
        a=b;
    }
}
const int N=11,M=22;
int mat[N][M];
inline bool gou(int x){
    return x&1;
}
inline bool gor(int x){
    return (x>>1)&1;
}
inline bool god(int x){
    return (x>>2)&1;
}
inline bool gol(int x){
    return (x>>3)&1;
}
bool vis[N][M];
int n,m;
inline bool valid(int x,int y){
    return x>=1&&x<=n&&y>1&&y<=m&&!vis[x][y];
}
inline void flow(int x,int y){
    static int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
    vis[x][y]=true;
    if(y==m){
        return;
    }
    for(int d=0;d<4;d++){
        if((mat[x][y]>>d)&1){
            int tx=x+dx[d],ty=y+dy[d];
            if(valid(tx,ty)&&((mat[tx][ty]>>((d+2)&3))&1)){
                flow(tx,ty);
            }
        }
    }
}
int ans=0;
int turn[16];
inline void dfs(int x,int y){
    if(y==m){
        x++;
        y=2;
    }
    if(x>n){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            if((mat[i][2]>>3)&1){
                flow(i,2);
            }
        }
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(vis[i][m]){
                cnt++;
            }
        }
        apmax(ans,cnt);
        return;
    }
    if(mat[x][y]==0){
        dfs(x,y+1);
        return;
    }
    for(int t=0;t<4;t++,mat[x][y]=turn[mat[x][y]]){
        dfs(x,y+1);
    }
}
int main(){
    for(int i=0;i<16;i++){
        turn[i]=i>>1;
        if(i&1){
            turn[i]|=8;
        }
    }
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=2;j<m;j++){
                mat[i][j]=ni;
            }
            mat[i][m]=8;
        }
        if(n==1){
            bool flag=true;
            for(int j=2;j<m;j++){
                if(!((gou(mat[1][j])&&god(mat[1][j]))||(gol(mat[1][j])&&gor(mat[1][j])))){
                    flag=false;
                    break;
                }
            }
            putchar('0'+flag);
            return 0;
        }
        dfs(1,2);
        printf("%d\n",ans);
    }
    return 0;
}