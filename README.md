# Social Network Analysis Project

This project was developed as part of an Erasmus program at Yeditepe University, with the goal of implementing a graph data structure to represent relationships between people. Each vertex in the graph corresponds to a person and is represented by a Person object.

## Introduction

The project involves the creation of a robust data structure to facilitate easy access and manipulation of information related to individuals within a social network.

## Methodology

1. **Person Structure:**
   - A detailed structure for a person was created, accompanied by various functions to modify individual parameters. Although some functions were not utilized in the final project, they served a crucial role in early testing and can be beneficial for future project enhancements.

2. **Graph Structure:**
   - Implementation of the graph structure involved testing with manually added persons initially. Once confirmed, a file containing information about multiple individuals was used to populate the graph, and functionalities were incrementally added.

## Implementation

### Person Structure

- Multiple functions were created to manually modify each parameter of a person, allowing for precise control over individual attributes.

### Suggest Friends Functions

1. **By Common Friends:**
   - The most challenging function, it involves retrieving all friends of a given person, expanding the network to friends of friends, sorting the list, and eliminating duplicates.

2. **By Occupation:**
   - The function checks for individuals with the same occupation, ensuring they are not already friends with the given person. If not, they are added to the suggested friends list.

3. **By Age:**
   - The function suggests friends based on age proximity, allowing users to specify the acceptable age difference.

### Additional Functions

- **Degree Centrality:**
  - Determines the degree centrality for each person by analyzing the number of friends.

- **Clustering Coefficient:**
  - Calculates the clustering coefficient for each person using a formula based on closed and connected triangles.

- **Girvan-Newman Algorithm:**
  - Detects communities within the graph by iteratively removing edges with the highest weight and assigning individuals to communities.

## Results

The project successfully achieved its objectives, demonstrating the manipulation of vectors, different data structures, and enhancing understanding of fundamental C++ concepts.

## Conclusion

While the code is functional, there are areas for improvement, such as strange community structures in the Girvan-Newman function and limitations in detecting occupation similarity. The display on the screen could also be enhanced. Overall, the project addresses the primary goal of providing tools to manipulate and extract information from a social network.

