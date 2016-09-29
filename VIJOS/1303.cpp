#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int height[30],f[30],sys[30];
char s[200];
int main(){
	int n=0,ans=0,minp;
	cin.getline(s,170);
	memset(height,0,sizeof(height));
	memset(f,0,sizeof(f));
	for(int i=0;s[i];i++){
		if(s[i]==','){
			n++;
		}else{
			height[n]=height[n]*10+s[i]-'0';
		}
	}
	n++;
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			if(height[j]>=height[i]&&f[j]>f[i]){
				f[i]=f[j];
			}
		}
		f[i]++;
		if(f[i]>ans){
			ans=f[i];
		}
	}
	cout<<ans<<",";
	ans=0;
	for(int i=0;i<n;i++){
		minp=-1;
		for(int j=0;j<ans;j++){
			if(sys[j]>=height[i]&&(minp==-1||sys[j]<sys[minp])){
				minp=j;
			}
		}
		if(minp==-1){
			sys[ans++]=height[i];
		}else{
			sys[minp]=height[i];
		}
	}
	cout<<ans-1;
}
