#ifndef PROJET_GRAPH_H
#define PROJET_GRAPH_H

#include "Person.h"
#include <iostream>
#include <vector>


class Graph {
public:
    Graph();
    Graph(const std::vector<std::pair<int, Person>>&);
    ~Graph();
    bool isEmpty() const;
    int getSize() const;
    void addPerson(int id, const Person &person);
    void setPerson(int id, Person person);
    Person getPerson(int id) const;
    std::vector<int> suggestFriends(int person_id, int mode) const;
    std::vector<int> suggestFriendsByCommonFriends(const Person *person) const;
    std::vector<int> suggestFriendsByOccupation(const Person *person) const;
    std::vector<int> suggestFriendsByAge(const Person *person) const;
    void degreeCentrality() const;
    float clusteringCoefficient(int id) const;
    std::vector<std::pair<int,Person>> getGraph() const;
    std::vector<std::vector<int>> girvanNewman(int iterations) const;
    int edgeWeight(const Graph &graph, int u, int v) const;
    Person removeFriendship(int id1, int id2);
    void addFriendship(int id1, int id2);
    void printGraph() const;
    void printSuggestion(int person_id) const;
    void printClusteringCoefficient() const;
    void printcommunities(int iteration) const;


        private:

    std::vector<std::pair<int, Person >> graph;
};




#endif //PROJET_GRAPH_H
