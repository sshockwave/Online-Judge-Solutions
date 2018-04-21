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
	cur=Decimal(0)
	pre=Decimal(0)
	for i in range(1,n+1):
		pre+=cur
		cur=i+pre*2/i
	return cur

sys.stdin=open('random.in','r')
sys.stdout=open('random6.out','w')
getcontext().prec=100
for i in range(0,10):
	print '%.10f'%main()
