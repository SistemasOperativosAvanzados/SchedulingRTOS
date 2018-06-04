#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct t{
	char task[25];
	int ejecutionTime;
	int period;
	int isActive;
	int stillRunning;
	int times;
	int remaining;

};

struct g{
	int *array;
	int arraySize;
};

struct lcm{
	int *number;
	int *howManyTimes;
	int howManyTimesIndex;
};

typedef struct t Table;
typedef struct g Game;
typedef struct lcm LeastCommon;

int RM();
int EDF();
int LLF();
int isSchedulable();
int isSchedulableEDF();
int getLargestPeriod();
Game whoActive();
int getTurn();
int getTurnEDF();
int getTurnLLF();
double U(int n);
int fillBoxes(int turn,int tablePointer);
void drawMatrix(int bound);
int checkDeadlines(int x);
int lcm();
int findExist(int* globalArray,int nTask,int divideby);
void printGlobalArray(int* globalArray,int x);
void fillEjecutionTable();
int checkProcess();




Table* table;
int nTask;
int** ejecutionTable;
int main(){

	// nTask = 3;
	nTask = 3;
	table = calloc(nTask, sizeof(Table));
	// strcpy(table[0].task,"1");
	// table[0].ejecutionTime=4;
	// table[0].period=12;
	// table[0].isActive=1;
	// table[0].times=1;

	// strcpy(table[1].task,"2");
	// table[1].ejecutionTime=1;
	// table[1].period=3;
	// table[1].isActive=1;
	// table[1].times=1;

	// strcpy(table[2].task,"3");
	// table[2].ejecutionTime=2;
	// table[2].period=6;
	// table[2].isActive=1;
	// table[2].times=1;

	strcpy(table[0].task,"1");
	table[0].ejecutionTime=10;
	table[0].period=30;
	table[0].isActive=1;
	table[0].stillRunning=0;
	table[0].times=1;
	table[0].remaining=0;

	strcpy(table[1].task,"2");
	table[1].ejecutionTime=10;
	table[1].period=40;
	table[1].stillRunning=0;
	table[1].isActive=1;
	table[1].times=1;
	table[1].remaining=0;

	strcpy(table[2].task,"3");
	table[2].ejecutionTime=12;
	table[2].stillRunning=0;
	table[2].period=52;
	table[2].isActive=1;
	table[2].times=1;
	table[2].remaining=0;


	// strcpy(table[0].task,"1");
	// table[0].ejecutionTime=3;
	// table[0].period=6;
	// table[0].isActive=1;
	// table[0].stillRunning=0;
	// table[0].times=1;
	// table[0].remaining=0;

	// strcpy(table[1].task,"2");
	// table[1].ejecutionTime=4;
	// table[1].period=9;
	// table[1].stillRunning=0;
	// table[1].isActive=1;
	// table[1].times=1;
	// table[1].remaining=0;

	

	// strcpy(table[0].task,"1");
	// table[0].ejecutionTime=1;
	// table[0].period=6;
	// table[0].isActive=1;
	// table[0].stillRunning=0;
	// table[0].times=1;
	// table[0].remaining=0;

	// strcpy(table[1].task,"2");
	// table[1].ejecutionTime=2;
	// table[1].period=9;
	// table[1].stillRunning=0;
	// table[1].isActive=1;
	// table[1].times=1;
	// table[1].remaining=0;

	// strcpy(table[2].task,"3");
	// table[2].ejecutionTime=6;
	// table[2].period=18;
	// table[2].isActive=1;
	// table[2].stillRunning=0;
	// table[2].times=1;
	// table[2].remaining=0;



	
	//RM();
	//EDF();
	LLF();

	//lcm();



	return 0;
}



