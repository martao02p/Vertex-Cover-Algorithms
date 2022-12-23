#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <time.h>


bool* vertexCoverApproximate(int** matrix, int V) {

    bool* visited = new bool [V];
    for (int i=0; i<V; i++)
        visited[i] = false;


    for (int u=0; u<V; u++)
    {
        // An edge is only picked when both visited[u] and visited[v] are false
        if (visited[u] == false)
        {
            for(int i = 0; i < V; i++)
            {
                if (visited[i] == false && matrix[u][i] == 1)
                {
                     // Add the vertices (u, v) to the visited set.
                     visited[i] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }

    return visited;
}
