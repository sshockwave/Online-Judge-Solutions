import sys
import random
sys.stdin=open("num9.in","r")
def gen(l,r):
    return random.randint(l,r)
def ni():
    return int(raw_input())
num=ni()
INF=100000000000000000000000000000000000000000000000
F=18
n=ni()-F
a=[0]*n
for i in range(0,n):
    a[i]=ni()
def dp(num):
    if num<0:
        num=-num
    f=[[0,INF]]
    op=[[0,0]]
    prestate=[[0,0]]
    f[0][0]=0
    for i in range(0,F):
        f+=[[INF,INF]]
        op+=[[0,0]]
        prestate+=[[0,0]]
        pw=10**(i*2)
        cur=num//pw
        if i!=F-1:
            cur%=100
        for j in [0,1]:
            if f[i][j]<INF:
                tmp=f[i][j]+cur+j
                #+
                if tmp<f[i+1][0]:
                    f[i+1][0]=tmp
                    op[i+1][0]=cur+j
                    prestate[i+1][0]=j
                #-
                tmp=f[i][j]+100-cur-j
                if tmp<f[i+1][1]:
                    f[i+1][1]=tmp
                    op[i+1][1]=100-cur-j
                    prestate[i+1][0]=j
    return f[F][0],op,prestate
def genarr(l):
    a=[0]*l
    for i in range(0,l):
        a[i]=random.randint(0,n-1)
    return a
def getans(arr):
    r=1
    global num
    ret=num
    pre=[0]
    for i in arr:
        ret+=a[i]
        pre+=[ret]
    ans=0
    for i in range(1,len(arr)+1):
        if dp(ret-pre[i]*2)<dp(ret-pre[ans]*2):
            ans=i
    return len(arr)+dp(ret-pre[i]*2)[0],ans
while True:
    print getans(genarr(10))[0]
#    sys.stdout=open("num9.out","w")
