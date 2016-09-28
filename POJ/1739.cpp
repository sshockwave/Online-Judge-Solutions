#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define setplug(d,s) plug[0]=s,plug[y]=d,hq[!r].enqueue(plug,f[r][hq[r].code]);
using namespace std;
int m,n,f[2][262144];
bool r,last=false;
/* 
void printp(int plug[]){
	for(int i=0;i<=n;i++){
		cout<<plug[i];
	}
}
*/ 
struct hashqueue{
	int code;
	queue<int>q;
	bool p;
	void enqueue(int plug[],int amount){
		code=0;
		/*
		cout<<"\tEnqueue ";
		printp(plug);
		*/ 
		for(int i=0;i<=n;i++){
			code=(code<<2)|plug[i];
		}
		/* 
		cout<<"="<<code<<"\t"<<amount<<endl; 
		if(f[p][code]){
			cout<<"\tCode hashed."<<endl;
		}
		*/ 
		if(!f[p][code]){
			q.push(code);
		}
		f[p][code]+=amount;
	}
	void dequeue(int plug[]){
		code=q.front();
		q.pop();
		for(int i=n;i>=0;i--){
			plug[i]=(code>>(n-i<<1))&3;
		}
		/* 
		cout<<"\tDecode ";
		printp(plug);
		cout<<endl;
		*/ 
	}
	void clear(){
		while(!q.empty()){
			q.pop();
		}
	}
}hq[2];
inline void transfer(int y){
	int plug[n+1],amount;
	while(!hq[r].q.empty()){
		hq[r].dequeue(plug);
		switch(plug[0]){
			case 0:{
				switch(plug[y]){
					case 0:{
						setplug(1,2);
						break;
					}
					case 1:{
						setplug(1,0);
						setplug(0,1);
						break;
					}
					case 2:{
						setplug(2,0);
						setplug(0,2);
						break;
					}
				}
				break;
			}
			case 1:{
				switch(plug[y]){
					case 0:{
						setplug(0,1);
						setplug(1,0);
						break;
					}
					case 1:{
						int match=y,cnt=1;
						while(cnt){
							match++;
							if(plug[match]==1){
								cnt++;
							}else if(plug[match]==2){
								cnt--;
							}
						}
						plug[match]=1;
						setplug(0,0);
						break;
					}
					case 2:{
						if(last){
							setplug(0,0);
						}
						break;
					}
				}
				break;
			}
			case 2:{
				switch(plug[y]){
					case 0:{
						setplug(2,0);
						setplug(0,2);
						break;
					}
					case 1:{
						setplug(0,0);
						break;
					}
					case 2:{
						int match=y,cnt=1;
						while(cnt){
							match--;
							if(plug[match]==1){
								cnt--;
							}else if(plug[match]==2){
								cnt++;
							}
						}
						plug[match]=2;
						setplug(0,0);
						break;
					}
				}
				break;
			}
		}
	}
}
inline void block(int y){
	int plug[n+1],amount;
	while(!hq[r].q.empty()){
		hq[r].dequeue(plug);
		if(plug[0]==0&&plug[y]==0){
			hq[!r].enqueue(plug,f[r][hq[r].code]);
		}
	}
}
inline void newline(){
	//cout<<"New line!"<<endl;
	memset(f[!r],0,sizeof(f[!r]));
	int plug[n+1],amount;
	while(!hq[r].q.empty()){
		hq[r].dequeue(plug);
		if(plug[0]==0){
			hq[!r].enqueue(plug,f[r][hq[r].code]);
		}
	}
	r=!r;
}
inline int solve(char op,int j){
	memset(f[!r],0,sizeof(f[!r]));
	if(op=='.'){
		transfer(j);
	}else{
		block(j);
	}
	r=!r;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	char op;
	hq[0].p=0;
	hq[1].p=1;
	for(cin>>m>>n;m&&n;cin>>m>>n){
		//reset
		hq[0].clear(),hq[1].clear();
		last=false;
		memset(f,0,sizeof(f));
		//new round
		int plug[n+1];
		memset(plug,0,sizeof(plug));
		hq[r].enqueue(plug,1);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				cin>>op;
				//cout<<"Process("<<i<<","<<j<<")"<<endl;
				solve(op,j);
			}
			newline();
		}
		//cout<<"Starting last two lines."<<endl;
		solve('.',1);
		for(int j=2;j<n;j++){
			solve('#',j);
		}
		solve('.',n);
		newline();
		for(int j=1;j<n;j++){
			solve('.',j);
		}
		last=true;
		solve('.',n);
		cout<<f[r][0]<<endl;
	}
}
