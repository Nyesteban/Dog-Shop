#include <QtWidgets/QApplication>
#include "a14Nyesteban.h"
#include "Tests.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	{
		Repo repo1;
		Service serv1(repo1);
		Tests t(serv1);
		t.tests();
	}
	Repo repo("repository.txt");
	Service serv(repo);

	bool ok;
	QString text = QInputDialog::getText(0, "Mode Select",
		"CSV or HTML", QLineEdit::Normal,
		"", &ok);

	if (ok && text.toLower() == "csv") {
		a14NyestebanCSV wcsv(serv);
		a14Nyesteban* w = &wcsv;
		w->show();
		return a.exec();
	}
	else if (ok && text.toLower() == "html")
	{
		a14NyestebanHTML whtml(serv);
		a14Nyesteban* w = &whtml;
		w->show();
		return a.exec();
	}
}