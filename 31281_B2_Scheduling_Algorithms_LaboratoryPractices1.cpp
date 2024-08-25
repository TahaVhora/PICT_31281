//============================================================================
// Name        : 31281_B2_LP1.cpp
// Author      : Taha Vhora
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

class Process{
public:
	int id;
	int at;
	int bt;
	int p;

	Process(int id, int at, int bt){
		this->id =id;
		this->at=at;
		this->bt=bt;
		p=0;
	}

	Process(int id, int at, int bt, int p){
		this->id =id;
		this->at=at;
		this->bt=bt;
		this->p=p;
	}
};

bool compareByAT(const Process &a, const Process &b){
	if(a.at != b.at){
		return a.at <b.at;
	}
	else{
		return a.id < b.id;
	}
}

bool compareByBT(const Process &a, const Process &b){
	if(a.bt != b.bt){
		return a.bt <b.bt;
	}
	else{
		return a.id < b.id;
	}
}

bool compareByP(const Process &a, const Process &b){
	if(a.p != b.p){
		return a.p <b.p;
	}
	else{
		return a.id < b.id;
	}
}

class Scheduler{
public:

	void FCFS(vector <Process> P){
		int time=0;
		sort(P.begin(), P.end(), compareByAT);
		cout<<"Gantt Chart is: "<<endl;
		for(int i=0; i<P.size(); i++){
			if(P[i].at > time){
				cout<<"Idle   "<<time<<"-"<<flush;
				sleep(P[i].at-time);
				cout<<P[i].at<<endl;
				time=P[i].at;
			}
			cout<<"P"<<P[i].id<<"     "<<time<<"-"<<flush;
			sleep(P[i].bt);
			time= time+P[i].bt;
			cout<<time<<endl;

		}
	}

	void Round_Robin(vector <Process> P){
		int q;
		cout<<"Enter the quantum slice: ";
		cin>>q;
		sort(P.begin(), P.end(), compareByAT);
		int time=0;
		vector <Process> ready_que;
		int front=0;
		int size_new, size_old;
		cout<<"Gantt Chart is: "<<endl;
		while(!P.empty() || !ready_que.empty()){
			size_old=ready_que.size();
			while(!P.empty() && P[0].at <= time ){
				ready_que.push_back(P[0]);
				P.erase(P.begin());
			}
			size_new = ready_que.size();
			//for idle state
			if(ready_que.empty()){
					if(!P.empty()){
					cout<<"Idle   "<<time<<"-"<<flush;
					sleep(P[0].at-time);
					time=P[0].at;
					cout<<time<<endl;
				}
			}
			else{
				if(size_old==0){
					size_old=size_new;
					front=0;
				}

				cout<<"P"<<ready_que[front].id<<"     "<<time<<"-"<<flush;
				if(ready_que[front].bt <=q){
					sleep(ready_que[front].bt);
					time=time+ready_que[front].bt;
					ready_que.erase(ready_que.begin()+front);
					if(front==ready_que.size()){
						front=0;
					}
				}
				else{
					sleep(q);
					time=time+q;
					ready_que[front].bt = ready_que[front].bt- q;
					front= (front +1 )%size_old;
				}
				cout<<time<<endl;
			}
		}
	}

	void Priority_Scheduler_NP(vector <Process> P){
		vector <Process> ready_que;
		int time=0;
		cout<<"Gantt Chart is: "<<endl;
		while(!P.empty() || !ready_que.empty()){
			while(!P.empty() && P[0].at <= time){
				ready_que.push_back(P[0]);
				P.erase(P.begin());
			}
			if(!ready_que.empty()){
				sort(ready_que.begin(), ready_que.end(), compareByP);
				cout<<"P"<<ready_que[0].id<<"     "<<time<<"-"<<flush;
				sleep(ready_que[0].bt);
				time=time+ready_que[0].bt;
				cout<<time<<endl;
				ready_que.erase(ready_que.begin());
			}
			else{
				cout<<"Idle   "<<time<<"-"<<flush;
				sleep(P[0].at - time);
				time= P[0].at;
				cout<<time<<endl;
			}
		}
	}

	void SJF(vector <Process> P){
		int time=0;
		vector <Process> ready_que;
		int p0_old, p0_new;
		p0_old =0;
		cout<<"Gantt Chart is:"
		while(!ready_que.empty() || !P.empty()){
			while(!P.empty() && P[0].at <= time){
				ready_que.push_back(P[0]);
				P.erase(P.begin());
			}
			if(!ready_que.empty()){
				sort(ready_que.begin(), ready_que.end(), compareByBT);
				p0_new = ready_que[0].id;

				if(p0_new != p0_old){
					if(p0_old !=0 )
						cout<<time<<endl;
					cout<<"P"<<ready_que[0].id<<"     "<<time<<"-"<<flush;
				}
				sleep(1);
				ready_que[0].bt = ready_que[0].bt -1;
				time++;
				p0_old = ready_que[0].id;
				if(ready_que[0].bt == 0){
					ready_que.erase(ready_que.begin());
				}

			}
			else{
				cout<<time<<endl;
				cout<<"Idle"<<"   "<<time<<"-"<<flush;
				sleep(P[0].at - time);
				time = P[0].at;
			}
		}
		cout<<time<<endl;
	}
};


int main() {
	int n, id, bt, at, p;
	char choice;
	vector <Process> P;
	Scheduler S;
	cout<<"Do you want prioritized scheduling or not? [Y/n]:";
	cin>>choice;
	if(choice=='Y' || choice=='y'){
		cout<<"Enter the number of processes do you want to create: ";
		cin>> n;
		for(int i=0; i<n; i++){
			cout<<"Process number "<<i+1<<" : ";
			cout<<"Enter process id, arrival time, burst time and priority: "<<endl;
			cin>>id;
			cin>>at;
			cin>>bt;
			cin>>p;
			P.push_back(Process(id, at, bt, p));
		}
	}
	else{
		cout<<"Enter the number of processes do you want to create: ";
		cin>> n;
		for(int i=0; i<n; i++){
			cout<<"Process number "<<i+1<<" : ";
			cout<<"Enter process id, arrival time and burst time: "<<endl;
			cin>>id;
			cin>>at;
			cin>>bt;
			P.push_back(Process(id, at, bt));
		}
	}

	//S.FCFS(P);
	//S.Round_Robin(P);
	//S.Priority_Scheduler_NP(P);
	//S.SJF(P);

	return 0;
}
