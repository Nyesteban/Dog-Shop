#pragma once
class RepoException {

private:
	std::string message;

public:

	RepoException(std::string _message)
	{
	}

	std::string getMessage() const
	{
		return this->message;
	}
};

class RepoExceptionInherited : public std::exception 
{

private:
	std::string message;

public:
	RepoExceptionInherited(std::string _message) : message{ _message }
	{
	}

	const char* what() const noexcept override
	{
		return message.c_str();
	}
};