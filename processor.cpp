//processor.cpp


#include "processor.h"

Processor::Processor()
{
	memory = 0;
	clock = 0;
	process_list_size = ARRAY_SIZE/5;
	process_count = 0;
	process_list = new Process*[process_list_size];
	cycle_count = 0;
}
Processor::Processor(int m ,int c)
{
	memory = m;
	clock = c;
	cycle_count = 0;
	process_list_size = ARRAY_SIZE/5;
	process_count = 0;
	process_list = new Process*[process_list_size];
	
}

Processor::~Processor()
{
	delete[] process_list;
}
//adds process to process_list
void Processor::addProcess(Process * inp)
{
	//add to array
	process_list[process_count] = inp;
	//set wait time for process
	process_list[process_count]->setWait(cycle_count);
	process_count++;
	//increase total cycle count
	cycle_count += inp->getCycles();
	//check if resize needed
	if(process_count == process_list_size)
	{
		process_list_size += ARRAY_SIZE;
		int old_size = process_list_size;
		Process ** new_array = new Process*[process_list_size];
		
		for(int i = 0; i < old_size; i++)
		{
			new_array[i] = process_list[i];	
		}
		delete[] process_list;
		process_list = new_array;
	}
		
}

//fetches process from process_list at indicated position
Process * Processor::getProcess(int inp)
{
	return process_list[inp];
}

//deletes process from process_list
void Processor::delProcess(int inp)
{
	cycle_count -= process_list[inp]->getCycles();
	process_list[inp] = NULL;
	process_count--;
}

void Processor::wipe()
{
	for(int i = 0; i < process_list_size;i++)
		process_list[i] = NULL;
	cycle_count = 0;
	process_count = 0;
}
