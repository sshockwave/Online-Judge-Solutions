#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
map<int,int>m;
int main(){
	int n,a;
	scanf("%d",&n);
	map<int,int>::iterator it;
	while(n--){
		scanf("%d",&a);
		it=m.find(a);
		if(it==m.end()){
			m[a]=1;
		}else{
			it->second++;
		}
	}
	for(it=m.begin();it!=m.end();it++){
		cout<<it->first<<' '<<it->second<<endl;
	}
}
