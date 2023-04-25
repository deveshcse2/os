#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	int pno=4;
	vector<int> AT={0,1,2,4};
	vector<int>BT={5,4,2,1};
	vector<vector<int>> shedule;
	for(int i=0; i<pno; i++){
		shedule.push_back({AT[i],BT[i],i});
	}
	sort(shedule.begin(),shedule.end());
	int timer=0;
	queue<vector<int>> ready_queue;
	vector<vector<int>>ans;
	int TQ=2;
	int i=0;
	while(i<pno or !ready_queue.empty()){
		
		if(!ready_queue.empty() ){
			vector<int> job = ready_queue.front();
			ready_queue.pop();
			while(i<pno){
				if(shedule[i][0] >timer )break;
				ready_queue.push({shedule[i][1],shedule[i][0],shedule[i][2]});
				i++;			
			}
			int RT = job[0]-TQ;
			cout<<job[2]+1<<"---"<<RT<<endl;
		     if(RT<0 ){   // RT is negative when there is no arrival for long time and our process completed much earlier
		    						   // before the arrival of a new process
		  	  ans.push_back({job[2],timer+RT});
		  	  timer+=RT;
			}
			if(RT==0)ans.push_back({job[2],timer+RT});
			if(RT>0)ready_queue.push({RT,timer,job[2]});
		}
		
		else if (i<pno){
			ready_queue.push({shedule[i][1],shedule[i][0],shedule[i][2]});
			timer=shedule[i][0];
			i++;
		}
		//cout<<ready_queue.front()[0];
		timer+=TQ;
	//	ready_queue.push({shedule[i][1],shedule[i][0],shedule[i][2]});
		
	}
/*	while(!ready_queue.empty()){
		vector<int> job = ready_queue.front();
		ready_queue.pop();
		int RT = job[0]-TQ;
		cout<<job[2]+1<<"---"<<RT<<endl;
		if(RT<0 ){   // RT is negative when there is no arrival for long time and our process completed much earlier
		    						   // before the arrival of a new process
		    ans.push_back({job[2],timer+RT});
		    timer+=RT;
		 
		}
		if(RT==0)ans.push_back({job[2],timer});
		if(RT>0)ready_queue.push({RT,timer,job[2]});
		timer+=TQ;
	}*/
	sort(ans.begin(),ans.end());
	for(auto i :ans ) cout<<i[0]+1<<"-"<<i[1]<<endl;
		
}