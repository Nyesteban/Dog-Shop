#include "a14Nyesteban.h"

a14Nyesteban::a14Nyesteban(Service& s, QWidget* parent)
	: s(s), QMainWindow(parent)
{
	ui.setupUi(this);
	this->buildWindow();
	this->connectSignalsAndSlots();
}

void a14Nyesteban::buildWindow()
{
	tabWidget = new QTabWidget;
	QWidget* wnd = new QWidget{};
	QHBoxLayout* hL = new QHBoxLayout{};
	QVBoxLayout* vL = new QVBoxLayout{};
	wnd->setLayout(hL);

	filterTextBox = new QLineEdit{};
	textEdit = new QListWidget;
	populateList();
	QLabel* list1Label = new QLabel{ "&Dogs" };
	list1Label->setBuddy(textEdit);

	filterTextBox->connect(
		filterTextBox,
		&QLineEdit::textChanged,
		this,
		&a14Nyesteban::updateDogs
	);

	vL->addWidget(filterTextBox);
	vL->addWidget(list1Label);
	vL->addWidget(textEdit);

	QFormLayout* formLayout = new QFormLayout{};

	// create labels and textboxes
	breedTextBox = new QLineEdit{};
	QLabel* breedLabel = new QLabel{ "&Breed:" };
	breedLabel->setBuddy(breedTextBox);

	nameTextBox = new QLineEdit{};
	QLabel* nameLabel = new QLabel{ "&Name:" };
	nameLabel->setBuddy(nameTextBox);

	ageTextBox = new QLineEdit{};
	QLabel* ageLabel = new QLabel{ "&Age:" };
	ageLabel->setBuddy(ageTextBox);

	linkTextBox = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "&Link:" };
	linkLabel->setBuddy(linkTextBox);

	formLayout->addRow(breedLabel, breedTextBox);
	formLayout->addRow(nameLabel, nameTextBox);
	formLayout->addRow(ageLabel, ageTextBox);
	formLayout->addRow(linkLabel, linkTextBox);

	vL->addLayout(formLayout);

	QGridLayout* gridLayout = new QGridLayout{};
	addDogButton = new QPushButton("Add");
	gridLayout->addWidget(addDogButton, 0, 0);
	deleteDogButton = new QPushButton("Delete");
	gridLayout->addWidget(deleteDogButton, 0, 1);
	updateDogButton = new QPushButton("Update");
	gridLayout->addWidget(updateDogButton, 0, 2);
	showDogButton = new QPushButton("Show");
	gridLayout->addWidget(showDogButton, 1, 1);
	undoButton = new QPushButton("Undo");
	gridLayout->addWidget(undoButton, 1, 0);
	redoButton = new QPushButton("Redo");
	gridLayout->addWidget(redoButton, 1, 2);

	vL->addLayout(gridLayout);

	hL->addLayout(vL);

	tabWidget->addTab(wnd, "Admin");

	undoAction = new QAction("Undo", this);
	undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
	redoAction = new QAction("Redo", this);
	redoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));

	wnd->addAction(undoAction);
	wnd->addAction(redoAction);

	QWidget* wnd2 = new QWidget{};

	QHBoxLayout* hL2 = new QHBoxLayout{};

	wnd2->setLayout(hL2);

	QVBoxLayout* vLuser = new QVBoxLayout{};

	list2 = new QListWidget{};
	//new QListWidgetItem("firstentry", list2);
	QLabel* list2Label = new QLabel{ "&User Dogs Iterator" };
	list2Label->setBuddy(list2);

	vLuser->addWidget(list2Label);
	vLuser->addWidget(list2);

	QGridLayout* gridLayoutuser = new QGridLayout{};
	nextUserButton = new QPushButton("Next");
	gridLayoutuser->addWidget(nextUserButton, 0, 0);
	adoptUserButton = new QPushButton("Adopt");
	gridLayoutuser->addWidget(adoptUserButton, 0, 1);
	showUserButton = new QPushButton("Show");
	gridLayoutuser->addWidget(showUserButton, 0, 2);
	filterUserButton = new QPushButton("Filter");
	gridLayoutuser->addWidget(filterUserButton, 1, 1);


	vLuser->addLayout(gridLayoutuser);

	QFormLayout* formLayoutuser = new QFormLayout{};

	// create labels and textboxes
	breedTextBoxuser = new QLineEdit{};
	QLabel* breedLabeluser = new QLabel{ "&Breed:" };
	breedLabeluser->setBuddy(breedTextBoxuser);

	ageTextBoxuser = new QLineEdit{};
	QLabel* ageLabeluser = new QLabel{ "&Age:" };
	ageLabeluser->setBuddy(ageTextBoxuser);

	formLayoutuser->addRow(breedLabeluser, breedTextBoxuser);
	formLayoutuser->addRow(ageLabeluser, ageTextBoxuser);

	vLuser->addLayout(formLayoutuser);

	hL2->addLayout(vLuser);

	QVBoxLayout* vLadoption = new QVBoxLayout{};

	list3 = new QListWidget{};
	QLabel* list3Label = new QLabel{ "&Adoption List" };
	list3Label->setBuddy(list3);

	vLadoption->addWidget(list3Label);
	vLadoption->addWidget(list3);

	showAdoptionsTable = new QPushButton("Table");
	vLadoption->addWidget(showAdoptionsTable);

	hL2->addLayout(vLadoption);

	tabWidget->addTab(wnd2, "User");

	QLinearGradient buttonGradient(0, 0, 0, textEdit->height());
	buttonGradient.setColorAt(0, QColor(100, 120, 140));
	buttonGradient.setColorAt(1, QColor(160, 180, 200));
	QPalette palette = qApp->palette();
	palette.setBrush(QPalette::Base, buttonGradient);
	palette.setBrush(QPalette::Highlight, buttonGradient);
	palette.setBrush(QPalette::HighlightedText, Qt::white);
	palette.setBrush(QPalette::Text, Qt::white);
	textEdit->setPalette(palette);


	this->setCentralWidget(tabWidget);
}