int RM(){
	int tableSize=10000;
	ejecutionTable = calloc(nTask,sizeof(int*));
	for (int i = 0; i < nTask; ++i) 
	{
		/* code */
		ejecutionTable[i]= calloc(tableSize,sizeof(int));
	}
	fillEjecutionTable();
	
	//int largestPeriod = getLargestPeriod(table,nTask);

	int isSched = isSchedulable(table,nTask);
	if (isSched){
		printf("The test is schedulable.\n");
	}else{
		printf("The test might not be schedulable.\n");
	}

	printf("Testing...\n");
	int keepGoing = 1;
	int tablePointer=0;
	int extra=0;
	int leastCommonMultiple =lcm();
	printf("lcm %d\n",leastCommonMultiple );
	// while (keepGoing){
	while (tablePointer<leastCommonMultiple){
		int turn = getTurn();
		printf("current turn =%d\n",turn );
		int keep = 1;
		int counter =0;
		//int temp =fillBoxes(turn,tablePointer);
		if (turn !=-1){
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>process turn =  %s\n",table[turn].task );
			printf("turn in program = %d\n",turn );
			printf("stillRunning=%d\n",table[turn].stillRunning);
			printf("remaining=%d\n",table[turn].remaining);
			printf("WE NEED TO DO: %d\n",(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ) );
			for (int i = 0; i < (table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ); ++i)
			{
				
				ejecutionTable[turn][tablePointer] = turn;
				tablePointer++;
				printf("tablepointer = %d\n",tablePointer );
				
				keep = checkDeadlines(tablePointer);
				
				if (keep==1||(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime)==i+1){
					
					
				
					if (i+1==(table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)){
						printf("disabling turn %s\n",table[turn].task);
						table[turn].isActive=0;
						table[turn].stillRunning=0;
						table[turn].remaining=0;
					}else{
						printf("creating remaining\n");
						table[turn].remaining = (table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)-(i+1);
						printf("there is a remaining of %d\n",table[turn].remaining);
						table[turn].stillRunning=1;
						//table[turn].isActive=0;
					}
					for (int x = 0; x < nTask; ++x)
					{
						if (table[x].times*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							table[x].times++;
							int validNotYetDone=checkProcess(x);
							if (validNotYetDone){
								printf("END OF WORK. ATOMIC BOM DETECTED.\n");
								return 0;
							}
						}
					}
					break;
				}else if (keep==-1){
					printf("Failed the test.\n");
					break;
				}
				if (i+1==table[turn].ejecutionTime){
					printf("disabling turn %s\n",table[turn].task);
					table[turn].isActive=0;
				}
			}
			
			printf("tablePointer==%d\n",tablePointer);
			
			// if(tablePointer==leastCommonMultiple){
			// 	keepGoing=0;
			// }

		}else{
	
			int keep=1;
			int blocks=0;
			while (keep){
				printf("idle CPU.\n");
				tablePointer++;
				keep=checkDeadlines(tablePointer);
				
				if (keep==1){
					for (int x = 0; x < nTask; ++x)
					{
						if (table[x].times*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							table[x].times++;
						}
					}
				
					keep=0;
				}

		

			}

		}

			
	}


}

int EDF(){
	int tableSize=10000;
	ejecutionTable = calloc(nTask,sizeof(int*));
	for (int i = 0; i < nTask; ++i) 
	{
		/* code */
		ejecutionTable[i]= calloc(tableSize,sizeof(int));
	}
	fillEjecutionTable();
	
	//int largestPeriod = getLargestPeriod(table,nTask);

	int isSched = isSchedulableEDF(table,nTask);
	if (isSched){
		printf("The test is schedulable.\n");
	}else{
		printf("The test might not be schedulable.\n");
	}

	printf("Testing...\n");
	int keepGoing = 1;
	int tablePointer=0;
	int extra=0;
	int leastCommonMultiple =lcm();
	printf("lcm %d\n",leastCommonMultiple );
	// while (keepGoing){
	while (tablePointer<leastCommonMultiple){
		int turn = getTurnEDF();
		printf("current turn =%d\n",turn );
		int keep = 1;
		int counter =0;
		//int temp =fillBoxes(turn,tablePointer);
		if (turn !=-1){
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>process turn =  %s\n",table[turn].task );
			printf("turn in program = %d\n",turn );
			printf("stillRunning=%d\n",table[turn].stillRunning);
			printf("remaining=%d\n",table[turn].remaining);
			printf("WE NEED TO DO: %d\n",(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ) );
			for (int i = 0; i < (table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ); ++i)
			{
				
				ejecutionTable[turn][tablePointer] = turn;
				tablePointer++;
				printf("tablepointer = %d\n",tablePointer );
				
				keep = checkDeadlines(tablePointer);
				
				if (keep==1||(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime)==i+1){
					
					
				
					if (i+1==(table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)){
						printf("disabling turn %s\n",table[turn].task);
						table[turn].isActive=0;
						table[turn].stillRunning=0;
						table[turn].remaining=0;
						table[turn].times++;
					}else{
						printf("creating remaining\n");
						table[turn].remaining = (table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)-(i+1);
						printf("there is a remaining of %d\n",table[turn].remaining);
						table[turn].stillRunning=1;
						//table[turn].isActive=0;
					}
					for (int x = 0; x < nTask; ++x)
					{
						if ((table[x].times-1)*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							//table[x].times++;
							int validNotYetDone=checkProcess(x);
							if (validNotYetDone){
								printf("END OF WORK. ATOMIC BOM DETECTED.\n");
								return 0;
							}
						}
					}
					break;
				}else if (keep==-1){
					printf("Failed the test.\n");
					break;
				}
				if (i+1==table[turn].ejecutionTime){
					printf("disabling turn %s\n",table[turn].task);
					table[turn].isActive=0;
				}
			}
			
			printf("tablePointer==%d\n",tablePointer);
			
			// if(tablePointer==leastCommonMultiple){
			// 	keepGoing=0;
			// }

		}else{
	
			int keep=1;
			int blocks=0;
			while (keep){
				printf("idle CPU.\n");
				tablePointer++;
				keep=checkDeadlines(tablePointer);
				
				if (keep==1){
					for (int x = 0; x < nTask; ++x)
					{
						if ((table[x].times-1)*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							table[x].times++;
						}
					}
				
					keep=0;
				}

		

			}

		}

			
	}


}

