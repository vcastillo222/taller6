
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


int local_min = INF;
for(int i=1 + rank; i < N; i += size){
      bool visited[N] = {false};
      visited[0] = true; // Test que parta en ciudad 0;
      visited[1] = true;
      tsp(i, 2, dist[0][i], visited, local_min, dist);

}


        
        int local_min = INF;
        for(int i=1 + rank; i < N; i += size){
              bool visited[N] = {false};
              visited[0] = true; // Test que parta en ciudad 0;
              visited[1] = true;
              tsp(i, 2, dist[0][i], visited, local_min, dist);
        }
