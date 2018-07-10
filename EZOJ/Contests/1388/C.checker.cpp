#include<bits/stdc++.h>
#define FINISH {printf("Finish with gold %d,hp %d",gold,hp);exit(32);}
#define ERROR {printf("Error %d",i+1);exit(32);}
#define DIED {printf("Died %d",i+1);exit(32);}
#define POI {if(poi)hp-=5;if(hp<=0)DIED}
using namespace std;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1},dir,id=1,x=7,y=5,i,j,n,atk=10,def=10,hp=500,wp1,wp2,sh1,sh2,mdf,gold;
int breaks,bombs,h_wp1,h_wp2,h_sh1,h_sh2,dpoi,poi,key1,key2,key3;
int eatk[12],edef[12],ehp[12],eget[12],ecanbomb[12],espe[12],cg=1;
char mp[11][11][11];
int spj1,spj2;
void special_judge(int id,int x,int y)
{
	if(id!=5)return;
	if(y==4&&(x==4||x==6))spj1++;
	if(y==6&&(x==4||x==6))spj2++;
	if(spj1==2)mp[id][5][3]='.';
	if(spj2==2)mp[id][5][7]='.';
	if(x==5&&y==1)mp[id][9][5]='.';
}
string s;
void deal_event(int id,int x,int y)
{
	if(x<0||y<0||x>10||y>10)ERROR
	char c=mp[id][x][y];
	if(c=='#'||c=='.')ERROR
	else if(c=='A'){if(!key1)ERROR key1--;}
	else if(c=='B'){if(!key2)ERROR key2--;}
	else if(c=='C'){if(!key3)ERROR key3--;}
	else if(c=='D')key1++;
	else if(c=='E')key2++;
	else if(c=='F')key3++;
	else if(c=='G')atk+=3;
	else if(c=='H')def+=3;
	else if(c=='I')mdf+=5;
	else if(c=='J')breaks++;
	else if(c=='K')bombs++;
	else if(c=='L')h_wp1=1;
	else if(c=='M')h_sh1=1;
	else if(c=='N')h_wp2=1;
	else if(c=='O')h_sh2=1;
	else if(c=='P')hp+=100;
	else if(c=='Q')hp+=200;
	else if(c=='R')hp+=500;
	else if(c=='S')hp+=1000;
	else if(c=='T'){POI ::id++,::x=x,::y=y;return;}
	else if(c=='U'){POI ::id--,::x=x,::y=y;return;}
	else if(c=='V'){POI ::id=10,::x=x,::y=y;return;}
	else if(c=='W')dpoi++;
	else if(c=='X')cg++;
	else if(c=='Y'||c=='Z')ERROR
	else if(c=='*'){if(gold<8)ERROR gold-=8;}
	else
	{
		int e=mp[id][x][y]-'a';
		int ed=edef[e];
		if(espe[e]==8)ed=max(ed,atk-1);
		int ea=eatk[e];
		int mdam=max(atk-ed,0);
		int edam=max(ea-def+def*(espe[e]==64),0);
		if(!mdam)DIED
		int times=ehp[e]/mdam-(ehp[e]%mdam==0);
		if(espe[e]==16)times++;
		if(espe[e]==128)times*=2;
		int damage=max(times*edam+2*def*(espe[e]==512)-mdf,0);
		if(damage>=hp)DIED
		hp-=damage;
		if(e==11)FINISH
		if(espe[e]==1)poi=1;
		gold+=eget[e]*cg;
		special_judge(id,x,y);
	}
	mp[id][x][y]='.';
}
void rev_we1()
{
	if(!h_wp1)ERROR
	if(wp2)wp2=0,atk-=50;
	if(wp1)wp1=0,atk-=10;else wp1=1,atk+=10;
}
void rev_we2()
{
	if(!h_wp2)ERROR
	if(wp1)wp1=0,atk-=10;
	if(wp2)wp2=0,atk-=50;else wp2=1,atk+=50;
}
void rev_sh1()
{
	if(!h_sh1)ERROR
	if(sh2)sh2=0,def-=50;
	if(sh1)sh1=0,def-=10;else sh1=1,def+=10;
}
void rev_sh2()
{
	if(!h_sh2)ERROR
	if(sh1)sh1=0,def-=10;
	if(sh2)sh2=0,def-=50;else sh2=1,def+=50;
}
int main()
{
	freopen("cff.txt","r",stdin);
	for(i=1;i<=10;i++)for(j=0;j<11;j++)scanf("%s",mp[i][j]);
	mp[id][x][y]='.';
	for(i=0;i<12;i++)cin>>eatk[i]>>edef[i]>>ehp[i]>>espe[i]>>eget[i]>>ecanbomb[i]; 
	freopen("cff.out","r",stdin);
	cin>>s;
	n=s.size();
	for(i=0;i<n;i++)
	{
		if(s[i]=='W')dir=0;
		else if(s[i]=='S')dir=1;
		else if(s[i]=='A')dir=2;
		else if(s[i]=='D')dir=3;
		else if(s[i]=='Q')deal_event(id,x+dx[dir],y+dy[dir]);
		else if(s[i]=='E')
		{
			x+=dx[dir];
			y+=dy[dir];
			if(x<0||x>10||y<0||y>10||mp[id][x][y]!='.')ERROR
			POI
		}
		else if(s[i]=='Z')rev_we1();
		else if(s[i]=='X')rev_we2();
		else if(s[i]=='N')rev_sh1();
		else if(s[i]=='M')rev_sh2();
		else if(s[i]=='V')
		{
			if(x+dx[dir]<0||y+dy[dir]<0||x+dx[dir]>10||y+dy[dir]>10||mp[id][x+dx[dir]][y+dy[dir]]!='#')ERROR
			if(!breaks)ERROR
			mp[id][x+dx[dir]][y+dy[dir]]='.';
			breaks--;
		}
		else if(s[i]=='C')
		{
			if(x+dx[dir]<0||y+dy[dir]<0||x+dx[dir]>10||y+dy[dir]>10)ERROR
			if(mp[id][x+dx[dir]][y+dy[dir]]<'a'||mp[id][x+dx[dir]][y+dy[dir]]>'l')ERROR
			if(!bombs)ERROR
			if(!ecanbomb[mp[id][x+dx[dir]][y+dy[dir]]-'a'])ERROR
			mp[id][x+dx[dir]][y+dy[dir]]='.';
			bombs--;
		}
		else if(s[i]=='B')
		{
			if(!dpoi)ERROR
			dpoi--;
			poi=0;
		}
		else ERROR
	}
	cout<<"now at level "<<id<<":"<<endl;
	cout<<endl;
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++){
			if(i==x&&j==y){
				putchar('X');
			}else if(mp[id][i][j]=='#'){
				putchar(' ');
			}else{
				putchar(mp[id][i][j]);
			}
		}
		putchar('\n');
	}
	cout<<endl;
	cout<<"HP="<<hp<<"\tdef="<<def<<"\tatk="<<atk<<"\tmdf="<<mdf<<"\tbombs="<<bombs<<endl;
	cout<<"keyA="<<key1<<"\tkeyB="<<key2<<"\tkeyC="<<key3<<endl;
	int ret=0;
	for(int i=0;i<4;i++){
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx<0||tx>10||ty<0||ty>10||mp[id][tx][ty]!='.'){
			ret|=1<<i;
		}
	}
	return ret;
}//***This Problem Is Too Simple!...Naive.***
