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
	M=1000000
	for i in range(1,M+1):
		ans+=fpow(Decimal(i)/M,n)
	print '%.10f'%ans
	return ans

sys.stdin=open('random.in','r')
#sys.stdout=open('random2.out','w')
getcontext().prec=100
for i in range(0,10):
	main()
