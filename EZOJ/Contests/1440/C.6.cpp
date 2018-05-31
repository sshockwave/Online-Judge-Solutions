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
vector<int>cliq;
inline void Main(){
	int cnt=0;
	for(int i=0;i<blockcnt;i++){
		cnt+=cliq[i]!=0;
	}
	cout<<outputfilename<<"\tcur="<<cnt<<"\topt="<<ans.size()<<"\r";
	for(int tot=0;tot<=LIM;++tot){
		vector<int>unvis;
		for(int i=0;i<blockcnt;i++){
			if(cliq[i]==0){
				unvis.push_back(i);
			}
		}
		if(unvis.empty()){
			upd_ans(cliq);
			exit(0);
		}
		const int x=unvis[gen(0,unvis.size()-1)];
		int dt=1;
		const int v=blocksize*x+gen(1,blocksize);
		for(int i=0;i<blockcnt;i++){
			if(cliq[i]){
				dt-=!con[cliq[i]][v];
			}
		}
		if(dt>=0||unit()<=expval[tot]){
			for(int i=0;i<blockcnt;i++){
				if(cliq[i]&&!con[cliq[i]][v]){
					cliq[i]=0;
				}
			}
			cnt+=dt;
			cliq[x]=v;
			if(cnt>ans.size()){
				vector<int>tmp;
				for(vector<int>::iterator it=cliq.begin();it!=cliq.end();++it){
					if(*it){
						tmp.push_back(*it);
					}
				}
				upd_ans(tmp);
			}
		}
	}
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
	cliq.resize(blockcnt);
	for(;;){
		Main();
	}
}
