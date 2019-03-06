//processor.cpp

#include "processor.h"

Processor::Processor()
{
	memory = 0;
	clock = 0;
	current_process = NULL;
}
Processor::Processor(int m ,int c)
{
	memory = m;
	clock = c;
	current_process = NULL;
}
//checks if processor meets mem requirements of process
bool Processor::setCurr(Process * inp)
{
	//if mem set to 0, ignore mem requirement
	//if process memory > processor mem then reject
	if(memory == 0||inp->getMemory()<memory)
	{
		current_process = inp;
		return true;
	}
	return false;
}
//cycle process
//returns true if process has cycles left to execute
//returns false if process has 0 cycles left to execute (is finished)
bool Processor::cycle()
{
	if(current_process == NULL)
		return false;
	if(current_process->getCycles() == 0)	//failsafe, probably uneccisary 
		return false;
	current_process->decCycles();		//decrement cycle & of process
	if(current_process->getCycles())	//check if process is finished
	{
		is_running = true;
		return true;
	}
	//process is finished
	is_running = false;		
	return false;
}

//returns true if cycles remain in process, false if else
bool Processor::cycle(int amount)
{
	int cycles;
	if(current_process == NULL)
		return false;
	cycles = current_process->getCycles();	//get remaining cycles from process
	cycles -= amount;			//decrement cycles by input amount
	current_process->setCycles(cycles);	//set new amount to process
	//if no cycles remain, set is_runnning to false
	if(cycles)
		is_running = true;
	else
		is_running = false;
	return is_running;
}
