//Score:50/100
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=50010;
struct bset{
	int lset,rset;
}sets[N];
inline ostream & operator << (ostream & out,bset x){
	out<<"{"<<x.lset<<","<<x.rset<<"}";
	return out;
}
int seq[N],bln[N];
struct ScapegoatTree{
	typedef int info[N];
	info fa,lson,rson,sum,size;
	ScapegoatTree(){
		memset(lson,-1,sizeof(lson));
		memset(rson,-1,sizeof(rson));
		memset(fa,-1,sizeof(fa));
		memset(size,0,sizeof(size));
		memset(sum,0,sizeof(sum));
	}
	inline int rank(int x){//cnt of elements less than x
		cout<<"Ask rank of "<<sets[x];
		if(x!=bln[x]){
			x=bln[x];
		}
		int ans=0;
		if(~lson[x]){
			ans=sum[lson[x]];
		}
		while(~fa[x]){
			if(x==rson[fa[x]]){
				ans+=sum[fa[x]]-sum[x];
			}
			x=fa[x];
		}
		cout<<"="<<ans<<endl;
		return ans;
	}
	inline void up(int x){
		sum[x]=size[x];
		if(~lson[x]){
			sum[x]+=sum[lson[x]];
		}
		if(~rson[x]){
			sum[x]+=sum[rson[x]];
		}
	}
	void dfs(int x,int &stop){
		if(~lson[x]){
			dfs(lson[x],stop);
		}
		seq[++stop]=x;
		if(~rson[x]){
			dfs(rson[x],stop);
		}
	}
	int rebuild(int l,int r,int f){
		if(l>r){
			return -1;
		}
		cout<<"Rebuilding["<<l<<","<<r<<"]  fa="<<f<<endl;
		int mid=(l+r)>>1,x=seq[mid];
		fa[x]=f;
		cout<<"New fa["<<x<<"]="<<fa[x]<<endl;
		lson[x]=rebuild(l,mid-1,x);
		rson[x]=rebuild(mid+1,r,x);
		up(x);
	}
	inline void maintain(int &x){
		int lsize=lson[x]==-1?0:sum[lson[x]];
		int rsize=rson[x]==-1?0:sum[rson[x]];
		if(lsize*5>=sum[x]*4||rsize*5>=sum[x]*4){
			cout<<"Maintain"<<endl;
			int stop=0;
			dfs(x,stop);
			x=rebuild(1,stop,fa[x]);
			cout<<"Rebuild complete"<<endl;
		}
	}
};
struct Ranking:ScapegoatTree{
	int root;
	Ranking(){
		root=-1;
	}
	void insert(int &x,int pt,int rank,int f){//rank:less than
		if(x==-1){
			assert(rank==0);
			x=pt;
			fa[x]=f;
			if(x==5){
				assert(rson[fa[x]]==x);
			}
			cout<<"New node  ";
		}
		cout<<"T2 insert "<<sets[pt]<<"  at "<<sets[x]<<"    ";
		int lsize=lson[x]==-1?0:sum[lson[x]];
		if(lsize==rank){
			if(bln[pt]==x){
				cout<<"Found!"<<endl;
				size[x]++;
				sum[x]++;
				return;
			}
			cout<<"Go left"<<endl;
			insert(lson[x],pt,rank,x);
		}else if(rank<lsize){
			cout<<"Go left"<<endl;
			insert(lson[x],pt,rank,x);
		}else{
			cout<<"Go right"<<endl;
			assert(rank>=lsize+size[x]);
			insert(rson[x],pt,rank-lsize-size[x],x);
		}
		up(x);
		maintain(x);
	}
	int brank(int x,bset &s,int lrank){//less than
		if(x==-1){
			return 0;
		}
		int curlrank=rank(sets[x].lset);
		if(lrank<=curlrank){
			cout<<"Go left!"<<endl;
			return brank(lson[x],s,lrank);
		}
		cout<<"Go right!"<<endl;
		int ans=brank(rson[x],s,lrank)+size[x];
		if(~lson[x]){
			ans+=sum[lson[x]];
		}
		return ans;
	}
}T2;
struct Forest:ScapegoatTree{
	info root;
	Forest(){
		memset(root,-1,sizeof(root));
	}
	void insert(int &x,int pt,int rrank,int f){
		if(x==-1){
			cout<<"New node.over."<<endl;
			x=pt;
			size[x]=1;
			sum[x]=1;
			fa[x]=f;
			bln[x]=x;
			assert(lson[x]==-1&&rson[x]==-1);
			return;
		}
		cout<<"T1 insert pt["<<pt<<"]:"<<sets[pt]<<" at pt["<<x<<"]:"<<sets[x]<<endl;
		int currank=T2.rank(sets[x].rset);
		cout<<"\t"<<sets[x]<<"'s rrank="<<currank<<"   pt's rrank="<<rrank<<"     ";
		if(rrank<currank){
			cout<<"Go left"<<endl;
			insert(lson[x],pt,rrank,x);
		}else if(rrank>currank){
			cout<<"Go right"<<endl;
			insert(rson[x],pt,rrank,x);
		}else{
			size[x]++;
			sum[x]++;
			bln[pt]=x;
			cout<<"Found! size["<<x<<"]++="<<size[x]<<endl;
		}
		up(x);
		maintain(x);
	}
	inline int first(int x){
		for(;~lson[x];x=lson[x]);
		return x;
	}
	inline int insert(int pt){
		int ls=sets[pt].lset,rs=sets[pt].rset,ptrank;
		cout<<"Inserting "<<pt<<":"<<sets[pt]<<"  at root "<<sets[ls]<<endl;
		insert(root[ls],pt,T2.rank(rs),-1);
		if(bln[pt]==pt){
			int fir=first(root[ls]);
			if(pt==fir){
				ptrank=T2.brank(T2.root,sets[pt],T2.rank(ls));
			}else{
				ptrank=T2.rank(fir)+rank(pt);
			}
		}else{
			ptrank=T2.rank(pt);
		}
		cout<<"ptrank of "<<sets[pt]<<" = "<<ptrank<<endl;
		T2.insert(T2.root,pt,ptrank,-1);
		return ptrank+size[bln[pt]];
	}
	inline void init(int n){
		cout<<"Init 0 && "<<n+1<<endl;
		insert(root[0],0,0,-1);
		insert(root[n+1],n+1,1,-1);
		T2.insert(T2.root,0,0,-1);
		T2.insert(T2.root,n+1,1,-1);
	}
}T1;
int main(){
	freopen("C.in","r",stdin);
	int n=ni();
	memset(bln,-1,sizeof(bln));
	sets[0]=(bset){0,0};
	sets[n+1]=(bset){n+1,n+1};
	T1.init(n);
	for(int i=1;i<=n;i++){
		sets[i]=(bset){bln[ni()],bln[ni()]};
		printf("%d\n",T1.insert(i));
	}
}
