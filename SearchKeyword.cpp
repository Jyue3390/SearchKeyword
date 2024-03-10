#include "SearchKeyword.h"

SearchKeyword::SearchKeyword(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(1200, 600);
	//this->setWindowState(Qt::WindowMaximized);
	setWindowTitle("Search Keyword");

	//背景平铺
	QPixmap bgImage(":/source/_20230905205315.jpg");
	QLabel* label = new QLabel(this);
	label->setGeometry(0, 0, this->width(), this->height());
	label->setStyleSheet("background-color:white");
	label->setPixmap(bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

	button1 = new QPushButton("Hash search", this);
	button2 = new QPushButton("Binary search", this);
	fileButton = new QPushButton("Select File", this);

	button1->setFixedSize(200, 50); // 设置按钮大小
	int x = (width() - button1->width()) / 9;
	int y = (height() - button1->height()) / 9;
	button1->move(3 * x, 9 * y);

	button2->setFixedSize(200, 50); // 设置按钮大小
	button2->move(6 * x, 9 * y);

	fileButton->setFixedSize(200, 50); // 设置按钮大小
	fileButton->move(4.5 * x, 8 * y); // 调整按钮位置

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	x = (screenGeometry.width() - this->width()) / 2;
	y = (screenGeometry.height() - this->height()) / 2;
	// 将窗口移动到屏幕中央
	this->move(x, y);


	// 连接按钮点击信号与槽函数
	connect(fileButton, &QPushButton::clicked, this, &SearchKeyword::chooseFile);
	connect(button1, &QPushButton::clicked, this, &SearchKeyword::showHash);
	connect(button2, &QPushButton::clicked, this, &SearchKeyword::showBin);
}

SearchKeyword::~SearchKeyword()
{}

void SearchKeyword::chooseFile()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("All Files (*.*)"));
	if (!filePath.isEmpty()) {
		program_path = filePath.toStdString();
		out_path1 = program_path.substr(0, program_path.find_last_of(".")) + "_hout.txt";
		out_path2 = program_path.substr(0, program_path.find_last_of(".")) + "_bout.txt";
	}
}
void SearchKeyword::showHash() {
	Hash* hashWindow = new Hash(this);
	hashWindow->createHashTable();
	hashWindow->process1(program_path, out_path1);
	hashWindow->View(QString::fromStdString(out_path1));
	hashWindow->show();
}
void SearchKeyword::showBin() {
	Bin* binWindow = new Bin(this);
	binWindow->createKeywords();
	binWindow->process2(program_path, out_path2);
	binWindow->View(QString::fromStdString(out_path2));
	binWindow->show();
}