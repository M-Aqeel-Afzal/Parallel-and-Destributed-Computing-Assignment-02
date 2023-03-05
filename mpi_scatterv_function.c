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
	int sendcount[8]={2,3,2,4,1,3,2,4};// send count for each process
	int data[25]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	int displs[8]={0,3,6,9,13,14,18,21};//starting indexs for all proesses

  if (rank == root_p) {     //for root process which will send data to all other process
    int i,j=0;
    for (i = 0; i < 8; i++) {
	int *sdata = (int*) malloc(sendcount[i]*sizeof(int));
      if (i != rank) {
	for(int l=displs[i],k=0;l<displs[i]+sendcount[i];l++,k++)
	sdata[k]=data[l];
        MPI_Send(sdata, sendcount[i], MPI_INT, i, 20, MPI_COMM_WORLD);
      }
    }
printf("process %d has: ", rank);
for(int g =0;g<sendcount[rank];g++)
printf("%d  ",data[g]);
  } else {   //all process except root will receive the data sent by root
    int *rdata = (int*) malloc(sendcount[rank]*sizeof(int));
	MPI_Recv(rdata, sendcount[rank], MPI_INT, 0, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("process %d has: ",rank);
	for(int g=0;g<sendcount[rank];g++)
	printf("%d  ",rdata[g]);
	
  }
printf("\n");
MPI_Finalize();
}

