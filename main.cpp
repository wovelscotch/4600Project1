#include <iostream>
#include "processor.h"
#include <cstdlib>

//prototype
int getRand(int,int);
void bubbleSort(Process **,int);

int main()
{
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

	//sort array by cycles, more likely to distribute evenly
	bubbleSort(proc_array,ARRAY_SIZE);
	
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		//assign process to processor
		processor[i%5].addProcess(proc_array[i]);
	}
	for(int i = 0; i < 5; i++)
	{
		std::cout<<i<<" total count: "<<processor[i].getCycleCount()<<"\n";	
	}
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
