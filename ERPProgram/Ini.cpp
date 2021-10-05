// Ini1.cpp: implementation of the CIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ini.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIni::CIni()
{
	Filename.Empty();
	Section.Empty();
}

CIni::~CIni()
{
}

void CIni::SetFile(CString fileName)
{
	Filename = fileName;
}

void CIni::SetSection(LPCTSTR fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	Section.FormatV(fmt, args);
	va_end(args);
}

int CIni::GetInt(CString entry, int defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256] = _T("");

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);

		// 2018.07.23. nhj ����.
		WriteLong(entry, defvalue);

		return defvalue;
	}

	if (valuebuf[0] == '0') {
		int value;

		if (valuebuf[1] == 'x' || valuebuf[1] == 'X') {
			_stscanf(valuebuf, _T("%x"), &value);
			return value;
		}
		_stscanf(valuebuf, _T("%o"), &value);
		return value;

	}
	return _ttoi(valuebuf);
}

int CIni::GetInt(CString entry, int defvalue, CString strComment, BOOL msgstat)
{
	_TCHAR  valuebuf[256] = _T("");
	CString	strValue;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);

		// 2018.07.23. nhj ����.
		//WriteLong(entry, defvalue);

		// 20.02.27.NHJ - ���Ͽ� ã�� ���� ���� ��, �ּ� �����Ͽ� ���Ͽ� �� ����.
		strValue.Format(_T("%d; %s"), defvalue, strComment);
		WritePrivateProfileString(Section, entry, strValue, Filename);
		// 20.02.27.NHJ - ���Ͽ� ã�� ���� ���� ��, �ּ� �����Ͽ� ���Ͽ� �� ����.

		return defvalue;
	}

	if (valuebuf[0] == '0') {
		int value;

		if (valuebuf[1] == 'x' || valuebuf[1] == 'X') {
			_stscanf(valuebuf, _T("%x"), &value);
			return value;
		}
		_stscanf(valuebuf, _T("%o"), &value);
		return value;

	}
	return _ttoi(valuebuf);
}

void CIni::GetFile(CString *fileName)
{
	*fileName = Filename;
}

long CIni::GetLong(CString entry, long defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256] = _T("");
	CString	strdefvalue;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);
		strdefvalue.Format(_T("%d"), defvalue);
		WritePrivateProfileString(Section, entry, strdefvalue, Filename);		//�� ��ã���� ��, default������ ���Ͽ� ����.
		return defvalue;
	}

	if (valuebuf[0] == '0') {
		long value;

		if (valuebuf[1] == 'x' || valuebuf[1] == 'X') {
			_stscanf(valuebuf, _T("%x"), &value);
			return value;
		}
		_stscanf(valuebuf, _T("%o"), &value);
		return value;

	}

	return _ttol(valuebuf);
}

long CIni::GetLongArray(CString entry, long *data, long num, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T(" \t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	while (p) {
		data[count++] = _ttol(p);
		p = _tcstok(NULL, delim);
	}

	if (count != num) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		return 0;
	}

	return count;
}

int CIni::GetIntArray(CString entry, int *data, long num, int *defdata, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T(" \t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		if (defdata) 
			CopyMemory(data, defdata, sizeof(int)*num);
		WriteIntArray(entry, data, num);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	//while (p) {
	//	data[count++] = _ttol(p);
	//	p = _tcstok(NULL, delim);
	//}

	//if (count != num) {
	//	//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
	//	return 0;
	//}
	while (p) {
#ifdef _UNICODE
		char temp_buffer[256] = "";
		wcstombs(temp_buffer, p, sizeof(temp_buffer));
		data[count++] = atof(temp_buffer);
#else
		data[count++] = atof(p);
#endif
		p = _tcstok(NULL, delim);
	}

	if (count != num) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		//if (defdata) CopyMemory(data, defdata, sizeof(int)*num);
		//return 0;
		return count;
	}

	return count;
}

long CIni::GetLongVector(CString entry, std::vector<long> &data, long num, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T(" \t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	while (p && count<num) {
		data.push_back(_ttol(p));
		count++;
		p = _tcstok(NULL, delim);
	}

	return data.size();
}

long CIni::GetDoubleArray(CString entry, double *data, long num, double *defdata, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T(" \t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		if (defdata) CopyMemory(data, defdata, sizeof(double)*num);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	while (p) {
#ifdef _UNICODE
		char temp_buffer[256] = "";
		wcstombs(temp_buffer, p, sizeof(temp_buffer));
		data[count++] = atof(temp_buffer);
#else
		data[count++] = atof(p);
#endif
		p = _tcstok(NULL, delim);
	}

	if (count != num) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		if (defdata) CopyMemory(data, defdata, sizeof(double)*num);
		return 0;
	}

	return count;
}

