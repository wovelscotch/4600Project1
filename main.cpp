#include <iostream>
#include "processor.h"
#include <cstdlib>

//prototype
int getRand(int,int);
void bubbleSort(Process **,int);

int main()
{
	const int ARRAY_SIZE = 25;		//number of processes
	long long int total_cycles = 0;		//total count of all cycles from all processes
	int total_waits = 0;			//total wait time of all processes
	bool is_not_empty = true;		//checks if process queue is empty
	bool is_all_idle = false;
	int process_count,smallest;			//process array iterator
	Process * proc_array[ARRAY_SIZE];	//process array
	Processor processor[5];			//processor array, 5 processors

	//seed rand
	srand(0);

	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		int temp_id;
		int temp_cycles;
		int temp_memory;
		//id
		temp_id = i;
		//cycles
		temp_cycles = getRand(1,500);	//these are test values
		//memory
		temp_memory = getRand(250,8000000);	//units in KB
		//create new process
		Process * temp_proc = new Process(temp_id,temp_cycles,temp_memory);
		//add process to array
		proc_array[i] = temp_proc;
	}

	//sort array by cycles
	bubbleSort(proc_array,ARRAY_SIZE);
	
	//print list of processes for diagnostic purposes
	for(int i = 0 ; i < ARRAY_SIZE; i++)
	{
		std::cout<<"Id: "<<proc_array[i]->getId()<<"\t";
		std::cout<<"Cyc: "<<proc_array[i]->getCycles()<<"\t";
		std::cout<<"Mem: "<<proc_array[i]->getMemory()<<"\n";
		total_cycles += proc_array[i]->getCycles();
	}
	std::cout<<"Total Cycles: "<<total_cycles<<"\n";	//print definative total cycles
	total_cycles = 0;	//reset total cycles

	//init process count to 0 (first)
	process_count = 0;
	//execute all processes
	//loops until process list is empty and all processors are idle (finished executing)
	while(is_not_empty||!is_all_idle)
	{
		is_all_idle = true;//assume break condition, must prove otherwise
		//this loop checks processor idle condition and assigns new processes to idle processors
		for(int i = 0; i < 5; i++)			//check all processes if waiting for process
		{
			if(!processor[i].getIsRunning())	//if processor idle, attempt to get new process
			{
				if(process_count < ARRAY_SIZE)	//if process available in process list
				{
					processor[i].setCurr(proc_array[process_count]);
					std::cout<<"Set "<<process_count<<" to P["<<i<<"]\n";
				}
				else
					is_not_empty = false;
			}
		}
		//this section simulates the running of processes
		//it gets the processor with the smallest remaining cycles and stores the number
		//it then decrements from all currently running processes that number
		//this is to improve performace comapared to decrementing each process cycle by 1 each loop
		//functionally it should be the same
		//get smallest number of cycles remaining
		smallest = processor[0].getCurr()->getCycles();	
		for(int i = 1; i < 5;i++)
		{
			if(smallest < processor[i].getCurr()->getCycles())
				smallest = processor[i].getCurr()->getCycles();
		}
		//decrement by smallest number of cycles
		//also check for idle condition
		for(int i = 0; i < 5;i++)
		{
			if(processor[i].cycle(smallest))
				is_all_idle = false;
			else
				std::cout<<process_count<<" is done\n";
		}
		total_cycles+= smallest;					
	}
	//get total waits
	for(int i = 0; i < ARRAY_SIZE;i++)
	{
		total_waits += proc_array[i]->getWait();
	}
	std::cout<<"Total Cycle Count: "<<total_cycles<<"\n";
	std::cout<<"Total Wait Count: "<<total_waits<<"\n";
	std::cout<<"Average Wait :"<<(float)total_waits/(float)ARRAY_SIZE<<"\n";
}

//return random number between l and u 
int getRand(int l, int u)
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
