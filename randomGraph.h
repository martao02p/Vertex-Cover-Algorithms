#pragma once
#include <random>

std::random_device r2;
std::default_random_engine e3( r2() );
std::uniform_real_distribution<float> uniform_Floats(0.0, 1.0);
void generateRandomGraph(int n, int **arr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float p = uniform_Floats(e3);
            if (p < 0.45) {
                arr[i][j] = 1;
            } else {
                arr[i][j] = 0;
            }
            arr[i][i] = 0;
            if (j < i) {
                arr[i][j] = arr[j][i];
            }
        }
    }
}