#include <iostream>
#include <cstdio>
#include <cstring>
//#include <cassert>
#define assert
#define N 150010
#define INF 0x7f7f7f7f
#define MOD 1073741824
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
struct interval{
	int l,r;
}care[N];
ostream& operator << (ostream& out,interval a){
	printf("(%d,%d)",a.l,a.r);
	return out;
}
int a[N],ctop=0,lord[N],ltop=0,apply[N],b[N];
inline int findl(int lval){
	int l=0,r=ltop-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(care[lord[mid]].l<lval){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
inline int findr(int rval,int l,int r){
	assert(l<=r);
	assert(care[l].l==care[r].l);
	while(l<r){
		int mid=((l+r)>>1)+1;
		if(care[mid].r>rval){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	return l;
}
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n=ni(),tot=ni(),k=ni();
	for(int i=1;i<=n;i++){
		a[i]=ni();
	}
	lord[ltop++]=0;
	for(int i=1;i<=n;i++){
		bool flag=false;
		for(int j=i,cur=0;j<=n;j++){
			cur^=a[j];
			if(cur==k){
				care[ctop].l=i,care[ctop].r=j,ctop++;
				flag=true;
			}
		}
		if(flag){
			lord[ltop++]=ctop;
		}
	}
	ltop--;
	memset(apply,0,sizeof(apply));
	while(tot--){
		int l=ni(),r=ni(),w=ni();
		if(l>care[lord[ltop-1]].l){
			continue;
		}
		for(int i=findl(l);i<ltop&&care[lord[i]].l<=r;i++){
			assert(care[lord[i]].l>=l);
			if(care[lord[i]].r>r){
				continue;
			}
			int p=findr(r,lord[i],lord[i+1]-1);
			assert(care[p].r<=r);
			apply[lord[i]]+=w,apply[p+1]-=w;
		}
	}
	memset(b,0,sizeof(b));
	for(int i=0,last=0;i<ctop;i++){
		last+=apply[i];
		b[care[i].l]+=last,b[care[i].r+1]-=last;
	}
	for(int i=1;i<=n;i++){
		b[i]+=b[i-1];
		printf("%d ",(b[i]%MOD+MOD)%MOD);
	}
}
