#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream> 

using namespace std;

 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); } 

void tabulador(int p, int ys){
	int x=0;
	int y=0;
	int i=0, num_procesos=0;
	num_procesos=p;
	y=ys;
	gotoxy(x,y);
	//IMPRIMIENDO TABULADOR PRINCIPAL POR CASOS
	
	printf("[    NULOS    ][     NUEVOS   ][     LISTOS   ][   EJECUCION ][ BLOQUEADOS ][  SUSPENDIDOS  ][  TERMINADOS  ][   BORRADOS  ]\n"); // 01
	printf("[      0      ][       1      ][       2      ][       3     ][     4      ][       5       ][      6       ][      7      ]\n"); // 01
	for(int i=0;i<=(num_procesos);i++){	
	printf("[      *      ][       *      ][       *      ][       *     ][     *      ][       *       ][      *       ][      *      ]\n"); // 02
	}
}

void transiciones(int no_procesos, int idproceso, int prioridad, int interrupcion, int renglon){
int intr=0;
int x, y, id, input, io[100];
input=no_procesos;
id=idproceso;
intr=interrupcion;
int i,j;
int xs=7, ys=0;
		
			ys=renglon;
			
			if (intr==0){
				for(i=0;i<4;i++){
					gotoxy(xs,ys);
					Sleep(2400);
					printf("%d",id);
					gotoxy(xs,ys);
		 			Sleep(2400);
		 			printf("*");
		 			xs=xs+16;
						if(i==3){
							gotoxy(xs+29,ys);
							Sleep(2400);
							printf("%d",id);
							gotoxy(100,ys);
			 				Sleep(2400);
			 				printf("*");
							gotoxy(116,ys);
							Sleep(2400);
							printf("%d",id);	
					}
				}	
			}
			else {
				if (intr==1){
					for(i=0;i<4;i++){
					gotoxy(xs,ys);
					Sleep(2400);
					printf("%d",id);
					gotoxy(xs,ys);
		 			Sleep(2400);
		 			printf("*");
		 			xs=xs+16;
		 				if(i==3){
							gotoxy(68,ys);
							Sleep(2400);
							printf("%d",id); // BLOQUEADO
							gotoxy(68,ys);
			 				Sleep(2400);
			 				printf("*"); // * BLOQUEADO
							gotoxy(39,ys);
							Sleep(2400);
							printf("%d",id); //LISTO
							gotoxy(39,ys);
			 				Sleep(2400);
			 				printf("*"); // listo con  el *	 --- ejecucion -suspendido -listo-ejecucion-terminado-borrado
			 				gotoxy(55,ys);
							Sleep(2400);
							printf("%d",id); // VALOR EJECUTANDOSE
							gotoxy(55,ys);
							Sleep(2400);
							printf("*"); // * EJECUTANDOSE 	
							gotoxy(84,ys);
							Sleep(2400);
							printf("%d",id); // VALOR SUSPENDIDO
							gotoxy(84,ys);
							Sleep(2400);
							printf("*"); // * SUSPENDIDO
							gotoxy(39,ys);
							Sleep(2400);
							printf("%d",id); // VALOR LISTO DESDE SUSPENDIDO
							gotoxy(39,ys);
							Sleep(2400);
							printf("*"); // * LISTO DESDE SUSPENDIDO
							gotoxy(55,ys);
							Sleep(2400);
							printf("%d",id); // VALOR EN EJECUTANDOSE 2DA RONDA
							gotoxy(55,ys);
							Sleep(2400);
							printf("*"); // * EJECUTANDOSE
							gotoxy(100,ys);
							Sleep(2400);
							printf("%d",id); // VALOR EN TERMINADO 2DA RONDA
							gotoxy(100,ys);
							Sleep(2400);
							printf("*"); // * TERMINADO
							gotoxy(116,ys);
							Sleep(2400);
							printf("%d",id); // VALOR EN TERMINADO 2DA RONDA*/							
					}
			}			
			}
	}
	ys=ys+1;
}

