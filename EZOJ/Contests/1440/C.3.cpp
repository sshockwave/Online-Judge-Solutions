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
		cout<<"new!!!!!!!!!!! ans="<<ans.size()<<endl;
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
vector<int>cliq,unvis;
bool vis[N];
const int LIM=3000000;
double expval[LIM+10];
lint mvcnt[N],okcnt[N];
double ucb[N];
inline void Main(){
	cout<<outputfilename<<"\tcurans="<<ans.size()<<"\r";
	memset(vis+1,0,n);
	for(vector<int>::iterator it=cliq.begin();it!=cliq.end();++it){
		vis[*it]=true;
	}
	unvis.clear();
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			unvis.push_back(i);
		}
	}
	vector<int>rej;
	memset(mvcnt+1,0,n*sizeof(mvcnt[0]));
	memset(okcnt+1,0,n*sizeof(okcnt[0]));
	for(int tot=0;!unvis.empty()&&tot<=LIM;++tot){
		int p;
		if(tot==0){
			p=gen(0,unvis.size()-1);
		}else{
			int len=unvis.size();
			double lgg=log(tot),sum=0;
			for(int i=0;i<len;i++){
				int x=unvis[i];
				if(mvcnt[x]==0){
					ucb[i]=1;
				}else{
					ucb[i]=(double)okcnt[x]/mvcnt[x]+1.414*sqrt(lgg/mvcnt[x]);
				}
				sum+=ucb[i];
			}
			sum*=unit();
			for(int &i=p=0;i<len;i++){
				if(sum<=ucb[i])break;
				sum-=ucb[i];
			}
			p=min(p,len-1);
		}
		swap(unvis.back(),unvis[p]);
		int x=unvis.back();
		++mvcnt[x];
		unvis.pop_back();
		int cnt=0;
		for(vector<int>::iterator it=cliq.begin(),ti=cliq.end();it!=ti;++it){
			cnt+=!con[x][*it];
		}
		if(cnt<=1||unit()<=expval[tot]){//cout
			++okcnt[cnt];
			vector<int>tmp;
			tmp.push_back(x);
			for(vector<int>::iterator it=cliq.begin(),ti=cliq.end();it!=ti;++it){
				if(con[x][*it]){
					tmp.push_back(*it);
				}else{
					unvis.push_back(*it);
				}
			}
			upd_ans(cliq=tmp);
			for(vector<int>::iterator it=rej.begin();it!=rej.end();++it){
				unvis.push_back(*it);
			}
			rej.clear();
		}else{
			rej.push_back(x);
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
	for(;;){
		Main();
	}
}
