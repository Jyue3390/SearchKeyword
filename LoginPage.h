#pragma once

#include "head.h"
#include "ui_LoginPage.h"
#include"SearchKeyword.h"
class LoginPage : public QMainWindow
{
	Q_OBJECT

public:
	LoginPage(QWidget* parent = nullptr);
	~LoginPage();

public slots:
	void enter();//槽：接受进入商店的信号

	//signals:
	//	void showmain();//显示进入页面

private:
	Ui::LoginPageClass ui;
	QPushButton* enterButton;
};
