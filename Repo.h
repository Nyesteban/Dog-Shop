#pragma once
#include "Dog.h"
#include "RepoException.h"
#include "FileException.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include<iostream>

class Repo
{

private:
	std::vector<Dog> arr;
	std::string filename="";

public:
	// constructor
	Repo();
	Repo(const std::string& filename);

	// Gets all the components of the repo.
	std::vector<Dog> getAll() const;
	// Checks if a dog exists by using the unique identifier (the name). Returns arr.end() if it does not exist and its iterator if it does.
	auto find(std::string _name);
	// Gets the length of the repo.
	int lengthOfRepo() const;
	// Adds a dog to the repo, raises an exception if dog is already in the repo.
	void addDog(const Dog& newDog);
	// Removes the dog from the repo with the given name and returns 1 if the dog exists, else it raises an exception.
	void removeFromRepo(const std::string& _name);
	// Updates the dog from the repo with the given name using the other variables (breed, age, link) and returns 1 if the dog exists, else it raises an exception.
	void updateRepo(const std::string& _name, const std::string& _breed, int _age, const std::string& _link);
	Dog findThatReturnsDog(const std::string& _name);

private:
	void readFromFile();
	void writeToFile();
};