int LLF(){
	int tableSize=10000;
	ejecutionTable = calloc(nTask,sizeof(int*));
	for (int i = 0; i < nTask; ++i) 
	{
		/* code */
		ejecutionTable[i]= calloc(tableSize,sizeof(int));
	}
	fillEjecutionTable();
	
	//int largestPeriod = getLargestPeriod(table,nTask);

	int isSched = isSchedulable(table,nTask);
	if (isSched){
		printf("The test is schedulable.\n");
	}else{
		printf("The test might not be schedulable.\n");
	}

	printf("Testing...\n");
	int keepGoing = 1;
	int tablePointer=0;
	int extra=0;
	int leastCommonMultiple =lcm();
	printf("lcm %d\n",leastCommonMultiple );
	// while (keepGoing){
	while (tablePointer<leastCommonMultiple){
		int turn = getTurnLLF();
		printf("current turn =%d\n",turn );
		int keep = 1;
		int counter =0;
		//int temp =fillBoxes(turn,tablePointer);
		if (turn !=-1){
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>process turn =  %s\n",table[turn].task );
			printf("turn in program = %d\n",turn );
			printf("stillRunning=%d\n",table[turn].stillRunning);
			printf("remaining=%d\n",table[turn].remaining);
			printf("WE NEED TO DO: %d\n",(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ) );
			for (int i = 0; i < (table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime ); ++i)
			{
				
				ejecutionTable[turn][tablePointer] = turn;
				tablePointer++;
				printf("tablepointer = %d\n",tablePointer );
				
				keep = checkDeadlines(tablePointer);
				
				if (keep==1||(table[turn].stillRunning?table[turn].remaining: table[turn].ejecutionTime)==i+1){
					

				
					if (i+1==(table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)){
						printf("disabling turn %s\n",table[turn].task);
						table[turn].isActive=0;
						table[turn].stillRunning=0;
						table[turn].remaining=0;
					}else{
						printf("creating remaining\n");
						table[turn].remaining = (table[turn].stillRunning?table[turn].remaining:table[turn].ejecutionTime)-(i+1);
						printf("there is a remaining of %d\n",table[turn].remaining);
						table[turn].stillRunning=1;
						//table[turn].isActive=0;
					}
					for (int x = 0; x < nTask; ++x)
					{
						if (table[x].times*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							table[x].times++;
							int validNotYetDone=checkProcess(x);
							if (validNotYetDone){
								printf("END OF WORK. ATOMIC BOM DETECTED.\n");
								return 0;
							}
						}
					}
					break;
				}else if (keep==-1){
					printf("Failed the test.\n");
					break;
				}
				if (i+1==table[turn].ejecutionTime){
					printf("disabling turn %s\n",table[turn].task);
					table[turn].isActive=0;
				}
			}
			
			printf("tablePointer==%d\n",tablePointer);
			
			// if(tablePointer==leastCommonMultiple){
			// 	keepGoing=0;
			// }

		}else{
	
			int keep=1;
			int blocks=0;
			while (keep){
				printf("idle CPU.\n");
				tablePointer++;
				keep=checkDeadlines(tablePointer);
				
				if (keep==1){
					for (int x = 0; x < nTask; ++x)
					{
						if (table[x].times*table[x].period==tablePointer){
							printf("enabling turn = %s\n",table[x].task);
							table[x].isActive=1;
							table[x].times++;
						}
					}
				
					keep=0;
				}

		

			}

		}

			
	}


}

