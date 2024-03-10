#pragma once

#include"head.h"
#include "ui_SearchKeyword.h"
#include"Bin.h"
#include"Hash.h"


class SearchKeyword : public QMainWindow
{
	Q_OBJECT

public:
	SearchKeyword(QWidget* parent = nullptr);
	~SearchKeyword();

private slots://槽
	void showHash();
	void showBin();
	void chooseFile();

private:
	string program_path;
	string out_path1;
	string out_path2;
	Ui::SearchKeywordClass ui;
	QPushButton* fileButton;
	QPushButton* button1;
	QPushButton* button2;
};
