//processor class
#include <cstdlib>
#include "process.h"	
class Processor
{
	private:
		int memory;			//memory availability of processor
		int clock;			//clock speed of processor
		Process * current_process;	//ptr to currently executing process
		bool is_running;		//true if process is executing
	public:
		//sets and gets
		void setMem(int inp){memory = inp;}
		int getMem(){return memory;}

		void setClock(int inp){clock = inp;}
		int getClock(){return clock;}
		
		//set current, must check mem requirement
		bool setCurr(Process * inp)
		{
			//if mem set to 0, ignore mem requirement
			//if process memory > processor mem then reject
			if(memory == 0||inp->getMem()<memory)
			{
				current_process = inp;
				return true;
			}
			return false;
		}
		Process * getCurr(){return current_process;}
	
		bool getIsRunning(){return is_running;}
		void setIsRunning(bool inp){is_running = inp;}
		//constructors
		Processor()
		{
			memory = 0;
			clock = 0;
			current_process = NULL;
		}
	
		Processor(int m, int c)
		{
			memory = m;
			clock = c;
			current_process = NULL;
		}
		//cycle process
		//returns true if process has cycles left to execute
		//returns false if process has 0 cycles left to execute (is finished)
		bool cycle()
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
};