a14Nyesteban::~a14Nyesteban()
{

}

void a14Nyesteban::updateDogs()
{
	auto filterText = filterTextBox->text().toStdString();
	filteredDogs.clear();
	for (int i = 0; i < textEdit->count(); ++i)
	{
		if (textEdit->item(i)->text().contains(filterText.c_str(), Qt::CaseInsensitive))
			filteredDogs.append(textEdit->item(i)->text());
	}
	textEdit->clear();
	for (auto elem : filteredDogs)
		textEdit->addItem(elem);
	if (filterText == "")
		populateList();
}

void a14Nyesteban::connectSignalsAndSlots()
{
	QObject::connect(this, &a14Nyesteban::updatedSignal, this, &a14Nyesteban::populateList);
	QObject::connect(this->textEdit, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChangedAdmin(); });
	QObject::connect(this->addDogButton, &QPushButton::clicked, this, &a14Nyesteban::addDogButtonHandler);
	QObject::connect(this, SIGNAL(addDogSignal(const std::string&, const std::string&, const std::string&, const std::string&)),
		this, SLOT(addDogUI(const std::string&, const std::string&, const std::string&, const std::string&)));
	QObject::connect(this->deleteDogButton, &QPushButton::clicked, this, &a14Nyesteban::deleteDogButtonHandler);
	QObject::connect(this, SIGNAL(deleteDogSignal(const std::string&)), this, SLOT(deleteDogUI(const std::string&)));
	QObject::connect(this->updateDogButton, &QPushButton::clicked, this, &a14Nyesteban::updateDogButtonHandler);
	QObject::connect(this, SIGNAL(updateDogSignal(const std::string&, const std::string&, const std::string&, const std::string&)),
		this, SLOT(updateDogUI(const std::string&, const std::string&, const std::string&, const std::string&)));
	QObject::connect(this->showDogButton, &QPushButton::clicked, this, &a14Nyesteban::showDogButtonHandler);
	QObject::connect(this->tabWidget, &QTabWidget::currentChanged, this, [this]() {this->beginUser(); this->populateIterator(); });
	QObject::connect(this->nextUserButton, &QPushButton::clicked, this, &a14Nyesteban::nextUserButtonHandler);
	QObject::connect(this->adoptUserButton, &QPushButton::clicked, this, &a14Nyesteban::adoptUserButtonHandler);
	QObject::connect(this->showUserButton, &QPushButton::clicked, this, &a14Nyesteban::showUserButtonHandler);
	QObject::connect(this->filterUserButton, &QPushButton::clicked, this, &a14Nyesteban::filterUserButtonHandler);
	QObject::connect(this, SIGNAL(filterUserSignal(const std::string&, const std::string&)), this, SLOT(filterUser(const std::string&, const std::string&)));
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &a14Nyesteban::undoButtonHandler);
	QObject::connect(this, SIGNAL(undoSignal()), this, SLOT(undoUI()));
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &a14Nyesteban::redoButtonHandler);
	QObject::connect(this, SIGNAL(redoSignal()), this, SLOT(redoUI()));
	QObject::connect(this->undoAction, &QAction::triggered, this, &a14Nyesteban::undoButtonHandler);
	QObject::connect(this->redoAction, &QAction::triggered, this, &a14Nyesteban::redoButtonHandler);
	QObject::connect(this->showAdoptionsTable, &QPushButton::clicked, this, &a14Nyesteban::tableHandler);
}

