#include "Bin.h"

Bin::Bin(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(900, 1000);
	QPixmap bgImage(":/source/_20230905205416.png");
	QLabel* label = new QLabel(this);
	label->setGeometry(0, 0, this->width(), this->height());
	label->setStyleSheet("background-color:white");
	label->setPixmap(bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

	/*createKeywords();
	process2();*/
	//View();

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width() - this->width()) / 2;
	int y = (screenGeometry.height() - this->height()) / 2;
	// 将窗口移动到屏幕中央
	this->move(x, y);

	//this->show();
}

Bin::~Bin()
{}
