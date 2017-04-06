#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
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
const int N=27,MOD=998244353;
int n,q[N];
inline int isqrt(int x){
	if(x<0){
		return -1;
	}
	int rt=round(sqrt(x));
	if(rt*rt!=x){
		return -1;
	}else{
		return rt;
	}
}
inline bool is_palin(){
	for(int i=1,j=n-1;i<j;i++,j--){
		if(q[i]!=q[j]){
			return false;
		}
	}
	return true;
}
int main(){
	for(int tot=ni();tot--;){
		n=ni();
		int sum=0,rt;
		bool flag=true;
		for(int i=0;i<n;i++){
			q[i]=ni();
			sum+=q[i];
			if(q[i]!=q[0]){
				flag=false;
			}
		}
		rt=isqrt(sum);
		if(rt<0||!is_palin()){
			puts("0");
		}else if(n==1){
			printf("1 %d\n",rt);
		}else if(flag){
			if(rt%n){
				puts("0");
			}else{
				putchar('1');
				rt/=n;
				for(int i=0;i<n;i++){
					printf(" %d",rt);
				}
				putchar('\n');
			}
		}else if(n==2){
			int rt2=isqrt(q[0]-q[1]);
			if(rt2<0){
				puts("0");
			}else if((rt+rt2)&1){
				puts("0");
			}else if(rt2==0){
				printf("1 %d %d\n",rt/2,rt/2);
			}else{
				printf("2 %d %d\n",(rt-rt2)/2,(rt+rt2)/2);
			}
		}else if(n==3){
			int rt2=isqrt(q[0]-q[1]);
			if(rt2<0){
				puts("0");
			}else if(rt2==0){
				if((q[0]+q[1])%6){
					puts("0");
				}else{
					int rt3=isqrt((q[0]+q[1])/6);
					if(rt3<0){
						puts("0");
					}else{
						printf("1 %d %d %d\n",rt3,rt3,rt3);
					}
				}
			}else{
				int rt3=isqrt(q[0]+2*q[1]);
				if(rt3<0){
					puts("0");
				}else if((rt2+rt3)%3){
					if((rt3+2*rt2)%3){
						puts("0");
					}else if(rt3<rt2){
						puts("0");
					}else{
						printf("1 %d %d %d\n",(rt3+2*rt2)/3,(rt3-rt2)/3,(rt3-rt2)/3);
					}
				}else if(rt3<2*rt2){
					puts("0");
				}else{
					printf("1 %d %d %d\n",(rt3-2*rt2)/3,(rt2+rt3)/3,(rt2+rt3)/3);
				}
			}
		}
	}
}
