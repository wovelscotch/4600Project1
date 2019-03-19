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
		}
		//=========================DELETE============================================
		std::ofstream pfile;
		pfile.open("procs.txt");
		for(int i = 0; i < ARRAY_SIZE;i++)
			pfile<<proc_array[i]->getId()<<"\t"<<proc_array[i]->getCycles()<<"\t"<<proc_array[i]->getMemory()<<"\n";
		pfile.close();
		//===========================================================================	
		//sort array by cycles, more likely to distribute evenly
		bubbleSortM(proc_array,ARRAY_SIZE);// sorts array by memory size
		pfile.open("pprocs.txt");
		for(int i = 0; i < ARRAY_SIZE;i++)
			pfile<<proc_array[i]->getId()<<"\t"<<proc_array[i]->getCycles()<<"\t"<<proc_array[i]->getMemory()<<"\n";
		pfile.close();
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
		//DELETE
		//=================================================
		std::ofstream arrfile;
		arrfile.open("2.txt");
		for(int i = 0; i < temp2; i++)
		{
			arrfile<<array2[i]->getId()<<"\t"<<array2[i]->getMemory()<<"\n";
		}
		arrfile.close();
		arrfile.open("4.txt");
		for(int i = 0; i <temp4; i++)
		{
			arrfile<<array4[i]->getId()<<"\t"<<array4[i]->getMemory()<<"\n";
		}
		arrfile.close();
		arrfile.open("8.txt");
		for(int i = 0; i <temp8; i++)
		{
			arrfile<<array8[i]->getId()<<"\t"<<array8[i]->getMemory()<<"\n";
		}
		arrfile.close();


		//==================================================
		int deltemp2 = temp2, deltemp4 = temp4, deltemp8 = temp8;
		//cout << "test1\n";
		int expected_cycles = total_cycles/5;
		// sorts the mem array by cycles from low to high
		bubbleSort(array2,temp2);
		bubbleSort(array4,temp4);
		bubbleSort(array8,temp8);
		// adds memory greater than 4 GB to process 4
		int k = 0, l = 0, m = 0;
		while(processor[4].getCycleCount() < expected_cycles){
			processor[4].addProcess(array8[k]);
		}

                //cout << "test2\n";

		// adds memory between 2-4GB to processes 3,2
		while( ( processor[3].getCycleCount()< expected_cycles) || (processor[2].getCycleCount()  < expected_cycles)){
			bool t = false;
			if(t == false){
	                        processor[3].addProcess(array4[l]);
                                temp4--;
                                if(processor[2].getCycleCount() < expected_cycles)
                                        t = true;
                                else
                                        t = false;

			}
			if( t == true){
	                        processor[2].addProcess(array4[l]);
                                temp4--;
                                if(processor[3].getCycleCount() < expected_cycles)
                                        t = false;
                                else
                                        t = true;

			}
		}
                //cout << "test3\n";

		// adds mem less than 2gb to process 1, 0
	         while( ( processor[1].getCycleCount() < expected_cycles)|| (processor[0].getCycleCount() )< expected_cycles){
                        bool t = false;
			
                        if(t == false){
                                processor[1].addProcess(array2[m]);
				temp2--;
				if(processor[0].getCycleCount() < expected_cycles)
                                	t = true;
				else
					t = false;
                        }
                        if( t == true){
                                processor[0].addProcess(array2[m]);
				temp2--;
				if(processor[1].getCycleCount() < expected_cycles)
                                	t = false;
				else
					t = true;
                        }
                }
                //cout << "test4\n";
		cout << temp2 <<"\n" << temp4;
		// check list size for any remaining processes and distribute them randomly
		int w = 0, x = 0;
                while(temp4 > 0){
			
			int y = getRand(2,4);
                        processor[y].addProcess(array4[w]);
			temp4--;
                }
                while(temp2 > 0){
			int z = getRand(0,4);
                        processor[z].addProcess(array2[x]);
			temp2--;
                }


                //cout << "test5\n";


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
		for(int i = 0; i < 2; i++)
			processor[i].wipe();
		for(int i = 0; i < ARRAY_SIZE;i++)
		{
			delete proc_array[i];
		}
		for(int i = 0; i < deltemp2;i++)
                {
                        delete array2[i];
                }
                for(int i = 0; i < deltemp4;i++)
                {
                        delete array4[i];
                }
                for(int i = 0; i < deltemp8;i++)
                {
                        delete array8[i];
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

