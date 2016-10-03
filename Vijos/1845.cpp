#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int n,cur,last=-1,ans=0;
	bool down=true;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&cur);
		if(down&&cur>last){
			down=false;
			ans++;
		}else if(!down&&cur<last){
			down=true;
			ans++;
		}
		last=cur;
	}
	cout<<ans;
}
