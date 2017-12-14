#include "namestatic.h"

NameStatic::NameStatic(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	readServerPositionNames();
	readNameText();
}

NameStatic::~NameStatic()
{

}

void NameStatic::readNameText()
{
#define LINELEN 1024
	char filename[] = "D:\\QinAn\\CompanyProgram\\GitTest\\MyNameStatices\\names.txt"; //文件名
	FILE *fp; 
	char StrLine[LINELEN];             //每行最大读取的字符数
	if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
	{ 
		return; 
	} 

	while (!feof(fp)) 
	{ 
		fgets(StrLine,LINELEN,fp);  //读取一行
		analyzeDate(StrLine);
	} 
	fclose(fp);
#undef LINELEN
	//printStatics();
	printStaticsByOrder();
}

void NameStatic::readServerPositionNames()
{
#define LINELEN 1024
	char filename[] = "services_persion_names.txt"; //文件名
	FILE *fp; 
	char StrLine[LINELEN];             //每行最大读取的字符数
	if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
	{ 
		return; 
	} 

	while (!feof(fp)) 
	{ 
		fgets(StrLine,LINELEN,fp);  //读取一行
		addServiceName(StrLine);
	} 
	fclose(fp);
#undef LINELEN
}

void NameStatic::addServiceName(char namesdata[])
{
	// 去掉最前面的空格
	int datalen = strlen(namesdata);
	int datapos = 0;
	for (int i = 0; i < datalen; ++i)
	{
		char tmpdata = namesdata[i];
		if (namesdata[i] != ' ')
		{
			datapos = i;
			break;
		}
	}

	std::wstring lines = StringToWstring(namesdata + datapos);
	int linelen = lines.length();
	wchar_t namesLine[512];
	for (int i = 0; i < linelen; ++i)
	{
		namesLine[i] = lines[i];
	}
	namesLine[linelen] = 0;

	int nameEndpos = 0;
	allNames.push_back(PositionInPosName(L""));
	PositionInPosName &tmpName = allNames[allNames.size() - 1];
	tmpName.serviceTimes = 0;
	int nameIndex = 0;
	while (nameEndpos < linelen)
	{
		wchar_t nameToGet[NAMELEN];
		int tmpendpos = getFirstName(namesLine + nameEndpos, nameToGet);
		tmpName.setName(nameIndex, nameToGet);
		if (tmpendpos == 0)
			break;
		nameEndpos += tmpendpos;
		++nameIndex;
	}
}

void NameStatic::printStatics()
{
	FILE * fp = NULL;
	if((fp = fopen("staticsResult.txt", "w")) != NULL)
	{
		int namesz = allNames.size();
		std::string tmpName;
		char tmpbuf[512];
		for (int i = 0; i < namesz; ++i)
		{
			if (wcslen(allNames[i].personName[0]) > 0)
			{
				tmpName = WstringToString(allNames[i].personName[0]);
				fwrite(tmpName.c_str(), tmpName.length(), 1, fp);
				sprintf(tmpbuf, "       %d次", allNames[i].serviceTimes);
				fwrite(tmpbuf, strlen(tmpbuf), 1, fp);
				fwrite("\r\n", strlen("\r\n"), 1, fp);
			}
		}
		fclose(fp);
	}
}

// 最多次数50；最低次数0次，排序打印
void NameStatic::printStaticsByOrder()
{
	FILE * fp = NULL;
	if((fp = fopen("staticsResult.txt", "w")) != NULL)
	{
		int namesz = allNames.size();
		std::string tmpName;
		char tmpbuf[512];
		for (int m = 50; m > 0; --m)
		{
			for (int i = 0; i < namesz; ++i)
			{
				if (allNames[i].serviceTimes == m)
				{
					tmpName = WstringToString(allNames[i].personName[0]);
					fwrite(tmpName.c_str(), tmpName.length(), 1, fp);
					sprintf(tmpbuf, "       %d次", allNames[i].serviceTimes);
					fwrite(tmpbuf, strlen(tmpbuf), 1, fp);
					fwrite("\r\n", strlen("\r\n"), 1, fp);
				}
			}
		}
		fclose(fp);
	}
}

