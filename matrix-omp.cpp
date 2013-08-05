/***********************************************************************
* Program:
*    Lab OpenMPmatrixMult
*    Brother Jones, CS 345
* Author:
*    Tyler Jones
* Summary:
*    This program multiplies two included matricies using OpenMP.
* Conclusions:
*    This program is easier than the trap-omp.cpp program.
*    I simply replaced what my pthreads were doing with openmp.
************************************************************************/
#include <iostream>
#include <pthread.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define M 5 // number of rows in matrix A
#define K 6 // number of rows in matrix B -- number of columns in matrix A
#define N 8 // number of columns in matrix B
// [5 x 6] * [6 x 8] = [5 x 8]

// result matrix
static int C [M][N];

// [rows][columns]
// first matrix
int A [M][K] = { {1,4,3,7,9,1}, 
                 {2,5,4,8,6,3}, 
                 {3,6,5,8,2,3},
                 {3,8,8,1,4,1}, 
                 {1,5,4,5,7,9} };
// second matrix
int B [K][N] = { {1,5,6,5,7,9,8,2}, 
                 {1,2,3,5,5,6,7,8}, 
                 {3,5,9,7,3,1,4,1},
                 {8,3,1,2,6,5,2,4}, 
                 {3,8,8,1,4,1,3,3}, 
                 {8,7,6,5,4,3,2,1} };

/* structure for passing data to threads */
struct ThreadData
{
  int row;
  int column;
};

/* multiplier method */
void multi_matrix(int i, int j){
  C[i][j]=0;
  for(int p=0;p<K;++p){
    C[i][j]=C[i][j]+( A[i][p] * B[p][j] );
  }
}

/* prints out the result matrix C */
void print_result(){
  cout << "The product of matrices A and B is:";
  for(int i=0;i<M;++i)
  {
    cout << endl;
    for(int j=0;j<N;++j)
      cout << setw(8) << C[i][j];
  }
  cout << endl;
}

int main(int argc, char** argv)
{
  int threadct = 1; /* number of threads to use */
  /* parse command-line arg for number of threads */
  if (argc > 1)
    threadct = atoi(argv[1]);

  #ifdef _OPENMP
    cout << "OMP defined, threadct = " << threadct << endl;
  #else
    cout << "OMP not defined" << endl;
  #endif

  int i=0;
  int j=0;


  for(i=0;i<M;++i)
  {
    for(j=0;j<N;++j)
    {
      #pragma omp parallel
      {
        multi_matrix(i,j);
      }
    }
  }

  print_result();
  return 0;
};


































