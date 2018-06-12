#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
#ifdef ONLINE_JUDGE
lint ans[16][20][2]={
	{
		{1,1ll},
		{2,2ll},
		{3,3ll},
		{4,4ll},
		{5,5ll},
		{6,6ll},
		{7,7ll},
		{8,8ll},
		{9,9ll},
		{10,10ll},
		{11,11ll},
		{12,12ll},
		{13,13ll},
		{14,14ll},
		{15,15ll},
		{16,16ll},
		{17,17ll},
		{18,18ll},
		{19,19ll},
		{20,20ll}
	},
	{
		{1,1ll},
		{2,3ll},
		{2,3ll},
		{3,10ll},
		{4,15ll},
		{4,15ll},
		{5,28ll},
		{6,36ll},
		{6,36ll},
		{7,55ll},
		{8,66ll},
		{8,66ll},
		{9,91ll},
		{10,105ll},
		{10,105ll},
		{11,136ll},
		{12,153ll},
		{12,153ll},
		{13,190ll},
		{14,210ll}
	},
	{
		{1,1ll},
		{1,2ll},
		{2,10ll},
		{2,12ll},
		{3,35ll},
		{3,50ll},
		{4,84ll},
		{4,112ll},
		{5,165ll},
		{5,210ll},
		{6,286ll},
		{6,352ll},
		{7,455ll},
		{7,546ll},
		{8,680ll},
		{8,800ll},
		{9,969ll},
		{9,1122ll},
		{10,1330ll},
		{10,1520ll}
	},
	{
		{1,1ll},
		{1,2ll},
		{2,15ll},
		{2,30ll},
		{2,30ll},
		{3,126ll},
		{3,182ll},
		{4,330ll},
		{4,486ll},
		{4,570ll},
		{5,1001ll},
		{5,1287ll},
		{6,1820ll},
		{6,2366ll},
		{6,2730ll},
		{7,3876ll},
		{7,4692ll},
		{8,5985ll},
		{8,7296ll},
		{8,8265ll}
	},
	{
		{1,1ll},
		{1,4ll},
		{2,21ll},
		{2,52ll},
		{2,80ll},
		{3,252ll},
		{3,455ll},
		{3,672ll},
		{3,504ll},
		{4,2002ll},
		{4,2992ll},
		{4,1980ll},
		{5,6188ll},
		{5,8554ll},
		{5,8463ll},
		{6,15504ll},
		{6,20332ll},
		{6,20808ll},
		{7,33649ll},
		{7,42484ll}
	},
	{
		{1,1ll},
		{1,4ll},
		{1,6ll},
		{2,84ll},
		{2,195ll},
		{2,270ll},
		{3,924ll},
		{3,1708ll},
		{3,2730ll},
		{3,1260ll},
		{4,8008ll},
		{4,12298ll},
		{4,17017ll},
		{4,10010ll},
		{5,38760ll},
		{5,54128ll},
		{5,71196ll},
		{6,100947ll},
		{6,134577ll},
		{6,174990ll}
	},
	{
		{1,1ll},
		{1,6ll},
		{1,6ll},
		{2,120ll},
		{2,325ll},
		{2,690ll},
		{2,630ll},
		{3,3432ll},
		{3,6426ll},
		{3,9960ll},
		{3,7392ll},
		{4,31824ll},
		{4,50375ll},
		{4,73684ll},
		{4,75075ll},
		{5,170544ll},
		{5,245140ll},
		{5,345168ll},
		{5,434112ll},
		{5,232560ll}
	},
	{
		{1,1ll},
		{1,6ll},
		{1,12ll},
		{2,165ll},
		{2,490ll},
		{2,1155ll},
		{2,1785ll},
		{3,6435ll},
		{3,12861ll},
		{3,23985ll},
		{3,39402ll},
		{3,35244ll},
		{4,125970ll},
		{4,203385ll},
		{4,314925ll},
		{4,413998ll},
		{5,735471ll},
		{5,1081557ll},
		{5,1561059ll},
		{5,2189940ll}
	},
	{
		{1,1ll},
		{1,8ll},
		{1,18ll},
		{2,220ll},
		{2,710ll},
		{2,1870ll},
		{2,3780ll},
		{2,4200ll},
		{3,24310ll},
		{3,48610ll},
		{3,91707ll},
		{3,157080ll},
		{3,121836ll},
		{4,497420ll},
		{4,817175ll},
		{4,1300928ll},
		{4,1889550ll},
		{4,1575288ll},
		{5,4686825ll},
		{5,6906880ll}
	},
	{
		{1,1ll},
		{1,8ll},
		{1,24ll},
		{1,24ll},
		{2,1001ll},
		{2,2976ll},
		{2,7322ll},
		{2,12040ll},
		{2,5040ll},
		{3,92378ll},
		{3,184679ll},
		{3,349404ll},
		{3,584727ll},
		{3,528528ll},
		{4,1961256ll},
		{4,3268624ll},
		{4,5302334ll},
		{4,8213346ll},
		{4,9966488ll},
		{5,20030010ll}
	},
	{
		{1,1ll},
		{1,10ll},
		{1,30ll},
		{1,24ll},
		{2,1365ll},
		{2,4362ll},
		{2,12152ll},
		{2,26936ll},
		{2,26460ll},
		{3,167960ll},
		{3,352704ll},
		{3,704748ll},
		{3,1338337ll},
		{3,2252250ll},
		{3,1396395ll},
		{4,7726160ll},
		{4,13037878ll},
		{4,21460392ll},
		{4,34179860ll},
		{4,49729080ll}
	},
	{
		{1,1ll},
		{1,10ll},
		{1,42ll},
		{1,48ll},
		{2,1820ll},
		{2,6181ll},
		{2,18277ll},
		{2,46018ll},
		{2,77532ll},
		{2,16800ll},
		{3,646646ll},
		{3,1351999ll},
		{3,2699554ll},
		{3,5059054ll},
		{3,8118110ll},
		{3,4724720ll},
		{4,30421755ll},
		{4,51895764ll},
		{4,86478728ll},
		{4,140450090ll}
	},
	{
		{1,1ll},
		{1,12ll},
		{1,48ll},
		{1,72ll},
		{2,2380ll},
		{2,8562ll},
		{2,26859ll},
		{2,73248ll},
		{2,161028ll},
		{2,168000ll},
		{3,1144066ll},
		{3,2496132ll},
		{3,5199350ll},
		{3,10375456ll},
		{3,19616025ll},
		{3,30144400ll},
		{3,12932920ll},
		{4,119759850ll},
		{4,206253056ll},
		{4,347350780ll}
	},
	{
		{1,1ll},
		{1,12ll},
		{1,60ll},
		{1,120ll},
		{2,3060ll},
		{2,11622ll},
		{2,38472ll},
		{2,111300ll},
		{2,271152ll},
		{2,489720ll},
		{2,207900ll},
		{3,4457400ll},
		{3,9657609ll},
		{3,20050368ll},
		{3,39851760ll},
		{3,73372728ll},
		{3,109249140ll},
		{3,24504480ll},
		{4,471435600ll},
		{4,818808990ll}
	},
	{
		{1,1ll},
		{1,14ll},
		{1,72ll},
		{1,144ll},
		{1,120ll},
		{2,15504ll},
		{2,54257ll},
		{2,168896ll},
		{2,449274ll},
		{2,896700ll},
		{2,1000230ll},
		{3,7726160ll},
		{3,17383847ll},
		{3,37440858ll},
		{3,77515659ll},
		{3,154301680ll},
		{3,283798476ll},
		{3,359165664ll},
		{3,77597520ll},
		{4,1855967520ll}
	},
	{
		{1,1ll},
		{1,14ll},
		{1,84ll},
		{1,216ll},
		{1,120ll},
		{2,20349ll},
		{2,74606ll},
		{2,244720ll},
		{2,720594ll},
		{2,1773870ll},
		{2,2718870ll},
		{2,831600ll},
		{3,30421755ll},
		{3,67863810ll},
		{3,145411305ll},
		{3,300042678ll},
		{3,591311578ll},
		{3,1068749370ll},
		{3,1282424988ll},
		{4,4059928950ll}
	}
};
int main(){
	for(int tot=ni;tot--;){
		const int n=ni-1,d=ni-1;
		printf("%lld %lld\n",ans[n][d][0],ans[n][d][1]);
	}
#else
const int N=22,INF=0x7f7f7f7f;
namespace gmath{
	int c[N][N];
	inline void main(int n=N-1){
		memset(c,0,sizeof(c));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=c[i-1][j-1]+c[i-1][j];
			}
		}
	}
}
int mencnt;
namespace atm{
	const int N=3000;
	struct Node;
	typedef Node* node;
	struct Node{
		vector<node>add;
		node del;
		int sum,cur;
		int unvis;
		//ans
		int day;
		bool f;
	}pool[N*20];
	node pt=pool;
	node s,t;
	inline node nn(){
		static node &n=pt;
		return n++;
	}
	void build(node x){
		x->add.resize(x->unvis+1);
		for(int j=1;j<=x->unvis;j++){
			if(j<x->cur){
				x->add[j]=x->del->add[j]->add[x->cur];
			}else{
				const node v=x->add[j]=nn();
				v->del=x;
				v->sum=x->sum+j,v->cur=j;
				v->unvis=x->unvis-j;
				build(v);
			}
		}
	}
	int curval;
	void dfs1(node x,node y,int dshrst,int dshmx,int menrst,int menpri){
		if(dshrst*menpri>menrst)return;
		if(dshrst==0){
			if(x==0){
				apmin(y->day,curval);
			}else if(x==s){
				const int unvis=x->unvis-y->sum;
				for(int i=0;i<=unvis;i++){
					dfs1(0,y,unvis-i,unvis,menrst,1);
				}
			}else{
				dfs1(x->del,y,x->cur,x->cur,menrst,0);
			}
		}else for(int i=1;i<=dshrst&&i<=dshmx&&i*menpri<=menrst;i++){
			dfs1(x,y->add[i],dshrst-i,i,menrst-i*menpri,menpri+1);
		}
	}
	void dp1(node x){
		if(x->day+1>=t->day)return;
		curval=x->day+1;
		dfs1(x,s,0,0,mencnt,0);
		for(int j=x->unvis;j>=x->cur&&j>=1;j--){
			dp1(x->add[j]);
		}
	}
	bool dfs3(node x,node y,int dshrst,int dshmx,int menrst,int menpri){
		if(dshrst*menpri>menrst)return false;
		if(y->day>curval)return false;
		if(dshrst==0){
			if(x==0)return y->day==curval&&y->f;
			else if(x==s){
				const int unvis=x->unvis-y->sum;
				for(int i=0;i<=unvis;i++){
					if(dfs3(0,y,unvis-i,unvis,menrst,1))return true;
				}
				return false;
			}else return dfs3(x->del,y,x->cur,x->cur,menrst,0);
			assert(false);
			return false;
		}
		for(int i=1;i<=dshrst&&i<=dshmx&&i*menpri<=menrst;i++){
			if(dfs3(x,y->add[i],dshrst-i,i,menrst-i*menpri,menpri+1))return true;
		}
		return false;
	}
	void dp2(node x){
		if(x->day>=t->day)return;
		for(int j=max(1,x->cur);j<=x->unvis;j++){
			dp2(x->add[j]);
		}
		if(x->day){
			curval=x->day+1;
			x->f=dfs3(x,s,0,0,mencnt,0);
		}
	}
	lint dfs4(node x,int menrst,int menpri){
		if(menrst==0)return x->day==1&&x->f;
		if(menpri>menrst)return 0;
		lint ans=0;
		if(menpri<menrst){
			ans+=dfs4(x,menrst,menpri+1);
		}
		for(int i=1;i<=x->unvis&&i*menpri<=menrst;i++){
			ans+=gmath::c[x->unvis][i]*dfs4(x->add[i],menrst-i*menpri,menpri+1);
		}
		return ans;
	}
}
atm::node rt[N];
inline void Main(const int n,const int d){
	mencnt=n;
	{
		using namespace atm;
		s=rt[d];
		const int d=s->unvis;
		s->day=0,s->f=false;
		for(node i=s+1;i<pt&&i->sum+i->unvis==d;i++){
			i->day=INF,i->f=false;
		}
	}
	{
		using atm::t;
		for(t=atm::s;t->unvis;t=t->add[1]);
		t->f=1;
	}
	atm::dp1(atm::s);
	atm::dp2(atm::s);
	printf("\t\t{%d,%lldll}",atm::t->day,atm::dfs4(atm::s,mencnt,1));
}
int main(){
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
	gmath::main();
	for(int i=1;i<=20;i++){
		atm::node s=rt[i]=atm::nn();
		s->del=0;
		s->sum=s->cur=0;
		s->unvis=i;
		s->day=0;
		atm::build(s);
	}
	puts("lint ans[16][20][2]={");
	for(int i=1;i<=16;i++){
		puts("\t{");
		for(int j=1;j<=20;j++){
			Main(i,j);
			if(j<20){
				putchar(',');
			}
			putchar('\n');
		}
		if(i<16){
			puts("\t},");
		}else{
			puts("\t}");
		}
	}
	puts("};");
#endif
	return 0;
}