long CIni::GetStringArray(CString entry, CString *data, long num, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T("\t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	while (p && count<num) {
		data[count] = p;
		data[count].TrimLeft();
		data[count].TrimRight();
		count++;
		p = _tcstok(NULL, delim);
	}

	return count;
}

long CIni::GetStringVector(CString entry, std::vector<CString>& data, long num, BOOL msgstat)
{
	CString s;
	_TCHAR temp[4096], *p, *delim = _T("\t;,");
	long count;

	s = GetString(entry, _T("~"), msgstat);
	if (s == _T("~")) {
		//	if(msgstat) AfxMessageBox(_T("Invalid data '") + entry + _T("' in ") + Filename);
		return 0;
	}

	_tcscpy(temp, s);

	count = 0;
	p = _tcstok(temp, delim);
	while (p && count<num) {
		CString str = p;

		str.TrimLeft();
		str.TrimRight();
		data.push_back(str);
		count++;

		p = _tcstok(NULL, delim);
	}

	return data.size();
}

double CIni::GetDouble(CString entry, double defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256];

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);

		WriteDouble(entry, defvalue);	//�� ��ã���� ��, default������ ���Ͽ� ����.

		return defvalue;
	}
#ifdef _UNICODE
	char temp_buffer[256] = "";
	wcstombs(temp_buffer, valuebuf, sizeof(temp_buffer));
	return atof(temp_buffer);
#else
	return atof(valuebuf);
#endif
}

CString CIni::GetString(CString entry, CString defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256];
	_TCHAR *p;
	CString s;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {

		WritePrivateProfileString(Section, entry, defvalue, Filename);		//�� ��ã���� ��, default������ ���Ͽ� ����.

		if (_taccess(Filename, 0) != 0) {
			//	if(msgstat) AfxMessageBox(_T("File not exist '") + Filename + _T("'"));
			return defvalue;
		}
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);

		return defvalue;
	}

	p = _tcschr(valuebuf, ';');
	if (p) *p = 0;

	s = valuebuf;

	s.TrimLeft();
	s.TrimRight();

	return s;
}

CString CIni::GetString(CString entry, CString defvalue, CString strComment, BOOL msgstat)
{
	_TCHAR  valuebuf[256];
	_TCHAR *p;
	CString s, strValue;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {

	//	WritePrivateProfileString(Section, entry, defvalue, Filename);		//�� ��ã���� ��, default������ ���Ͽ� ����.
		// 20.02.27.NHJ - ���Ͽ� ã�� ���� ���� ��, �ּ� �����Ͽ� ���Ͽ� �� ����.
		strValue.Format(_T("%s; %s"), defvalue, strComment);
		WritePrivateProfileString(Section, entry, strValue, Filename);
		// 20.02.27.NHJ - ���Ͽ� ã�� ���� ���� ��, �ּ� �����Ͽ� ���Ͽ� �� ����.

		if (_taccess(Filename, 0) != 0) {
			//	if(msgstat) AfxMessageBox(_T("File not exist '") + Filename + _T("'"));
			return defvalue;
		}
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);

		return defvalue;
	}

	p = _tcschr(valuebuf, ';');
	if (p) *p = 0;

	s = valuebuf;

	s.TrimLeft();
	s.TrimRight();

	return s;
}

CPoint CIni::GetPoint(CString entry, CPoint defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256];
	_TCHAR *p;
	long len;
	CPoint pt;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);
		return defvalue;
	}

	p = _tcstok(valuebuf, _T(";"));	// remove after ';'
	while (*p == ' ' || *p == '\t') p++;	// remove first space & tab
	len = _tcslen(p);
	while (len>0 && (p[len - 1] == ' ' || p[len - 1] == '\t')) len--; // remove last space & tab
	p[len] = 0;

	pt = CPoint(0, 0);
	p = _tcstok(p, _T(", "));
	if (!p) return defvalue;
	pt.x = _ttol(p);

	p = _tcstok(NULL, _T(", "));
	if (!p) return defvalue;
	pt.y = _ttol(p);

	return pt;
}

