#include<fstream>
#include<string>
using namespace std;
string ans[10];
ifstream cin("1416.in");
ofstream cout("1416.out");
int i;
int main()
{
	ans[1]="A";
	ans[2]="A";
	ans[3]="D";
	ans[4]="D";
	ans[5]="D";
	ans[6]="A";
	ans[7]="A";
    cin >> i;
	cout << ans[i];    
    return 0;
}
