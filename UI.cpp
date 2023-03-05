#include "UI.h"
#include <iostream>
#include <string>

UI::UI(Service& s) : service(s)
{

}

/*
	Prints the available menu for the administrator
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	std::cout << "\n**********************************************************\n";
	std::cout << "1 - add a dog.\n";
	std::cout << "2 - list all dogs.\n";
	std::cout << "3 - remove an dog.\n";
	std::cout << "4 - update a dog.\n";
	std::cout << "0 - to exit.\n";
	std::cout << "**********************************************************\n";
}

/*
	Prints the available menu for the modes
	Input: -
	Output: the menu is printed at the console
*/
void printModes()
{
	std::cout << "\n**********************************************************\n";
	std::cout << "1 - administrator.\n";
	std::cout << "2 - user.\n";
	std::cout << "0 - to exit.\n";
	std::cout << "**********************************************************\n";
}

/*
	Prints the available menu for the user
	Input: -
	Output: the menu is printed at the console
*/
void printUser()
{
	std::cout << "\n**********************************************************\n";
	std::cout << "1 - iterate over all dogs, choose which one to adopt.\n";
	std::cout << "2 - iterate over all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs will be considered, and choose which one to adopt.\n";
	std::cout << "3 - see the adoption list.\n";
	std::cout << "0 - to exit.\n";
	std::cout << "**********************************************************\n";
}

/*
	Prints the available menu for the adoption interface
	Input: -
	Output: the menu is printed at the console
*/
void printAdoptionMenu()
{
	std::cout << "\n**********************************************************\n";
	std::cout << "1 - adopt.\n";
	std::cout << "0 - next.\n";
	std::cout << "**********************************************************\n";
}

/*
	Verifies if the given command is valid (is either 1, 2, 3, 4 or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command, int max)
{
	if (command >= 0 && command <= max)
		return 1;
	return 0;
}

int readIntegerNumber(std::string message) {
	std::string str;
	int flag = 0;
	while (flag == 0)
	{
		std::cout << message;
		std::cin >> str;
		flag = 1;
		for (unsigned int i = 0; i < str.length(); i++)
			if (isdigit(str[i]) == false)
				flag = 0;;
		if (flag == 0)
			std::cout << "Error reading number!\n";
	}
    return stoi(str);
}

int UI::addDogUI()
{
	std::string breed, name, link;
	int age;
	std::cout << "Please enter the breed: ";
	std::cin.ignore();
	std::getline(std::cin, breed);
	std::cout << "Please enter the name: ";
	//std::cin.ignore();
	std::getline(std::cin, name);
	age = readIntegerNumber("Please enter the age: ");
	std::cout << "Please enter the link: ";
	std::cin.ignore();
	std::getline(std::cin, link);
	return service.addDog(breed, name, age, link);
	/*
	Dog d;
	std::cout << "Format: breed,name,age,link\n";
	std::cin.ignore();
	std::cin >> d;
	return service.addDog(d.getBreed(), d.getName(), d.getAge(), d.getLink());
	*/
}

void UI::listAllDogs() const
{
	std::vector<Dog> all = service.getAllServ();
	for (auto i: all)
	{
		std::cout << i << "\n";
		std::cout << "-------------------------------\n";
		i.play();
	}
}

int UI::removeDogUI()
{
	std::string name;
	std::cout << "Please enter the name: ";
	std::cin.ignore();
	std::getline(std::cin, name);
	return service.removeDogServ(name);
}

int UI::updateDogUI()
{
	std::string breed, name, link, newname;
	int age;
	std::cout << "Please enter the name: ";
	std::cin.ignore();
	std::getline(std::cin, name);
	std::cout << "Please enter the new breed: ";
	//std::cin.ignore();
	std::getline(std::cin, breed);
	age = readIntegerNumber("Please enter the new age: ");
	std::cout << "Please enter the new link: ";
	std::cin.ignore();
	std::getline(std::cin, link);
	return service.updateDogServ(name, breed, age, link);
}

