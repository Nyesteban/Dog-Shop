#pragma once
class FileException {

private:
	std::string message;

public:

	FileException(std::string _message): message{ _message }
	{
	}

	std::string getMessage() const
	{
		return this->message;
	}
};