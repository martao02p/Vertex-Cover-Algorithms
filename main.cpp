#include <iostream>
#include "randomGraph.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "intoJSONfile.h"
#include "bruteForce.h"
#include "approximate.h"
#include "genetic.h"
using json = nlohmann::json;
json j;
int main() {
    // create graph
    int n = 5;
    int** graph = new int *[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    generateRandomGraph(n,graph);
    //to repair :((
    graphIntoJson(n, graph, j);


    //BRUTE FORCE
    std::string vertex = bruteForce(graph, n);
    std::cout << "BRUTE FORCE: " << std::endl << "vertices: ";
        for(int i = 0; i< n; i++){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    //APPROXIMATE
    bool* visited = vertexCoverApproximate(graph, n);
    std::cout << "APPROXIMATE METHOD:" << std::endl << "vertices: ";
    for (int i=0; i<n; i++)
        if (visited[i])
            std::cout << i << " ";
    std::cout << std::endl;
    //HEURISTIC
    std::cout << "GENETIC ALGORITHM:" << std::endl;
    //create population
    int population_size = 30;
    int generation = 0;
    std::vector<std::vector<int>> population;
    for(int i = 0; i<population_size; i++){
        population.push_back(create_individual(n));
    }

    //
    int best_fitness = fitness(graph, population[0], n);
    std::vector<int> fittest_individual = population[0];
    int gen = 0;
    while(gen != 1000) {
        best_fitness = fitness(graph, population[0], n);
        fittest_individual = population[0];
        for (std::vector<int> individual : population) {
            int f = fitness(graph, individual, n);
            if (f < best_fitness) {
                best_fitness = f;
                fittest_individual = individual;
            }
        }
        if(gen % 100 == 0){
            std::cout << "Generation: " << gen << " Best Fitness: " << best_fitness << " Individual: " << std::endl;
            for(int x : fittest_individual)
                std::cout << x << " ";
            std::cout << std::endl;
        }
        gen++;
        population = tournament_selection(graph, population, population_size, n);
        std::vector<std::vector<int>> new_population;
        for(int i = 0; i< population_size - 1; i+=2){

            auto children = crossover(n, population[i], population[i+1]);
            new_population.push_back(children.first);
            new_population.push_back(children.second);
        }
        for(std::vector<int> ind : new_population){
            mutation(ind, gen < 400 ? 0.4 : 0.2, n);
            if(gen < 400){
                mutation(ind, 0.4, n);
            }

            else{
                mutation(ind, 0.2, n);
            }
        }
        population = new_population;
    }
    for(int i = 0; i<n; i++){
        std::cout << i << " : " << fittest_individual[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << fitness(graph, fittest_individual, n) << std::endl;

    //free taken memory
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}