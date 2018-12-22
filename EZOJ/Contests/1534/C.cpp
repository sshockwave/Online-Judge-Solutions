#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef vector<db>vi;
typedef long long lint;
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
struct relu{
	inline db operator () (const db x)const{
		return max(x,0.01*x);
	}
	inline db deri(const db x)const{
		return x>=0?1:0.01;
	}
};
struct sigmoid_tanh{
	inline db operator () (const db x)const{
		return tanh(x);
	}
	inline db deri(const db x)const{
		return 1-sqr(tanh(x));
	}
};
struct sigmoid{
	inline db operator () (const db x)const{
		return 1/(1+exp(-x));
	}
	inline db deri(const db x)const{
		const db tmp=operator()(x);
		return tmp*(1-tmp);
	}
};
inline db gen(){
	return ((db)rand()/RAND_MAX-0.5)*1e-1;
}
template<class actfunc>struct layer{
	int n1,n2;
	db *c,**w;
	db learnrate;
	inline void init(int _n1,int _n2){
		n1=_n1,n2=_n2;
		c=new db[n2];
		w=new db*[n2];
		for(int i=0;i<n2;i++){
			c[i]=gen();
			w[i]=new db[n1];
			for(int j=0;j<n1;j++){
				w[i][j]=gen();
			}
		}
	}
	inline vi feed(const vi &a)const{
		assert(n1==(int)a.size());
		vi b;
		const static actfunc f;
		for(int i=0;i<n2;i++){
			db sum=0;
			for(int j=0;j<n1;j++){
				sum+=w[i][j]*a[j];
			}
			b.push_back(f(sum+c[i]));
		}
		return b;
	}
	inline void bp_deri(const vi &a,vi &deri)const{
		assert(n1==(int)a.size());
		assert(n2==(int)deri.size());
		const static actfunc f;
		for(int i=0;i<n2;i++){
			db sum=0;
			for(int j=0;j<n1;j++){
				sum+=w[i][j]*a[j];
			}
			assert(!isnan(sum));
			deri[i]*=f.deri(sum+c[i]);
			assert(!isnan(deri[i]));
		}
	}
	inline vi bp(const vi &a,vi deri)const{
		bp_deri(a,deri);
		vi ans(n1);
		for(int i=0;i<n2;i++){
			for(int j=0;j<n1;j++){
				ans[j]+=deri[i]*w[i][j];
			}
		}
		return ans;
	}
	inline void train(const vi &a,vi deri){
		bp_deri(a,deri);
		for(int i=0;i<n2;i++){
			c[i]-=learnrate*deri[i];
			for(int j=0;j<n1;j++){
				w[i][j]-=learnrate*deri[i]*a[j];
			}
		}
	}
};
layer<relu>lay1;
layer<relu>lay2;
const int Q=50000;
const int n=28;
FILE *fin=fopen("training.in","r");
FILE *fout=fopen("training.out","r");
const db YES=1.5,NO=0;
struct testcase{
	vi a;
	int ans;
	inline void input(bool inputans){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				db tmp;
				fscanf(fin,"%lf",&tmp);
				a.push_back(tmp);
			}
		}
		if(inputans){
			fscanf(fout,"%d",&ans);
		}
	}
	inline void train()const{
		vi b=lay1.feed(a);
		vi c=lay2.feed(b);
		vi deri(10);
		for(int i=0;i<10;i++){
			db d=i==ans?YES:NO;
			deri[i]=2*(c[i]-d);
		}
		lay2.train(b,deri);
		c=lay2.feed(b);
		for(int i=0;i<10;i++){
			db d=i==ans?YES:NO;
			deri[i]=2*(c[i]-d);
		}
		lay1.train(a,lay2.bp(b,deri));
	}
	inline db err()const{
		vi c=lay2.feed(lay1.feed(a));
		db ans=0;
		for(int i=0;i<10;i++){
			db d=i==ans?YES:NO;
			ans+=sqr(d-c[i]);
		}
		return ans;
	}
	inline int run()const{
		vi v=lay2.feed(lay1.feed(a));
		int ansp=0;
		db ansv=-2;
		for(int i=0;i<10;i++){
			if(v[i]>ansv){
				ansp=i,ansv=v[i];
			}
		}
		return ansp;
	}
	inline bool test()const{
		return run()==ans;
	}
}q[Q];
int lst[Q];
int main(){
	lay1.init(n*n,30),lay1.learnrate=1e-3;
	lay2.init(30,10),lay2.learnrate=1e-4;
	for(int i=0;i<Q;i++){
		q[i].input(true);
		lst[i]=i;
	}
	cout<<"["<<clock()<<"us]read in complete"<<endl;
	const static int tQ=50000;
	int lastt=clock();
	random_shuffle(q,q+Q);
	for(;;){
		random_shuffle(lst,lst+tQ);
		for(int i=0;i<tQ;i++){
			q[lst[i]].train();
		}
		db err=0;
		int cnt1=0,cnt2=0;
		for(int i=0;i<tQ;i++){
			cnt1+=q[i].test();
			err+=q[i].err();
		}
		for(int i=tQ;i<Q;i++){
			cnt2+=q[i].test();
		}
		cout<<"["<<clock()-lastt<<"us]"<<cnt1<<"/"<<tQ<<"\t"<<cnt2<<"/"<<Q-tQ<<"\terr="<<err<<endl;
		lastt=clock();
		if(cnt1>=0.955*tQ){
			break;
		}
	}
	fin=fopen("test.in","r");
	freopen("test.out","w",stdout);
	int n=10000;
	for(int i=0;i<n;i++){
		testcase tc;
		tc.input(false);
		printf("%d\n",tc.run());
	}
	return 0;
}
