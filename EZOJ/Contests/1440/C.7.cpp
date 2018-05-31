#include <bits/stdc++.h>
#define cout cerr
using namespace std;
typedef long long lint;
const int N=1410;
int n,m;
int blocksize,blockcnt;
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
vector<int>stk;
inline vector<int>inters(const vector<int>&vec,const set<int>&s){
	vector<int>ans;
	for(vector<int>::const_iterator it=vec.begin();it!=vec.end();++it){
		if(s.find(*it)!=s.end()){
			ans.push_back(*it);
		}
	}
	return ans;
}
bool vis[N];
void dfs(vector<int>vec){
	upd_ans(stk);
	const int tcol=blockcnt-stk.size();
	memset(vis,0,tcol);
	for(vector<int>::iterator it=vec.begin();it!=vec.end();++it){
		vis[(*it-1)/blocksize]=true;
	}
	for(int i=0;i<tcol;i++){
		if(!vis[i])return;
	}
	const int col=(vec.back()-1)/blocksize;
	vector<int>unvis;
	for(;!vec.empty()&&(vec.back()-1)/blocksize==col;unvis.push_back(vec.back()),vec.pop_back());
	for(;!unvis.empty();){
		swap(unvis.back(),vec[gen(0,unvis.size()-1)]);
		const int x=unvis.back();
		stk.push_back(x);
		dfs(inters(vec,to[x]));
		stk.pop_back();
		if(ans.size()==blockcnt)return;
	}
}
inline void Main(){
	vector<int>vec;
	for(int i=1;i<=n;i++){
		vec.push_back(i);
	}
	dfs(vec);
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
	}
	if(n==450){
		blocksize=15;
	}else if(n==945){
		blocksize=21;
	}else if(n==1150){
		blocksize=23;
	}else if(n==1272){
		blocksize=24;
	}else if(n==1400){
		blocksize=25;
	}else{
		assert(false);
	}
	blockcnt=n/blocksize;
	for(;;){
		Main();
	}
}
