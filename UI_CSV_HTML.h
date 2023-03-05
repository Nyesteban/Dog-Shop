#pragma once
#include "UI.h"
class UI_CSV: public UI
{
private:
	std::string csvFile;

public:
	UI_CSV(Service& s, const std::string& _csvFile);

private:
	void showAdoptedDogs(std::vector<Dog> lst) override;
	void userEnd(std::vector<Dog> lst) override;
};

class UI_HTML : public UI
{
private:
	std::string htmlFile;

public:
	UI_HTML(Service& s, const std::string& _htmlFile);

private:
	void showAdoptedDogs(std::vector<Dog> lst) override;
	void userEnd(std::vector<Dog> lst) override;
};