#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <complex>
#include <queue>
#include <cassert>
#define N 710
#define D 1048576
#define EPS 1e-5
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
struct coor{
	int x,y;
};
typedef complex<double> comp;
const double PI=acos(-1);
int rev[D],n,m,len,lm,rm,um,dm,mx[4]={-1,0,1,0},my[4]={0,1,0,-1};
bool vis[N][N];
char mat[N][N];
comp blk[D],ship[D],cross[D];
queue<coor>q;
inline bool nz(comp a){
	return (int)(a.real()+EPS);
}
inline void bitrev(int n){
	for(int i=1;i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=n>>1;
		}
	}
}
inline void bitrev(int n,comp *num){
	for(int i=0;i<n;i++){
		if(i<rev[i]){
			swap(num[i],num[rev[i]]);
		}
	}
}
inline comp unit(int n){
	double angle=PI*2/n;
	return comp(cos(angle),sin(angle));
}
inline void fft(int n,comp *num,int d){
	bitrev(n,num);
	for(int i=2,half;i<=n;i<<=1){
		half=i>>1;
		comp wn=unit(i*d),w=1,p,q;
		for(int j=0;j<half;j++){
			for(int k=j;k<n;k+=i){
				p=num[k],q=w*num[k+half];
				num[k]=p+q,num[k+half]=p-q;
			}
			w*=wn;
		}
	}
	if(d==-1){
		for(int i=0;i<n;i++){
			num[i]/=n;
		}
	}
}
inline void push(int x,int y){
	int shift=(x+um)*m+y+lm;
	if(x+um<0||x+dm>=n||y+lm<0||y+rm>=m||nz(blk[shift])||nz(cross[(len>>1)-1+m*x+y])){
		return;
	}
	blk[shift]=1;
	q.push((coor){x,y});
}
inline void mul(comp *a,comp *b){
	fft(len,a,1);
	fft(len,b,1);
	for(int i=0;i<len;i++){
		a[i]*=b[i];
	}
	fft(len,a,-1);
}
int main(){
	n=ni(),m=ni(),len=n*m*2;
	lm=m,rm=0,um=n,dm=0;
	for(int i=0;i<n;i++){
		gets(mat[i]);
		comp *b=blk+i*m,*s=ship+i*m;
		for(int j=0;j<m;j++){
			if(mat[i][j]=='o'){
				s[j]=1;
				apmin(lm,j),apmax(rm,j);
				apmin(um,i),apmax(dm,i);
			}else if(mat[i][j]=='#'){
				b[j]=1;
			}
		}
	}
	int shift=0;
	for(;(1<<shift)<len;shift++);
	len=(1<<shift);
	bitrev(len);
	for(int i=0,j=(len>>1)-1;i<j;i++,j--){
		swap(ship[i],ship[j]);
	}
	fft(len,ship,1);
	fft(len,blk,1);
	for(int i=0;i<len;i++){
		cross[i]=ship[i]*blk[i];
	}
	fft(len,cross,-1);
	memset(vis,0,sizeof(vis));
	memset(blk,0,sizeof(blk));
	push(0,0);
	while(!q.empty()){
		int x=q.front().x,y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){
			push(x+mx[i],y+my[i]);
		}
	}
	fft(len,blk,1);
	for(int i=0;i<len;i++){
		blk[i]*=ship[i];
	}
	fft(len,blk,-1);
	int ans=0;
	for(int i=0;i<len;i++){
		if(nz(blk[i])){
			ans++;
		}
	}
	printf("%d",ans);
}
