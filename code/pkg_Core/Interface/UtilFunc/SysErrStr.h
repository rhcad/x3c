//! \file SysErrStr.h
//! \brief 定义得到系统错误的描述内容的函数 GetSystemErrorString

#ifndef UTILFUNC_SYSERRSTR_H_
#define UTILFUNC_SYSERRSTR_H_

//! 得到系统错误的描述内容
/*!
	\ingroup _GROUP_UTILFUNC
	\param errorcode 错误码，例如 GetLastError() 返回值或 HRESULT 值
	\return 错误信息描述内容
*/
inline std::wstring GetSystemErrorString(DWORD errorcode)
{
	std::wstring retstr;
	WCHAR buf[21] = { 0 };

	if (errorcode != 0)
	{
		LPWSTR p = NULL;

		::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, errorcode, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&p, 0, NULL);

		if (p != NULL)
		{
			retstr = p;
			::LocalFree((HLOCAL)p);
		}

		swprintf_s(buf, _countof(buf), L"[0x%x]", errorcode);
		retstr = buf + retstr;
	}

	return retstr;
}

#endif // UTILFUNC_SYSERRSTR_H_
