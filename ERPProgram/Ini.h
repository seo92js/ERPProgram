// Ini1.h: interface for the CIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INI1_H__A274F521_670C_11D3_BC77_00105A6B502B__INCLUDED_)
#define AFX_INI1_H__A274F521_670C_11D3_BC77_00105A6B502B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "io.h"
#include <vector>

class CIni
{
public:
	CString Filename;
	CString Section;
public:
	CIni();
	virtual ~CIni();

	void SetFile(CString fileName);
	void SetSection(LPCTSTR fmt, ...);


	// Get series
	int GetInt(CString entry, int defvalue, BOOL msgstat = TRUE);
	long GetLong(CString entry, long defvalue, BOOL msgstat = TRUE);
	void GetFile(CString *fileName);

	long GetLongArray(CString entry, long *data, long num, BOOL msgstat = TRUE);
	int GetIntArray(CString entry, int *data, long num, int *defdata = NULL,BOOL msgstat = TRUE);
	long GetLongVector(CString entry, std::vector<long> &data, long num, BOOL msgstat);
	long GetDoubleArray(CString entry, double *data, long num, double *defdata = NULL, BOOL msgstat = TRUE);
	long GetStringArray(CString entry, CString *data, long num, BOOL msgstat = TRUE);
	long GetStringVector(CString entry, std::vector<CString>& data, long num, BOOL msgstat = TRUE); // by leeks

	double GetDouble(CString entry, double defvalue, BOOL msgstat = TRUE);

	CString GetString(CString entry, CString defvalue, BOOL msgstat = TRUE);
	CString GetString(CString entry, CString defvalue, CString strComment, BOOL msgstat);

	CPoint GetPoint(CString entry, CPoint defvalue, BOOL msgstat = TRUE);
	CRect GetRect(CString entry, CRect defvalue, BOOL msgstat = TRUE);

	COLORREF GetColor(CString entry, COLORREF defvalue, BOOL msgstat = TRUE);

	int GetAllKeyValue(CString entry, CStringList *Key, CStringList *Value);

	// 20.02.27.NHJ
	int GetInt(CString entry, int defvalue, CString strComment, BOOL msgstat);
	// 20.02.27.NHJ

	// Write series
	void WriteDouble(CString entry, double value);
	void WriteInt(CString entry, int value);
	void WriteLong(CString entry, long value);
	void Write_String(CString entry, CString value);
	void WriteIntArray(CString entry, const int *data, long num);
	void WriteLongArray(CString entry, const long *data, long num);
	void WriteDoubleArray(CString entry, const double *data, long num);

	void UpdateFile();
	void Copy_File(CString SourceFileName, CString TargetFileName);

	// Delete
	void DeleteKey(CString strSection, CString entry);
	void DeleteKey(CString entry);

	// Find
public:
	CFileFind		Find;

	BOOL FindFile(CString fileName);

};

#endif // !defined(AFX_INI1_H__A274F521_670C_11D3_BC77_00105A6B502B__INCLUDED_)
