void drawGanttChart();
void calculateProcessSequence();
int findAptProcessNumber(int);
#include<stdlib.h>
#include<stdio.h>
#include <iostream>

using namespace std;

int numberOfProcesses,totalCPUBurstTime,*arrivalTime,*CPUBurstTime,*CPUBurstTimeCopy,*processNumber,minimumArrivalTime,*processSequenceForEachSecond,*waitingTime;
float averageWaitingTime,averageTurnAroundTime;

/*arrays used to draw Gantt Chart*/
int *processNumberGantt,*CPUBurstTimeGantt,ganttSize;

int main()
{
start:
	   printf("Programmed by: Jo-Mari R. Reloj\n");
                int i,j,temp;
             
    	        printf("SHORTEST JOB FIRST PREEMPTIVE ALGORITHM\n\n");
                printf("Enter No. of Processes: ");
                scanf("%d",&numberOfProcesses);
                arrivalTime=(int*)malloc(sizeof(int)*numberOfProcesses);
                CPUBurstTime=(int*)malloc(sizeof(int)*numberOfProcesses);
                CPUBurstTimeCopy=(int*)malloc(sizeof(int)*numberOfProcesses);
                processNumber=(int*)malloc(sizeof(int)*numberOfProcesses);
                waitingTime=(int*)malloc(sizeof(int)*numberOfProcesses);
               
                minimumArrivalTime=2147483647;
                printf("Arrival Time:\n");
                for(i=0;i<numberOfProcesses;i++)
                {
                                waitingTime[i]=0;
                                processNumber[i]=i;
       
                            	cout << "P"<<i<<":";
                                scanf("%d",&arrivalTime[i]);
                                
                                if(minimumArrivalTime>arrivalTime[i])
                                                minimumArrivalTime=arrivalTime[i];
                }
                
                 printf("Burst Time:\n");
                 for(i=0;i<numberOfProcesses;i++)
                {
                                
                        	cout << "P"<<i<<":";
                                scanf("%d",&CPUBurstTime[i]);
                                CPUBurstTimeCopy[i]=CPUBurstTime[i];
                                totalCPUBurstTime+=CPUBurstTime[i];
                                
                }
                
                
                
                
                processSequenceForEachSecond=(int*)malloc(sizeof(int)*totalCPUBurstTime);
               
                /* this function calculates the process sequence for each second. */
               
                calculateProcessSequence();
                
                
            
               
                drawGanttChart();
              char e;
    cout<<"Do you want to run again [y/n]:";
    cin>>e;
    if(e == 'y')
    {
    		system("CLS");
    	goto start;
	}
	else{
		exit(0);
	}
	return 0;
           	                
}
void calculateProcessSequence()
{
                int i,j,pNumber,prevProcess,tempCPUBurstTime,counter,prevProcesss;
                for(i=minimumArrivalTime;i<totalCPUBurstTime + minimumArrivalTime;i++)
                {
                                pNumber=findAptProcessNumber(i);
                                processSequenceForEachSecond[i-minimumArrivalTime]=pNumber;
                                CPUBurstTime[pNumber]--;
                                /*
                                                claculating the waiting time of each process;
                                */
                                for(j=0;j<numberOfProcesses;j++)
                                                if(CPUBurstTime[j]!=0 && arrivalTime[j]<=i && j!=pNumber)
                                                                waitingTime[j]++;
                               
                }
               
               
                /* claculating the size of gantt chart arrays*/
                ganttSize=1;
                prevProcess=processSequenceForEachSecond[0];
                for(i=0;i<totalCPUBurstTime;i++)
                {
                                if(prevProcess!=processSequenceForEachSecond[i])
                                                ganttSize++;
                                prevProcess=processSequenceForEachSecond[i];
                }
               
                /* allocating the size of gantt chart arrays */
                processNumberGantt=(int*)malloc(sizeof(int)*ganttSize);
                CPUBurstTimeGantt=(int*)malloc(sizeof(int)*ganttSize);
               
                /* assigning the values to Gantt Chart Arrays */
                prevProcess=processSequenceForEachSecond[0];
                tempCPUBurstTime=0;
                counter=0;
                for(i=0;i<totalCPUBurstTime;i++)
                {
                                if(prevProcess!=processSequenceForEachSecond[i])
                                {
                                                processNumberGantt[counter]=prevProcess;
                                                CPUBurstTimeGantt[counter]=tempCPUBurstTime;
                                                counter++;
                                                tempCPUBurstTime=0;
                                }
                                tempCPUBurstTime++;
                                prevProcess=processSequenceForEachSecond[i];
                }
               
                CPUBurstTimeGantt[ganttSize-1]=tempCPUBurstTime;
                processNumberGantt[ganttSize-1]=prevProcess;
               
               
                /* calculating the averageWaitingTime and averageTurnAroundTime */
                averageWaitingTime=0;
                averageTurnAroundTime=0;
                 cout<<"\n\nTable\n";
               	cout << "Process\t\tTAT\tWT " << endl;
               	
                for(i=0;i<numberOfProcesses;i++)
                {
                                averageWaitingTime+=waitingTime[i];
        	cout << "P"<< i<< "\t\t"<<  waitingTime[i]+CPUBurstTimeCopy[i] <<  "\t" << waitingTime[i] << endl;
                                
                                averageTurnAroundTime+=waitingTime[i]+CPUBurstTimeCopy[i];
                              
                }
                
  	cout << "Total\t\t" <<averageTurnAroundTime<<"\t"<<averageWaitingTime<< endl;
	cout << "Average\t\t" <<  averageTurnAroundTime/(float)numberOfProcesses<< "\t"<<averageWaitingTime/(float)numberOfProcesses<< endl<<endl;

                
              
               
}

int findAptProcessNumber(int currentTime)
{
                int i,min=2147483647,pNumber;
                for(i=0;i<numberOfProcesses;i++)
                                if(arrivalTime[i]<=currentTime && min>CPUBurstTime[i] && CPUBurstTime[i]!=0)
                                {
                                                min=CPUBurstTime[i];
                                                pNumber=i;
                                }
                return pNumber;
}
void drawGanttChart()
{
                const int maxWidth=100;
                int scalingFactor,i,counter,tempi,currentTime;
                printf("Gantt Chart \n\n");
               
                scalingFactor=maxWidth/totalCPUBurstTime;
                for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
                                printf("-");
                printf("\n|");
                counter=0,tempi=0;
                for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
                                if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
                                {
                                                counter++;
                                                tempi=i;
                                                printf("|");
                                }
                                else if(i==(CPUBurstTimeGantt[counter]*scalingFactor)/2+tempi)
                                                printf("P%d",processNumberGantt[counter]);
                                else
                                                printf(" ");
                printf("|");
                printf("\n");
                for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
                                printf("-");
                printf("\n");

                /* printing the time labels of the gantt chart */
                counter=0;
                tempi=0;
                currentTime=minimumArrivalTime;
                printf("%d",currentTime);
                for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
                                if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
                                {
                                                tempi=i;
                                                currentTime+=CPUBurstTimeGantt[counter];
                                                averageWaitingTime+=currentTime;
                                                counter++;
                                                printf("%2d",currentTime);
                                }
                                else
                                {
                                                printf(" ");
                                }
                currentTime+=CPUBurstTimeGantt[counter];
                printf("%2d\n\n",currentTime);
}
