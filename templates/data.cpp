#include <bits/stdc++.h>
#define WITH_MODERN_CPP
typedef long long lint;
using namespace std;
inline auto getseed(){
	random_device dev;
	auto t=dev();
	srand(t);
	ofstream fout("seed");
	fout<<t<<endl;
	return t;
}
default_random_engine eng(getseed());
template<class T>constexpr T gen(T l,T r){
	return uniform_int_distribution<T>(l,r)(eng);
}
int main(){
}
