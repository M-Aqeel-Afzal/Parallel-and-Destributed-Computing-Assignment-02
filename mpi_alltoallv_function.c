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
  int data[8][12]={{1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,2,2,2,2,2,2},
		{3,3,3,3,3,3,3,3,3,3,3,3},
		{4,4,4,4,4,4,4,4,4,4,4,4},
		{5,5,5,5,5,5,5,5,5,5,5,5},
		{6,6,6,6,6,6,6,6,6,6,6,6},
		{7,7,7,7,7,7,7,7,7,7,7,7},
		{8,8,8,8,8,8,8,8,8,8,8,8}};
	int *sdata = (int*) malloc(10*sizeof(int));

int sendcount[8]={1,2,3,1,1,1,1,2};
int indexs[8]={0,1,3,6,7,8,9,10};
  int *all_rec = (int*) malloc(sendcount[rank]+12*sizeof(int));
printf("process %d has:",rank);
for(int i=0;i<12;i++)
printf("%d  ",data[rank][i]);
printf("\n");
for( int i=0,k=8;i<8;i++,k--)
	 {	
	for(int j=indexs[i];j<(indexs[i]+sendcount[i]);j++)
		sdata[j]=data[rank][j];
		if(i!=rank)
		MPI_Send(sdata, sendcount[i], MPI_INT,i, 20, MPI_COMM_WORLD);
	 }

	for(int j=0,k=0;j<8;j++)
	{
  int *rdata = (int*) malloc(sendcount[j]*sizeof(int));

		if(j!=rank)
		{
			MPI_Recv(rdata, sendcount[rank], MPI_INT, j, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			
		for(int m=0;m<sendcount[j];m++,k++)
		all_rec[k]=rdata[m];
			
		} else 
			all_rec[j]=data[j][0];
	}
printf("Now process %d has:",rank);
for(int i=0;i<(sendcount[rank]+12);i++)
printf("%d  ",all_rec[i]);
	

printf("\n");
MPI_Finalize();
}

