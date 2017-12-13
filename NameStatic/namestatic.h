#ifndef NAMESTATIC_H
#define NAMESTATIC_H

#include <QtWidgets/QDialog>
#include "ui_namestatic.h"

class NameStatic : public QDialog
{
	Q_OBJECT

public:
#define NAMELEN 4
	struct StaticName 
	{
		wchar_t standname[NAMELEN];
		wchar_t logoname1[NAMELEN];
		wchar_t logoname2[NAMELEN];
		wchar_t logoname3[NAMELEN];
		short serviceTimes;
	};
	NameStatic(QWidget *parent = 0);
	~NameStatic();

private:
	Ui::NameStaticClass ui;
	std::vector<StaticName> allNames;

	void readNameText();
	inline void analyzeDate(char namesdata[]);
	bool is2017year(char namesline[]);
	bool isNameChar(wchar_t pchar);

	void dicomposeNameLine(wchar_t *pNameLine);
	int getFirstName(wchar_t *pNameLine, wchar_t outName[]); // 返回第一个名字的结尾index

	std::wstring StringToWstring(const std::string str);
	std::string WstringToString(const std::wstring str);
};

#endif // NAMESTATIC_H
