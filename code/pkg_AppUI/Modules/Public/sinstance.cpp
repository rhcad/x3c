/*
Module : SINSTANCE.CPP
Purpose: Defines the implementation for an MFC wrapper classe
         to do instance checking
Created: PJN / 29-07-1998
History: PJN / 25-03-2000 Neville Franks made the following changes. Contact nevf@getsoft.com, www.getsoft.com
                          1. Changed #pragma error to #pragma message. Former wouldn't compile under VC6
                          2. Replaced above #pragma with #include
                          3. Added TrackFirstInstanceRunning(), MakeMMFFilename()
         PJN / 27-03-2000 1. Fixed a potential handle leak where the file handle m_hPrevInstance was not being
                          closed under certain circumstances.
                          Neville Franks made the following changes. Contact nevf@getsoft.com, www.getsoft.com
                          2. Split PreviousInstanceRunning() up into separate functions so we
                          can call it without needing the MainFrame window.
                          3. Changed ActivatePreviousInstance() to return hWnd.
         PJN / 15-05-2000 1. Serialized access to all of the CSingleInstance class to prevent race conditions
                          which can occur when you app is programatically spawned.
         PJN / 17-05-2000 1. Updated sample to show how the code can be used for dialog based apps.
         PJN / 01-01-2001 1. Added a number of asserts to CInstanceChecker::ActivatePreviousInstance
                          2. Now includes copyright message in the source code and documentation.
         PJN / 15-01-2001 1. Now allows multiple calls to PreviousInstanceRunning without ASSERTing
                          2. Removed some unnecessary VERIFY's from ActivatePreviousInstance
                          3. Made the MMF filename used modifiable via a virtual function GetMMFFilename 
                          4. Made the window to track modifiable via a virtual function GetWindowToTrack
                          5. Made destructor virtual since the introduction of other virtual functions in the class
                          6. Removed a number of unnecessary verifies
                          7. Changed the meaning of the return value from TrackFirstInstanceRunning
         PJN / 17-06-2001 1. Moved most of the code from CInstanceChecker::CInstanceChecker to 
                          CInstanceChecker::ActivateChecker. This allows client code to turn on or off the instance
                          checking code easily. Thanks to Anders Rundegren for this addition.
         PJN / 31-08-2001 1. made the name of the mutex which the class uses to serialize access to itself a paramter
                          to the constructor. That way multiple independent apps do not block each other while
                          they are calling into the CSingleInstance class. Thanks to Eugene Shmelyov for spotting
                          this problem.
         PJN / 23-03-2002 1. Provided a QuitPreviousInstance method. Thanks to Jon Bennett for providing this.
         PJN / 30-10-2002 1. The name of the internal memory mapped file is now based on the Mutex name rather than
                          the application name. An example: a client was writing a webcam application and wanted it to 
                          run with multiple configuration for multiple camera support. So the app can run multiple times 
                          as long as a special configuration is given on the command line. But for that configuration 
                          only one instance is allowed. Using the application name for the memory mapped file was tying 
                          the single instance to the app rather than the unique mutex name. Thanks to Frank Fesevur for 
                          this nice update.
         PJN / 06-02-2003 1. Was missing a call to ReleaseLock in CInstanceChecker::ActivatePreviousInstance. Thanks to 
                          Pierrick Ingels for reporting this problem.
         PJN / 09-05-2004 1. Updated the copyright details.
                          2. Extended CInstanceChecker::ActivatePreviousInstance to now allow the command line of the
                          second app to be passed to the original app. By default the parameter is NULL, meaning that 
                          you get the original behaviour which just activates the previous instance. To respond to this
                          information you should add the following to your mainfrm module:

                          mainfrm.h

                          afx_msg LRESULT OnCopyData(WPARAM, LPARAM);


                          mainfrm.cpp

                          LRESULT CMyFrameWnd::OnCopyData(WPARAM wParam, LPARAM lParam)
                          {
                            COPYDATASTRUCT* pCDS = reinterpret_cast<COPYDATASTRUCT*>(lParam);
                            TCHAR* pszCmdLine = static_cast<TCHAR*>(pCDS->lpData);
                            if (pszCmdLine)
                            {
                              //DO SOMETHING with pszCmdLine here such as call AfxGetApp()->OpenDocumentFile(pszCmdLine);
                            }
                            return TRUE;
                          }

                          Also hook up your onCopyData to the windows message map using

                          ON_MESSAGE(WM_COPYDATA, OnCopyData)


                          Thanks to Ingo H. de Boer for providing this nice update.

                          3. Following a discussion on the Codeproject.com discussion forum for CSingleInstance on what
                          exactly a single instance app means (See http://www.codeproject.com/cpp/csingleinst.asp?msg=766108#xx1103xx),
                          Daniel Lohmann has produced a simple function called CreateUniqueName which given a number of 
                          settings as flags, will produce a name which is unique. This code can be downloaded at 
                          http://www.losoft.de/code/SingleInstance.zip. You can then use this name in the constructor for
                          CInstanceChecker. The concept of a single instance app is complicated by the concept of Window stations
                          and desktops as used by NT Services and Windows Terminal Services. In addition you might want to allow your
                          program to be run once per user. 
         PJN / 30-05-2005 1. Fix for a crash where CWnd::GetLastActivePopup can sometimes return a NULL pointer. Thanks to 
                          Dominik Reichl for reporting this bug.
         PJN / 07-07-2006 1. Updated copyright details.
                          2. Addition of CSINGLEINSTANCE_EXT_CLASS and CSINGLEINSTANCE_EXT_API which allows the class to be easily used
                          in an extension DLL.
                          3. Removed derivation from CObject as it was not really needed.
                          4. Updated the documentation to use the same style as the web site.
                          5. Code now uses newer C++ style casts instead of C style casts.
                          6. Fixed a number of level 4 warnings in the sample app.
                          7. Updated code to compile cleanly using VC 2005.
         PJN / 17-03-2007 1. Updated copyright details.
                          2. Optimized _INSTANCE_DATA constructor code
                          3. Reworked how the method CInstanceChecker::GetMMFFilename creates the name of the memory mapped filename
                          the code requires for sharing. Now the main instance name appears before the hard coded string. This
                          ensures that the CInstanceChecker class works correctly for terminal sessions i.e. kernel objects prefixed
                          with the value "Local\". Thanks to Mathias Berchtold for reporting this issue.
                          4. Updated the sample app code to clean compile on VC 2005
                          5. QuitPreviousInstance now uses GetLastActivePopup API to ensure it posts the WM_QUIT message to the 
                          correct window of the previous instance.
         PJN / 02-02-2008 1. Updated copyright details
                          2. Removed VC 6 style classwizard comments from the sample apps code
                          3. Updated ActivatePreviousInstance method to support Win64 compliant data
                          4. ActivatePreviousInstance now takes a "dwTimeout" parameter which it now uses internally as the timeout when
                          calling SendMessageTimeout instead of SendMessage. The code now uses SendMessageTimeout instead of SendMessage 
                          to ensure we do not hang if the previous instance itself is hung. Thanks to Paul Shore for suggesting this 
                          update.
                          5. Updated the sample apps to clean compile on VC 2008

Copyright (c) 1996 - 2008 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "sinstance.h"


/////////////////////////////// Defines / Macros //////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


///////////////////////////////// Implementation //////////////////////////////

//struct which is put into shared memory
struct CWindowInstance
{
  HWND hMainWnd;
};

//Class which is used as a static to ensure that we
//only close the file mapping at the very last chance
class _SINSTANCE_DATA
{
public:
//Constructors / Destructors
  _SINSTANCE_DATA();
  ~_SINSTANCE_DATA();

protected:
//Member variables
  HANDLE hInstanceData;

  friend class CInstanceChecker;
};

_SINSTANCE_DATA::_SINSTANCE_DATA() : hInstanceData(NULL)
{
}

_SINSTANCE_DATA::~_SINSTANCE_DATA()
{
  if (hInstanceData != NULL)
  {
    ::CloseHandle(hInstanceData);
    hInstanceData = NULL;
  }
}

static _SINSTANCE_DATA g_sinstanceData;


CInstanceChecker::CInstanceChecker(const CString& sUniqueName) : m_executeMutex(FALSE, sUniqueName)
{
  //Hive away the unique name as we will also be using it for the name of the memory mapped file
  m_sName = sUniqueName;

  //Only one object of type CInstanceChecker should be created
  ASSERT(g_sinstanceData.hInstanceData == NULL);
  m_pExecuteLock = NULL;
}

void CInstanceChecker::ActivateChecker()
{
  ASSERT(m_pExecuteLock == NULL);

  //Ensure there is only ever one CInstanceChecker instance 
  //active at any one time throughout the system
  m_pExecuteLock = new CSingleLock(&m_executeMutex, TRUE);
}

CInstanceChecker::~CInstanceChecker()
{
  //Free up the instance lock
  ReleaseLock();
}

void CInstanceChecker::ReleaseLock()
{
  if (m_pExecuteLock)
  {
    delete m_pExecuteLock;
    m_pExecuteLock = NULL;
  }  
}

//Track the first instance of our App.
//return TRUE on success, else FALSE
BOOL CInstanceChecker::TrackFirstInstanceRunning()
{
  //If a previous instance is running, just return prematurely
  if (PreviousInstanceRunning())
    return FALSE;

  //If this is the first instance then copy in our info into the shared memory

  //First create the MMF
  int nMMFSize = sizeof(CWindowInstance);
  g_sinstanceData.hInstanceData = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, nMMFSize, GetMMFFilename());
  if (g_sinstanceData.hInstanceData == NULL)
  {
    TRACE(_T("Failed to create the MMF even though this is the first instance, you might want to consider overriding GetMMFFilename()\n"));
    return FALSE;
  }

  //Open the MMF
  CWindowInstance* pInstanceData = static_cast<CWindowInstance*>(MapViewOfFile(g_sinstanceData.hInstanceData, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nMMFSize));
  ASSERT(pInstanceData != NULL);   //Opening the MMF should work

  //Lock the data prior to updating it
  CSingleLock dataLock(&m_instanceDataMutex, TRUE);
  pInstanceData->hMainWnd = GetWindowToTrack();
  UnmapViewOfFile(pInstanceData);

  //Since this will be the last function that will be called 
  //when this is the first instance we can release the lock
  ReleaseLock();

  return TRUE;
}

// Returns TRUE if a previous instance of the App is running.
BOOL CInstanceChecker::PreviousInstanceRunning()
{
  //Try to open the MMF first to see if we are the second instance
  HANDLE hPrevInstance = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, GetMMFFilename());
  BOOL bPreviousInstance = (hPrevInstance != NULL);
  if (hPrevInstance)
    CloseHandle(hPrevInstance);

  return bPreviousInstance;
}

CString CInstanceChecker::GetMMFFilename()
{
  CString sMMF(m_sName);
  sMMF += _T("_CInstanceChecker_MMF");
  return sMMF;
}

HWND CInstanceChecker::GetWindowToTrack()
{
  //By default the window tracked will be the standard AfxGetMainWnd()
  ASSERT(AfxGetMainWnd() != NULL); //Did you forget to set up the mainfrm in InitInstance ?
  return AfxGetMainWnd()->GetSafeHwnd();
}

//Activate the Previous Instance of our Application.
HWND CInstanceChecker::ActivatePreviousInstance(LPCTSTR lpCmdLine, ULONG_PTR dwCopyDataItemData, DWORD dwTimeout)
{
  //What will be the return value from this function (assume the worst)
  HWND hWindow = NULL;

  //Try to open the previous instances MMF
  HANDLE hPrevInstance = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, GetMMFFilename());
  if (hPrevInstance)
  {
    //Open up the MMF
    int nMMFSize = sizeof(CWindowInstance);
    CWindowInstance* pInstanceData = static_cast<CWindowInstance*>(MapViewOfFile(hPrevInstance, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nMMFSize));
    if (pInstanceData) //Opening the MMF should work
    {
      //Lock the data prior to reading from it
      CSingleLock dataLock(&m_instanceDataMutex, TRUE);

      //activate the old window
      ASSERT(pInstanceData->hMainWnd); //Something gone wrong with the MMF
      hWindow = pInstanceData->hMainWnd;
	  if (::IsWindow(hWindow))
      {
        CWnd wndPrev;
        wndPrev.Attach(hWindow);
        CWnd* pWndChild = wndPrev.GetLastActivePopup();

        //Restore the focus to the previous instance and bring it to the foreground
        if (wndPrev.IsIconic())
          wndPrev.ShowWindow(SW_RESTORE);

        if (pWndChild)
          pWndChild->SetForegroundWindow();

        if (lpCmdLine)
        {  
          //Send the current apps command line to the previous instance using WM_COPYDATA
          COPYDATASTRUCT cds;
          cds.dwData = dwCopyDataItemData;
          DWORD dwCmdLength = static_cast<DWORD>(_tcslen(lpCmdLine) + 1);
          cds.cbData = dwCmdLength * sizeof(TCHAR); 
          TCHAR* pszLocalCmdLine = new TCHAR[dwCmdLength]; //We use a local buffer so that we can specify a constant parameter
                                                           //to this function
        #if (_MSC_VER >= 1400)
          _tcscpy_s(pszLocalCmdLine, dwCmdLength, lpCmdLine);
        #else                                                 
          _tcscpy(pszLocalCmdLine, lpCmdLine);
        #endif
          cds.lpData = pszLocalCmdLine;
          CWnd* pMainWindow = AfxGetMainWnd();
          HWND hSender = NULL;
          if (pMainWindow)
            hSender = pMainWindow->GetSafeHwnd();

          //Send the message to the previous instance. Use SendMessageTimeout instead of SendMessage to ensure we 
          //do not hang if the previous instance itself is hung
          DWORD_PTR dwResult = 0;
          if (SendMessageTimeout(hWindow, WM_COPYDATA, reinterpret_cast<WPARAM>(hSender), reinterpret_cast<LPARAM>(&cds),
                                 SMTO_ABORTIFHUNG, dwTimeout, &dwResult) == 0)
          {
            //Previous instance is not responding to messages
            hWindow = NULL;
          }

          //Tidy up the heap memory we have used
          delete [] pszLocalCmdLine;
        }

        //Detach the CWnd we were using
        wndPrev.Detach();
      }

      //Unmap the MMF we were using
      UnmapViewOfFile(pInstanceData);
    }

    //Close the file handle now that we 
    CloseHandle(hPrevInstance);

    //When we have activate the previous instance, we can release the lock
    ReleaseLock();
  }

  return hWindow;
}

void CInstanceChecker::QuitPreviousInstance(int nExitCode)
{
  //Try to open the previous instances MMF
  HANDLE hPrevInstance = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, GetMMFFilename());
	if (hPrevInstance)
	{
		// Open up the MMF
		int nMMFSize = sizeof(CWindowInstance);
		CWindowInstance* pInstanceData = static_cast<CWindowInstance*>(MapViewOfFile(hPrevInstance, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nMMFSize));
		if (pInstanceData != NULL) //Opening the MMF should work
		{
		  // Lock the data prior to reading from it
		  CSingleLock dataLock(&m_instanceDataMutex, TRUE);

		  //activate the old window
		  ASSERT(pInstanceData->hMainWnd); //Something gone wrong with the MMF?
		  HWND hWnd = pInstanceData->hMainWnd;

      //Ask it to exit
      HWND hChildWnd = GetLastActivePopup(hWnd);
  	  PostMessage(hChildWnd, WM_QUIT, nExitCode, 0);
	  }

    //Close the file handle now that we 
    CloseHandle(hPrevInstance);
  }
}

