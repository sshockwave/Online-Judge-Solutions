#include <bits/stdc++.h>
#define cout cerr
using namespace std;
typedef long long lint;
const int N=3000;
int n,m;
set<int>to[N];
inline int gen(int l,int r){
	static random_device rand;
	return rand()%(r-l+1)+l;
}
inline bool test(int u,int v){
	return to[u].find(v)!=to[u].end();
}
string outputfilename;
vector<int>ans;
inline void upd_ans(const vector<int>&vec){
	if(vec.size()>ans.size()){
		ans=vec;
		freopen(outputfilename.c_str(),"w",stdout);
		cout<<"new ans="<<ans.size()<<endl;
		printf("%d\n",int(ans.size()));
		for(int i=0;i<ans.size();i++){
			printf("%d ",ans[i]);
		}
		putchar('\n');
		fflush(stdout);
		fclose(stdout);
	}
}
vector<int>cliq;
bool vis[N];
inline void Main(){
	double tmp=1;
	vector<int>unvis;
	for(int i=1;i<=n;i++){
		vis[i]=false;
	}
	for(int i=0;i<cliq.size();i++){
		vis[cliq[i]]=true;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			unvis.push_back(i);
		}
	}
	for(;unvis.size()&&tmp>=1e-10;tmp*=0.99){
		swap(unvis[gen(0,unvis.size()-1)],unvis.back());
		int x=unvis.back();
		int cnt=0;
		for(int i=0;i<cliq.size();++i){
			cnt+=!test(x,cliq[i]);
		}
		const int mx=100000000;
		if((double)gen(0,mx)*cnt/mx<=tmp){
			vector<int>tmp=cliq;
			cliq.clear();
			for(int i=0;i<tmp.size();i++){
				if(test(tmp[i],x)){
					cliq.push_back(tmp[i]);
				}
			}
			cliq.push_back(x);
			unvis.pop_back();
		}
		upd_ans(cliq);
	}
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
	}
	for(;;){
		Main();
	}
}
