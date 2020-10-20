#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int n,ans=0;
	cin>>n;
	int ml[n+1],dp[n+1];
	for(int i=1;i<=n;i++){
		cin>>ml[i];
	}
	
	if(n==1){
		ans=ml[1];
	}else if(n==2){
		ans=ml[1]+ml[2];
	}else if(n==3){
		ans=ml[1]+ml[2]+ml[3]-min(ml[3],min(ml[1],ml[2]));
	}else{
		dp[1]=ml[1];
		dp[2]=ml[1]+ml[2];
		dp[3]=ml[1]+ml[2]+ml[3]-min(ml[3],min(ml[1],ml[2]));
		for(int i=4;i<=n;i++){
			dp[i]=max(max(dp[i-1],ml[i]+dp[i-2]),ml[i]+ml[i-1]+dp[i-3]);
		}
		ans=dp[n];
	}
	printf("%d\n",ans);
	return 0;
}
