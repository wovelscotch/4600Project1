#include <iostream>
#include "processor.h"
#include <cstdlib>
#include <fstream>
#include <string>


//prototype
long long int getRand(long long int,long long int);
void bubbleSort(Process **,int);

//main
int main(int argc, char**argv)
{
	long long int avg_wait;
	long long int total_cycles = 0;		//total count of all cycles from all processes
	long long int total_waits = 0;			//total wait time of all processes
	bool is_not_empty = true;		//checks if process queue is empty
	bool is_all_idle = false;
	int process_count,smallest,batch, tc =0;			//process array iterator
	Process * proc_array[ARRAY_SIZE];	//process array
	Processor processor[5];			//processor array, 5 processors
	std::ofstream outfile;
	
	if(argc != 2)
	{
		std::cout<<"Unexpected number of args\n";
		std::cout<<"Usage: a.out <number of iterations>\n";
		exit(0);
	}
	processor[0].setClock(2);
	processor[1].setClock(2);
	processor[2].setClock(3);
	processor[3].setClock(3);
	processor[4].setClock(4);
	outfile.open("results.txt");
	batch = atoi(argv[1]);
	outfile<<"Number\tTotal Cycles\tIdeal Exec time\tExp Exec Time\tAvg Wait\n";
	for(int j = 1; j <= batch; j++)
	{
		total_cycles = 0;
		total_waits = 0;
		//seed rand
		srand(j);
		outfile<<j<<"\t";

		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			int temp_id;
			long long int temp_cycles;
			int temp_memory;
			//id
			temp_id = i;
			//cycles
			temp_cycles = getRand(1000000,5000000000000);	//these are test values
			//memory
			temp_memory = getRand(250,8000000);	//units in KB
			//create new process
			Process * temp_proc = new Process(temp_id,temp_cycles,temp_memory);
			//add process to array
			proc_array[i] = temp_proc;
			total_cycles += temp_cycles;
		}
		for(int i = 0; i < 5; i++)
			tc += processor[i].getClock();//get total clock for expected calculation
		for(int i = 0 ; i < 5; i++)
		{
			processor[i].calcExpected(total_cycles,tc);//calc expected cycles
		}
		std::cout<<"Total cycles: "<<total_cycles<<"\n";
		for(int i = 0; i < 5; i++)
			std::cout<<"P"<<i<<" WCycles: "<<processor[i].getEWCycleCount()<<"\n";
		//sort array by cycles to reduce wait times
		bubbleSort(proc_array,ARRAY_SIZE);

		
		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			int sm = 0;
			//get lowest weighted cycles
			for(int k = 1; k < 5;k++)
			{
				if(processor[sm].getWCycleCount() > processor[k].getWCycleCount())
				{
					sm = k;
				}
			}
			processor[sm].addProcess(proc_array[i]);//add to processor with lowest weighted cycles
		}
		
		std::cout<<"Total Cycles\t: "<<total_cycles<<"\n";
		std::cout<<"Ideal Exec Time\t: "<<total_cycles/5<<"\n";
		outfile<<total_cycles<<"\t"<<total_cycles/5<<"\t";
		total_cycles = processor[0].getCycleCount();
		//print total cycles for each processor (mostly for diagnostic purposes)
		for(int i = 0; i < 5; i++)
		{
			std::cout<<i<<" total count: "<<processor[i].getCycleCount()<<"\n";
			if(total_cycles < processor[i].getCycleCount())
				total_cycles = processor[i].getCycleCount();
		}
		//get total waits
		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			total_waits += proc_array[i]->getWait();
		}
		avg_wait = (long long int)total_waits/(long long int)ARRAY_SIZE;
		std::cout<<"Exec time\t: "<<total_cycles<<" cycles\n";
		std::cout<<"Average Wait\t: "<<avg_wait<<" cycles\n";
		outfile<<total_cycles<<"\t"<<avg_wait<<"\n";
	
		//cleanup 
		for(int i = 0; i < 5; i++)
			processor[i].wipe();
		for(int i = 0; i < ARRAY_SIZE;i++)
		{
			delete proc_array[i];
		}
	}
	outfile.close();
	return 0;
}

//return random number between l and u 
long long int getRand(long long int l, long long int u)
{
	return (rand()%(u-l))+l;
}


//sort processes on cycles low to high
void bubbleSort(Process ** array, int size)
{	
	int i , j;
	for(i = 0; i < size - 1; i++)
	{
		for(j = 0; j < size-i-1;j++)
		{
			if(array[j]->getCycles() > array[j+1]->getCycles())	//swap
			{
				Process * temp_proc = array[j];
				array[j] = array[j+1];
				array[j+1] = temp_proc;
			}
		}
	}
}