CRect CIni::GetRect(CString entry, CRect defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256];
	_TCHAR *p;
	long len;
	CRect rect;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);
		return defvalue;
	}

	p = _tcstok(valuebuf, _T(";"));	// remove after ';'
	while (*p == ' ' || *p == '\t') p++;	// remove first space & tab
	len = _tcslen(p);
	while (len>0 && (p[len - 1] == ' ' || p[len - 1] == '\t')) len--; // remove last space & tab
	p[len] = 0;


	rect.SetRectEmpty();
	p = _tcstok(p, _T(", "));
	if (!p) return defvalue;
	rect.left = _ttol(p);

	p = _tcstok(NULL, _T(", "));
	if (!p) return defvalue;
	rect.top = _ttol(p);

	p = _tcstok(NULL, _T(", "));
	if (!p) return defvalue;
	rect.right = _ttol(p);

	p = _tcstok(NULL, _T(", "));
	if (!p) return defvalue;
	rect.bottom = _ttol(p);

	return rect;
}

COLORREF CIni::GetColor(CString entry, COLORREF defvalue, BOOL msgstat)
{
	_TCHAR  valuebuf[256];
	_TCHAR *p;
	CString s;
	COLORREF color;

	GetPrivateProfileString(Section, entry, _T("~"), valuebuf, sizeof(valuebuf), Filename);

	if (valuebuf[0] == '~') {
		//	if(msgstat) AfxMessageBox(_T("Cannot find '") + entry + _T("' in ") + Filename);
		return defvalue;
	}

	p = _tcstok(valuebuf, _T(";"));	// remove after ';'
	s = p;

	s.TrimLeft();
	s.TrimRight();

	if (s.IsEmpty()) {
		//	if(msgstat) AfxMessageBox(_T("Invalid color at '") + entry + _T("' in ") + Filename);
		return defvalue;
	}

	s.MakeLower();

	_tcscpy(valuebuf, s);
	if (valuebuf[0] == '#') {
		if (s.GetLength() != 7) {
			//	if(msgstat) AfxMessageBox(_T("Invalid color at '") + entry + _T("' in ") + Filename);
			return defvalue;
		}

		_stscanf(&valuebuf[1], _T("%x"), &color);
		color = RGB(color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff);

		return color;
	}

	// color table
	long i;
	struct COLORTABLE {
		LPCTSTR keyword;
		COLORREF color;
	} rescolor[] = {
		_T("black"), RGB(0, 0, 0),
		_T("blue"), RGB(0, 0, 255),
		_T("green"), RGB(0, 255, 0),
		_T("cyan"), RGB(0, 255, 255),
		_T("red"), RGB(255, 0, 0),
		_T("magenta"), RGB(255, 0, 255),
		_T("yellow"), RGB(255, 255, 0),
		_T("white"), RGB(255, 255, 255),

		_T("darkblue"), RGB(0, 0, 128),
		_T("darkgreen"), RGB(0, 128, 0),
		_T("darkcyan"), RGB(0, 128, 128),
		_T("darkred"), RGB(128, 0, 0),
		_T("darkmagenta"), RGB(128, 0, 128),
		_T("darkyellow"), RGB(128, 128, 0),
		_T("darkgray"), RGB(128, 128, 128),

		_T("lightblue"), RGB(0, 0, 192),
		_T("lightgreen"), RGB(0, 192, 0),
		_T("lightcyan"), RGB(0, 192, 192),
		_T("lightred"), RGB(192, 0, 0),
		_T("lightmagenta"), RGB(192, 0, 192),
		_T("lightyellow"), RGB(192, 192, 0),
		_T("lightgray"), RGB(192, 192, 192),
		NULL,
	};

	for (i = 0; rescolor[i].keyword; i++) {
		if (s == rescolor[i].keyword) {
			return rescolor[i].color;
		}
	}

	//	if(msgstat) AfxMessageBox(_T("Invalid color at '") + entry + _T("' in ") + Filename);
	return defvalue;
}

void CIni::WriteDouble(CString entry, double value)
{
	char mbcsbuf[64];
	_gcvt(value, 10, mbcsbuf);
#ifdef _UNICODE
	_TCHAR wcsbuf[64];
	mbstowcs(wcsbuf, mbcsbuf, sizeof(wcsbuf));
	WritePrivateProfileString(Section, entry, wcsbuf, Filename);
#else
	WritePrivateProfileString(Section, entry, mbcsbuf, Filename);
#endif
}

void CIni::WriteInt(CString entry, int value)
{
	_TCHAR temp[64];
	_stprintf(temp, _T("%d"), value);
	WritePrivateProfileString(Section, entry, temp, Filename);
}

