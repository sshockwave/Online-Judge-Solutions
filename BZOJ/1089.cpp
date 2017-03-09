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
	void set(int r){
		dtop=0;
		do{
			digit[dtop++]=r%10;
			r/=10;
		}while(r);
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
	bigint operator += (bigint b){
		for(int i=dtop;i<b.dtop;i++){
			digit[i]=0;
		}
		apmax(dtop,b.dtop);
		int r=0;
		for(int i=0;i<dtop;i++){
			digit[i]+=b.digit[i]+r;
			r=digit[i]/10;
			digit[i]%=10;
		}
		while(r){
			digit[dtop++]=r%10;
			r/=10;
		}
	}
}f[D][N],_f[D][N];
ostream & operator << (ostream & out,bigint b){
	for(int i=b.dtop-1;i>=0;i--){
		putchar(b.digit[i]+'0');
	}
	return out;
}
bigint operator * (bigint a,bigint b){
	bigint ans;
	ans.clear();
	for(int i=0;i<a.dtop;i++){
		for(int j=0;j<b.dtop;j++){
			ans.digit[i+j]+=a.digit[i]*b.digit[j];
		}
	}
	ans.dtop=a.dtop+b.dtop;
	int r=0;
	for(int i=0;i<ans.dtop;i++){
		ans.digit[i]+=r;
		r=ans.digit[i]/10;
		ans.digit[i]%=10;
	}
	while(r){
		ans.digit[ans.dtop++]=r%10;
		r/=10;
	}
	while(ans.dtop&&ans.digit[ans.dtop-1]==0){
		ans.dtop--;
	}
	if(ans.dtop==0){
		ans.dtop++;
	}
	return ans;
}
bigint operator * (bigint a,int b){
	bigint ans=a;
	int r=0;
	for(int i=0;i<ans.dtop;i++){
		ans.digit[i]*=b;
		ans.digit[i]+=r;
		r=ans.digit[i]/10;
		ans.digit[i]%=10;
	}
	while(r){
		ans.digit[ans.dtop++]=r%10;
		r/=10;
	}
	return ans;
}
int c[N][N];
int main(){
	int n=ni(),d=ni();
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[0][i]=1;
		for(int j=1;j<=i;j++){
			c[j][i]=c[j-1][i-1]+c[j][i-1];
		}
	}
	for(int i=0;i<=n;i++){
		f[0][i].set(1);
		_f[0][i].set(1);
	}
	f[1][0].set(1);
	_f[1][0].set(1);
	f[1][1].set(1);
	_f[1][1].set(2);
	for(int i=2;i<=n;i++){
		f[1][i].set(1);
		_f[1][i]=_f[1][i-1]*_f[1][1];
	}
	cout<<"f[0]="<<f[0][1]<<endl;
	cout<<"f[1]="<<f[1][1]<<endl;
	for(int i=2;i<=d;i++){
		f[i][0].set(1);
		_f[i][0].set(1);
		f[i][1].set(0);
		for(int j=1;j<=n;j++){
			f[i][1]+=f[i-1][j]*_f[i-2][n-j]*c[j][n];
		}
		cout<<"f["<<i<<"]="<<f[i][1]<<endl;
		_f[i][1]=f[i][1];
		_f[i][1]+=_f[i-1][1];
		for(int j=2;j<=n;j++){
			f[i][j]=f[i][j-1]*f[i][1];
			_f[i][j]=_f[i][j-1]*_f[i][1];
		}
	}
	cout<<f[d][1];
}
