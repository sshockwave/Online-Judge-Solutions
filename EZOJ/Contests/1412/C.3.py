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

def main():
	n=int(raw_input())
	ans=Decimal(0)
	for i in range(1,n+1):
		ans+=Decimal(n)/i
	print '%.10f'%ans
	return ans

sys.stdin=open('random.in','r')
sys.stdout=open('random3.out','w')
getcontext().prec=100
for i in range(0,10):
	main()
