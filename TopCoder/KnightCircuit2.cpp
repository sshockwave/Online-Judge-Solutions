#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
class KnightCircuit2{
	public:
	int maxSize(int w,int h){
		if(min(w,h)==1){
			return 1;
		}
		if(min(w,h)==2){
			return (max(w,h)+1)/2;
		}
		if(w==3&&h==3){
			return 8;
		}
		return w*h;
	}
};