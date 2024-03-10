#pragma once

#include "ui_Bin.h"
#include"head.h"

class Bin : public QMainWindow {
	Q_OBJECT
private:
	struct keybin {
		string keyword = "";//关键字
		int freq = 0;//出现频率
		int count = 0;//查找次数
		bool operator< (const keybin& W)const {
			return keyword < W.keyword;
		}
	}keywords[MAX_T];//
	Ui::BinClass ui;
public:
	Bin(QWidget* parent = nullptr);
	~Bin();
	std::ostringstream Bin::output;
	void BinSearch(string str) {
		int left = 0, right = MAX_T;
		int mid, cnt = 0;
		bool success = false;
		while (left <= right) {
			mid = (left + right) / 2;
			if (str < keywords[mid].keyword)
				right = mid - 1;
			else if (str > keywords[mid].keyword)
				left = mid + 1;
			else if (str == keywords[mid].keyword)
			{
				keywords[mid].freq++;
				cnt++;
				success = true;
				break;
			}
			cnt++;
		}
		if (success)
			keywords[mid].count += cnt;
	}
	void process2(string program_path, string out_path)
	{
		ifstream prog(program_path);
		if (!prog.is_open()) {
			QMessageBox::warning(this, tr("Error"), tr("Read file error"));
			return;
		}
		char c;
		string word = "";
		prog >> std::noskipws;
		while (prog >> c) {
			while (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
			{
				prog >> c;
				if (prog.eof()) {
					break;
				}
			}
			if (prog.eof()) {
				break;
			}
			while ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))    //记录下关键字内容   
			{
				word += c;
				prog >> c;
			}
			BinSearch(word);
			word = "";
		}

		std::ofstream output;
		output.open(out_path);
		output << program_path;
		output << "\n\t\t\t\t\t文件存在的关键字\n\n\t关键字\t\t   出现频度\t\t总查找次数   \t平均查找次数" << std::endl;
		for (int i = 0; i < MAX_T; i++) {
			if (keywords[i].freq != 0) {
				output << std::right << setw(13) <<
					keywords[i].keyword << setw(20) <<
					keywords[i].freq << setw(20) << keywords[i].count
					<< setw(20) << keywords[i].count / keywords[i].freq << endl;
			}
		}

	}
	void createKeywords()
	{
		ifstream file("keyword.txt");
		int i = 0;
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				keywords[i++].keyword = line; // 将读取的一行字符串存入数组
			}
			file.close();
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Read file error"));
			return;
		}
		sort(keywords, keywords + MAX_T);
	}
	void View(QString fileName)
	{
		//QString fileName = "bin_output.txt";
		QFile file(fileName);
		// 当文件无法进行读操作的时候，将弹出信息框
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Error"), tr("read file error:&1").arg(file.errorString()));
			return;
		}
		// 定义文本流
		QTextStream in(&file);
		// 创建一个 QTextEdit 对象
		QTextEdit* textEditFileShow = new QTextEdit(this);
		// 设置字体大小
		QFont font = textEditFileShow->font();
		font.setPointSize(font.pointSize() + 1); // 调大一号
		textEditFileShow->setFont(font);
		// 将文件内容读取并设置为 QTextEdit 的文本
		textEditFileShow->setText(in.readAll());
		textEditFileShow->setStyleSheet("background-color: transparent;");

		// 设置窗口标题
		this->setWindowTitle(fileName);
		// 将 textEditFileShow 添加为中央部件
		setCentralWidget(textEditFileShow);
	}
};
