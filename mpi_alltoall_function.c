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
  int data[8][8]={{1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,2,2},
		{3,3,3,3,3,3,3,3},
		{4,4,4,4,4,4,4,4},
		{5,5,5,5,5,5,5,5},
		{6,6,6,6,6,6,6,6},
		{7,7,7,7,7,7,7,7},
		{8,8,8,8,8,8,8,8}};
  int *sdata = (int*) malloc(8*sizeof(int));
  int *rdata = (int*) malloc(8*sizeof(int));
  int *all_rec = (int*) malloc(8*sizeof(int));
printf("process %d has:",rank);
for(int i=0;i<8;i++)
printf("%d  ",data[rank][i]);
printf("\n");
for( int i=0,k=8;i<8;i++,k--)
	 {	
		if(i!=rank)
		MPI_Send(&data[rank][i], 1, MPI_INT, i, 20, MPI_COMM_WORLD);
	 }

	for(int j=0;j<8;j++)
	{
		if(j!=rank)
		{
			MPI_Recv(&rdata, 1, MPI_INT, j, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			all_rec[j]=rdata;
			
		} else 
			all_rec[j]=data[rank][j];
	}
printf("Now process %d has:",rank);
for(int i=0;i<8;i++)
printf("%d  ",all_rec[i]);
	

printf("\n");
MPI_Finalize();
}

