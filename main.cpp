#include <iostream>
#include <fstream>

using namespace std;

// Number of vertices in the graph
//#define V 6
int V = 0;

// Utility function for matrix
// multiplication
void multiply(int **A, int **B, int **C)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < V; k++)
            {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}


// Utility function to calculate
// trace of a matrix (sum of
// diagonal elements)
int getTrace(int **graph)
{
    int trace = 0;

    for (int i = 0; i < V; i++)
    {
        trace += graph[i][i];
    }

    return trace;
}

//  Utility function for calculating
// number of triangles in graph
int triangleInGraph(int **graph)
{
    int **aux2 = new int*[V];  // int aux2[V][V] to store graph^2
    int **aux3 = new int*[V];  // int aux3[V][V] to store graph^3

    for(int i = 0; i < V; i++)
    {
        aux2[i] = new int[V];
        aux3[i] = new int[V];
    }

    //  Initialising aux
    // matrices with 0
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            aux2[i][j] = aux3[i][j] = 0;

    // aux2 is graph^2 now  printMatrix(aux2);
    multiply(graph, graph, aux2);

    // after this multiplication aux3 is graph^3 printMatrix(aux3);
    multiply(graph, aux2, aux3);

    int trace = getTrace(aux3);
    return trace / 6;
}

int main() {

    // calculate the total run time of the program
    clock_t start, end;
    start = clock();

    int count = 0;  // the total number of triangle in the given graph
    int numVertex = 0;  // the number of vertices in the give graph
    int num=0;

    //read the value of numVertex from data.txt
    ifstream infile;
    infile.open("data.txt");
    infile >> numVertex >> num;

    cout<<"ver:"<<numVertex<<"num: "<<num<<endl;

    V = numVertex;

    // generate the 2-D matrix for the graph
    int **graph = new int*[V];
    for(int i = 0; i < V; i++)
    {
        graph[i] = new int[V];
    }

    // read graph from adjacent matrix
    /*for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            infile>>graph[i][j];
        }
    }*/

    int a, b;
    // read graph from adjacent matrix
    for(int i = 0; i < num; i++)
    {
        infile>>a>>b;
        graph[a][b] = 1;
    }

    // call function to calculate the value of triangle in the graph
    count = triangleInGraph(graph);

    cout <<"The total number of triangles in the given graph is: " << count << endl;

    end = clock();
    cout <<"System run time: "<< (double) (end - start) / CLOCKS_PER_SEC << "(s)";

    return 0;

}