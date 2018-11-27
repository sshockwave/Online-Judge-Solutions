#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
#define cout cerr
class op{
	private:
		struct Node;
		typedef Node* node;
		struct Node{
			node lson,rson;
			int size;
			char c;
			inline void up(){
				size=lson->size+(c!=0)+rson->size;
			}
		};
		static node null;
		node x;
	public:
		op():x(null){}
		op(node p):x(p){}
		op(op l,char c,op r){
			x=new Node;
			x->lson=l.x,x->c=c,x->rson=r.x,x->up();
		}
		op(op l,char c){
			*this=op(l,c,null);
		}
		op(char c,op r){
			*this=op(null,c,r);
		}
		op(const char s[]){
			for(x=null;s[0];s++){
				*this=op(*this,s[0]);
			}
		}
		inline int len(){
			return x->size;
		}
		inline friend op operator + (op l,op r){
			return op(l,0,r);
		}
		inline friend ostream & operator << (ostream & out,op b){
			stack<node>stk;
			for(node x=b.x;x!=null;x=x->lson){
				stk.push(x);
			}
			for(;!stk.empty();){
				node x=stk.top();
				stk.pop();
				if(x->c){
					out<<x->c;
				}
				for(x=x->rson;x!=null;x=x->lson){
					stk.push(x);
				}
			}
			return out;
		}
		inline static node getnull(){
			null=new Node;
			null->lson=null->rson=null;
			null->size=0,null->c=0;
			return null;
		}
};
op::node op::null=op::getnull();
int mem;
inline void reset(){
	mem=0;
}
class expr{
	public:
		op inst;
		explicit expr(op t):inst(t){}
		expr(lint n){
			if(n>=0){
				for(;n>9;n/=9){
					inst=op(op(op("9*"),'0'+n%9),'+',inst);
				}
				inst=op('0'+n,inst);
			}else{
				inst="0"+expr(-n).inst+"-";
			}
		}
		inline friend expr operator + (expr a,expr b){
			return expr(a.inst+b.inst+"+");
		}
		inline friend expr operator - (expr a,expr b){
			return expr(a.inst+b.inst+"-");
		}
		inline friend expr operator * (expr a,expr b){
			return expr(a.inst+b.inst+"*");
		}
		inline friend expr operator / (expr a,expr b){
			return expr(a.inst+b.inst+"/");
		}
		inline friend expr operator % (expr a,expr b){
			static op tmp1("1^"),tmp2(tmp1+tmp1),tmp3(tmp2+"/*-");
			return expr(a.inst+b.inst+tmp3);
		}
		inline friend expr operator >= (expr a,expr b){
			return expr(expr(expr(op(a.inst+b.inst,':'))+1).inst+"0:");
		}
		inline friend expr operator <= (expr a,expr b){
			return b>=a;
		}
		inline friend expr operator < (expr a,expr b){
			return 1-(a>=b);
		}
		inline friend expr operator > (expr a,expr b){
			return b<a;
		}
		inline friend expr operator != (expr a,expr b){
			return expr(op(a.inst+b.inst,':',op("0^*")));
		}
		inline friend expr operator == (expr a,expr b){
			return 1-(a!=b);
		}
}ni(op("r"));
class cmd{
	private:
		op inst;
	public:
		explicit cmd(op t=op()):inst(t){}
		inline int len(){
			return inst.len();
		}
		inline friend cmd operator + (cmd a,cmd b){
			return cmd(a.inst+b.inst);
		}
		inline friend expr operator + (cmd a,expr b){
			return expr(a.inst+b.inst);
		}
		inline cmd & operator += (cmd b){
			inst=inst+b.inst;
			return *this;
		}
		inline friend ostream & operator << (ostream & out,cmd b){
			return out<<b.inst;
		}
		inline friend cmd ifs(expr cond,cmd cont){
			return cmd(op(cond.inst+expr(cont.len()).inst,'?',cont.inst));
		}
		inline friend cmd ife(expr cond,cmd a,cmd b){
			a+=cmd(op(expr(b.len()).inst,'g'));
			return cmd(op(cond.inst+expr(a.len()).inst,'?',a.inst+b.inst));
		}
		inline friend cmd loop(expr cond,cmd cont){
			op body(cond.inst+expr(cont.len()+3).inst,'?',cont.inst+"0^g");
			return cmd(expr(-body.len()).inst+body+"d");
		}
		inline friend cmd forr(cmd ini,expr cond,cmd step,cmd cont){
			return ini+loop(cond,cont+step);
		}
		inline friend cmd dowh(cmd cont,expr cond){
			return cont+loop(cond,cont);
		}
};
class var;
class arr{
	private:
		expr addr;
	public:
		arr(int len):addr(mem){
			mem+=len;
		}
		inline var operator [] (expr i);
};
class var:public expr{
	private:
		expr addr;
		inline void operator = (var){
			assert(false);
		}
		explicit var(expr ad):expr(op(ad.inst,'<')),addr(ad){}
	public:
		inline friend var arr::operator [] (expr i);
		var():expr(op()),addr(mem++){
			inst=op(addr.inst,'<');
		}
		inline cmd set(expr b){
			return cmd(op(b.inst+addr.inst,'>'));
		}
		inline cmd operator += (expr b){
			return set(*this+b);
		}
		inline cmd operator -= (expr b){
			return set(*this-b);
		}
		inline friend cmd rep(var i,expr l,expr r,cmd cont){
			return forr(i.set(l),i<=r,i+=1,cont);
		}
		inline expr operator -- (){
			return (*this-=1)+*this;
		}
		inline expr operator ++ (int){
			return (*this+=1)+(*this-1);
		}
};
inline var arr::operator [] (expr i){
	return var(addr+i);
}
inline cmd print(expr e){
	return cmd(op(e.inst,'p'));
}
inline cmd printchar(expr e){
	return cmd(op(e.inst,'P'));
}
namespace task1{//a+b
	inline cmd main(){
		return print(ni+ni);
	}
}
namespace task2{//a%b
	inline cmd main(){
		return print(ni%ni);
	}
}
namespace task3{//a^b%c
	inline cmd main(){
		var a,x,n,p;
		cmd ans;
		ans+=a.set(1);
		ans+=x.set(ni);
		ans+=n.set(ni);
		ans+=p.set(ni);
		ans+=loop(n,ifs(n%2,a.set(a*x%p))+(n.set(n/2))+(x.set(x*x%p)));
		ans+=print(a);
		return ans;
	}
}
namespace task4{//median
	inline cmd xswap(var a,var b){
		var t;
		return ifs(a>=b,t.set(a)+a.set(b)+b.set(t));
	}
	inline cmd main(){
		var n,i,j,t;
		arr a(101);
		cmd ans;
		ans+=n.set(ni);
		ans+=rep(i,1,n,a[i].set(ni));
		ans+=rep(i,1,n,rep(j,1,n-1,xswap(a[j],a[j+1])));
		ans+=print(a[(n+1)/2]);
		return ans;
	}
}
namespace task5{//shortest path
	inline cmd apmin(var a,expr b){
		return ifs(b<a,a.set(b));
	}
	inline cmd main(){
		const int N=41;
		const lint LINF=0x7f7f7f7f7f7f7fll;
		var n,m,u,v,w,pt,d,i,j,ret;
		arr nvis(N),e(N*N),dis(N);
		cmd ans;
		ans+=n.set(ni)+m.set(ni);
		ans+=rep(i,0,n,dis[i].set(LINF)+nvis[i].set(1));
		ans+=rep(i,0,N*N-1,e[i].set(LINF));
		ans+=rep(i,1,m,
				u.set(ni)+v.set(ni)+w.set(ni)+
				e[u*N+v].set(w)+
				e[v*N+u].set(w));
		ans+=dis[1].set(0);
		ans+=rep(i,1,n,
				pt.set(0)+
				rep(j,1,n,ifs((nvis[j]*(dis[j]<dis[pt])),pt.set(j)))+
				nvis[pt].set(0)+
				d.set(dis[pt])+
				pt.set(pt*N)+
				rep(j,1,n,apmin(dis[j],d+e[pt+j])));
		ans+=ret.set(0)+rep(i,1,n,ret+=dis[i]);
		ans+=print(ret);
		return ans;
	}
}
namespace task6{//tarjan
	const int N=110,E=3010;
	inline cmd apmin(var a,expr b){
		return ifs(b<a,a.set(b));
	}
	inline cmd main(){
		var n,m,u,v,i,x;
		arr to(E),bro(E),head(N);
		arr dfn(N),low(N);
		arr stk(N),instk(N);
		arr ndstk(N);
		var tim,ss,ns,bakw;
		var anscnt;
		cmd ans;
		ans+=n.set(ni)+m.set(ni);
		ans+=rep(i,1,m,u.set(ni)+to[i].set(ni)+bro[i].set(head[u])+head[u].set(i));
		ans+=rep(i,1,n,
				ifs(dfn[i]==0,
					bakw.set(0)+(ns+=1)+ndstk[ns].set(i)+
					loop(ns,
						x.set(ndstk[ns])+
						ife(bakw,apmin(low[x],low[ndstk[ns+1]]),
							bakw.set(1)+
							(tim+=1)+dfn[x].set(tim)+low[x].set(tim)+
							stk[ss].set(x)+instk[x].set(1)+(ss+=1))+
						loop(bakw*head[x],
							v.set(to[head[x]])+
							head[x].set(bro[head[x]])+
							ife(dfn[v]==0,
								bakw.set(0)+(ns+=1)+ndstk[ns].set(v),
								ifs(instk[v],apmin(low[x],dfn[v]))))+
						ifs(bakw,
							(ns-=1)+
							ifs(dfn[x]==low[x],
								(anscnt+=1)+
								dowh(
									(ss-=1)+
									v.set(stk[ss])+
									instk[v].set(0),
									v!=x))))));
		ans+=print(anscnt);
		return ans;
	}
}
namespace task7{//quine
	const int N=1000;
	inline cmd parsenum(var n){
		arr stk(30);
		var ss;
		cmd ans;
		ans+=forr(ss.set(0),n>9,n.set(n/9),stk[ss].set(n%9)+(ss+=1));
		ans+=printchar('0'+n);
		ans+=loop(ss>0,
				(ss-=1)+
				printchar('9')+
				printchar('*')+
				printchar('0'+stk[ss])+
				printchar('+'));
		return ans;
	}
	inline cmd main(){
		arr str(N);
		var i,num;
		cmd parser=parsenum(num);
		cmd printer;
		printer+=forr(i.set(0),str[i],i+=1,
				num.set(str[i])+parser+
				num.set(i)+parser+
				printchar(expr('>')));
		printer+=forr(i.set(0),str[i],i+=1,printchar(str[i]));
		stringstream src;
		src<<printer;
		string s=src.str();
		cmd setter;
		for(int i=0;i<(int)s.length();i++){
			setter+=cmd(op(expr(s[i]).inst+expr(i).inst,'>'));
		}
		return setter+printer;
	}
}
namespace task8{
	const int N=60010,MEM=65536;
	const int FL=100;
	const int L=128*FL;
	char finans[L+1];
	inline void putcode(int i,cmd w){
		stringstream ss;
		ss<<w;
		memcpy(finans+i,ss.str().c_str(),ss.str().length());
	}
	inline void reg(char c,cmd w){
		w+=cmd(op("$"));
		assert(w.len()<FL);
		putcode(c*FL,w);
	}
	inline cmd main(){
		memset(finans,' ',L),finans[L]=0;
		putcode(0,cmd(expr(L-50).inst));
		putcode(49,cmd(op("g")));
		cmd ans,w;
		var c,pc;
		var ss,css;
		var i,tmp;
		arr stk(N),callstk(N);
		arr mem(N);
		arr src(0);//WARNING!!! end of declaration
		{//get w
			reg(' ',cmd());
			reg('\n',cmd());
			reg('p',print(stk[--ss]));
			reg('+',(ss-=1)+(stk[ss-1]+=stk[ss]));
			reg('-',(ss-=1)+(stk[ss-1]-=stk[ss]));
			reg('*',(ss-=1)+stk[ss-1].set(stk[ss-1]*stk[ss]));
			reg('/',(ss-=1)+stk[ss-1].set(stk[ss-1]/stk[ss]));
			reg(':',(ss-=1)+stk[ss-1].set(expr(op(stk[ss-1].inst+stk[ss].inst,':'))));
			reg('g',(ss-=1)+(pc+=stk[ss]));
			reg('?',(ss-=2)+ifs(stk[ss]==0,pc+=stk[ss+1]));
			reg('c',callstk[css++].set(pc)+pc.set(stk[--ss]));
			reg('$',pc.set(callstk[--css]));
			reg('<',stk[ss-1].set(mem[stk[ss-1]]));
			reg('>',(ss-=2)+mem[stk[ss+1]].set(stk[ss]));
			reg('^',stk[ss-1].set(stk[ss-stk[ss-1]-2]));
			reg('v',
					(ss-=1)+
					tmp.set(stk[ss-stk[ss]-1])+
					rep(i,ss-stk[ss]-1,ss-2,stk[i].set(stk[i+1]))+
					stk[ss-1].set(tmp));
			reg('d',ss-=1);
		}
		ans+=pc.set(-1);
		ans+=dowh((pc+=1)+src[pc].set(expr(op("R"))),src[pc]!=-1);
		ans+=pc.set(0);
		ans+=loop(c.set(src[pc])+((c!='!')*(c!=-1)),
				(pc+=1)+
				ife((c>='0')*(c<='9'),
					stk[ss++].set(c-'0'),
					cmd((c*FL).inst+op("c"))));
		return cmd(op(finans))+ans;
	}
}
inline void putans(const char id[],cmd ans){
	ofstream out((string("data")+id+string(".out")).c_str());
	out<<ans;
}
int main(){
	reset(),putans("1",task1::main());
	reset(),putans("2",task2::main());
	reset(),putans("3",task3::main());
	reset(),putans("4",task4::main());
	reset(),putans("5",task4::main());
	reset(),putans("6",task5::main());
	reset(),putans("7",task5::main());
	reset(),putans("8",task6::main());
	reset(),putans("9",task6::main());
	reset(),putans("10",task7::main());
	reset(),putans("11",task8::main());
	return 0;
}
