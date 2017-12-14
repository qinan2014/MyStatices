#ifndef NAMESTATIC_H
#define NAMESTATIC_H

#include <QtWidgets/QDialog>
#include "ui_namestatic.h"

class NameStatic : public QDialog
{
	Q_OBJECT

public:
#define NAMELEN 4
#define NAMESCOUNT 6
	struct PositionInPosName 
	{
		wchar_t personName[NAMESCOUNT][NAMELEN];
		short serviceTimes;

		PositionInPosName(wchar_t inName[NAMELEN])
		{
			int namalen = wcslen(inName);
			if (namalen > NAMELEN)
				namalen = NAMELEN;
			for (int i = 0; i < namalen; ++i)
			{
				personName[0][i] = inName[i];
			}
			personName[0][namalen] = 0;
			serviceTimes = 1;
			for (int i = 1; i < NAMESCOUNT; ++i)
			{
				personName[i][0] = 0;
			}
		}

		void setName(int pIndex, wchar_t inName[NAMELEN])
		{
			int namalen = wcslen(inName);
			if (namalen > NAMELEN)
				namalen = NAMELEN;
			for (int i = 0; i < namalen; ++i)
			{
				personName[pIndex][i] = inName[i];
			}
			personName[pIndex][namalen] = 0;
		}

		bool isEqualName(wchar_t inName[NAMELEN])
		{
			int namelen = wcslen(inName);
			if (namelen > NAMELEN)
				namelen = NAMELEN;
			for (int i = 0; i < NAMESCOUNT; ++i)
			{
				bool isEqualThisName = true;
				for (int j = 0; j < namelen; ++j)
				{
					if (personName[i][j] != inName[j])
					{
						isEqualThisName = false;
						break;
					}
				}
				if (isEqualThisName)
					return true;
			}
			return false;
		}
	};
	NameStatic(QWidget *parent = 0);
	~NameStatic();

private:
	Ui::NameStaticClass ui;
	std::vector<PositionInPosName> allNames;

	void readServerPositionNames();
	void addServiceName(char namesdata[]);


	void readNameText();
	inline void analyzeDate(char namesdata[]);
	bool is2017year(char namesline[]);
	bool isNameChar(wchar_t pchar);

	void printStatics();
	void printStaticsByOrder();

	void dicomposeNameLine(wchar_t *pNameLine);
	int getFirstName(wchar_t *pNameLine, wchar_t outName[]); // 返回第一个名字的结尾index
	void staticNames(wchar_t inName[]);

	std::wstring StringToWstring(const std::string str);
	std::string WstringToString(const std::wstring str);
};

#endif // NAMESTATIC_H