inline void NameStatic::analyzeDate(char namesdata[])
{
	// 去掉最前面的空格
	int datalen = strlen(namesdata);
	int datapos = 0;
	for (int i = 0; i < datalen; ++i)
	{
		char tmpdata = namesdata[i];
		if (namesdata[i] != ' ')
		{
			datapos = i;
			break;
		}
	}
	if (is2017year(namesdata))
	{
		std::wstring lines = StringToWstring(namesdata + datapos);
		std::wstring flagdata = L"点";
		// 去除时间
		int timepos = 0;
		int linelen = lines.length();
		for (int i = 0; i < linelen; ++i)
		{
			if (lines[i] == flagdata[0])
			{
				timepos = i;
				break;
			}
		}
		// 从timepos + 1的位置开始是人名
		// 以空格为人名间隔符，将人名无关字符换成空格
		int beginSearchNamePos = timepos + 1;
		wchar_t namesLine[512];
		int nameslineAdapterIndex = 0;
		for (int i = beginSearchNamePos; i < linelen; ++i)
		{
			namesLine[nameslineAdapterIndex] = lines[i];
			if (!isNameChar(namesLine[nameslineAdapterIndex]))
				namesLine[nameslineAdapterIndex] = ' ';
			if (namesLine[nameslineAdapterIndex] == '\r' || namesLine[nameslineAdapterIndex] == '\n')
				namesLine[nameslineAdapterIndex] = 0;
			++nameslineAdapterIndex;
		}
		namesLine[nameslineAdapterIndex] = 0;
		dicomposeNameLine(namesLine);
	}
}

void NameStatic::dicomposeNameLine(wchar_t *pNameLine)
{
	int linelen = wcslen(pNameLine);
	int nameEndpos = 0;
	while (nameEndpos < linelen)
	{
		wchar_t nameToGet[NAMELEN];
		int tmpendpos = getFirstName(pNameLine + nameEndpos, nameToGet);
		staticNames(nameToGet);
		if (tmpendpos == 0)
			break;
		nameEndpos += tmpendpos;
	}
}

void NameStatic::staticNames(wchar_t inName[])
{
	// 首先查看内存中是否存在这个名字
	int namesz = allNames.size();
	for (int i = 0; i < namesz; ++i)
	{
		if (allNames[i].isEqualName(inName))
		{
			++allNames[i].serviceTimes;
			return;
		}
	}
	allNames.push_back(PositionInPosName(inName));
}

int NameStatic::getFirstName(wchar_t *pNameLine, wchar_t outName[])
{
	int nameBeginPos = 0;
	int linelen = wcslen(pNameLine);
	for (int i = 0; i < linelen; ++i)
	{
		if (pNameLine[i] != ' ')
		{
			nameBeginPos = i;
			break;
		}
	}
	int nameIndex = 0;
	int nameEndPos = 0;
	for (int i = nameBeginPos; i < nameBeginPos + 4; ++i)
	{
		outName[nameIndex] = pNameLine[i];
		if (outName[nameIndex] == ' ' || outName[nameIndex] == '\r' || outName[nameIndex] == '\n')
		{
			outName[nameIndex] = 0;
			nameEndPos = i;
			break;
		}
		++nameIndex;
	}
	return nameEndPos;
}

bool NameStatic::is2017year(char namesline[])
{
	const char *yearchar = "2017";
	bool isyear2017 = true;
	for (int i = 0; i < 4; ++i)
	{
		if (namesline[i] != yearchar[i])
		{
			isyear2017 = false;
			break;
		}
	}
	return isyear2017;
}

bool NameStatic::isNameChar(wchar_t pchar)
{
	bool isName = true;
	static std::wstring flagdata = L"，车场厂膛堂内里：外面；、。前边后";
	static int flaglen = flagdata.length();
	for (int i = 0; i < flaglen; ++i)
	{
		if (pchar == flagdata[i])
		{
			isName = false;
			break;
		}
	}

	return isName;
}

std::wstring NameStatic::StringToWstring(const std::string str)
{// string转wstring
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p,str.c_str(),len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

std::string NameStatic::WstringToString(const std::wstring str)
{// wstring转string
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	wcstombs(p,str.c_str(),len);
	std::string str1(p);
	delete[] p;
	return str1;
}