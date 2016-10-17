#include<fstream>
#include<string>
using namespace std;
string ans[20];
ifstream cin("1422.in");
ofstream cout("1422.out");
int i;
int main()
{
	ans[1]="D";
	ans[2]="B";
	ans[3]="B";
	ans[4]="B";
	ans[5]="B";
	ans[6]="D";
	ans[7]="D";
	ans[8]="A";
	ans[9]="D";
	ans[10]="A";
	ans[11]="AB";
	ans[12]="AC";
    cin >>  i;
	cout  << ans[i];
    
    return 0;
}
