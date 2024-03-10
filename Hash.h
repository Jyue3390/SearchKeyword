#pragma once

#include"head.h"
#include "ui_Hash.h"

class Hash : public QMainWindow {
	Q_OBJECT
private:
	struct hash {
		std::string keyword = "";
		//int key = 0;
		int h = 0;
		bool flag = false;
		int freq = 0;  // 频度
		int cnt = 0;   // 查找次数
		//hash函数结果
		//int clashCnt = 0;
	} keyword_hash[MAX_T];
	string program_path = "program.txt";//默认路径
	Ui::HashClass ui;

public:
	Hash(QWidget* parent = nullptr);
	~Hash();

	void createHashTable() {
		std::ifstream file("keyword.txt");
		if (!file.is_open()) {
			QMessageBox::warning(this, tr("Error"), tr("Read file error"));
			return;
		}
		std::string line;
		int first, last, loc = 0;
		while (std::getline(file, line)) {
			first = line[0];
			last = line[line.length() - 1];
			loc = (first * 100 + last) % 41;
			int tmp = loc;
			if (keyword_hash[loc].flag == 0) {
				keyword_hash[loc].keyword = line;
				keyword_hash[loc].flag = 1;
				keyword_hash[loc].h = tmp;
			}
			else {
				while (keyword_hash[loc].flag == 1) {
					loc++;
					loc %= 41;
				}
				keyword_hash[loc].flag = 1;
				keyword_hash[loc].keyword = line;
				keyword_hash[loc].h = tmp;
			}
		}
		file.close();
	}

	void process1(string program_path, string out_path) {
		for (int i = 0; i < MAX_T; i++) {
			keyword_hash[i].flag = 0;
			keyword_hash[i].cnt = 0;
		}
		std::ifstream prog(program_path);
		std::ofstream output;

		// 检查文件是否成功打开
		if (!prog.is_open()) {
			// 如果打开失败，弹出错误提示窗口
			QMessageBox::warning(this, tr("Error"), tr("Read file error"));
			return; // 返回，不再继续执行后续逻辑
		}

		char c;
		std::string word = "";
		prog >> std::noskipws;
		while (prog >> c) {
			word = "";
			while (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122))) {
				prog >> c;
				if (prog.eof()) {
					break;
				}
			}
			if (prog.eof()) {
				break;
			}
			while ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
				word += c;
				prog >> c;
			}
			int first = word[0];
			int last = word[word.length() - 1];
			int p = (first * 100 + last) % 41;
			bool success = false;
			if (keyword_hash[p].keyword == word) {
				success = true;
				keyword_hash[p].freq++;
				keyword_hash[p].cnt++;
			}
			else {
				int i;
				for (i = 0; i < 41 && keyword_hash[p].keyword != word && keyword_hash[p].keyword != ""; i++) {
					p++;
					p %= 41;
				}
				if (keyword_hash[p].keyword == word) {
					success = true;
					keyword_hash[p].freq++;
					keyword_hash[p].cnt += i;
				}
			}
			//if (success) {
			//	if (keyword_hash[p].flag == 0) {//没有过
			//		keyword_hash[p].freq = 1; keyword_hash[p].flag = 1;
			//		keyword_hash[p].keyword = word;
			//	}
			//	else {
			//		if (keyword_hash[p].keyword == word)
			//			keyword_hash[p].freq++;
			//		else {
			//			int i, p = 0;
			//			for (i = 0; keyword_hash[p].flag == 1 && keyword_hash[p].keyword != word && keyword_hash[p].keyword != ""; i++) {
			//				p++;
			//				p %= 41;
			//			}
			//			keyword_hash[p].clashCnt += i;
			//			if (keyword_hash[p].keyword == word)
			//				keyword_hash[p].freq++;
			//			else {
			//				keyword_hash[p].keyword = word;
			//				keyword_hash[p].flag = 1;
			//				keyword_hash[p].freq = 1;
			//			}
			//		}
			//	}
			//}
		}

		output.open(out_path);
		output << program_path;
		output << "\n\t\t\t\t文件存在的关键字\n\n\t关键字\t\t   出现频度\t\t总查找次数   \t平均查找次数\n";
		for (int i = 0; i < MAX_T; i++) {
			if (keyword_hash[i].freq) {
				output << std::right << setw(13) << keyword_hash[i].keyword
					<< setw(20) << keyword_hash[i].freq << setw(20) << keyword_hash[i].cnt
					<< setw(20) << keyword_hash[i].cnt / keyword_hash[i].freq << endl;
			}
		}
		output.close();
		prog.close();
	}
	void View(QString fileName)
	{
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly | QFile::Text)) {// 当文件无法进行读操作的时候，将弹出信息框
			QMessageBox::warning(this, tr("Error"), tr("read file error:&1").arg(file.errorString()));
			return;
		}
		QTextStream in(&file);// 定义文本流
		QTextEdit* textEditFileShow = new QTextEdit(this);// 创建一个 QTextEdit 对象

		QFont font = textEditFileShow->font();// 设置字体大小
		font.setPointSize(font.pointSize() + 1); // 调大一号
		textEditFileShow->setFont(font);
		textEditFileShow->setText(in.readAll());// 将文件内容读取并设置为 QTextEdit 的文本
		textEditFileShow->setStyleSheet("background-color: transparent;");
		this->setWindowTitle(fileName);
		setCentralWidget(textEditFileShow);// 将 textEditFileShow 添加为中央部件
	}
};