#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setWindowState(Qt::WindowMaximized);
	setWindowTitle("Game Login");

	//设置窗口大小
	this->setFixedSize(1200, 600);
	//背景平铺
	QPixmap bgImage(":/source/_20230905205412_1.jpg");
	QLabel* label = new QLabel(this);
	label->setGeometry(0, 0, this->width(), this->height());
	label->setStyleSheet("background-color:white");
	label->setPixmap(bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

	//enterButton按钮
	enterButton = new QPushButton("enter", this);
	enterButton->setFixedSize(100, 50); // 设置按钮大小
	int x = (width() - enterButton->width()) / 2;
	int y = (height() - enterButton->height()) / 10;
	enterButton->move(x, 9 * y); // 将按钮移动到指定位置

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	x = (screenGeometry.width() - this->width()) / 2;
	y = (screenGeometry.height() - this->height()) / 2;
	// 将窗口移动到屏幕中央
	this->move(x, y);

	connect(enterButton, &QPushButton::clicked, this, &LoginPage::enter);
	//连接点击按钮的信号和进入商店的槽
}

LoginPage::~LoginPage()
{}
void LoginPage::enter() {
	qDebug() << "enter";
	this->hide();
	SearchKeyword* window = new SearchKeyword(this);
	window->show();
}