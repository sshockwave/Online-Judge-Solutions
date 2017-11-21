#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
int pos[N],v[N],lst[N];
vector<int>vec[2];
inline bool pcmp(int a,int b){
	return pos[a]<pos[b];
}
int ans[N];
int main(){
	int n=ni,len=ni;
	lint t=ni;
	for(int i=1;i<=n;i++){
		pos[i]=ni;
		lst[i]=i;
		v[i]=3-(ni<<1);
		vec[v[i]>0].push_back(i);
	}
	if(vec[0].size()==0||vec[1].size()==0){
		for(int i=1;i<=n;i++){
			printf("%lld\n",((pos[i]+v[i]*t)%len+len)%len);
		}
		return 0;
	}
	sort(lst+1,lst+n+1,pcmp);
	sort(vec[1].begin(),vec[1].end(),pcmp);
	reverse(vec[1].begin(),vec[1].end());
	for(int i=0;i<(int)vec[0].size();i++){
		if(pos[vec[0][i]]<pos[vec[1][0]]){
			pos[vec[0][i]]+=len;
		}
	}
	sort(vec[0].begin(),vec[0].end(),pcmp);
	bool latter=false;
	lint finpos;
	{
		lint tmpans;
		{
			lint l=0,r=t;
			while(l<r){
				lint m=(l+r)>>1;
				lint p0=m%vec[0].size();
				lint p1=(m+1)%vec[1].size();
				lint pos0=pos[vec[0][p0]]+m/vec[0].size()*len;
				lint pos1=pos[vec[1][p1]]-(m+1)/vec[1].size()*len;
				if((t<<1)<pos0-pos1){
					r=m;
				}else{
					l=m+1;
				}
			}
			tmpans=l;
		}
		lint p0=tmpans%vec[0].size();
		lint p1=tmpans%vec[1].size();
		lint pos0=pos[vec[0][p0]]+tmpans/vec[0].size()*len;
		lint pos1=pos[vec[1][p1]]-tmpans/vec[1].size()*len;
		if((t<<1)<=pos0-pos1){
			finpos=pos1+t;
		}else{
			finpos=pos0-t;
		}
		finpos=(finpos%len+len)%len;
		if(tmpans){
			lint p11=(tmpans-1)%vec[0].size();
			lint pos11=pos[vec[0][p11]]+(tmpans-1)/vec[0].size()*len;
			if((t<<1)==pos11-pos1){
				latter=true;
			}
		}
	}
	for(int i=1;i<=n;i++){
		pos[i]=((pos[i]+(lint)v[i]*t)%len+len)%len;
	}
	sort(pos+1,pos+n+1);
	int curpos,curlst;
	for(int i=1;i<=n;i++){
		if(pos[i]==finpos){
			if(latter){
				if(pos[i%n+1]==pos[i]){
					curpos=i%n+1;
				}else{
					curpos=i;
				}
			}else{
				if(pos[i==1?n:i-1]==pos[i]){
					curpos=i==1?n:i-1;
				}else{
					curpos=i;
				}
			}
			break;
		}
	}
	for(int i=1;i<=n;i++){
		if(lst[i]==vec[1][0]){
			curlst=i;
			break;
		}
	}
	for(int i=1;i<=n;i++,curpos=curpos%n+1,curlst=curlst%n+1){
		ans[lst[curlst]]=pos[curpos];
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