int checkProcess(int deadline){
	if (table[deadline].stillRunning && table[deadline].isActive){
		return 1;
	}
	return 0;
}

void fillEjecutionTable(){
	for (int i = 0; i < nTask; ++i)
	{
		for (int j = 0; j < 10000; ++j)
		{
			ejecutionTable[i][j]=-1;
		}
	}
}
int lcm(){

	LeastCommon* l = calloc(nTask,sizeof(LeastCommon));
	int globalArray[10];
	int gIndex=0;
	int times=0;
	int result=1;
	int current; 
	int x=1;
	for (int i = 0; i < nTask; ++i){
		
		int number = table[i].period;
		printf("working number outside %d\n",number );
		int divideby=2;
		l[i].number = calloc(x,sizeof(int));
		l[i].howManyTimes=calloc(x,sizeof(int));
		l[i].howManyTimes[x-1]=0;
		//printf("2\n" );
		while (number!=1){
		//	printf("3\n" );
			if (number%divideby==0 && l[i].howManyTimes[x-1]==0){
			//	printf("4\n" );
				l[i].number[x-1]=divideby;
				l[i].howManyTimes[x-1]++;


				int exist = findExist(globalArray,gIndex,divideby);
				printf("exist =%d\n",exist );
				if (!exist){

					globalArray[gIndex]=divideby;
					printGlobalArray(globalArray,gIndex);
					gIndex++;
				}
				number/=divideby;
				printf("working number %d\n",number );
			}else if (number%divideby==0 && l[i].howManyTimes[x-1]!=0){
				//printf("5\n" );
				l[i].howManyTimes[x-1]++;
				number/=divideby;
				printf("working number %d\n",number );
				
			}else{
				//printf("6\n" );
				x++;
				l[i].number =(int*) realloc(l[i].number,sizeof(int)*x);
				l[i].howManyTimes=(int*)realloc(l[i].howManyTimes,sizeof(int)*x);
				l[i].howManyTimes[x-1]=0;
				divideby++;

			}
		}
		l[i].howManyTimesIndex= x;
		x=1;
	}
	printf("gIndex=%d\n",gIndex);
	for (int i = 0; i < gIndex; ++i)
		{
			for (int j = 0; j < nTask; ++j)
			{
				for (int k = 0; k < l[j].howManyTimesIndex; k++)
				{
					if (l[j].number[k]==globalArray[i]){
						current = l[j].howManyTimes[k];
						printf("period=%d number=%d howManyTimes = %d\n",table[j].period,l[j].number[k],l[j].howManyTimes[k]);
						break;
					}
				}
				if (current>times){
 					times=current;
					printf("times = %d\n",times );
				}
			}
			for (int x = 0; x < times; ++x)
			{
				result*=globalArray[i];
			}
			times=0;
		}
	printf("result=%d\n",result );
	return result;
}

void printGlobalArray(int* globalArray,int x){
	for (int i = 0; i <= x; ++i)
	{
		printf("%d ", globalArray[i]);
	}
	printf("\n");

}

int findExist(int* globalArray,int x,int divideby){
	for (int i = 0; i < x; ++i)
	{
		if (globalArray[i]==divideby){
			return 1;
		}
	}
	return 0;
}

void drawMatrix(int bound){


	for (int i = 0; i < nTask; ++i)
	{
		printf("| ");
		for (int j = 0; j < bound; ++j)
		{
			printf("%d |", ejecutionTable[i][j] );
		}
		printf("\n");
	}
}


