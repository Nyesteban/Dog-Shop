#include "UI_CSV_HTML.h"

UI_CSV::UI_CSV(Service& s, const std::string& _csvFile) : UI{ s }, csvFile{ _csvFile }
{
    
}

void UI_CSV::showAdoptedDogs(std::vector<Dog> lst)
{
    std::ofstream file(this->csvFile);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (auto d : lst)
    {
        file << d << "\n";
    }

    file.close();

    ShellExecuteA(0, 0, this->csvFile.c_str(), 0, 0, SW_SHOW);
}

void UI_CSV::userEnd(std::vector<Dog> lst)
{
    std::ofstream file(this->csvFile);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (auto d : lst)
    {
        file << d << "\n";
    }

    file.close();

    for (auto i : lst)
    {
        service.removeDogServ(i.getName());
    }
}

UI_HTML::UI_HTML(Service& s, const std::string& _htmlFile) : UI{ s }, htmlFile{ _htmlFile }
{

}

void UI_HTML::showAdoptedDogs(std::vector<Dog> lst)
{
    std::ofstream file(this->htmlFile);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<title>Adoption List</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n";
    file << "<td>Breed</td>\n";
    file << "<td>Name</td>\n";
    file << "<td>Age</td>\n";
    file << "<td>Photo link</td>\n";
    file << "</tr>\n";

    for (auto d : lst)
    {
        file << "<tr>\n";
        file << "<td>" << d.getBreed() << "</td>\n";
        file << "<td>" << d.getName() << "</td>\n";
        file << "<td>" << d.getAge() << "</td>\n";
        file << "<td><a href = " << d.getLink() << ">Link</a></td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();

    ShellExecuteA(0, 0, this->htmlFile.c_str(), 0, 0, SW_SHOW);
}

void UI_HTML::userEnd(std::vector<Dog> lst)
{
    std::ofstream file(this->htmlFile);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<title>Adoption List</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n";
    file << "<td>Breed</td>\n";
    file << "<td>Name</td>\n";
    file << "<td>Age</td>\n";
    file << "<td>Photo link</td>\n";
    file << "</tr>\n";

    for (auto d : lst)
    {
        file << "<tr>\n";
        file << "<td>" << d.getBreed() << "</td>\n";
        file << "<td>" << d.getName() << "</td>\n";
        file << "<td>" << d.getAge() << "</td>\n";
        file << "<td><a href = " << d.getLink() << ">Link</a></td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();

    for (auto i : lst)
    {
        service.removeDogServ(i.getName());
    }
}