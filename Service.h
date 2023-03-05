#pragma once
#include "Repo.h"
#include "DogValidator.h"
#include <fstream>
#include <memory>
#include "Undo.h"

class Service
{
private:
	Repo repo;
	std::vector<std::unique_ptr<UndoAction>> undoActions;
	std::vector<std::unique_ptr<UndoAction>> redoActions;

public:
	//constructor
	Service(Repo& r);

	// Adds a dog to the repo.
	void addDog(const std::string& breed, const std::string& name, int age, const std::string& link);
	// Gets the length of the repo.
	int getLengthOfRepo() const;
	// Removes the dog from the repo with the given name and returns 1 if the dog exists, else it does nothing and returns -1.
	void removeDogServ(const std::string& _name);
	// Updates the dog from the repo with the given name using the other variables (breed, age, link) and returns 1 if the dog exists, else it does nothing and returns -1.
	void updateDogServ(const std::string& _name, const std::string& _breed, int _age, const std::string& _link);
	// Gets all the components of the repo.
	std::vector<Dog> getAllServ() const;
	// Returns an altered repo, containing only the dogs of a given breed, having an age less than a given number.  If no breed is provided, then all the dogs will be considered.
	std::vector<Dog> getFilteredRaw(std::string _breed, int _age);
	void undo();
	void redo();
};