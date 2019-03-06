//processor.cpp

#include "processor.h"

Processor::Processor()
{
	memory = 0;
	clock = 0;
	process_list = NULL;
	process_list_size = ARRAY_SIZE/5;
	process_count = 0;
}
Processor::Processor(int m ,int c)
{
	memory = m;
	clock = c;
	process_list = NULL;
	process_list_size = ARARY_SIZE/5;
	process_count = 0;
	
}
//adds process to process_list
Processor::addProcess(Process * inp)
{
	//add to array
	process_list[]
}
//fetches process from process_list at indicated position
Processor::getProcess()
{
	
}
//deletes process from process_list
Processor::delProcess()
{
	
}
