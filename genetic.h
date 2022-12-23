#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>

//for random values
std::random_device r;
std::default_random_engine e1( r() );
std::uniform_real_distribution<float> uniform_dist_Floats(0.0, 1.0);
std::uniform_int_distribution<int> uniform_dist_0_1(0,1);


std::vector<int> create_individual(int n){
    std::vector<int> indVec;
    for(int i = 0; i< n; i++){
        indVec.push_back(uniform_dist_0_1(e1));
    }
    return  indVec;
}

int fitness(int** graph, std::vector<int> individ, int n){
    int fitnessScore = 0;
    for(int i =0; i<n; i++){
        if(individ[i] == 1)
            fitnessScore++;
        for(int j = 0; j< i; j++){
            if(graph[i][j] == 1)
                if(individ[i] == 0 && individ[j] == 0)
                    fitnessScore += 10;
        }
    }
    return fitnessScore;
}

std::pair<std::vector<int>, std::vector<int>> crossover(int n, std::vector<int> parent1, std::vector<int> parent2){
    std::pair<std::vector<int>, std::vector<int>> children;

    std::uniform_int_distribution<int> uniform_dist_1_n_3(1,n-3);
    int position = uniform_dist_1_n_3(e1);
    for(int i = 0; i < position + 1; i++){
        children.first.push_back(parent1[i]);
        children.second.push_back(parent2[i]);
    }
    for(int i = position + 1; i < n; i++){
        children.first.push_back(parent2[i]);
        children.second.push_back(parent1[i]);
    }
    return children;
}
void mutation(std::vector<int> individ, float probality, int n){
    std::uniform_int_distribution<int> uniform_dist_0_n_1(1,n-3);
    float x = uniform_dist_Floats(e1);
    if(x <= probality){
        int position = uniform_dist_0_n_1(e1);
        individ[position] = 1 - individ[position];
    }
}
std::vector<std::vector<int>> tournament_selection(int** graph, std::vector<std::vector<int>> population, int population_size, int n){
    std::vector<std::vector<int>> new_population;
    for(int j = 0; j< 2; j++){
        std::random_shuffle(population.begin(), population.end());
        for(int i = 0; i< population_size-1; i+=2){
            if(fitness(graph, population[i], n) < fitness(graph, population[i+1], n)){
                new_population.push_back(population[i]);
            }
            else{
                new_population.push_back(population[i+1]);
            }
        }
    }
    std::random_shuffle(new_population.begin(), new_population.end());
    return new_population;
}
