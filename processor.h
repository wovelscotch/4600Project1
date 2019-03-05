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
		//constructors
		Processor();
		Processor(int, int);
	
		//sets and gets
		void setMem(int inp){memory = inp;}
		int getMem(){return memory;}

		void setClock(int inp){clock = inp;}
		int getClock(){return clock;}
		
		bool setCurr(Process *);
		Process * getCurr(){return current_process;}
	
		bool getIsRunning(){return is_running;}
		void setIsRunning(bool inp){is_running = inp;}
		
		//processor functions
		bool cycle();
};
