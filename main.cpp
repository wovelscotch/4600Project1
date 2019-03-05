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
	int process_count;			//process array iterator
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
	}

	//init process count to 0 (first)
	process_count = 0;
	//execute all processes
	while(is_not_empty)
	{
		for(int i = 0; i < 5; i++)	//check all processes if waiting for process
		{
			if(process_count < ARRAY_SIZE)//if process available in array
			{	
				if(!processor[i].getIsRunning())//if not running, get new process
				{
					std::cout<<"Processor "<<i<<" is getting new process ";//diag print
					//give processor new process
					processor[i].setCurr(proc_array[process_count]);
					process_count++;
					processor[i].setIsRunning(true);
					//diagnostic print statement
					std::cout<<processor[i].getCurr()->getId()<<"\n";
				}
				else	//process is running
				{
					processor[i].cycle();	//decrement cycle of process
					total_cycles++;		//increment total number of cycles
				}
				for(int j = process_count; j < ARRAY_SIZE; j++)
				{
					//increment wait
					proc_array[j]->incWait();
				}
			}
			else	//process array is empty
				is_not_empty = false;
		}		
	}
	//finish running remaining process
	for(int i = 0; i < 5; i++)
	{
		std::cout<<"I:"<<i<<"\n";
		if(processor[i].getCurr()==NULL)
			std::cout<<"NULL\n";
		else
		{
		while(processor[i].cycle())
			total_cycles++;
		}
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
