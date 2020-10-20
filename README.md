### #14 Algorithm

#### 一、题一

##### （一）题目内容

​	在西点屋吃完甜点后，吉吉哥玩起了terraria。这时他要搭一些桥方便日后跑图，但他的材料有些紧张，吉吉是个讲究人，他不想造浮空桥，并且每个桥需要左右两端各一个支柱，高的桥的支柱可以从正下方桥面上建起，给定高度和每段桥的开始结束位置，每格需要一个材料（桥面也是）问最少需要多少材料。

**输入格式：**

第一行一个数字n，表示桥的个数

接下来n行，每行三个数字，分别为各个桥的高度h（地面为0）、开始位置x_start，结束位置x_end，中间用空格隔开

**输出格式**：

一个数字，表示需要的材料数量

**输入示例：**                                                                    **输出示例：**

3                                                                                     17

3 1 2

2 4 6

5 2 4

<img src="https://d.jotang.club/uploads/default/original/1X/2a525d2798a402024751163f58f53183bbb4a07a.png" style="zoom:20%;" />

**数据范围：**

1<= n <= 10^5, 0 <= x <= 10^4

##### （二）题目分析

​	题目重点在于为了节省材料，高的桥的支柱可以从正下方桥面上建起，所以我们在建造时应从高度较低的桥开始搭建。具体流程如下：

1. 创建桥结构以及存储桥数据的数组br[]。

```c++
struct bridge
{
	int h;
	int x_start;
	int x_end;
}br[100];
```

2. 读入桥的数据，存储值数组br[]中，再将输入的桥按桥高度h从小到大排序。

```c++
//比较函数
bool cmp(bridge a,bridge b){
	return a.h<b.h;
}
```

```c++
//读入和排序	
for(int i=0;i<n;i++){
	cin>>br[i].h>>br[i].x_start>>br[i].x_end;
}
sort(br,br+n,cmp);
```

3. 循化搭建每一个桥。

* 使用一个数组high记录当前坐标下最高桥面高度，即若在坐标x的上方的最高桥面高度为H，则high[x]=H，high数组初始值为零；

```c++
memset(high,0,sizeof(high));
```

* 使用变量ans记录当前消耗的材料，每次加上搭建当前桥耗费的材料；

```c++
ans+=(br[i].h-high[br[i].x_start])+(br[i].h-high[br[i].x_end])+br[i].x_end-br[i].x_start-1;
```

* 更新high[br[i].x_start]到high[br[i].x_end]之间的数据。

```c++
for(int j=br[i].x_start;j<=br[i].x_end;j++){
	high[j]=br[i].h;
}	
```

4. 输出结果ans。

##### （三）完整代码

```c++
#include <iostream>
#include <string>
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

//比较函数
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
```

##### （四）运行结果展示

1. 题目示例：

<img src="C:\Users\18735\Desktop\14\运行截图\题一01.jpg" style="zoom:150%;" />

2. 4座桥，数据分别为5 2 9；3 3 9；2 1 3； 2 8 10；根据示意图，所需材料为5+5+7+11=28。

<img src="C:\Users\18735\Desktop\14\运行截图\题一02.jpg" style="zoom:130%;" /><img src="C:\Users\18735\Desktop\14\运行截图\题一3.jpg" style="zoom:11%;" />

#### 二、题二

##### （一）题目内容

​	多年以后，当曹导面对建设巷的时候，他一定会想起曾经疯狂喝奶茶的日子。在某日，曹导面前放了一个传送带，上面有n杯奶茶，每一杯里面奶茶的量x(1)…x(n)都不一定是相同的。这n杯奶茶从曹导面前过去。曹导每连续喝光两杯就要休息至少一杯移动过去的时间（指每连续喝两杯，后面这杯就不能喝）。问曹导最多可以喝到多少奶茶（mL)。

**输入格式：**

第一行一个数字n；

第二行n个数字，表示每杯中奶茶的量（mL)，数字间用空格隔开

**输出格式**：

一个数字，表示最多可以喝到的奶茶的量（mL)

**输入示例：**                                                                    **输出示例：**

6                                                                                     2100

100 600 300 400 500 700

**数据范围：**

1<= n <= 10^5, 0 <= x <= 10^4

##### （二）题目分析

​	本题n的数据范围较大，这里使用动态规划求解，重点在于找到状态转移方程。

1. 求状态转移方程。（1表示喝当前的奶茶，0表示不喝；数组dp[n]表示前n杯奶茶曹导可以可到的最大量）

| 情况 | x(1) | ...  | x(n-2) | x(n-1) | x(n) |
| :--: | :--: | :--: | :----: | :----: | :--: |
|  1   |  /   | ...  |   /    |   /    |  0   |
|  2   |  /   | ...  |   /    |   0    |  1   |
|  3   |  /   | ...  |   0    |   1    |  1   |

根据题意，若第i杯不喝，则前i-1杯奶茶的选择将不受后面奶茶选择方式的限制。

* 情况1：第n杯不喝，则前n-1杯奶茶怎样喝不受限制，所以此时能喝到的最大量为dp[n-1]。

* 情况2：喝第n杯，第n-1杯奶茶不喝，则前n-2杯奶茶怎样喝不受限制，此时能喝到的最大量为

  dp[n-2]+x(n)。

* 情况3：喝第第n杯和第n-1杯奶茶，根据规则，第n-2杯奶茶一定不喝，则前n-3杯奶茶怎样喝不受限制，此时能喝到的最大量为dp[n-3]+x(n-1)+x(n)。

由于每连续喝两杯，后面这杯就不能喝，即不可能出现连续喝3杯的情况，所以情况只有上述三种。

根据上述分析dp[n]为dp[n-1]，dp[n-2]+x(n)，dp[n-3]+x(n-1)+x(n)中的最大值，这里n>=4。

2. 由于在状态转移方程中限制n>=4，所以需要先求出dp[1]，dp[2]，dp[3]。

* dp[1]=x(1)
* dp[2]=x(1) + x(2)
* dp[3]=x(1) + x(2) + x(3) - min(x(1),x(2),x(3))

3. 最终结果ans=dp[n]。

##### （三）完整代码

```c++
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
	printf("%d",ans);
	return 0;
}
```

##### （四）运行结果展示

1. 题目示例：

<img src="C:\Users\18735\Desktop\14\运行截图\题二01.jpg" style="zoom:150%;" />

2. 测试数据：1 100 200 10000 10 300 20 30，

   选择方案为10110101：1+200+10000+300+30=10531

<img src="C:\Users\18735\Desktop\14\运行截图\题二02.jpg" style="zoom:150%;" />

