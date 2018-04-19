#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
using namespace std;
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
int mn;
bool testA(int t,int prod);
bool testB(int t,int sum);
bool testA(int t,int prod){//is it possible for Alice to say "no" on the t'th time?
	set<int>s;
	for(int a=mn;a<=prod/a;a++){
		if(prod%a==0){
			s.insert(a);
		}
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testB(i-1,*it+prod/(*it))){
					s.erase(it);
				}
			}
		}
	}
	return s.size()>1;
}
bool testB(int t,int sum){//is it possible for Bob to say "no" on the t'th time?
	set<int>s;
	for(int a=mn;a<=sum-a;a++){
		s.insert(a);
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testA(i-1,*it*(sum-*it))){
					s.erase(it);
				}
			}
		}
	}
	return s.size()>1;
}
inline bool testA1(int t,int prod){
	set<int>s;
	for(int a=mn;a<=prod/a;a++){
		if(prod%a==0){
			s.insert(a);
		}
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testB(i-1,*it+prod/(*it))){
					s.erase(it);
				}
			}
		}
	}
	return s.size()==1;
}
bool testB1(int t,int sum){
	set<int>s;
	for(int a=mn;a<=sum-a;a++){
		s.insert(a);
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testA(i-1,*it*(sum-*it))){
					s.erase(it);
				}
			}
		}
	}
	return s.size()==1;
}
inline bool testA2(int t,int prod){
	set<int>s;
	for(int a=mn;a<=prod/a;a++){
		if(prod%a==0){
			s.insert(a);
		}
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testB(i-1,*it+prod/(*it))){
					s.erase(it);
				}
			}
		}
	}
	if(s.size()<=1)return false;
	for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
		nxt=it,++nxt;
		if(!testB1(t+1,*it+prod/(*it))){
			s.erase(it);
		}
	}
	if(s.size()==1){
		cout<<"now a="<<*s.begin()<<"\tb="<<prod/(*s.begin())<<endl;
		printf("%d %d\n",*s.begin(),prod/(*s.begin()));
	}
	return s.size()==1;
}
inline bool testB2(int t,int sum){
	set<int>s;
	for(int a=mn;a<=sum-a;a++){
		s.insert(a);
	}
	for(int i=2-(t&1);i<=t;i+=2){
		if(s.size()<=1)return false;
		if(i!=1){
			for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
				nxt=it,++nxt;
				if(!testA(i-1,*it*(sum-*it))){
					s.erase(it);
				}
			}
		}
	}
	if(s.size()<=1)return false;
	for(set<int>::iterator it=s.begin(),nxt;it!=s.end();it=nxt){
		nxt=it,++nxt;
		if(!testA1(t+1,*it*(sum-*it))){
			s.erase(it);
		}
	}
	if(s.size()==1){
		cout<<"now a="<<*s.begin()<<"\tb="<<sum-*s.begin()<<endl;
		printf("%d %d\n",*s.begin(),sum-*s.begin());
	}
	return s.size()==1;
}
int main(){
	mn=ni;
	char str[10];
	scanf("%s",str);
	int t=ni;
	if((t&1)==0){
		str[0]^='A'^'B';
	}
	if(str[0]=='A'){
		for(int i=mn*mn;i<=100000;i++){
			if(testA2(t,i)){
				break;
			}
		}
	}else{
		for(int i=mn*2;;i++){
			if(testB2(t,i)){
				break;
			}
		}
	}
	return 0;
}
