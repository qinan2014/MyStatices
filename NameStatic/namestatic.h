#ifndef NAMESTATIC_H
#define NAMESTATIC_H

#include <QtWidgets/QDialog>
#include "ui_namestatic.h"

class NameStatic : public QDialog
{
	Q_OBJECT

public:
	NameStatic(QWidget *parent = 0);
	~NameStatic();

private:
	Ui::NameStaticClass ui;

	void readNameText();
	inline void analyzeDate(char namesdata[]);

	std::wstring StringToWstring(const std::string str);
	std::string WstringToString(const std::wstring str);
};

#endif // NAMESTATIC_H
