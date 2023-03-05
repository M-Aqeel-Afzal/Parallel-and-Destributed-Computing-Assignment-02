#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
  int i, rank, size;
  int root_p = 0;
MPI_Request req;
MPI_Status  st;  
MPI_Init(&argc, &argv) ;
  MPI_Comm_size (MPI_COMM_WORLD,&size);
  MPI_Comm_rank (MPI_COMM_WORLD,&rank);
int data[8]={11,12,13,14,15,16,17,18};
  if (rank != root_p) {     //all processes will send data to root process
    int d=data[rank];
	printf("process %d is sending %d \n",rank,d); 
        MPI_Isend(&d, 1, MPI_INT, root_p, rank, MPI_COMM_WORLD,&req);
     MPI_Wait(&req,&st);
  } else if(rank==root_p) {   //root is receiving data from all pocess
	int rec =0,total=0;
	for(int i=0;i<8;i++)
		{
		if(i!=root_p)
		{
		MPI_Recv(&rec, 1, MPI_INT, i, i, MPI_COMM_WORLD,&st);
		total+=rec;
		}
		else
		total+=data[i];
		}
		printf("\n process %d has calculated the sum: ",rank);
		printf("%d  ",total);
	
  }

printf("\n");
MPI_Finalize();
}

