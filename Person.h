#ifndef PROJET_PERSON_H
#define PROJET_PERSON_H

#include <iostream>
#include <vector>

class Person
{
public:
    Person();
    Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);
    ~Person();
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getOccupation() const;
    std::vector<int> getFriends() const;
    void setId(int id);
    void setName(std::string name);
    void setAge(int age);
    void setGender(std::string gender);
    void setOccupation(std::string occupation);
    void setFriends(std::vector<int> friends);
    void addFriend(int id);
    std::vector<int> removeFriend(int id);
    bool isFriend(int id) const;
    void print() const;


private:
    int id{};
    std::string name;
    int age{};
    std::string gender;
    std::string occupation;
    std::vector<int> friends;
};


#endif //PROJET_PERSON_H
