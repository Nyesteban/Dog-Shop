#include "Dog.h"

Dog::Dog()
	: breed(""), name(""), age(), link("")
{
}

Dog::Dog(std::string _breed, std::string _name, int _age, std::string _link)
	: breed(_breed), name(_name), age(_age), link(_link)
{
}

Dog::Dog(const Dog& rhs)
	: breed(rhs.breed), name(rhs.name), age(rhs.age), link(rhs.link)
{
}

bool Dog::operator== (const Dog& rhs)
{
	if (rhs.breed.compare(this->getBreed()) == 0 && rhs.name.compare(this->getName()) == 0 && rhs.age == this->getAge() && rhs.link.compare(this->getLink()) == 0)
		return true;
	else 
		return false;
}

std::ostream& operator<<(std::ostream& os, const Dog& d) {
	os << d.breed << "," << d.name << "," << d.age << "," << d.link;
	return os;
}

std::istream& operator>>(std::istream& is, Dog& d) {
	if (is.eof())
		is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
	else
	{
		getline(is, d.breed, ',');
		getline(is, d.name, ',');
		std::string age;
		getline(is, age, ',');
		d.setAge(stoi(age)); 
		getline(is, d.link, '\n');
	}
	return is;
}

std::string Dog::getBreed() const
{
	return breed;
}

std::string Dog::getName() const
{
	return name;
}

int Dog::getAge() const
{
	return age;
}

std::string Dog::getLink() const
{
	return link;
}
/*
void Dog::setBreed(std::string _breed)
{
	breed = _breed;
}

void Dog::setName(std::string _name)
{
	name = _name;
}
*/
void Dog::setAge(int _age)
{
	age = _age;
}
/*
void Dog::setLink(std::string _link)
{
	link = _link;
}
*/

void Dog::play() const
{
	ShellExecuteA(NULL, NULL, "microsoftedge.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}