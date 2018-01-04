#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <random>
#include <vector>
#include <fstream>
using namespace std;
typedef __int128 lint;
typedef unsigned int uint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T abs(T x){return x>=0?x:-x;}
const int N=200,F=8;
lint fix[F];
lint f[F+1][2];
inline lint fixup(lint x){
    if(x<0){
        x=-x;
    }
    memset(f,127,sizeof(f));
    lint (*f)[2]=::f+1;
    f[-1][0]=0;
    for(int i=0;i<F;i++,x/=100){
        for(int j=0;j<2;j++){
            //+
            apmin(f[i][0],f[i-1][j]+(i==F-1?x+j:x%100+j));
            //-
            apmin(f[i][1],f[i-1][j]+(100-x%100-j));
        }
    }
    return f[F-1][0];
}
lint a[N];
int n;
inline void putnum(ofstream &fout,int x,lint cnt){
    lint ti=cnt>0?cnt:-cnt;
    for(int i=0;i<ti;i++){
        if(cnt<0){
            fout<<'-'<<x<<endl;
        }else{
            fout<<x<<endl;
        }
    }
}
int op[F+1][2];
int prestate[F+1][2];
inline void realfixup(ofstream &fout,lint x){
    int flag=1;
    if(x<0){
        x=-x;
        flag=-1;
    }
    memset(f,127,sizeof(f));
    lint (*f)[2]=::f+1;
    f[-1][0]=0;
    for(int i=0;i<F;i++,x/=100){
        for(int j=0;j<2;j++){
            lint newval;
            //+
            newval=f[i-1][j]+(i==F-1?x+j:x%100+j);
            if(newval<f[i][0]){
                f[i][0]=newval;
                op[i][0]=i==F-1?x+j:x%100+j;
                prestate[i][0]=j;
            }
            //-
            newval=f[i-1][j]+(100-x%100-j);
            if(newval<f[i][1]){
                f[i][1]=newval;
                op[i][1]=-(100-x%100-j);
                prestate[i][1]=j;
            }
        }
    }
    int curstate=0;
    for(int i=F-1;i>=0;i--){
        x+=fix[i]*op[i][curstate];
        putnum(fout,i+n+1,op[i][curstate]*flag);
        curstate=prestate[i][curstate];
    }
}
inline lint eval(int x){
    if(x>0)return a[x];
    return -a[-x];
}
inline int gen(int l,int r){
    static random_device rand;
    return rand()%(r-l+1)+l;
}
inline int gnum(){
    static random_device rand;
    if(gen(0,1)){
        return rand()%n+1;
    }else{
        return -(rand()%n+1);
    }
}
inline pair<lint,vector<int>>anneal(lint num){
    const int chs=15;
    vector<int>vec;
    for(int i=0;i<chs;i++){
        int x=gnum();
        vec.push_back(x);
        num+=eval(x);
    }
    uint tmpe=-1;
    lint curans=chs+fixup(num);
    lint ans2=chs+abs(num);
    double cold=gen(60,99)/100.0;
    for(;tmpe>0;tmpe*=cold){
        if(gen(0,1)){
            int x=gnum();
            lint newval=vec.size()+1+fixup(num+eval(x));
            lint val2=vec.size()+1+abs(num+eval(x));
            if(newval<curans||rand()<tmpe){
            //if(val2<ans2||rand()<tmpe){
            //if(fixup(num+eval(x))<fixup(num)||rand()<tmpe){
                curans=newval;
                ans2=val2;
                vec.push_back(x);
                num+=eval(x);
            }
        }else if(!vec.empty()){
            int x=gen(0,vec.size()-1);
            lint newval=vec.size()-1+fixup(num-eval(vec[x]));
            lint val2=vec.size()-1+abs(num+eval(x));
            if(newval<curans||rand()<tmpe){
            //if(val2<ans2||rand()<tmpe){
            //if(fixup(num-eval(x))<fixup(num)||rand()<tmpe){
                curans=newval;
                ans2=val2;
                num-=eval(vec[x]);
                vec.erase(vec.begin()+x);
            }
        }
    }
    return make_pair(vec.size()+fixup(num),vec);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("num8.in","r",stdin);
#endif
    lint num=next_num<lint>();
    n=ni-F;
	for(int i=1;i<=n;i++){
		a[i]=next_num<lint>();
	}
    for(int i=0;i<F;i++){
        fix[i]=next_num<lint>();
    }
    auto ans=make_pair(1000000,vector<int>());
    while(true){
        auto p=anneal(num);
        if(p.first<ans.first){
            ans=p;
            cout<<"new ans:"<<ans.first<<endl;
            ofstream fout("num8.out");
            fout<<ans.first<<endl;
            lint sum=num;
            for(vector<int>::iterator it=ans.second.begin();it!=ans.second.end();it++){
                fout<<-(*it)<<endl;
                sum+=eval(*it);
            }
            realfixup(fout,sum);
        }
    }
	return 0;
}
