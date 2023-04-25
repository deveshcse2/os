#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	int pno=4;
	vector<int> AT={1,2,1,4};
	vector<int>BT={3,4,2,4};
	vector<vector<int>> shedule;
	for(int i=0; i<pno; i++){
		shedule.push_back({AT[i],BT[i],i});
	}
	sort(shedule.begin(),shedule.end());
	int selector=0;
	int timer=shedule[0][0];
	priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>> > ready_queue;   
	vector<vector<int>> ans;
	//for(int i=0; i<pno ; i++){
	while(ans.size()<pno){
		//while(selector<pno)
		for(int i=selector; i<pno; i++){
		    if(shedule[i][0]<=timer)ready_queue.push({shedule[i][1],shedule[i][0],shedule[i][2]});
		    else {
		    	selector=i;
		    	if(ready_queue.size()==0)timer=shedule[selector][0];
		    	break;
		    }
		}
		timer+=ready_queue.top()[0];
		ans.push_back({ready_queue.top()[2],timer});
		ready_queue.pop();
	}
	for(auto i :ans ) cout<<i[0]<<"-"<<i[1]<<endl;
		
}