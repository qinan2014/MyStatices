#include "namestatic.h"

NameStatic::NameStatic(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	readNameText();
}

NameStatic::~NameStatic()
{

}

void NameStatic::readNameText()
{
#define LINELEN 1024
	char filename[] = "E:\\QADoc\\Study\\MyNameStatic\\names.txt"; //文件名
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
}

inline void NameStatic::analyzeDate(char namesdata[])
{
	// 去掉最前面的空格
	std::wstring namew = StringToWstring(namesdata);
	std::wstring flagdata = L"点";

	int datalen = namew.length();
	int datapos = 0;
	for (int i = 0; i < datalen; ++i)
	{
		wchar_t tmpdata = namew[i];
		if (tmpdata == flagdata[0])
		{
			datapos = i;
		}
	}
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