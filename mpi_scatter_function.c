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
  int data[14]={1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  int sdata[2]={0,0};
  int rdata[2]={0,0};
  if (rank == root_p) {     //for root process which will send data to all other process
    int i,j=0;
	
    for (i = 0; i < 8; i++) {
      if (i != rank) {
	sdata[0]=data[j];
	sdata[1]=data[++j];
	j++;
        MPI_Send(sdata, 2, MPI_INT, i, 20, MPI_COMM_WORLD);
      } else {
	rdata[0]=data[0];
	rdata[1]=data[1];
	printf("process %d has: %d %d ",rank,rdata[0],rdata[1]);
	}
    }
  } else {   //all process except root will receive the data sent by root
    
	MPI_Recv(rdata, 2, MPI_INT, 0, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("process %d has: %d %d ",rank,rdata[0],rdata[1]);
	
  }
printf("\n");
MPI_Finalize();
}

