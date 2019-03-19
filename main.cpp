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
	int process_count,smallest,batch;			//process array iterator
	Process * proc_array[ARRAY_SIZE];	//process array
	Processor processor[5];			//processor array, 5 processors
	std::ofstream outfile;
	
	if(argc != 2)
	{
		std::cout<<"Unexpected number of args\n";
		std::cout<<"Usage: a.out <number of iterations>\n";
		exit(0);
	}
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
			temp_cycles = getRand(1,5000000);	//these are test values
			//memory
			temp_memory = getRand(250,8000000);	//units in KB
			//create new process
			Process * temp_proc = new Process(temp_id,temp_cycles,temp_memory);
			//add process to array
			proc_array[i] = temp_proc;
		}
	
		//sort array by cycles, more likely to distribute evenly
		bubbleSort(proc_array,ARRAY_SIZE);

		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			//assign process to processor
			processor[i%5].addProcess(proc_array[i]);
			total_cycles += proc_array[i]->getCycles();
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
