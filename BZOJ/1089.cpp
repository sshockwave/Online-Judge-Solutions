#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define T 10010
#define D 18
#define N 35
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
struct bigint{
	int digit[T],dtop;
	void clear(){
		memset(digit,0,sizeof(digit));
		dtop=0;
	}
	void operator = (int r){
		dtop=0;
		do{
			digit[dtop++]=r%10;
			r/=10;
		}while(r);
	}
	inline int & operator [] (int i){
		return digit[i];
	}
	void operator += (int r){
		for(int i=0;i<dtop&&r;i++){
			digit[i]+=r;
			r=digit[i]/10;
			digit[i]%=10;
		}
		while(r){
			digit[dtop++]=r%10;
			r/=10;
		}
	}
	void operator -= (bigint b){
		assert(dtop>=b.dtop);
		for(int i=0;i<b.dtop;i++){
			digit[i]-=b[i];
		}
		int r=0;
		for(int i=0;i<dtop;i++){
			digit[i]+=r;
			r=0;
			while(digit[i]<0){
				r--;
				digit[i]+=10;
			}
		}
		while(dtop&&digit[dtop-1]==0){
			dtop--;
		}
		if(dtop==0){
			dtop=1;
		}
	}
}_f[D];
bigint operator * (bigint a,bigint b){
	bigint ans;
	ans.clear();
	ans.dtop=a.dtop+b.dtop;
	for(int i=0;i<a.dtop;i++){
		for(int j=0;j<b.dtop;j++){
			ans[i+j]+=a[i]*b[j];
		}
	}
	int r=0;
	for(int i=0;i<ans.dtop;i++){
		ans[i]+=r;
		r=ans[i]/10;
		ans[i]%=10;
	}
	while(r){
		ans[ans.dtop++]=r%10;
		r/=10;
	}
	while(ans.dtop&&ans[ans.dtop-1]==0){
		ans.dtop--;
	}
	if(ans.dtop==0){
		ans.dtop=1;
	}
	return ans;
}
bigint operator ^ (bigint x,int n){
	bigint ans;
	if(n==0){
		ans=1;
		return ans;
	}
	ans=x^(n>>1);
	ans=ans*ans;
	if(n&1){
		ans=ans*x;
	}
	return ans;
}
ostream & operator << (ostream & out,bigint b){
	for(int i=b.dtop-1;i>=0;i--){
		putchar(b.digit[i]+'0');
	}
	return out;
}
int main(){
	int n=ni(),d=ni();
	_f[0]=1;
	for(int i=1;i<=d;i++){
		_f[i]=_f[i-1]^n;
		_f[i]+=1;
	}
	if(d){
		_f[d]-=_f[d-1];
	}
	cout<<_f[d]<<endl;
}
