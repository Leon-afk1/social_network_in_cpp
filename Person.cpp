
#include "Person.h"
#include <utility>

using namespace std;

Person::Person()
{
    id = 0;
    name = "";
    age = 0;
    gender = "";
    occupation = "";
    friends = std::vector<int>();
}

Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
{
    this->id = id;
    this->name = std::move(name);
    this->age = age;
    this->gender = std::move(gender);
    this->occupation = std::move(occupation);
    this->friends = std::move(friends);
}

Person::~Person()
{

}

int Person::getId() const {
    return id;
}

int Person::getAge() const {
    return age;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getGender() const {
    return gender;
}

std::string Person::getOccupation() const {
    return occupation;
}

std::vector<int> Person::getFriends() const {
    return friends;
}

void Person::setId(int id) {
    this->id = id;
}

void Person::setAge(int age) {
    this->age = age;
}

void Person::setName(std::string name) {
    this->name = name;
}

void Person::setGender(std::string gender) {
    this->gender= gender;
}

void Person::setOccupation(std::string occupation) {
    this->occupation = occupation;
}

void Person::setFriends(std::vector<int> friends) {
    this->friends = friends;
}

void Person::addFriend(int id) {
    friends.push_back(id);
}

std::vector<int> Person::removeFriend(int id) {
    for (int i = 0; i < friends.size(); i++) {
        if (friends[i] == id) {
            friends.erase(friends.begin() + i);
        }
    }
    return friends;
}

bool Person::isFriend(int id) const {
    for (int i : friends) {
        if (i == id) {
            return true;
        }
    }
    return false;
}

void Person::print() const {
    if (id == 0) {
        std::cout << "This person does not exist" << std::endl;
        return;
    }else {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Gender: " <<gender << std::endl;
        std::cout << "Occupation: " << occupation << std::endl;
        std::cout << "Friends: ";
        for (int i : friends) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}