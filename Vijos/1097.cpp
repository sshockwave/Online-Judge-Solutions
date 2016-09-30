#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10000
using namespace std;
int heap[N],htop=1;
inline void insert(int x){
	heap[htop]=x;
	for(int i=htop++;heap[i>>1]>heap[i];i>>=1){//i>0 => i>1
		swap(heap[i>>1],heap[i]);
	}
}
inline int pop(){
	swap(heap[--htop],heap[1]);
	for(int i=0,p=1;p!=i;){//p!=i;i=p    =>   while(p!=i)  i=p
		i=p;
		if((i<<1)<htop&&heap[i<<1]<heap[p]){
			p=i<<1;
		}
		if(((i<<1)|1)<htop&&heap[(i<<1)|1]<heap[p]){
			p=(i<<1)|1;//(i<<1)&1  =>  (i<<1)|1
		}
		if(p!=i){
			swap(heap[i],heap[p]);
		}
	}
	return heap[htop];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,a,cnt=0,tmp;
	heap[0]=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
		insert(a);
	}
	for(int i=1;i<n;i++){
		tmp=pop()+pop();
		cnt+=tmp;
		insert(tmp);
	}
	cout<<cnt;
}
