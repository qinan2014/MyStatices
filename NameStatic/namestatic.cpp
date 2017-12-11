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
	char filename[] = "E:\\QADoc\\Study\\MyNameStatic\\names.txt"; //�ļ���
	FILE *fp; 
	char StrLine[LINELEN];             //ÿ������ȡ���ַ���
	if((fp = fopen(filename,"r")) == NULL) //�ж��ļ��Ƿ���ڼ��ɶ�
	{ 
		return; 
	} 

	while (!feof(fp)) 
	{ 
		fgets(StrLine,LINELEN,fp);  //��ȡһ��
		analyzeDate(StrLine);
	} 
	fclose(fp);
#undef LINELEN
}

inline void NameStatic::analyzeDate(char namesdata[])
{
	// ȥ����ǰ��Ŀո�
	std::wstring namew = StringToWstring(namesdata);
	std::wstring flagdata = L"��";

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
{// stringתwstring
	unsigned len = str.size() * 2;// Ԥ���ֽ���
	setlocale(LC_CTYPE, "");     //������ô˺���
	wchar_t *p = new wchar_t[len];// ����һ���ڴ���ת������ַ���
	mbstowcs(p,str.c_str(),len);// ת��
	std::wstring str1(p);
	delete[] p;// �ͷ�������ڴ�
	return str1;
}

std::string NameStatic::WstringToString(const std::wstring str)
{// wstringתstring
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	wcstombs(p,str.c_str(),len);
	std::string str1(p);
	delete[] p;
	return str1;
}