void a14Nyesteban::addDogButtonHandler()
{
	QString breed = this->breedTextBox->text();
	QString name = this->nameTextBox->text();
	QString age = this->ageTextBox->text();
	QString link = this->linkTextBox->text();

	emit addDogSignal(breed.toStdString(), name.toStdString(), age.toStdString(), link.toStdString());
}

void a14Nyesteban::deleteDogButtonHandler()
{
	QString name = this->nameTextBox->text();

	emit deleteDogSignal(name.toStdString());
}

void a14Nyesteban::updateDogButtonHandler()
{
	QString breed = this->breedTextBox->text();
	QString name = this->nameTextBox->text();
	QString age = this->ageTextBox->text();
	QString link = this->linkTextBox->text();

	emit updateDogSignal(name.toStdString(), breed.toStdString(), age.toStdString(), link.toStdString());
}

void a14Nyesteban::showDogButtonHandler()
{
	int idx = this->getSelectedIndexAdmin();
	if (idx == -1)
		return;

	if (idx >= this->s.getAllServ().size())
		return;
	Dog d = this->s.getAllServ()[idx];
	d.play();
}

void a14Nyesteban::addDogUI(const std::string& breed, const std::string& name, const std::string& age, const std::string& link)
{
	try
	{
		int a = stoi(age);
		s.addDog(breed, name, a, link);
		emit updatedSignal();
	}
	catch (const ValidationException& ve)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ve.getMessage().c_str());
	}
	catch (const RepoExceptionInherited& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
	catch (const std::invalid_argument& ie) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
	catch (const std::out_of_range& oe) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
}

void a14Nyesteban::deleteDogUI(const std::string& name)
{
	try
	{
		s.removeDogServ(name);
		emit updatedSignal();
	}
	catch (const RepoExceptionInherited& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
}

void a14Nyesteban::updateDogUI(const std::string& name, const std::string& breed, const std::string& age, const std::string& link)
{
	try
	{
		int a = stoi(age);
		s.updateDogServ(name, breed, a, link);
		emit updatedSignal();
	}
	catch (const ValidationException& ve)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ve.getMessage().c_str());
	}
	catch (const RepoExceptionInherited& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
	catch (const std::invalid_argument& ie) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
	catch (const std::out_of_range& oe) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
}

void a14Nyesteban::populateList()
{
	std::vector<Dog> all = s.getAllServ();
	std::stringstream dogstream;
	dogstream.str("");
	textEdit->clear();
	for (auto i : all)
	{
		dogstream << i;
		const std::string& tmp = dogstream.str();
		const char* cstr = tmp.c_str();
		new QListWidgetItem(cstr, textEdit);
		dogstream.str("");
	}
}

int a14Nyesteban::getSelectedIndexAdmin()
{
	if (this->textEdit->count() == 0)
		return -1;

	// get selected index
	QModelIndexList index = this->textEdit->selectionModel()->selectedIndexes();

	if (index.size() == 0)
	{
		this->breedTextBox->clear();
		this->nameTextBox->clear();
		this->breedTextBox->clear();
		this->linkTextBox->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void a14Nyesteban::listItemChangedAdmin()
{
	int idx = this->getSelectedIndexAdmin();
	if (idx == -1)
		return;

	if (idx >= this->s.getAllServ().size())
		return;
	Dog d = this->s.getAllServ()[idx];

	this->breedTextBox->setText(QString::fromStdString(d.getBreed()));
	this->nameTextBox->setText(QString::fromStdString(d.getName()));
	this->ageTextBox->setText(QString::number(d.getAge()));
	this->linkTextBox->setText(QString::fromStdString(d.getLink()));
}

void a14Nyesteban::populateIterator()
{
	std::vector<Dog> all = copy;
	if (all.size() == 0)
	{
		list2->clear();
		return;
	}
	std::stringstream dogstream;
	dogstream.str("");
	list2->clear();
	dogstream << all[itD];
	const std::string& tmp = dogstream.str();
	const char* cstr = tmp.c_str();
	new QListWidgetItem(cstr, list2);
	dogstream.str("");
}

void a14Nyesteban::beginUser()
{
	itD = 0;
	if (list3->count() > 0)
	{
		list3->clear();
		for (auto d : userLst)
			s.removeDogServ(d.getName());
		userLst.clear();
	}
	copy = s.getAllServ();
	populateList();
}

void a14Nyesteban::nextUserButtonHandler()
{
	if (s.getLengthOfRepo() == 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more dogs!");
		return;
	}
	itD++;
	if (itD >= copy.size())
		itD = 0;
	populateIterator();
}

void a14Nyesteban::adoptUserButtonHandler()
{
	if (s.getLengthOfRepo() == 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more dogs!");
		return;
	}
	Dog d = copy[itD];
	for (auto i : userLst)
	{
		if (i.getName() == d.getName() && i.getAge() == d.getAge() && i.getLink() == d.getLink())
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", "Dog already in adoption list!");
			return;
		}
	}
	userLst.push_back(d);
	std::stringstream dogstream;
	dogstream.str("");
	dogstream << copy[itD];
	const std::string& tmp = dogstream.str();
	const char* cstr = tmp.c_str();
	new QListWidgetItem(cstr, list3);
}

void a14Nyesteban::showUserButtonHandler()
{
	if (s.getLengthOfRepo() == 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more dogs!");
		return;
	}
	copy[itD].play();
}

void a14Nyesteban::filterUserButtonHandler()
{
	if (s.getLengthOfRepo() == 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more dogs!");
		return;
	}
	QString breed = this->breedTextBoxuser->text();
	QString age = this->ageTextBoxuser->text();

	emit filterUserSignal(breed.toStdString(), age.toStdString());
}

void a14Nyesteban::filterUser(const std::string& breed, const std::string& age)
{
	try
	{
		itD = 0;
		if (breed == "" && age == "")
		{
			copy = s.getAllServ();
			populateIterator();
			return;
		}
		int a = stoi(age);
		copy = s.getFilteredRaw(breed, a);
		if (copy.size() <= 0)
		{
			throw "No dogs matching the criteria found.";
		}
		populateIterator();
	}
	catch (const char* e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e);
	}
	catch (const std::invalid_argument& ie) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
	catch (const std::out_of_range& oe) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Please enter a valid age");
	}
}

