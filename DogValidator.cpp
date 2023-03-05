#include "DogValidator.h"

using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}


ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
	return message.c_str();
}


void DogValidator::validate(const Dog& d)
{
	string errors;
	if (d.getName().size() < 1)
		errors += string("The dog's name cannot be less than 1 characters!\n");
	if (!isupper(static_cast<unsigned char>(d.getName()[0])))
		errors += string("The dog's name must start with a capital letter!\n");
	if (d.getBreed().size() < 3)
		errors += string("The breed cannot be less than 3 characters!\n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}
