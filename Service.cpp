#include "Service.h"

Service::Service(Repo& r) : repo(r)
{
    if (getLengthOfRepo() < 1)
    {
        addDog("Labrador", "Tim", 10, "https://www.taramulanimalelor.com/wp-content/uploads/2020/10/Labrador-caracteristici-rasa-caine.jpg");
        addDog("Rottweiler", "Max", 2, "https://www.animalepierdute.ro/wp-content/uploads/2019/09/Rottweiler.jpg");
        addDog("Affenpinscher", "Cooper", 1, "https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2020/05/21144745/Affenpinscher-running.jpg");
        addDog("Border Collie", "Charlie", 3, "https://i.differencevs.com/preview/animals/6858143-difference-between-collie-and-border-collie.jpg");
        addDog("Boxer", "Teddy", 1, "https://s36700.pcdn.co/wp-content/uploads/2019/03/Close-up-of-a-Boxer-with-tongue-out-happy.jpg.optimal.jpg");
        addDog("Barbet", "Kobe", 7, "https://www.akc.org/wp-content/uploads/2017/11/Barbet-standing-in-the-snow.jpg");
        addDog("Husky", "Oscar", 9, "https://www.zooplus.ro/ghid/wp-content/uploads/2021/11/Caini-din-rasa-Husky-Siberian.-Adult-si-pui.jpg");
        addDog("Border Terrier", "Bo", 3, "https://vetwork.co/galaxy/wp-content/uploads/8-face.jpg");
        addDog("Akita Inu", "Buddy", 8, "https://brit-petfood.com/file/nodes/product/akitainu.jpg");
        addDog("Bull Terrier", "Walter", 10, "https://www.akc.org/wp-content/uploads/2017/11/bull-terrier-on-white-10.jpg");
    }
}

void Service::addDog(const std::string& breed, const std::string& name, int age, const std::string& link)
{
	Dog newDog(breed, name, age, link);
    DogValidator::validate(newDog);
    this->repo.addDog(newDog);
    this->undoActions.push_back(std::make_unique<UndoAdd>(this->repo, newDog));
    this->redoActions.clear();
}

int Service::getLengthOfRepo() const
{
	return repo.lengthOfRepo();
}

void Service::removeDogServ(const std::string& _name)
{
    Dog d = this->repo.findThatReturnsDog(_name);
    this->repo.removeFromRepo(_name);
    this->undoActions.push_back(std::make_unique<UndoRemove>(this->repo, d));
    this->redoActions.clear();
}

void Service::updateDogServ(const std::string& _name, const std::string& _breed, int _age, const std::string& _link)
{
    Dog updatedDog(_breed, _name, _age, _link);
    DogValidator::validate(updatedDog);
    Dog oldDog = this->repo.findThatReturnsDog(_name);
    this->repo.updateRepo(_name, _breed, _age, _link);
    this->undoActions.push_back(std::make_unique<UndoUpdate>(this->repo, oldDog, updatedDog));
    this->redoActions.clear();
}

std::vector<Dog> Service::getAllServ() const
{
	return repo.getAll();
}

std::vector<Dog> Service::getFilteredRaw(std::string _breed, int _age)
{
    std::vector<Dog> copy = repo.getAll();
    if (_breed.compare("") == 0)
    {
        copy.erase(std::remove_if(
            copy.begin(), copy.end(),
            [_age](const Dog& i) {
                return i.getAge() >= _age;
            }), copy.end());
    }
    else
    {
        copy.erase(std::remove_if(
            copy.begin(), copy.end(),
            [_breed, _age](const Dog& i) {
                return (i.getBreed().compare(_breed) != 0 || i.getAge() >= _age);
            }), copy.end());
    }
    return copy;

}

void Service::undo()
{
    if (undoActions.empty())
    {
        throw RepoExceptionInherited("There are no more actions to undo");
    }
    
    try
    {
        std::unique_ptr<UndoAction> last = move(this->undoActions.back());
        last->doUndo();

        this->undoActions.pop_back();
        this->redoActions.push_back(move(last));
    }
    catch (RepoExceptionInherited& e)
    {
        std::cout << e.what() << "\n";
    }
}

void Service::redo()
{
    if (redoActions.empty())
    {
        throw RepoExceptionInherited("There are no more actions to redo");
    }
    try
    {
        std::unique_ptr<UndoAction> last = move(this->redoActions.back());
        last->doRedo();

        this->redoActions.pop_back();
        this->undoActions.push_back(move(last));
    }
    catch (RepoExceptionInherited& e)
    {
        std::cout << e.what() << "\n";
    }
}