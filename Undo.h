#pragma once
#include "Dog.h"
#include "Repo.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual ~UndoAction() {}
};

class UndoAdd : public UndoAction {
private:
	Dog addedDog;
	Repo& repo;
public:
	UndoAdd(Repo& repo, const Dog& d) : repo(repo), addedDog(d) {}

	void doUndo()
	{
		repo.removeFromRepo(addedDog.getName());
	}

	void doRedo()
	{
		repo.addDog(addedDog);
	}
};

class UndoRemove : public UndoAction {
private:
	Dog removedDog;
	Repo& repo;
public:
	UndoRemove(Repo& repo, const Dog& d) : repo(repo), removedDog(d) {}

	void doUndo()
	{
		repo.addDog(removedDog);
	}

	void doRedo()
	{
		repo.removeFromRepo(removedDog.getName());
	}
};

class UndoUpdate : public UndoAction {
private:
	Dog oldDog, newDog;
	Repo& repo;
public:
	UndoUpdate(Repo& repo, const Dog& oldDog, const Dog& newDog) : repo(repo), oldDog(oldDog), newDog(newDog) {}

	void doUndo()
	{
		repo.updateRepo(newDog.getName(), oldDog.getBreed(), oldDog.getAge(), oldDog.getLink());
	}

	void doRedo()
	{
		repo.updateRepo(oldDog.getName(), newDog.getBreed(), newDog.getAge(), newDog.getLink());
	}
};