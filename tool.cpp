/*!
 * The code if from wxWiki, to get the execute file path.
 * When you create a instill program, a execute file need to know its path.
 */
#include "tool.h"

const wxString GetExecutablePath()
{    
    static wxString path;

#ifdef __WXMSW__

	wxChar buf[512];
	*buf = '\0';
	GetModuleFileName(NULL, buf, 511);
	path = wxString(buf);

#elif defined(__WXMAC__)

	ProcessInfoRec processinfo;
	ProcessSerialNumber procno ;
	FSSpec fsSpec;

	procno.highLongOfPSN = NULL ;
	procno.lowLongOfPSN = kCurrentProcess ;
	processinfo.processInfoLength = sizeof(ProcessInfoRec);
	processinfo.processName = NULL;
	processinfo.processAppSpec = &fsSpec;

	GetProcessInformation( &procno , &processinfo ) ;
	path = wxMacFSSpec2MacFilename(&fsSpec);
#else
	wxString argv0 = wxTheApp->argv[0];

	if (wxIsAbsolutePath(argv0))
		path = argv0;
	else
	{
		wxPathList pathlist;
		pathlist.AddEnvList(_T("PATH"));
		path = pathlist.FindAbsoluteValidPath(argv0);
	}

	wxFileName filename(path);
	filename.Normalize();
	path = filename.GetFullPath();
#endif
	return path;
    
}

/*****************************************************************************
 * Get phon input method conversion list
 *****************************************************************************/ 
#ifdef __WXMSW__
WCHAR **GetConversionList(WCHAR *imefilename, WCHAR *instring)
{
	CANDIDATELIST *pCand;
	char  *cBuff;
	TCHAR strIME[255];  
	int   iKeyLayoutCount;  
	HKL   arrKeyLayout[20]; 
	HKL	  hKL;	
	BOOL  isChineseIme = FALSE;   
	DWORD dwGCL;
	DWORD dwOffset;
	WCHAR **outstring = NULL;

	iKeyLayoutCount = GetKeyboardLayoutList(255, arrKeyLayout);  
	isChineseIme = FALSE;  

	for(int i = 0; i < iKeyLayoutCount; i++)  
	{  
		memset(strIME,0,sizeof(strIME));  
		if(ImmGetIMEFileName(arrKeyLayout[i], strIME, sizeof(strIME)))
		{
			if(!wcscmp(imefilename, strIME))
			{
				hKL = arrKeyLayout[i];
				isChineseIme = TRUE;  
				break;  
			}  
		}
	}	

	if(!isChineseIme)  
	{  
		return NULL;
	}  

	int iMaxkey = ImmEscape(hKL, 0, IME_ESC_MAX_KEY, NULL);

	dwGCL = ImmGetConversionList(hKL, 0, instring, pCand, 0, GCL_REVERSECONVERSION);
	if(dwGCL > 0)
	{
		cBuff = new char[dwGCL];
		dwGCL = ImmGetConversionList(hKL, 0, instring, (CANDIDATELIST *) cBuff, 
				dwGCL, GCL_REVERSECONVERSION);

		pCand = (CANDIDATELIST *) cBuff;
		if(pCand->dwCount > 0)
		{
			outstring = (WCHAR **) malloc(sizeof(WCHAR *) * (pCand->dwCount + 1));
			outstring[pCand->dwCount] = NULL;
			for(int i = 0; i < pCand->dwCount; i++)
			{
				//OK, get the first string
				dwOffset = (DWORD) *(cBuff + 24 + i * 4); 

				outstring[i] = (WCHAR *)malloc(sizeof(WCHAR) * (iMaxkey + 1));  
				wcscpy(outstring[i], (TCHAR *) (LPBYTE) (cBuff + dwOffset));
			}
		}

		delete [] cBuff;  
		cBuff = NULL;  
	}

	return outstring;
}
#endif

