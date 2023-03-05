
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
  int i, rank, size;
  int root_p = 0;
  MPI_Init(&argc, &argv) ;
  MPI_Comm_size (MPI_COMM_WORLD,&size);
  MPI_Comm_rank (MPI_COMM_WORLD,&rank);

  if (rank == root_p) {     //for root process which will send data to all other process
    int i;
	char sdata[] = "Greeting! From ";
    for (i = 0; i < 8; i++) {
      if (i != rank) {
        MPI_Send(sdata, 14, MPI_CHAR, i, 20, MPI_COMM_WORLD);
      }
	else{

	printf(sdata);
	printf("%d",rank);
	    }
    }
  } else  {   //all process except root will receive the data sent by root
    char rdata[]="";
	MPI_Recv(rdata, 20, MPI_CHAR, 0, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf(rdata);
	printf("%d",rank);
	
  }
printf("\n");
MPI_Finalize();
}



