import sys
sys.stdin=open("num7.in","r")
sys.stdout=open("num7.out","w")
def ni():
    return int(raw_input())
def ilen(num):
    l=len(str(num))
    if num<0:l=l-1
    return l
num=ni()
n=ni()
a=[0]*n
for i in range(n):
    a[i]=ni()
best=0
bestop=0
def dfs(x,a,num,op,cnt,rest):
    if x==9:
        global best
        global bestop
        if abs(num)<abs(best):
            best=num
            bestop=op[:]
        return
    for i in range(-rest,rest+1):
        op[x]=i
        dfs(x+1,a,num+a[x]*i,op[:],cnt+abs(i),rest-abs(i))
low=36
for i in range(n-9,low-1,-9):
    if ilen(a[i])>ilen(num):continue
#1
    best=num
    bestop=[0]*9
    dfs(0,a[i:i+9],num,[0]*9,0,1)
    realbest=best
    realop=bestop
#2
    best=num
    bestop=[0]*9
    dfs(0,a[i:i+9],num,[0]*9,0,2)
    if ilen(best)+1<ilen(realbest):
        realbest=best
        realop=bestop
    for j in range(0,9):
        num+=a[i+j]*realop[j]
        for k in range(0,abs(realop[j])):
            if realop[j]<0:
                print i+j+1
            else:
                print '-'+str(i+j+1)
ansop=0
ansabs=100000000000000000000
def dfs2(x,num,op,rest):
    global a
    if x==low:
        global ansabs
        if abs(num)<ansabs:
            ansabs=abs(num);
            sys.stderr.write('cur num='+str(num)+'\n')
        global ansop
        if num==0:
            ansop=op
            return True
        else:
            return False
    for i in range(-rest,rest+1):
        op[x]=i
        if dfs2(x+1,num+a[x]*i,op[:],rest-abs(i)):
            return True
    return False
sys.stderr.write('cur num='+str(num)+'\n')
for i in range(1,15):
    sys.stderr.write('i='+str(i)+'\n')
    if dfs2(0,num,[0]*low,i):
        for j in range(0,low):
            num+=a[j]*ansop[j]
            for k in range(0,abs(ansop[j])):
                if ansop[j]<0:
                    print j+1
                else:
                    print '-'+str(j+1)
        break
