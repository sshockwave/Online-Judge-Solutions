#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int n,cur,last=-1,ans=1;
	bool down;
	scanf("%d%d",&n,&last);
	for(int i=1;i<n;i++){
		scanf("%d",&cur);
		if(i==1){
			if(cur<last){
				down=false;
			}else{
				down=true;
			}
		}
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
