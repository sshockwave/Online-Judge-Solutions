from decimal import *
import sys
def fpow(x,n):
	return Decimal(x)**n
	ans=Decimal(1)
	while n!=0:
		if n&1:
			ans*=x
		n>>=1
		x*=x
	return ans

p=1-Decimal(1)/100000

def C(n,k):
	ans=1
	for i in range(0,k):
		ans=ans*(n-i)/(i+1)
	return ans

def calc1(n,t):
	ans=0
	wn=fpow(p,t)*(p-1)
	w=Decimal(1)
	for i in range(0,min(n/t+1,50)):
		ans+=C(n-t*i,i)*w
		w*=wn
	return ans

def calc2(n,t):
	return calc1(n,t)-fpow(p,t)*calc1(n-t,t)

def main():
	n=int(raw_input())
	if n<1000000:
		return 0
	ans=n
	cnt=0
	for i in range(1,n+1):
		ans-=calc2(n,i)
		cnt+=1
		if cnt==1000:
			print 'i=%d'%i
			cnt=0
	return ans

sys.stdin=open('random.in','r')
#sys.stdout=open('random10.out','w')
getcontext().prec=50
for i in range(0,10):
	print '%.10f'%main()
