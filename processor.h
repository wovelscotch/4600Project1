//processor class
#include <cstdlib>
#include "process.h"

const int ARRAY_SIZE = 200;

class Processor
{
	private:
		int memory;				//memory availability of processor
		int clock;				//clock speed of processor
		long long int cycle_count;		//sum of cycles in process_list
		long long int weighted_cycle_count;	//
		Process ** process_list;		//list of assigned processes
		int process_count;			//amount of processes in list
		int process_list_size;			//size of list, including vacancies 
		long long int expected_weighted_cycle_count;
		
	public:
		//constructors
		Processor();
		Processor(int, int);
		~Processor();

		//sets and gets
		void setMem(int inp){memory = inp;}
		int getMem(){return memory;}

		void setClock(int inp){clock = inp;}
		int getClock(){return clock;}
		
		void setCycleCount(long long int inp){cycle_count = inp;}
		long long int getCycleCount(){return cycle_count;}
		
		void setProcessCount(int inp){process_count = inp;}
		int getProcessCount(){return process_count;}
	
		void setProcessListSize(int inp){process_list_size = inp;}
		int getProcessListSize(){return process_list_size;}

		void setWCycleCount(long long int inp){weighted_cycle_count = inp;}
		long long int getWCycleCount(){return weighted_cycle_count;}

		void setEWCycleCount(long long int inp){expected_weighted_cycle_count = inp;}
		long long int getEWCycleCount(){return expected_weighted_cycle_count;}
		
		void setProcessList(Process ** inp){process_list = inp;}
		Process ** getProcessList(){return process_list;}

		void addProcess(Process*);
		Process * getProcess(int);
		void delProcess(int);
		void wipe();

		void calcExpected(long long int, int);
};
