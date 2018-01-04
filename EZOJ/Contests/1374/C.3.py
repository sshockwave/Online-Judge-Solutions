import sys
sys.stdin=open("num3.in","r")
sys.stdout=open("num3.tmp","w")
print (bin(int(raw_input())))[2:]
