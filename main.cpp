#include <iostream>
#include "processor.h"
#include <cstdlib>
#include <fstream>
#include <string>
const long long GIGABYTE = 1000000; //*10^3
using namespace std;

//prototype
long long int getRand(long long int,long long int);
void bubbleSort(Process **,int);
void bubbleSortM(Process **,int);

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
	const long long int GB2 = 2*GIGABYTE;
	const long long int GB4 = 4*GIGABYTE;
	const long long int GB8 = 8*GIGABYTE;
	//int *array2, array4, array8;
	Process * array2[ARRAY_SIZE];
	Process * array4[ARRAY_SIZE];
	Process * array8[ARRAY_SIZE];
        int temp2 = 0, temp4 = 0, temp8 = 0;
	
	if(argc != 2)
	{
		std::cout<<"Unexpected number of args\n";
		std::cout<<"Usage: a.out <number of iterations>\n";
		exit(0);
	}
	batch = atoi(argv[1]);
	for(int j = 1; j <= batch; j++)
	{
		total_cycles = 0;
		total_waits = 0;
		//seed rand
		srand(j);
		for(int i = 0; i < ARRAY_SIZE; i++)
		{
			int temp_id;
			long long int temp_cycles;
			long long int temp_memory;
			//id
			temp_id = i;
			//cycles
			temp_cycles = getRand(1,5000000);//*10^6
			//memory
			temp_memory = getRand(250,8000000); //.25MB - 8GB (in KB)
			//create new process
			Process * temp_proc = new Process(temp_id,temp_cycles,temp_memory);
			//add process to array
			proc_array[i] = temp_proc;
			total_cycles += temp_cycles;
		}
		//sort array by cycles, more likely to distribute evenly
		bubbleSortM(proc_array,ARRAY_SIZE);// sorts array by memory size
                // sorts array by mem size
		for(int i = ARRAY_SIZE-1; i >= 0; i--){
			//add all <4GB to array8
			if(proc_array[i]->getMemory() > GB4)
			{
				array8[temp8] = proc_array[i];
				temp8++;
			}
			else if (proc_array[i]->getMemory()>GB2)
			{
				array4[temp4] = proc_array[i];
				temp4++;
			}
			else
			{
				array2[temp2] = proc_array[i];
				temp2++;
			}
		

		}

		int deltemp2 = temp2, deltemp4 = temp4, deltemp8 = temp8;
		//cout << "test1\n";
		int expected_cycles = total_cycles/5;
		// sorts the mem array by cycles from low to high
		bubbleSort(array2,temp2);
		bubbleSort(array4,temp4);
		bubbleSort(array8,temp8);
		// adds memory greater than 4 GB to process 4
		int k = 0, l = 0, m = 0;
		//add all processes > 4GB to proc 4
		for(int i = 0; i < temp8; i++)
		{
			processor[4].addProcess(array8[i]);
		}
		//add all processes > 2GB to proc 2 and 3
		bool swap = true;
		for(int i = 0; i < temp4; i++)
		{
			if(swap)
			{
				processor[3].addProcess(array4[i]);
				swap = false;
			}
			else
			{
				processor[2].addProcess(array4[i]);
				swap = true;
			}
		}
		swap = true;
		//add remaining processes to proc 0 and 1
		for(int i = 0; i < temp2;i++)
		{
			if(swap)
			{
				processor[1].addProcess(array2[i]);
				swap = false;
			}
			else
			{
				processor[0].addProcess(array2[i]);
				swap = true;
			}
		}


		std::cout<<"Total Cycles\t: "<<total_cycles<<"\n";
		std::cout<<"Ideal Exec Time\t: "<<total_cycles/5<<"\n";
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
	
		//cleanup 
		for(int i = 0; i < 2; i++)
			processor[i].wipe();
		for(int i = 0; i < ARRAY_SIZE;i++)
		{
			delete proc_array[i];
		}
	}
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
//sort processes on memory
void bubbleSortM(Process ** array, int size)
{
	int max = 0;
        int i , j;
        for(i = 0; i < size - 1; i++)
        {
                for(j = 0; j < size-i-1;j++)
                {
                        if(array[j]->getMemory() > array[j+1]->getMemory())     //swap
                        {
                                Process * temp_proc = array[j];
                                array[j] = array[j+1];
                                array[j+1] = temp_proc;
                        }
                }
        
	
        
	}
// cout << "\n Largest Memomry process: " << max << "\n";

}

