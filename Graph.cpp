#include <algorithm>
#include "utils.h"
#include "Graph.h"

using namespace std;

Graph::Graph() {
    this->graph = std::vector<std::pair<int, Person>>();
}

Graph::Graph(const std::vector<std::pair<int, Person>>&) {
    this->graph = graph;
}

Graph::~Graph() {
    if (isEmpty()) {
        return;
    }else{
        for (auto &i : graph) {
            graph.erase(graph.begin());
        }
    }
    graph.clear();
}

bool Graph::isEmpty() const {
    return graph.empty();
}

int Graph::getSize() const {
    return graph.size();
}

void Graph::addPerson(int id, const Person &person) {
    graph.push_back(std::make_pair(id, person));
}

void Graph::setPerson(int id, Person person) {
    for (auto &i : graph) {
        if (i.first == id) {
            i.second = person;
        }
    }
}

Person Graph::getPerson(int id) const {
    for (auto &i : graph) {
        if (i.first == id) {
            return i.second;
        }
    }
    return Person();
}

std::vector<int> Graph::suggestFriends(int person_id, int mode) const {
    std::vector<int> suggestedFriends;
    Person pers= getPerson(person_id);

    switch (mode) {
        case 1:
            suggestedFriends = suggestFriendsByCommonFriends(&pers);
            break;
        case 2:
            suggestedFriends = suggestFriendsByOccupation(&pers);
            break;
        case 3:
            suggestedFriends = suggestFriendsByAge(&pers);
            break;
        default:
            suggestedFriends = suggestFriendsByCommonFriends(&pers);
            break;
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByCommonFriends(const Person *person) const {
    std::vector<int> suggestedFriends;
    std::vector<int> friends = person->getFriends();
    std::vector<int> friendsOfFriends;
    std::vector<int> commonFriends;

    for (auto &i : friends) {
        friendsOfFriends = getPerson(i).getFriends();
        for (auto &j : friendsOfFriends) {
            if (std::find(friends.begin(), friends.end(), j) == friends.end()) {
                commonFriends.push_back(j);
            }
        }
    }
    std::sort(commonFriends.begin(), commonFriends.end());
    commonFriends.erase(std::unique(commonFriends.begin(), commonFriends.end()), commonFriends.end());
    for (auto &i : commonFriends) {
        if (i != person->getId()) {
            suggestedFriends.push_back(i);
        }
    }

    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByOccupation(const Person *person) const {
    std::vector<int> sameoccupation;
    std::vector<int> friends = person->getFriends();
    std::vector<int> suggestedFriends;
    std::string occupation= person->getOccupation();
    for (auto &i : graph) {
        if (i.second.getOccupation() == occupation) {
            if (i.second.getId() != person->getId()){
                sameoccupation.push_back(i.first);
            }
        }
    }
    for (auto &i : sameoccupation) {
        if (std::find(friends.begin(), friends.end(), i) == friends.end()) {
            suggestedFriends.push_back(i);
        }
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByAge(const Person *person) const {
    int age = person->getAge();
    int average = 2;
    std::vector<int> suggestedFriends;
    std::vector<int> friends = person->getFriends();
    for (auto &i : graph) {
        if (i.second.getAge() >= age - average && i.second.getAge() <= age + average) {
            if (i.second.getId() != person->getId()){
                suggestedFriends.push_back(i.first);
            }
        }
    }
    for (auto &i : suggestedFriends) {
        if (std::find(friends.begin(), friends.end(), i) != friends.end()) {
            suggestedFriends.erase(std::remove(suggestedFriends.begin(), suggestedFriends.end(), i), suggestedFriends.end());
        }
    }
    return suggestedFriends;
}

void Graph::degreeCentrality() const {
    int degreeCentrality = 0;
    for (auto &i : graph) {
        degreeCentrality = i.second.getFriends().size();
        cout << i.second.getName()<< " (id : " << i.first << ") has a degree centrality of " << degreeCentrality << endl;
    }
    cout<<"____________________________________________________\n"<<endl;
}

float Graph::clusteringCoefficient(int id) const {
    float clusteringCoefficient = 0;
    int connectedTriplets = 0;
    int closedTriplets = 0;
    std::vector<int> friends = getPerson(id).getFriends(), copyFriends = friends;
    std::vector<int> friendsOfFriends;

    for (auto &i : friends) {
        friendsOfFriends = getPerson(i).getFriends();
        for (auto &j : friendsOfFriends) {
            if (std::find(friends.begin(), friends.end(), j) != friends.end()) {
                closedTriplets++;
                friends.erase(std::remove(friends.begin(), friends.end(), j), friends.end());
            }
        }
    }
    connectedTriplets=copyFriends.size()*(copyFriends.size()-1);
    connectedTriplets = connectedTriplets/2;
    if (connectedTriplets != 0) {
        clusteringCoefficient = (float) closedTriplets / connectedTriplets;
    }
    return clusteringCoefficient;
}

std::vector<std::pair<int, Person>> Graph::getGraph() const {
    return graph;
}

std::vector<std::vector<int>> Graph::girvanNewman(int iterations) const {
    Graph graph = *this;
    int minId = graph.getGraph()[0].first, maxId = graph.getGraph()[0].first;
    std::vector<std::vector<int>> communities;
    std::vector<int> community;
    int maxWeight=0,idMaxWeight1=0,idMaxWeight2=0;
    for (int i = 0; i < iterations; ++i) {
        for (auto &j : graph.getGraph()){
            for (auto &k : j.second.getFriends()){
                if (edgeWeight(graph, j.first, k) > maxWeight){
                    maxWeight = edgeWeight(graph, j.first, k);
                    idMaxWeight1 = j.first;
                    idMaxWeight2 = k;
                }
            }
        }
        graph.setPerson(idMaxWeight1, graph.removeFriendship(idMaxWeight1, idMaxWeight2));
        maxWeight=0;
    }

    for (auto &i : graph.getGraph()){
        if (i.first < minId){
            minId = i.first;
        }
        if (i.first > maxId){
            maxId = i.first;
        }
    }

    for (int i = minId; i <= maxId; ++i) {
        for (auto &k : communities){
            for (auto &j : k){
                if (j == i){
                    for (auto &p : graph.getPerson(i).getFriends()){
                        k.push_back(p);
                    }
                    sort(k.begin(), k.end());
                    k.erase(std::unique(k.begin(), k.end()), k.end());
                    community.push_back(i);
                    break;
                }
            }
        }
        if (community.empty()){
            community.push_back(i);
            for (auto &j : graph.getPerson(i).getFriends()){
                if (std::find(community.begin(), community.end(), j) == community.end()){
                    community.push_back(j);
                }
            }
            sort(community.begin(), community.end());
            communities.push_back(community);
        }
        community.clear();

    }
    communities.erase(std::unique(communities.begin(), communities.end()), communities.end());
    return communities;
}

int Graph::edgeWeight(const Graph &graph, int u, int v) const {;
    return graph.getPerson(u).getFriends().size() + graph.getPerson(v).getFriends().size();
}

Person Graph::removeFriendship(int id1, int id2) {
    Person person1 = getPerson(id1);
    std::vector<int> friends1 = person1.removeFriend(id2);
    person1.setFriends(friends1);
    return person1;

}

void Graph::addFriendship(int id1, int id2) {
    Person person1 = getPerson(id1);
    Person person2 = getPerson(id2);
    std::vector<int> friends1 = person1.getFriends();
    std::vector<int> friends2 = person2.getFriends();

    friends1.push_back(id2);
    friends2.push_back(id1);

    person1.setFriends(friends1);
    person2.setFriends(friends2);
}

void Graph::printGraph() const {
    if (isEmpty()) {
        cout << "Graph is empty" << endl;
        return;
    }else{
        for (auto &i : graph) {
            i.second.print();
            std::cout << "________________________________________________" << std::endl;
        }
    }
}

void Graph::printSuggestion(int person_id) const {
    int method = 0;
    std::cout << "Suggest friends for users based on common friends(1), similar occupation(2), or similar age(3)" << std::endl;
    std::cin >> method;
    std::vector<int> suggestedFriends = suggestFriends(person_id, method);
    if (suggestedFriends.empty()) {
        cout << "No suggested friends for person " << person_id << endl;
        return;
    }else{
        cout << "Suggested friends for person " << person_id << " are: " << endl;
        for (auto &i : suggestedFriends) {
            for (auto &j : graph) {
                if (j.first == i) {
                    cout << j.second.getName() << "(id: "<< j.second.getId()<< "), who is " << j.second.getAge() << " years old and works as a " << j.second.getOccupation();
                    cout <<" and has for friends(id): ";
                    for (auto &k : j.second.getFriends()){
                        cout << k << " ";
                    }
                    cout << endl;
                    std::cout << "________________________________________________" << std::endl;
                }
            }
        }
        std::cout<< endl;
    }
}


void Graph::printClusteringCoefficient() const {
    float clustering_coefficient = 0;
    int id= 0;
    for (auto &i : graph) {
        id = i.first;
        clustering_coefficient = clusteringCoefficient(id);
        cout << "Clustering coefficient for person " << id << " is " << clustering_coefficient << endl;
    }
    std::cout << "________________________________________________\n" << std::endl;

}

void Graph::printcommunities(int iteration) const {
    std::cout<<"Communities: "<<std::endl;
    std::vector<std::vector<int>> communities= girvanNewman(iteration);
    for (auto &i : communities){
        for (auto &j : i){
            cout << j << " ";
        }
        cout << endl;
        std::cout << "________________________________________________" << std::endl;
    }
    std::cout << "________________________________________________" << std::endl;
}