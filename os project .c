#include<stdio.h>

struct process
{
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int wt;
    int tat;
};

void calculate(struct process p[],int n)
{
    for(int i=0;i<n;i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void display(struct process p[],int n)
{
    float awt=0,atat=0;

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);

        awt += p[i].wt;
        atat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f",awt/n);
    printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}

void fcfs(struct process p[],int n)
{
    int time=0;

    printf("\nGantt Chart:\n|");

    for(int i=0;i<n;i++)
    {
        if(time < p[i].at)
            time = p[i].at;

        time = time + p[i].bt;
        p[i].ct = time;

        printf(" P%d |",p[i].pid);
    }

    calculate(p,n);
    display(p,n);
}

void sjf(struct process p[],int n)
{
    int completed=0,time=0;
    int visited[20]={0};

    printf("\nGantt Chart:\n|");

    while(completed<n)
    {
        int min=999,idx=-1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && visited[i]==0 && p[i].bt<min)
            {
                min=p[i].bt;
                idx=i;
            }
        }

        if(idx!=-1)
        {
            time += p[idx].bt;
            p[idx].ct=time;
            visited[idx]=1;
            completed++;

            printf(" P%d |",p[idx].pid);
        }
        else
        {
            time++;
        }
    }

    calculate(p,n);
    display(p,n);
}

void priority(struct process p[],int n)
{
    int completed=0,time=0;
    int visited[20]={0};

    printf("\nGantt Chart:\n|");

    while(completed<n)
    {
        int high=999,idx=-1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && visited[i]==0 && p[i].pr<high)
            {
                high=p[i].pr;
                idx=i;
            }
        }

        if(idx!=-1)
        {
            time += p[idx].bt;
            p[idx].ct=time;
            visited[idx]=1;
            completed++;

            printf(" P%d |",p[idx].pid);
        }
        else
        {
            time++;
        }
    }

    calculate(p,n);
    display(p,n);
}

void roundrobin(struct process p[],int n,int q)
{
    int time=0,completed=0;
    int rem[20];

    for(int i=0;i<n;i++)
        rem[i]=p[i].bt;

    printf("\nGantt Chart:\n|");

    while(completed<n)
    {
        for(int i=0;i<n;i++)
        {
            if(rem[i]>0)
            {
                if(rem[i]>q)
                {
                    time += q;
                    rem[i] -= q;
                }
                else
                {
                    time += rem[i];
                    rem[i]=0;
                    p[i].ct=time;
                    completed++;
                }

                printf(" P%d |",p[i].pid);
            }
        }
    }

    calculate(p,n);
    display(p,n);
}

int main()
{
    int n,q;

    struct process p[20],temp[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i].pid=i+1;

        printf("\nProcess P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);
    }

    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d",&q);

    printf("\n----- FCFS Scheduling -----\n");
    for(int i=0;i<n;i++) temp[i]=p[i];
    fcfs(temp,n);

    printf("\n----- SJF Scheduling -----\n");
    for(int i=0;i<n;i++) temp[i]=p[i];
    sjf(temp,n);

    printf("\n----- Priority Scheduling -----\n");
    for(int i=0;i<n;i++) temp[i]=p[i];
    priority(temp,n);

    printf("\n----- Round Robin Scheduling -----\n");
    for(int i=0;i<n;i++) temp[i]=p[i];
    roundrobin(temp,n,q);

    return 0;
}
