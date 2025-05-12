#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <mpi.h>
}

int main(int argc, char *argv[]) {
  int rank, size, N = 100;
  int local_sum = 0, global_sum = 0;
  int start, end;
  
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // Dividir el trabajo entre los procesos
  int range = N / size;
  start = rank * range + 1;
  end = (rank == size - 1) ? N : (rank + 1) * range;
  // Cada proceso calcula su suma local
  for (int i = start; i <= end; ++i) {
    local_sum += i;
  }
  // Reducir las sumas locales a la suma global
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  // Imprimir la suma global en el proceso maestro (rank 0)
  if (rank == 0) {
    std::cout << "La suma de los números enteros de 1 a " << N << " es " << global_sum << std::endl;
  }

  // Finalizar MPI
  MPI_Finalize();
  
  
void backtracking(int matrix[MAX_N][MAX_N], int n, int current, int end, int dist, int *minDist, int visited[]){
    if (current == end){
        if(dist < *minDist){
            *minDist = dist;
        }
        return;
    }
    for (int i=0; i < n; i++){
        if(matrix[current][i]!=0 && visited[i] == 0){
            visited[i] = 1;
            backtracking(matrix, n, i, end, dist+matrix[current][i], minDist, visited);
            visited[i] = 0;
        }
    }
}

void limpiarVisitados(int visited[MAX_N]){
    for(int i=0; i < MAX_N; i++ ){
        visited[i] = 0;
    }
}

void limpiarMatrix(int matrix[MAX_N][MAX_N], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matrix[i][j] = 0;
        }
    }
}

void mostrarMatrix(int matrix[MAX_N][MAX_N], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}



void tsp(int curr_pos, int count, int cost, bool visited[], int &min_path, int dist[N][N]){

      if(count == N && dist[curr_pos][0]){

          min_path = std::min(min_path, cost + dist[curr_pos][0]);

          return;

      }

      for(int i=0; i<N; i++) {

          if(!visited[i] && dist[curr_pos][i]){

                 visited[i] = true;

                 tsp(i, count+1, cost + dist[curr_pos][i], visited, min_path, dist);

                 visited[i] = false;

          }

     }

}


void llenarMatrix(int matrix[MAX_N][MAX_N], int n){
    for(int i=0; i< n; i++){
        for(int j=0; j< n; j++){
            if(!(matrix[j][i]== INF && matrix[j][i] == INF)){
                matrix[i][j] = rand() % 10 - 1;
                matrix[j][i] = matrix[i][j];
                if(i == j){
                    matrix[i][j] = 0;
                }
                if(matrix[i][j] == -1){
                    matrix[i][j] = INF;
                    matrix[j][i] = INF;
                }
            } else {
                matrix[i][j] = INF;
                matrix[j][i] = INF;
            }
        }
    }    
}

int main(void) {
    int matrix[MAX_N][MAX_N];
    int visited[MAX_N];
    int start=0;
    int end=0;
    int dist=0;
    int minDist = INF;
    clock_t inicio, fin;
    double time_ms;
    
    

int local_min = INF;
for(int i=1 + rank; i < N; i += size){
      bool visited[N] = {false};
      visited[0] = true; // Test que parta en ciudad 0;
      visited[1] = true;
      tsp(i, 2, dist[0][i], visited, local_min, dist);

}

    for (int n =2 ; n <= MAX_N; n++){
        limpiarMatrix(matrix, n);
        minDist = INF;
        printf("Matrix %dX%d \n", n, n);
        srand((unsigned)time(NULL));
        inicio = clock();
        llenarMatrix(matrix, n);
        limpiarVisitados(visited);
        mostrarMatrix(matrix, n);
        start = rand() % n;
        end = rand() % n;
        printf("Origen: %d\n", start);
        printf("Destino: %d\n", end);
        backtracking(matrix, n, start, end, dist, &minDist, visited);
        fin = clock();
        time_ms = ((double)(fin-inicio)/CLOCKS_PER_SEC)*1000;
        printf("Matrix %dX%d Tiempo : %.2f milisegundos\n", n,n, time_ms);
        
        int local_min = INF;
        for(int i=1 + rank; i < N; i += size){
              bool visited[N] = {false};
              visited[0] = true; // Test que parta en ciudad 0;
              visited[1] = true;
              tsp(i, 2, dist[0][i], visited, local_min, dist);
        }
  
    }
    
      MPI_Finalize();

    return 0;
}
