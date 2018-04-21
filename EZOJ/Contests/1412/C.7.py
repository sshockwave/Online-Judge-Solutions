from decimal import *
import sys
def fpow(x,n):
	ans=Decimal(1)
	while n!=0:
		if n&1:
			ans*=x
		n>>=1
		x*=x
	return ans
cnt=[]
M=100003
for i in range(0,M):
	cnt.append(0)

def dfs(x,h):
	if(x>5):
		cnt[h%M]=cnt[h%M]+1
		return
	for i in range(0,26):
		dfs(x+1,(h*31+i)%1000000007)

dfs(1,0)
N=0
sigc=0
for i in range(0,M):
	N+=cnt[i]
	sigc+=cnt[i]*(cnt[i]-1)
N2=N*N
q=(Decimal(N)-1)/N

def main():
	n=int(raw_input())
	return (n-1-(q-fpow(q,n))*N)/N*sigc+n;
	return n

sys.stdin=open('random.in','r')
sys.stdout=open('random7.out','w')
getcontext().prec=200
for i in range(0,10):
	print '%.10f'%main()
