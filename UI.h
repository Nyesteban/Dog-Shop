#pragma once
#include "Service.h"
class UI
{
protected:
	Service service;

public:
	UI(Service& s);
	void startUI();

private:
	int addDogUI();
	void listAllDogs() const;
	int removeDogUI();
	int updateDogUI();
	Dog userAllDogs();
	Dog userSpecificDogs();
	virtual void showAdoptedDogs(std::vector<Dog> lst);
	virtual void userEnd(std::vector<Dog> lst);
	void startUIadmin();
	void startUIuser();
};
