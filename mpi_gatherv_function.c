#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
  int  rank, size;
  int root_p = 0;
MPI_Request req;
MPI_Status st;
  MPI_Init(&argc, &argv) ;
  MPI_Comm_size (MPI_COMM_WORLD,&size);
  MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	int sendcount[8]={2,3,2,4,1,3,2,4};// send count for each process
	int data[25]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	int displs[8]={0,3,6,9,13,14,18,21};//starting indexs for all proesses

  if (rank != root_p) {     //all processes will send variable length data to root
    int i,j=0;
	int *sdata = (int*) malloc(sendcount[rank]*sizeof(int));
	
	for(int l=displs[rank],k=0;l<(displs[rank]+sendcount[rank]);l++,k++)
	sdata[k]=data[l];
        MPI_Isend(sdata, sendcount[rank], MPI_INT, root_p, rank, MPI_COMM_WORLD,&req);
	MPI_Wait(&req,&st);
  } else if (rank==root_p) {   //root will receive
	int *recdata= (int*) malloc(25*sizeof(int));
for (int i = 0; i < 8; i++) {
	int *rdata = (int*) malloc(sendcount[i]*sizeof(int));
      if (i != root_p) {
	MPI_Recv(rdata, sendcount[i], MPI_INT, i, i, MPI_COMM_WORLD,&st);
	for(int l=displs[i],k=0;l<(displs[i]+sendcount[i]);l++,k++)
	recdata[l]=rdata[k];
      }
	else
	{
	for(int l=displs[i],k=0;l<(displs[i]+sendcount[i]);l++,k++)
	recdata[l]=data[k];
	}
    }
	printf("process %d has: ",rank);
	for(int g=0;g<25;g++)
	printf("%d  ",recdata[g]);
	
  }
printf("\n");
MPI_Finalize();
}