void CIni::WriteLong(CString entry, long value)
{
	_TCHAR temp[64];
	_stprintf(temp, _T("%ld"), value);
	WritePrivateProfileString(Section, entry, temp, Filename);
}

void CIni::Write_String(CString entry, CString value)
{
	WritePrivateProfileString(Section, entry, value, Filename);
}

void CIni::WriteLongArray(CString entry, const long *data, long num)
{
	CString value, s;
	int i;

	for (i = 0; i<num; i++) {
		s.Format(_T("%ld"), data[i]);
		if (!value.IsEmpty()) value += _T(",");
		value += s;
	}
	WritePrivateProfileString(Section, entry, value, Filename);
}

void CIni::WriteIntArray(CString entry, const int *data, long num)
{
	CString value, s;
	int i;

	for (i = 0; i<num; i++) {
		s.Format(_T("%ld"), data[i]);
		if (!value.IsEmpty()) value += _T(",");
		value += s;
	}
	WritePrivateProfileString(Section, entry, value, Filename);
}

void CIni::WriteDoubleArray(CString entry, const double *data, long num)	//NHJ
{
	CString value, s;
	int i;

	for (i = 0; i<num; i++) {
		s.Format(_T("%lf"), data[i]);
		if (!value.IsEmpty()) value += _T(",");
		value += s;
	}
	WritePrivateProfileString(Section, entry, value, Filename);
}

void CIni::UpdateFile()
{
	WritePrivateProfileSection(NULL, NULL, NULL);
}


void CIni::Copy_File(CString SourceFileName, CString TargetFileName)
{
	CopyFile(SourceFileName, TargetFileName, false);
}

BOOL CIni::FindFile(CString fileName)
{
	BOOL bRet;

	bRet = Find.FindFile(fileName);

	return bRet;
}

void CIni::DeleteKey(CString strSection, CString entry)
{
	WritePrivateProfileString(strSection, entry, NULL, Filename);
}

void CIni::DeleteKey(CString entry)
{
	WritePrivateProfileString(Section, entry, NULL, Filename);
}

int CIni::GetAllKeyValue(CString entry, CStringList *Key, CStringList *Value)
{
	TCHAR s_section[4096] = { 0 }; //���� �Ʒ��� ��� ���� ������ ����
	TCHAR s_key[256] = { 0x00, }; //�� ���� �о� ������ ����(Ű)
	TCHAR s_data[256] = { 0x00, }; //�� ���� �о� ������ ����(��)
	int key_pos = 0; //�� ���� Ű�� �ε��� ��ġ
	int data_pos = 0; //�� ���� ���� �ε��� ��ġ

	//nSize = �� ������ ��� �� �ϳ��ϳ��� ��.
	DWORD nSize = GetPrivateProfileSection(entry, s_section, 4096, Filename);
	BOOL bSection = false; // �� ���� ��� Ȯ�������� true�Ͽ�, pos�� 0���� �ʱ�ȭ�ؼ� ���� ���� ���� �غ�
	bool bEqul = false; //'='���� Ű�� ���� �и�. =������ true�ؼ� ����

	int count = 0;

	//i�� ��� ������ �ε��� ��ġ�̰�, pos�� �� ���� �ε��� ��ġ
	for (int i = 0; i < (int)nSize; i++)
	{
		if (s_section[i] != '\0') //���ڰ� ���� ���
		{
			if (s_section[i] != '=')
			{
				if (bSection){
					key_pos = 0;
					data_pos = 0;
					bSection = FALSE;
				}

				if (bEqul == false) //=���� ���ڴ� �ٷ� Ű
				{
					memcpy(s_key + key_pos, s_section + i, sizeof(s_key + key_pos)*2 - 6); //=�������� Ű�� ����
					key_pos++;
				}
				else  //=���� ���ڴ� �ٷ� ��
				{
					memcpy(s_data + data_pos, s_section + i, sizeof(s_data + data_pos) - 2);
					data_pos++;
				}
			}
			else //���ڰ� =�� ���
				bEqul = true;

		}
		else //������� ( Ű�� �� / ������ ��)
		{
			(*Key).AddTail(s_key);
			(*Value).AddTail(s_data);

			count++;

			//s_key �ʱ�ȭ
			s_key[i] = '\0';
			s_data[i] = '\0';
			memset(s_key, 0x00, sizeof(s_key));
			memset(s_data, 0x00, sizeof(s_data));
			bSection = true;
			bEqul = false;
		}
	}

	return count;
}