Dog UI:: userAllDogs()
{
	std::vector<Dog> copy = service.getAllServ();
	int i = 0;
	while (1)
	{
		std::cout << copy[i] << std::endl;
		copy[i].play();
		printAdoptionMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command, 1) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		switch (command)
		{
		case 0:
		{
			i++; 
			break;
		}
		case 1:
		{
			return copy[i];
			break;
		}
		}
		if (i >= copy.size())
			i = 0;
	}
}

Dog UI::userSpecificDogs()
{
	std::string breed;
	int age;
	std::cout << "Please enter the breed: ";
	std::cin.ignore();
	std::getline(std::cin, breed);
	age = readIntegerNumber("Please enter the age: ");
	std::vector<Dog> copy = service.getFilteredRaw(breed, age);
	if (copy.size() <= 0)
	{
		throw "No dogs matching the criteria found.";
	}
	int i = 0;
	while (1)
	{
		std::cout << copy[i] << std::endl;
		copy[i].play();
		printAdoptionMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command, 1) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		switch (command)
		{
		case 0:
		{
			i++;
			break;
		}
		case 1:
		{
			return copy[i];
			break;
		}
		}
		if (i >= copy.size())
			i = 0;
	}
}

void UI::showAdoptedDogs(std::vector<Dog> lst)
{
	for (auto i: lst)
	{
		std::cout << i << std::endl;
		i.play();
	}
}

void UI::userEnd(std::vector<Dog> lst)
{
	for (auto i: lst)
	{
		service.removeDogServ(i.getName());
	}
}

void UI::startUIadmin()
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command, 4) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = -1;
			try
			{
				res = addDogUI();
			}
			catch (const ValidationException& ve)
			{
				std::cout << ve.getMessage() << "\n";
			}
			catch (const RepoExceptionInherited& re) {
				std::cout << re.what() << "\n";
			}
			if (res == 1)
				printf("Dog successfully added.\n");
			break;
		}
		case 2:
		{
			listAllDogs();
			break;
		}
		case 3:
		{
			int res = -1;
			try
			{
				res = removeDogUI();
			}
			catch (const RepoExceptionInherited& re) {
				std::cout << re.what() << "\n";
			}
			if (res == 1)
				printf("Dog successfully removed.\n");
			break;
		}
		case 4:
		{
			int res = -1;
			try
			{
				res = updateDogUI();
			}
			catch (const ValidationException& ve)
			{
				std::cout << ve.getMessage() << "\n";
			}
			catch (const RepoExceptionInherited& re) {
				std::cout << re.what() << "\n";
			}
			if (res == 1)
				printf("Dog successfully updated.\n");
			break;
		}

		}
	}
}

void UI::startUIuser()
{
	std::vector<Dog> list;
	while (1)
	{
		printUser();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command, 3) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
		{
			userEnd(list);
			break;
		}
		switch (command)
		{
		case 1:
		{
			int ok = 1;
			if (service.getLengthOfRepo() == 0)
			{
				std::cout << "No more dogs!\n";
				break;
			}
			Dog d = userAllDogs();
			for (auto i: list)
			{
				if (i.getName() == d.getName() && i.getAge() == d.getAge() && i.getLink() == d.getLink())
				{
					std::cout << "Dog already in adoption list!\n";
					ok = 0;
					break;
				}
			}
			if (ok == 0)
				break;
			list.push_back(d);
			break;
		}
		case 2:
		{
			int ok = 1;
			if (service.getLengthOfRepo() == 0)
			{
				std::cout << "No more dogs!\n";
				break;
			}
			try {
				Dog d = userSpecificDogs();
				for (auto i: list)
				{
					if (i.getName() == d.getName() && i.getAge() == d.getAge() && i.getLink() == d.getLink())
					{
						std::cout << "Dog already in adoption list!\n";
						ok = 0;
						break;
					}
				}
				if (ok == 0)
					break;
				list.push_back(d);
			}
			catch (const char* e) {
				std::cout << e << "\n";
			}
			break;
		}

		case 3:
		{
			showAdoptedDogs(list);
			break;
		}

		}
	}
}

void UI::startUI()
{
	while (1)
	{
		printModes();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command, 2) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			startUIadmin();
			break;
		}
		case 2:
		{
			startUIuser();
			break;
		}
		}
	}
}