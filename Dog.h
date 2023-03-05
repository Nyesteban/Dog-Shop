#pragma once
#include <string>
#include <Windows.h>
#include <iostream>

class Dog {
private:
	std::string breed;
	std::string name;
	int age;
	std::string link;

public:
	//constructor
	Dog();
	Dog(std::string, std::string, int, std::string);
	Dog(const Dog& rhs);
	bool operator== (const Dog& rhs);
	friend std::ostream& operator<<(std::ostream& output, const Dog& d);
	friend std::istream& operator>>(std::istream& input, Dog& d);

	// Gets the breed of a dog.
	std::string getBreed() const;
	// Gets the name of a dog.
	std::string getName() const;
	// Gets the age of a dog.
	int getAge() const;
	// Gets the link of a dog's photo.
	std::string getLink() const;
	/*
	void setBreed(std::string _breed);
	void setName(std::string _name);
	*/
	void setAge(int _age);
	/*
	void setLink(std::string _link);
	*/
	// Plays the link of a dog's photo.
	void play() const;

};