/* INICIO FUNCIONES PARA ROUND ROBIN */
void findWaitingTimeRR(int id[], int n, int bt[], int wt[], int quantum) // FUNCION PARA ENCONTRAR EL TIEMPO DE ESPERA EN EL ALGORITMO ROUND ROBIN
{ 
	// Mhace copia de los burst times bt[] para almacenar lo restante
	// burst times. 
	int rem_bt[n]; 
	for (int i = 0 ; i < n ; i++) 
		rem_bt[i] = bt[i]; 

	int t = 0; // tiempo actual

	// Sigue atravesando los procesos de a manera RR
	// hasta que no esten terminados
	while (1) 
	{ 
		bool done = true; 

		// atraviesa todos los procesos uno x uno repetidamente
		for (int i = 0 ; i < n; i++) 
		{ 
			// Si burst time del proceso es mayor a 0
			// entonces solo es necesario seguir procesando 
			if (rem_bt[i] > 0) 
			{ 
				done = false; // Hay proceso pendiente

				if (rem_bt[i] > quantum) 
				{ 
					// Incrementa el valor de t es decir
					// por cuanto tiempo han sido procesados los procesos
					t += quantum; 
					// Decrementa burst_time del proceso actual
					// por quantum
					rem_bt[i] -= quantum; 
				} 
				// Si burst time es menor or equal que el
				// quantum. El ultimo proceso del ciclo es ejecutado
				else
				{ 
					// Incrementa el valor de t, es decir, muestra
					// cuánto tiempo se ha procesado un proceso	
					t = t + rem_bt[i]; 

					// Waiting time es tiempo actual menos el tiempo 
					// used by this process 
					wt[i] = t - bt[i]; 

					// A medida que el proceso se ejecuta por completo
					// hace que su tiempo de ráfaga restante(bt) = 0 
					rem_bt[i] = 0; 
				} 
			} 
		} 
		// Si todos los procesos han terminado
		if (done == true) 
		break; 
	} 
} 

void findTurnAroundTimeRR(int id[], int n, int bt[], int wt[], int tat[]) // FUNCION PARA ENCONTRAR EL TAT EN EL ALGORITMO ROUND ROBIN
{ 
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < n ; i++) 
		tat[i] = bt[i] + wt[i]; 
} 

void findavgTimeRR(int id[], int n, int bt[], int quantum) // FUNCION PARA ENCONTRAR EL TIEMPO PROMEDIO DE EJECUCION EN EL ALGORITMO ROUND ROBIN
{ 
	int wt[n], tat[n], total_wt = 0, total_tat = 0; 

	// Function to find waiting time of all processes 
	findWaitingTimeRR(id, n, bt, wt, quantum); 

	// Function to find turn around time for all processes 
	findTurnAroundTimeRR(id, n, bt, wt, tat); 

	printf("\nALGORITMO POR ROUND ROBIN\n");
	printf("\nSON %d PROCESOS\n",n);

	// Display processes along with all details 
	cout << "PROCESOS "<< " BURST TIME "
		<< " TIEMPO DE ESPERA " << " TURN AROUND TIME\n"; 

	// Calculate total waiting time and total turn 
	// around time 
	for (int i=0; i<n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< wt[i] <<"\t\t " << tat[i] <<endl; 
	} 
	cout << "TIEMPO DE ESPERA PROMEDIO = "
		<< (float)total_wt / (float)n; 
	cout << "\nTURN AROUND TIME PROMEDIO = "
		<< (float)total_tat / (float)n; 
}
//FIN FUNCIONES PARA ROUND ROBIN

