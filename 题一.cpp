#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct bridge
{
	int h;
	int x_start;
	int x_end;
}br[100];
int high[1005];
int ans=0;

//±È½Ïº¯Êý
bool cmp(bridge a,bridge b){
	return a.h<b.h;
}

int main()
{
	int n;
	cin>>n;
	memset(high,0,sizeof(high));
	
	for(int i=0;i<n;i++){
		cin>>br[i].h>>br[i].x_start>>br[i].x_end;
	}
	sort(br,br+n,cmp);
	
	for(int i=0;i<n;i++){
		ans+=(br[i].h-high[br[i].x_start])+(br[i].h-high[br[i].x_end])+br[i].x_end-br[i].x_start-1;
		for(int j=br[i].x_start;j<=br[i].x_end;j++){
			high[j]=br[i].h;
		}	
	}
	
	cout<<ans<<endl;
	return 0;
}
