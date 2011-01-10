/*! \file InitXMLDLL.h
 *  \brief Define InitXMLDLL() to Ensure XML component correctly initialized.
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2011.01.10
 */
#ifndef _APP_INITXMLDLL_H
#define _APP_INITXMLDLL_H

#include <comdef.h>

struct __declspec(uuid("2933bf81-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMDocForCheck : IDispatch {};
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocForCheck, __uuidof(IXMLDOMDocForCheck));

//! Ensure XML component correctly initialized
/*! Call this function to ensure ConfigXml plugin can work correctly.
	\note Must initialize COM (such as OleInitialize) before call this function.
	\ingroup _GROUP_PLUGIN_XML_
*/
bool InitXMLDLL()
{
	const CLSID CLSID_XmlDocument60 = 
		{ 0x88d96a05, 0xf192, 0x11d4,{0xa6,0x5f,0x00,0x40,0x96,0x32,0x51,0xe5}};
	const CLSID CLSID_XmlDocument40 = 
		{ 0x88d969c0, 0xf192, 0x11d4,{0xa6,0x5f,0x00,0x40,0x96,0x32,0x51,0xe5}};
	HRESULT hr = E_FAIL;
	IXMLDOMDocForCheckPtr ptr;

	HMODULE hDll = ::LoadLibrary(_T("MSXML6.dll"));

	if (NULL == hDll)
	{
		hDll = ::LoadLibrary(_T("MSXML4.dll"));
	}
	if (hDll != NULL)
	{
		hr = ptr.CreateInstance(CLSID_XmlDocument60);
		if (FAILED(hr))
		{
			hr = ptr.CreateInstance(CLSID_XmlDocument40);
		}
		if (FAILED(hr))
		{
			typedef HRESULT (__stdcall *PDLLREGISTERSERVER)();
			PDLLREGISTERSERVER pfn = (PDLLREGISTERSERVER)GetProcAddress(hDll, "DllRegisterServer");

			if (pfn != NULL)
			{
				hr = pfn();
				if (SUCCEEDED(hr))
				{
					hr = ptr.CreateInstance(CLSID_XmlDocument60);
					if (FAILED(hr))
					{
						hr = ptr.CreateInstance(CLSID_XmlDocument40);
					}
				}
			}
		}
		if (ptr != NULL)
		{
			ptr.Release();
		}
		FreeLibrary(hDll);
	}

	return SUCCEEDED(hr);
}

#endif // _APP_INITXMLDLL_H