a14NyestebanCSV::a14NyestebanCSV(Service& s, QWidget* parent)
	: a14Nyesteban(s, parent)
{

}

a14NyestebanHTML::a14NyestebanHTML(Service& s, QWidget* parent)
	: a14Nyesteban(s, parent)
{

}

void a14NyestebanCSV::beginUser()
{
	itD = 0;
	if (list3->count() > 0)
	{
		list3->clear();
		std::ofstream file("example.csv");
		if (!file.is_open())
			throw FileException("The file could not be opened!");;
		for (auto d : userLst)
		{
			file << d << "\n";
			s.removeDogServ(d.getName());
		}
		file.close();
		userLst.clear();
		ShellExecuteA(0, 0, "example.csv", 0, 0, SW_SHOW);
	}
	copy = s.getAllServ();
	populateList();
}

void a14NyestebanHTML::beginUser()
{
	itD = 0;
	if (list3->count() > 0)
	{
		list3->clear();
		std::ofstream file("example.html");
		if (!file.is_open())
			throw FileException("The file could not be opened!");;

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

		for (auto d : userLst)
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

		for (auto d : userLst)
		{
			s.removeDogServ(d.getName());
		}
		userLst.clear();
		ShellExecuteA(0, 0, "example.html", 0, 0, SW_SHOW);
	}
	copy = s.getAllServ();
	populateList();
}

void a14Nyesteban::undoButtonHandler()
{
	emit undoSignal();
}

void a14Nyesteban::redoButtonHandler()
{
	emit redoSignal();
}

void a14Nyesteban::undoUI()
{
	try
	{
		s.undo();
		emit updatedSignal();
	}
	catch (const RepoExceptionInherited& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
}

void a14Nyesteban::redoUI()
{
	try
	{
		s.redo();
		emit updatedSignal();
	}
	catch (const RepoExceptionInherited& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
}

void a14Nyesteban::tableHandler()
{
	hide();
	QWidget* wtable = new QWidget;
	QVBoxLayout* vLtable = new QVBoxLayout{};
	wtable->setLayout(vLtable);
	QTableView* tableView = new QTableView;
	MyModel* myModel = new MyModel(userLst);
	tableView->setModel(myModel);
	vLtable->addWidget(tableView);
	QPushButton* goBack = new QPushButton("Go back");
	goBack->connect(goBack, &QPushButton::clicked, [this,wtable] { wtable->close(); show(); });
	vLtable->addWidget(goBack);
	wtable->show();
}

MyModel::MyModel(std::vector<Dog> lst, QObject* parent)
	: lst(lst), QAbstractTableModel(parent)
{

}

int MyModel::rowCount(const QModelIndex&) const
{
	return lst.size();
}

int MyModel::columnCount(const QModelIndex&) const
{
	return 4;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
		return QString("%1, %2, %3, %4")
		.arg(lst[index.row()].getBreed().c_str())
		.arg(lst[index.row()].getName().c_str())
		.arg(lst[index.row()].getAge())
		.arg(lst[index.row()].getLink().c_str());

	return QVariant();
}