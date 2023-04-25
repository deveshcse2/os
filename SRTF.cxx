#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	int pno=4;
	vector<int> AT={0,1,2,5};
	vector<int>BT={5,3,4,1};
	vector<vector<int>> shedule;
	for(int i=0; i<pno; i++){
		shedule.push_back({AT[i],BT[i],i});
	}
	sort(shedule.begin(),shedule.end());
	int selector=0;
	int timer=shedule[0][0];
	priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>> > ready_queue;   
	vector<vector<int>> ans;
	for(int i=0; i<pno ; i++){
		   
		timer=shedule[i][0];
		if(ready_queue.size()!=0){
			vector<int>job=ready_queue.top();  //job with least Remaining time
		    ready_queue.pop();
		    int RT=job[0]-(timer-job[1]);  //Remaining Time
		    while(RT<0 ){   // RT is negative when there is no arrival for long time and our process completed much earlier
		    						   // before the arrival of a new process
		    	ans.push_back({job[2],timer+RT});
		    	if(ready_queue.size()==0) break;
		    	job=ready_queue.top();
		        ready_queue.pop();
		        RT+=job[0];
		    }
		    if(RT==0)ans.push_back({job[2],timer});
		    if(RT>0)ready_queue.push({RT,timer,job[2]});
		}	
		ready_queue.push({shedule[i][1],shedule[i][0],shedule[i][2]});
	}
	while(!ready_queue.empty()){
		vector<int> job= ready_queue.top();
		ready_queue.pop();
		timer+=job[0];
		ans.push_back({job[2],timer});
	}
	for(auto i :ans ) cout<<i[0]<<"-"<<i[1]<<endl;
		
}