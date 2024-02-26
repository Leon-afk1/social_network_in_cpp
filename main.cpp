#include <iostream>
#include "utils.h"

using namespace std;

int main() {
 
    std::string filename= "social_network.csv";
    Graph g2= readData(filename);
    g2.printGraph();

    int answer=0,id=0,iteration=0;

    while (answer!=6){
        std::cout << "\nChoose what you want to do\n\n"
                     "1. Display the social network\n"
                     "2. Suggest friends for users based on common friends, similar occupation, or similar age\n"
                     "3. Calculate degree centrality for each user\n"
                     "4. Calculate clustering coefficient for each user\n"
                     "5. Detect communities using the Girvan-Newman algorithm\n"
                     "6. Exit the program\n" << std::endl;
        std::cin >> answer;
        switch (answer) {
            case 1:
                g2.printGraph();
                break;
            case 2:
                std::cout << "________________________________________________\n" << std::endl;
                std::cout << "Enter the id of the user you want to suggest friends for" << std::endl;
                std::cin >> id;
                g2.printSuggestion(id);
                break;
            case 3:
                std::cout << "________________________________________________\n" << std::endl;
                std::cout << "Calculate degree centrality for each user" << std::endl;
                g2.degreeCentrality();
                break;
            case 4:
                std::cout << "________________________________________________\n" << std::endl;
                std::cout << "Calculate clustering coefficient for each user" << std::endl;
                g2.printClusteringCoefficient();
                break;
            case 5:
                std::cout << "________________________________________________\n" << std::endl;
                std::cout << "Detect communities using the Girvan-Newman algorithm" << std::endl;
                std::cout <<"How many iteration do you want to do?"<<std::endl;
                std::cin >> iteration;
                g2.printcommunities(iteration);
                break;
            case 6:
                std::cout << "________________________________________________\n" << std::endl;
                std::cout << "Exit the program" << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
                break;
        }
        std::cin. clear();

    }
    return 0;
}