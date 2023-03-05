#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <sstream>
#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextEdit>
#include <string>
#include <vector>
#include "ui_a14Nyesteban.h"
#include "Service.h"
#include "FileException.h"
#include <QInputDialog>

class a14Nyesteban : public QMainWindow
{
    Q_OBJECT

public:
    a14Nyesteban(Service& s, QWidget* parent = 0);
    ~a14Nyesteban();

protected:
    Ui::a14NyestebanClass ui;
    void buildWindow();
    void connectSignalsAndSlots();
    Service& s;
    int itD;
    std::vector<Dog> copy;
    std::vector<Dog> userLst;
    QListWidget* list3;
    void populateList();

private:
    QListWidget* textEdit;
    QLineEdit* filterTextBox;
    QList<QString> filteredDogs;
    QLineEdit* breedTextBox;
    QLineEdit* nameTextBox;
    QLineEdit* ageTextBox;
    QLineEdit* linkTextBox;
    QPushButton* addDogButton;
    QPushButton* deleteDogButton;
    QPushButton* updateDogButton;
    QPushButton* showDogButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QListWidget* list2;
    QPushButton* nextUserButton;
    QPushButton* showUserButton;
    QPushButton* filterUserButton;
    QPushButton* adoptUserButton;
    QLineEdit* breedTextBoxuser;
    QLineEdit* ageTextBoxuser;
    QTabWidget* tabWidget;
    QAction* undoAction;
    QAction* redoAction;
    QPushButton* showAdoptionsTable;
    void updateDogs();
    int getSelectedIndexAdmin();
    void listItemChangedAdmin();
    void addDogButtonHandler();
    void deleteDogButtonHandler();
    void updateDogButtonHandler();
    void showDogButtonHandler();
    void populateIterator();
    virtual void beginUser();
    void nextUserButtonHandler();
    void adoptUserButtonHandler();
    void showUserButtonHandler();
    void filterUserButtonHandler();
    void undoButtonHandler();
    void redoButtonHandler();
    void tableHandler();
signals:
    void updatedSignal();
    void addDogSignal(const std::string& breed, const std::string& name, const std::string& age, const std::string& link);
    void deleteDogSignal(const std::string& name);
    void updateDogSignal(const std::string& name, const std::string& breed, const std::string& age, const std::string& link);
    void filterUserSignal(const std::string& breed, const std::string& age);
    void undoSignal();
    void redoSignal();
public slots:
    void addDogUI(const std::string& breed, const std::string& name, const std::string& age, const std::string& link);
    void deleteDogUI(const std::string& name);
    void updateDogUI(const std::string& name, const std::string& breed, const std::string& age, const std::string& link);
    void filterUser(const std::string& breed, const std::string& age);
    void undoUI();
    void redoUI();
};

class a14NyestebanCSV : public a14Nyesteban
{
public:
    a14NyestebanCSV(Service& s, QWidget* parent = 0);
private:
    void beginUser();
};

class a14NyestebanHTML : public a14Nyesteban
{
public:
    a14NyestebanHTML(Service& s, QWidget* parent = 0);
private:
    void beginUser();
};


class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(std::vector<Dog> lst, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
protected:
    std::vector<Dog> lst;
};