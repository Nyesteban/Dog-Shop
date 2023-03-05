#include "Repo.h"

Repo::Repo()
{
}

Repo::Repo(const std::string& filename)
{
    this->filename = filename;
    this->readFromFile();
}


std::vector<Dog> Repo::getAll() const
{
    return arr;
}

auto Repo::find(std::string _name)
{
    
    return find_if(arr.begin(), arr.end(), [_name](const Dog& i) { return i.getName().compare(_name) == 0; });
}

Dog Repo::findThatReturnsDog(const std::string& _name)
{
    for (auto d : this->arr)
    {
        if (d.getName() == _name)
            return d;
    }
    throw RepoExceptionInherited("Dog not in repo!");
}

int Repo::lengthOfRepo() const
{
    return arr.size();
}

void Repo::addDog(const Dog& newDog)
{
    if (find(newDog.getName()) != arr.end())
    {
        throw RepoExceptionInherited("Dog already in repo!");
    }
    else
    {
        arr.push_back(newDog);
        if (filename != "")
        {
            this->writeToFile();
        }
    }
}
void Repo::removeFromRepo(const std::string& _name)
{
    auto pos = find(_name);
    if (pos == arr.end())
    {
        throw RepoExceptionInherited("Dog already not in repo!");
    }
    arr.erase(pos);
    if (filename != "")
    {
        this->writeToFile();
    }
}

void Repo::updateRepo(const std::string& _name, const std::string& _breed, int _age, const std::string& _link)
{
    auto pos = find(_name);
    if (pos == arr.end())
    {
        throw RepoExceptionInherited("Dog not in repo!");
    }
    Dog newDog(_breed, _name, _age, _link);
    *pos = newDog;
    if (filename != "")
    {
        this->writeToFile();
    }
}

void Repo::readFromFile()
{
    std::ifstream file(this->filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Dog d;
    while (file >> d)
        this->arr.push_back(d);

    file.close();
}

void Repo::writeToFile()
{
    std::ofstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (auto it = this->arr.begin(); it != this->arr.end(); it++)
    {
        if (std::next(it, 1) == this->arr.end())
        {
            file << *it;
        }
        else
            file << *it << "\n";
    }
    file.close();
}