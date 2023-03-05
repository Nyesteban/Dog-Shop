#include "Tests.h"
#include <iostream>
#include <assert.h>
#include <exception>
#include <Windows.h>

Tests::Tests(Service& s) : service(s)
{

}

void Tests::tests()
{
    /*
    service.addDog("Labrador", "Tim", 10, "https://www.taramulanimalelor.com/wp-content/uploads/2020/10/Labrador-caracteristici-rasa-caine.jpg");
    service.addDog("Rottweiler", "Max", 2, "https://www.animalepierdute.ro/wp-content/uploads/2019/09/Rottweiler.jpg");
    service.addDog("Affenpinscher", "Cooper", 1, "https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2020/05/21144745/Affenpinscher-running.jpg");
    service.addDog("Border Collie", "Charlie", 3, "https://i.differencevs.com/preview/animals/6858143-difference-between-collie-and-border-collie.jpg");
    service.addDog("Boxer", "Teddy", 1, "https://s36700.pcdn.co/wp-content/uploads/2019/03/Close-up-of-a-Boxer-with-tongue-out-happy.jpg.optimal.jpg");
    service.addDog("Barbet", "Kobe", 7, "https://www.akc.org/wp-content/uploads/2017/11/Barbet-standing-in-the-snow.jpg");
    service.addDog("Husky", "Oscar", 9, "https://www.zooplus.ro/ghid/wp-content/uploads/2021/11/Caini-din-rasa-Husky-Siberian.-Adult-si-pui.jpg");
    service.addDog("Border Terrier", "Bo", 3, "https://vetwork.co/galaxy/wp-content/uploads/8-face.jpg");
    service.addDog("Akita Inu", "Buddy", 8, "https://brit-petfood.com/file/nodes/product/akitainu.jpg");
    service.addDog("Bull Terrier", "Walter", 10, "https://www.akc.org/wp-content/uploads/2017/11/bull-terrier-on-white-10.jpg");*/
    try
    {
        service.addDog("Bull Terrier", "Walter", 10, "https://www.akc.org/wp-content/uploads/2017/11/bull-terrier-on-white-10.jpg");
    }
    catch (const RepoExceptionInherited&) {
        assert(1);
    }
    return;
    try
    {
        service.removeDogServ("Timmy") ;
    }
    catch (const RepoExceptionInherited&) {
        assert(1);
    }
    service.removeDogServ("Walter");
    assert(service.getLengthOfRepo() == 9);
    service.addDog("Bull Terrier", "Walter", 10, "https://www.akc.org/wp-content/uploads/2017/11/bull-terrier-on-white-10.jpg");
    std::vector<Dog> lst = service.getAllServ();
    assert(lst[0].getBreed() == "Labrador");
    try {
        service.updateDogServ("Joe", "Shiba Inu", 9, "https://pisicutesicaini.ro/wp-content/uploads/2021/06/Shiba-Inu-standing-in-profile-outdoors.jpg");
    }
    catch (const RepoExceptionInherited&) {
        assert(1);
    }
    catch(const ValidationException&) {
        assert(1);
    }
    service.updateDogServ("Walter", "Shiba Inu", 9, "https://pisicutesicaini.ro/wp-content/uploads/2021/06/Shiba-Inu-standing-in-profile-outdoors.jpg");
    std::vector<Dog> tst = service.getAllServ();
    assert(tst[9].getAge() == 9);
    assert(tst[9].getName() == "Walter");
    assert(tst[9].getLink() == "https://pisicutesicaini.ro/wp-content/uploads/2021/06/Shiba-Inu-standing-in-profile-outdoors.jpg");
    bool exceptionThrown = false;
    try
    {
        tst[9].play();
    }
    catch (const std::exception&)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown == false);
    service.addDog("AAA", "A", 1, "1");
    service.addDog("BBB", "B", 2, "2");
    service.removeDogServ("A");
    service.removeDogServ("B");
    std::vector<Dog> arr1 = service.getAllServ();
    assert(arr1[9].getAge() == 9);
    std::vector<Dog> arr2 = service.getFilteredRaw("Rottweiler", 3);
    assert(arr2[0].getName().compare("Max") == 0);
    assert(arr2.size() == 1);
    std::vector<Dog> arr3 = service.getFilteredRaw("", 2);
    assert(arr3.size() == 2);
    assert(arr3[0].getName().compare("Cooper") == 0);
}