int checkDeadlines(int x){
	printf("------------------->we are in %d\n",x );
	if (nTask>0){
		for (int i = 0; i < nTask; ++i)
		{
			if ((x)%table[i].period==0){
				printf("there is a deadline\n");
				// if (table[i].stillRunning){
				// 	return -1;
				// }
				return 1;
			}
		}		
	}
	return 0;
}

int fillBoxes(int turn, int tablePointer){
	
	printf("table pointer pointer=>%d\n",tablePointer );
	for (int i = tablePointer; i < table[turn].ejecutionTime ; ++i)
	{
		ejecutionTable[turn][i] = turn;
	}
	return tablePointer + table[turn].ejecutionTime-1;
	
}

double U(int n){
	return n*(pow(2.0,1.0/n)-1.0);
}

int isSchedulable(){
	if (nTask>0){
		double result=0;
		for (int i = 0 ; i <nTask ; i++){
			result+=table[i].ejecutionTime/table[i].period;
		}
		double u = U(nTask);
		printf("u==> %.5f\n", u);
		if (result<=u){
			return 1;

		} 
	}
	return 0;
}

int isSchedulableEDF(){
	if (nTask>0){
		double result=0;
		for (int i = 0 ; i <nTask ; i++){
			result+=table[i].ejecutionTime/table[i].period;
		}

		
		if (result<=1.0){
			return 1;

		} 
	}
	return 0;
}

int getTurn(){
	int l=-1;
	int turnIndex=-1;
	int first=1;
	if (nTask>0){
		
		for (int i = 0; i < nTask; ++i)
		{
			/* code */
			if ((table[i].isActive) && first){
				printf("first time table[%d].times=%d table[%d].period=%d\n",i,table[i].times,i,table[i].period );
				l=table[i].period;
				turnIndex=i;
				first=0;
				printf("shutting first variable\n");
			}else{
				printf("table[%d].period=%d table[%d].times=%d && table[%d].isActive= %d\n",i, table[i].period,i,table[i].times,i,table[i].isActive);
				if ((l>=table[i].period) && (table[i].isActive)){
					printf("changin turn....\n");
					l=table[i].period;
					turnIndex=i;
				}
			}
		}
		return turnIndex;
	}
}

int getTurnEDF(){
	int l=-1;
	int turnIndex=-1;
	int first=1;
	if (nTask>0){
		
		for (int i = 0; i < nTask; ++i)
		{
			/* code */
			if ((table[i].isActive) && first){
				printf("first time table[%d].times=%d table[%d].period=%d\n",i,table[i].times,i,table[i].period );
				l=table[i].period*table[i].times;
				turnIndex=i;
				first=0;
				printf("shutting first variable\n");
			}else{
				printf("table[%d].period=%d table[%d].times=%d && table[%d].isActive= %d\n",i, table[i].period,i,table[i].times,i,table[i].isActive);
				if (l>=table[i].times*table[i].period && (table[i].isActive)){
					printf("changin turn....\n");
					l=table[i].period*table[i].times;
					turnIndex=i;
				}
			}
		}
		return turnIndex;
	}
}

int getTurnLLF(){
	int l=-1;
	int turnIndex=-1;
	int first=1;
	if (nTask>0){
		
		for (int i = 0; i < nTask; ++i)
		{
			/* code */
			if ((table[i].isActive) && first){
				printf("first time table[%d].times=%d table[%d].period=%d\n",i,table[i].times,i,table[i].period );
				l=table[i].period-table[i].ejecutionTime;
				turnIndex=i;
				first=0;
				printf("shutting first variable\n");
			}else{
				printf("table[%d].period=%d table[%d].times=%d && table[%d].isActive= %d\n",i, table[i].period,i,table[i].times,i,table[i].isActive);
				if ((l>=table[i].period-table[i].ejecutionTime) && (table[i].isActive)){
					printf("changin turn....\n");
					l=table[i].period-table[i].ejecutionTime;
					turnIndex=i;
				}
			}
		}
		return turnIndex;
	}
}

Game whoActive(){
	Game g;
	if (nTask>0){
		int index=0;
		int* array=calloc(index+1,sizeof(int));
		for (int i = 0; i < nTask; ++i)
		{
			/* code */
			if (table[i].isActive){
				array[index]=i;
				index++;
				array= realloc(array,(index+1)*sizeof(int));
			}
		}
		g.array = array;
		g.arraySize=index;
		return g;
	}
	return g;
}