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
inline void Main(){
	vector<vector<int>>st;
	for(int i=1;i<=n;i++){
		bool flag=false;
		shuffle(st.begin(),st.end(),random_device());
		for(vector<vector<int>>::iterator it=st.begin();it!=st.end();++it){
			bool cur=true;
			for(vector<int>::iterator it2=it->begin();it2!=it->end();++it2){
				if(!test(*it2,i)){
					cur=false;
					break;
				}
			}
			if(cur){
				it->push_back(i);
				flag=true;
				break;
			}
		}
		if(!flag){
			st.push_back(vector<int>());
			st.back().push_back(i);
		}
	}
	for(vector<vector<int>>::iterator it=st.begin();it!=st.end();++it){
		upd_ans(*it);
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
