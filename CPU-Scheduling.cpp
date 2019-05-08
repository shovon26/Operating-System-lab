#include<bits/stdc++.h>
using namespace  std;
#define pb push_back
#define F first
#define S second
#define pr pair < int,int >

struct schedule
{

    int arr;
    int burst;
    int prio;

} process[100];

int input()
{
    cout<<"Enter total number of process : ";
    int p;
    cin>>p;
    cout<<"\nEnter arrival time and burst time for each process ::\n\n";
    for(int i=1; i<=p; i++)
    {
        cout<<"Process "<<i<<"->\n";
        cout<<"  i)Arrival time : ";
        cin>>process[i].arr;
        cout<<" ii)Burst time   : ";
        cin>>process[i].burst;
        cout<<"\n";
    }
    return p;

}

void input_priority(int p)
{
    cout<<"Enter priority for each process ::\n\n";
    for(int i=1; i<=p; i++)
    {
        cout<<"Process "<<i<<" priority : ";
        cin>>process[i].prio;
    }

}

void S_J_F(int p)
{

    vector<int>ganttchart;
    /// { remaining_time , process_number }
    priority_queue< pr, vector<pr>, greater< pr > > pq;
    queue<int>arrive[1000];
    for(int i=1; i<=p; i++)arrive[ process[i].arr ].push(i);
    int end_time[p+1];
    int process_done=0,tm=0;

    while(process_done<p)
    {

        while(!arrive[tm].empty())
        {
            int a=arrive[tm].front();
            arrive[tm].pop();
            pq.push( { process[a].burst,a } );
        }

        if(pq.empty())
        {
            ganttchart.pb(-1);
            tm++;
            continue;
        }

        auto a=pq.top();
        pq.pop();
        ganttchart.pb(a.S);
        a.F--;
        if(a.F!=0)pq.push(a);
        else
        {
            end_time[a.S]=tm;
            process_done++;
        }
        tm++;
    }


    cout<<"\n******Gantt Chart******\n";
//    cout<<"   Time ------- Process_Number\n\n";
//    int x=0;
//    for(auto a:ganttchart)cout<<"   "<<x++<<"            "<<a<<"\n";

    cout<< "Process Number --> ";
    for(auto x: ganttchart)
    {
        if(x==-1)cout<<"NL ";
        else cout<<"P"<<x<<" ";
    }
    cout<<"\n";
    cout<< "Time           --> ";
    for(int i=0; i<ganttchart.size(); i++)cout<<" "<<i<<" ";


    cout<<"\n\n";
    int wait[p+1];

    double avw=0.0;
    for(int i=1; i<=p; i++)
    {
        int a=(end_time[i] - process[i].arr + 1) - process[i].burst;
        wait[i]=a;
        avw = (avw + (double)a );
    }

    cout<<"Waiting time for each Process ::\n\n";
    cout<<"Process_Number **** Waiting_Time\n\n";
    for(int i=1; i<=p; i++)cout<<i<<"                     "<<wait[i]<<"\n";

    cout<<"\n\nAverage waiting time :: "<<avw/(double)p<<"\n\n";

}

void P_Q(int p)
{
    input_priority(p);
    vector<int>ganttchart;
    /// { priority ,{ remaining_time , process_number } }
    priority_queue< pair< int, pair< int,int > > > pq;
    queue<int>arrive[1000];
    for(int i=1; i<=p; i++)arrive[ process[i].arr ].push(i);
    int end_time[p+1];
    int process_done=0,tm=0;

    while(process_done<p)
    {

        while(!arrive[tm].empty())
        {
            int a=arrive[tm].front();
            arrive[tm].pop();
            pq.push( { process[a].prio, { process[a].burst, a } } );
        }

        if(pq.empty())
        {
            ganttchart.pb(-1);
            tm++;
            continue;
        }

        auto a=pq.top();
        pq.pop();
        ganttchart.pb(a.S.S);
        a.S.F--;

        if(a.S.F!=0)pq.push(a);
        else
        {
            end_time[a.S.S]=tm;
            process_done++;
        }

        tm++;
    }


    cout<<"\n******Gantt Chart******\n";
//    cout<<"   Time ------- Process_Number\n\n";
//    int x=0;
//    for(auto a:ganttchart)cout<<"   "<<x++<<"            "<<a<<"\n";

    cout<< "Process Number --> ";
    for(auto x: ganttchart)
    {
        if(x==-1)cout<<"NL ";
        else cout<<"P"<<x<<" ";
    }
    cout<<"\n";
    cout<< "Time           --> ";
    for(int i=0; i<ganttchart.size(); i++)cout<<" "<<i<<" ";


    cout<<"\n\n";
    int wait[p+1];

    double avw=0.0;
    for(int i=1; i<=p; i++)
    {
        int a=(end_time[i] - process[i].arr + 1) - process[i].burst;
        wait[i]=a;
        avw = (avw + (double)a );
    }

    cout<<"Waiting time for each Process ::\n\n";
    cout<<"Process_Number **** Waiting_Time\n\n";
    for(int i=1; i<=p; i++)cout<<i<<"                     "<<wait[i]<<"\n";

    cout<<"\n\nAverage waiting time :: "<<avw/(double)p<<"\n\n";

}

