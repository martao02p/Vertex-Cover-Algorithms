#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>
#include <strings.h>


std::vector<std::string> generateSubsets(int n) {
    std::vector<std::string> subsets;
    std::cout << std::endl;

    subsets.push_back("0");
    subsets.push_back("1");

    for (int i = 2; i < (1 << n); i = i << 1) {
        // Enter the previously generated codes again in arr[] in reverse
        // order. Nor arr[] has double number of codes.
        for (int j = i - 1; j >= 0; j--)
            subsets.push_back(subsets[j]);

        // append 0 to the first half
        for (int j = 0; j < i; j++)
            subsets[j] = "0" + subsets[j];

        // append 1 to the second half
        for (int j = i; j < 2 * i; j++)
            subsets[j] = "1" + subsets[j];
    }
    return subsets;
}

std::string fitness(int** graph, std::vector<std::string> subsets, int n) {
    std::string bestSet = "";
    int bestNumOfVer = n;

    for (std::string individ: subsets) {
        int currentNumOfVer = 0;
        std::vector<std::vector<int>> truthArray;
        std::vector<int> v(n, 0);
        for (int i = 0; i < n; i++)
            truthArray.push_back(v);

        for (int i = 0; i < n; i++) {
            if (individ[i] == '1') {
                currentNumOfVer++;
                for (int k = 0; k < n; k++) {
                    if (graph[i][k] == 1) {
                        truthArray[i][k] = 1;
                        truthArray[k][i] = 1;
                    }
                }
            }
        }

        bool flag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] != truthArray[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag == false)
                break;
        }

        if (flag && currentNumOfVer < bestNumOfVer) {
            bestNumOfVer = currentNumOfVer;
            bestSet = individ;
        }

    }
    return bestSet;

}


std::string bruteForce(int** graph, int n) {
    std::vector<std::string> subsets = generateSubsets(n);
    std::string result = fitness(graph, subsets, n);
    return result;
}