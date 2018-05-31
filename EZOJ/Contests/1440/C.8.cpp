#include <bits/stdc++.h>
#define cout cerr
using namespace std;
typedef long long lint;
const int N=1410;
bool con[N][N];
int n,m;
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
		cout<<"new!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ans="<<ans.size()<<endl;
		printf("%d\n",int(ans.size()));
		for(int i=0;i<ans.size();i++){
			printf("%d ",ans[i]);
		}
		putchar('\n');
		fflush(stdout);
		fclose(stdout);
	}
}
inline double unit(){
	static random_device rand;
	static uniform_real_distribution<double>randdb(0.0,1.0);
	return randdb(rand);
}
int blocksize,blockcnt;
struct Node;
typedef Node* node;
int stk[N],ss;
inline bool teststk(int x){
	for(int i=0;i<ss;i++){
		if(!con[stk[i]][x])return false;
	}
	return true;
}
struct Node{
	int tries;
	lint sum;
	Node* nxt[25];
	bool valid[25];
	Node(){
		memset(nxt,0,sizeof(nxt));
		for(int i=0;i<25;i++){
			valid[i]=teststk(i+blocksize*ss+1);
		}
	}
	inline int getnxt(){
		static int lst[N];
		int ls=0;
		for(int i=0;i<25;i++){
			if(valid[i]){
				lst[++ls]=i;
			}
		}
		if(ls==0)return -1;
		return lst[gen(1,ls)];
		static int ucb[N];
		//cout ucb
		for(int i=1;i<=ls;i++){
		}
	}
};
node ndstk[N];
void set_stk_top_invalid(){
	if(ss==0)return;
	//ndstk[ss] is invalid
	const node tstk=ndstk[ss-1];
	tstk->valid[(stk[ss-1]-1)%blocksize]=false;
	ss--;
	for(int i=0;i<25;i++){
		if(tstk->valid[i])return;
	}
	set_stk_top_invalid();
}
inline void Main(){
	static node rt=0;
	ss=0;
	if(rt==0){
	}
	ndstk[ss]=rt;
}
int main(int argc,char* args[]){
	for(int tot=0;tot<=LIM;tot++){
		expval[tot]=exp(-1e-5*tot);
	}
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
	memset(con,0,sizeof(con));
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		to[u].insert(v);
		to[v].insert(u);
		con[u][v]=true;
		con[v][u]=true;
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