void R_R(int p)
{
    int q_t;
    cout<<"Enter Time Quantum : ";
    cin>>q_t;
    vector<int>ganttchart;
    /// { remaining_time , process_number }
    queue< pair < int, int > > pq;
    queue<int>arrive[1000];
    for(int i=1; i<=p; i++)arrive[ process[i].arr ].push(i);
    int end_time[p+1];
    int process_done=0,tm=0;

    while(process_done<p)
    {
        while(!arrive[tm].empty())
        {
            int a=arrive[tm].front();
            arrive[tm].pop();
            pq.push( { process[a].burst, a } );
        }

        if(pq.empty())
        {
            ganttchart.pb(-1);
            tm++;
            continue;
        }

        auto a=pq.front();
        pq.pop();
        int x=min(a.F,q_t);
        a.F-=x;

        for(int i=tm; i<tm+x; i++)ganttchart.pb(a.S);
        for(int i=tm+1; i<tm+x; i++)
        {
            while(!arrive[i].empty())
            {
                int d=arrive[i].front();
                arrive[i].pop();
                pq.push( { process[d].burst, d } );
            }
        }
        tm+=x;
        if(a.F!=0)pq.push(a);
        else
        {
            end_time[a.S]=tm-1;
            process_done++;
        }
    }



    cout<<"\n******Gantt Chart******\n";
//    cout<<"   Time ------- Process_Number\n\n";
//    int x=0;
//    for(auto a:ganttchart)cout<<"   "<<x++<<"            "<<a<<"\n";

    cout<< "Process Number --> ";
    for(auto x: ganttchart)
    {
        if(x==-1)cout<<"NL ";
        else cout<<"P"<<x<<" ";
    }
    cout<<"\n";
    cout<< "Time           --> ";
    for(int i=0; i<ganttchart.size(); i++)cout<<" "<<i<<" ";


    cout<<"\n\n";
    int wait[p+1];

    double avw=0.0;
    for(int i=1; i<=p; i++)
    {
        int a=(end_time[i] - process[i].arr + 1) - process[i].burst;
        wait[i]=a;
        avw = (avw + (double)a );
    }

    cout<<"Waiting time for each Process ::\n\n";
    cout<<"Process_Number **** Waiting_Time\n\n";
    for(int i=1; i<=p; i++)cout<<i<<"                     "<<wait[i]<<"\n";

    cout<<"\n\nAverage waiting time :: "<<avw/(double)p<<"\n\n";

}

int main()
{
    int p=input();
    while(true)
    {
        cout<<"\n**Which Scheduling you want ?\n\n";
        cout<<" 1 -> Shortest Job First Scheduling.\n";
        cout<<" 2 -> Priority Queue Scheduling.\n";
        cout<<" 3 -> Round Robin Scheduling.\n";
        cout<<"Enter your choice : ";
        int ch;
        cin>>ch;
        if(ch==1) S_J_F(p);
        if(ch==2)P_Q(p);
        if(ch==3)R_R(p);
        cout<<"Do you want any other scheduling ? \n";
        cout<<" 1 -> YES\n";
        cout<<" 2 -> NO\n";
        cout<<"Enter your choice : ";
        cin>>ch;
        if(ch==2)break;
    }
    return 0;
}
