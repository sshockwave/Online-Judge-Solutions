#include <bits/stdc++.h>
#define cout cerr
using namespace std;
typedef long long lint;
const int N=1410;
int n,m;
bool con[N][N];
set<int>to[N];
inline int gen(int l,int r){
	static random_device rand;
	return rand()%(r-l+1)+l;
}
string outputfilename;
vector<int>ans;
inline void upd_ans(const vector<int>&vec){
	if(vec.size()>ans.size()){
		ans=vec;
		freopen(outputfilename.c_str(),"w",stdout);
		cout<<outputfilename<<"\tnew ans="<<ans.size()<<endl;
		printf("%d\n",int(ans.size()));
		for(int i=0;i<ans.size();i++){
			printf("%d ",ans[i]);
		}
		putchar('\n');
		fflush(stdout);
		fclose(stdout);
	}
}
int prv[N],sz[N];
inline bool sz_cmp(int a,int b){
	return sz[a]<sz[b];
}
inline double unit(){
	static random_device rand;
	static uniform_real_distribution<double>randdb(0.0,1.0);
	return randdb(rand);
}
bool vis[N];
inline vector<int>getlst(int n){
	vis[0]=true;
	vector<int>vec;
	for(int i=1;i<n;i++){
		vis[i]=vis[prv[i]]&&con[n][i];
		if(vis[i]){
			vec.push_back(i);
		}
	}
	sort(vec.begin(),vec.end(),sz_cmp);
	return vec;
}
inline vector<int>getchain(int x){
	vector<int>vec;
	for(;x;vec.push_back(x),x=prv[x]);
	return vec;
}
inline void Main(){
	cout<<"new round"<<endl;
	for(int i=1;i<=n;i++){
		vector<int>vec=getlst(i);
		//optimum
		prv[i]=!vec.empty()?vec.back():0,sz[i]=sz[prv[i]]+1;
		if(sz[i]>ans.size()){
			upd_ans(getchain(i));
		}
	}
	for(double tempr=1;tempr>=1e-7;tempr*=1-1e-7){//cout
		int x=gen(1,n);
		vector<int>vec=getlst(x);
		if(vec.size()==0)continue;
		int pt;
		{
			int t=vec.size();
			t=gen(1,(t*(t+1))>>1);
			for(int &i=pt=1;t>i;t-=i,i++);
		}
		if(sz[vec[pt]]-sz[prv[x]]>=0||unit()<=tempr){
			//Accept
			for(int i=x+1;i<=n;i++){
				vector<int>vec=getlst(i);
				//optimum
				prv[i]=!vec.empty()?vec.back():0,sz[i]=sz[prv[i]]+1;
				if(sz[i]>ans.size()){
					upd_ans(getchain(i));
				}
			}
			if(sz[x]>ans.size()){
				upd_ans(getchain(x));
			}
		}
	}
	exit(0);
}
int main(int argc,char* args[]){
	assert(argc==2);
	freopen((string("maxcliq")+args[1]+string(".in")).c_str(),"r",stdin);
	outputfilename=(string("maxcliq")+args[1]+string(".out"));
	{
		ifstream fout(outputfilename.c_str());
		int cnt;
		fout>>cnt;
		ans.clear();
		while(cnt--){
			int x;
			fout>>x;
			ans.push_back(cnt);
		}
	}
	cout<<"cur ans="<<ans.size()<<endl;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		to[u].insert(v);
		to[v].insert(u);
		con[u][v]=con[v][u]=true;
	}
	for(;;){
		Main();
	}
}
