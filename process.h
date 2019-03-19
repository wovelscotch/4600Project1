//process class
class Process
{
	private:
		int id;		//process id
		long long int cycles;	//number of cycles to compelete
		unsigned long long int memory;	//memory requirement 
		long long int wait;	//number of cycles it has to wait
	public:
		//sets and gets
		int getId(){return id;}
		void setId(int inp){id = inp;}

		long long int getCycles(){return cycles;}
		void setCycles(long long int inp){cycles = inp;}
		void decCycles(){cycles--;}

		long long int getMemory(){return memory;}
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
			setCycles(c);// = c;
			setMemory(m);// = m;
		}
	
		Process(int i, long long int c,long long  int m)
		{
			wait = 0;
			id = i;
                        setCycles(c);// = c;
                        setMemory(m);// = m;
		}
};
