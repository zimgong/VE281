#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

using namespace std;

class ShortestP2P {
  public:
      ShortestP2P() {
        V = 0;
        vector<vector<int>> M;
      }

      ~ShortestP2P() {
        vector<vector<int>>().swap(M);
      }

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph() {
        unsigned int X, Y;
        cin >> X;
        cin >> Y;

        resizeGraph(X);
        
        unsigned int start_node, end_node;
        int weight;

        for (unsigned int i = 0; i < Y; i++)
        {
          cin >> start_node >> end_node >> weight;
          addEdge(start_node, end_node, weight);
        }
        FloydWarshall();
      }

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(int A, int B) {
        auto dist = M[A][B];
        if (dist != INT_MAX)
        {
          cout << dist << endl;
        }
        else
        {
          cout << "INF" << endl;
        }
        return;
      }

  private:
    // internal data and functions.    
    unsigned int V;
    vector<vector<int>> M;

    void resizeGraph(unsigned int V) {
      this->V = V;
      this->M = vector<vector<int>>(V, vector<int>(V, INT_MAX));
      for (unsigned int i = 0; i < V; i++)
      {
            M[i][i] = 0;
      }
      return;
    }

    void addEdge(unsigned int start_node, unsigned int end_node, int weight) {
      M[start_node][end_node] = weight;
      return;
    }

    void FloydWarshall() {
      for (unsigned int k = 0; k < V; k++)
      {
        for (unsigned int i = 0; i < V; i++)
        {
          for (unsigned int j = 0; j < V; j++)
          {
            if (M[i][j] > M[i][k] + M[k][j] && M[i][k] != INT_MAX && M[k][j] != INT_MAX)
            {
              M[i][j] = M[i][k] + M[k][j];
            }
          }
          if (!checkGraphValid(i))
          {
            cout << "Invalid graph. Exiting. " << endl;
            exit(0);
          }
        }   
      } 
      return;
    }

    bool checkGraphValid(const unsigned int i) {
      return (M[i][i] >= 0);
    }
};