//INICIO FUNCIONES POR PRIORIDAD
priority_algorithm(int id[], int nprocesos, int bt[], int pr[]){
	

	
	printf("\nALGORITMO POR PRIORIDAD\n");
	
	
	int bts[20],p[20],wt[20],tat[20],prs[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
	n=nprocesos;
	for(i=0;i<n;i++)
    {
	bts[i]=bt[i];
	prs[i]=pr[i];
	p[i]=id[i];
	p[i]=i+1; 
	}
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%d",avg_wt);
    printf("\nAverage Turnaround Time=%d\n",avg_tat);
}
 //FIN POR PRIORIDAD
  	// ALGORITMO FCFS
  	
  	// Function to find the waiting time for all processes
int waitingtime(int proc[], int n, int burst_time[], int wait_time[]) {
   // waiting time for first process is 0
   wait_time[0] = 0;
   // calculating waiting time
   for (int i = 1; i < n ; i++ )
   wait_time[i] = burst_time[i-1] + wait_time[i-1] ;
   return 0;
}
// Function to calculate turn around time
int turnaroundtime(int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   int i;
   for ( i = 0; i < n ; i++)
   tat[i] = burst_time[i] + wait_time[i];
   return 0;
}

//Function to calculate average time
int avgtime( int proc[], int n, int burst_time[]) {
	
int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
int i;
   //Function to find waiting time of all processes
   waitingtime(proc, n, burst_time, wait_time);
   //Function to find turn around time for all processes
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   
   printf("\nFirst come First Serve\n");
   //Display processes along with all details
   printf("PROCESOS	BURST	WAITING TURN AROUND \n"); //
   // Calculate total waiting time and total turn
   // around time
   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t  %d\t\t %d \t%d\n", i+1, burst_time[i], wait_time[i], tat[i]);
   }
   printf("TIEMPO DE ESPERA PROMEDIO = %f\n", (float)total_wt / (float)n);
   printf("TIEMPO PROMEDIO DE TURN AROUND = %f\n", (float)total_tat / (float)n); 
   return 0;
}
	/*
	round_robin_algorithm();{
	
	}
	
	priority_algorithm(){
		
	}

	fcfs_algorithm(){
		
	}
*/
main(){
		
	int nprocesos;
	int i, mt, ys;
	int id[10], at[10], bt[10], burst[10], pr[10], io[10];
	
// VARIABLES
// CONTADORES POR COLA
int cntq1=0, cntq2=0, cntq3=0;

// VARIABLES PARA LOS PROCESOS

int id1[10], at1[10], bt1[10], burst1[10], pr1[10], io1[10];
int id2[10], at2[10], bt2[10], burst2[10], pr2[10], io2[10];
int id3[10], at3[10], bt3[10], burst3[10], pr3[10], io3[10];

// VARIABLES PARA ALGORITMO ROUND ROBIN
int n = sizeof id / sizeof id[0];
int quantum = 4;
//
		
		printf("\n MODO MANUAL \n\n");
		
		// INGRESAS CUANTOS PROCESOS DESEA TRABAJAR.
		printf("CUANTOS PROCESOS DESEA CAPTURAR ? : ");
		scanf("%d",&nprocesos);


		for(i=0;i<nprocesos;i++) {
		 			
			gotoxy(0,5);
			id[i]=i+1;
			printf("\nTIEMPO DE LLEGADA DEL PROCESO P%d :  ",i+1); 
			scanf("%d",&at[i]);
			printf("\nTIEMPO DE EJECUCION DEL PROCESO P%d :",i+1); 
			scanf("%d",&bt[i]);
			burst[i]=bt[i];
			printf("\nPRIORIDAD DEL PROCESO P%d : ",i+1); 
			scanf("%d",&pr[i]);
			printf("\nREQUIERE ALGUNA E/S? (1/YES 0/NO) : "); 
			scanf("%d",&io[i]);
			
				// CUENTA CUANTOS PROCESOS HAY DE CADA TIPO O COLA.
						
						if (pr[i]==(1)){ // Cola 1, Round Robin
						cntq1=cntq1+1;
						id1[i]=id[i];
						at1[i]=at[i];
						bt1[i]=bt[i];
						pr1[i]=pr[i];
						io1[i]=io[i];
					
						}
						
						if (pr[i]==(2)){ // Cola 2, Priority
						cntq2=cntq2+1;
						id2[i]=id[i];
						at2[i]=at[i];
						bt2[i]=bt[i];
						pr2[i]=pr[i];
						io2[i]=io[i];
					
						}
						
						if (pr[i]==(3)){// Cola 1, FCFS
						cntq3=cntq3+1;
						id3[i]=id[i];
						at3[i]=at[i];
						bt3[i]=bt[i];
						pr3[i]=pr[i];
						io3[i]=io[i];
					
						}
	          
		}
			printf("\nDESEA VER LAS TRANSICIONES DE LOS PROCESOS (1/SI 0/NO)?: "); 
			scanf("%d",&mt);
	
		if (mt==1){				
		// PARA MOSTRAR LOS MOVIMIENTOS DE ESTADO PARA CADA PROCESO.
			tabulador(nprocesos,17);
			i=0;
			ys=ys+2;
			for(i=0;i<nprocesos;i++) { 
			transiciones(nprocesos,id[i],pr[i],io[i],ys+16);
			ys=ys+1;
			}
		}
			// MUESTRA UN BREVE RESUMEN DE LOS PROCESOS POR COLA.
			gotoxy(2,25);
			printf("EL ANALISIS INDICA: Son %d Procesos, de los Cuales : %d Procesos en Cola 1, %d Procesos en Cola 2, %d Procesos en Cola 3\n",nprocesos,cntq1,cntq2,cntq3);
								
			// REPORTES POR ALGORITMOS.
			if (cntq1>0){
				//round_robin_algorithm();
				findavgTimeRR(id, nprocesos, bt, quantum); // MANDAMOS LLAMAR LA FUNCION DE BUSCA TIEMPO PROMEDIO DE EJECUCION PARA CALCULAR POR ROUND ROBIN
				//findavgTimeRR(id1, cntq1, bt1, quantum);
			}
			
			if (cntq2>0){
				//priority_algorithm();
				//priority_algorithm(id2, cntq2, bt2, pr2); // MANDAMOS LLAMAR LA FUNCION DE ALGORITMO POR PRIORIDAD
				 priority_algorithm(id, nprocesos, bt, pr);	
				 	 	 
			}
			
			if (cntq3>0){
   					//fcfs_algorithm();
				   //avgtime(id3, cntq3, bt3); // MANDAMOS LLAMAR LA FUNCION DE ALGORITMO POR FCFS
				   avgtime(id, nprocesos, bt);
			} // FIN REPORTE DE ALGORITMOS					
				
}
