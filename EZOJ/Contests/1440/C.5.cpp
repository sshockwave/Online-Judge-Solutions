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
const int LIM=30000000;
double expval[LIM+10];
inline int getcnt(const vector<int>&vec){
	int cnt=0;
	for(vector<int>::const_iterator i=vec.begin();i!=vec.end();++i){
		for(vector<int>::const_iterator j=vec.begin();j!=i;++j){
			cnt+=!con[*i][*j];
		}
	}
	return cnt;
}
vector<int>cliq;
inline void Main(){
	for(int i=0;i<blockcnt;i++){
		cliq[i]=i*blocksize+gen(1,blocksize);
	}
	int ansval=getcnt(cliq);
	for(int tot=0;tot<=LIM;++tot){
		int b=gen(0,blockcnt-1);
		const int v1=cliq[b],v2=b*blocksize+gen(1,blocksize);
		int dt=0;
		for(int i=0;i<blockcnt;i++){
			if(i==b)continue;
			dt+=(!con[cliq[i]][v2])-(!con[cliq[i]][v1]);
		}
		if(dt<=0||unit()<=expval[tot]){
			cliq[b]=v2,ansval+=dt;
			if(ansval==0){
				upd_ans(cliq);
				exit(0);
			}
		}
	}
	cout<<outputfilename<<"\terrorcnt="<<ansval<<"\topt="<<ans.size()<<"\r";
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
	if(n==945){
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
	cliq.resize(blockcnt);
	for(;;){
		Main();
	}
}
