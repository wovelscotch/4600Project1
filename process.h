//process class
class Process
{
	private:
		int id;		//process id
		long long int cycles;	//number of cycles to compelete
		int memory;	//memory requirement 
		long long int wait;	//number of cycles it has to wait
	public:
		//sets and gets
		int getId(){return id;}
		void setId(int inp){id = inp;}

		long long getCycles(){return cycles;}
		void setCycles(long long int inp){cycles = inp;}
		void decCycles(){cycles--;}

		int getMemory(){return memory;}
		void setMemory(int inp){memory = inp;}

		long long int getWait(){return wait;}
		void setWait(long long int inp){wait = inp;}
		void incWait(){wait++;}
		//constructors 
		Process()
		{
			id = cycles = memory = wait = 0;
		}
		
		Process(int c,int m)
		{
			id = wait = 0;
			cycles = c;
			memory = m;
		}
	
		Process(int i, int c, int m)
		{
			wait = 0;
			id = i;
			cycles = c;
			memory = m;
		}
};
