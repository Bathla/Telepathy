// TAPIEventNotification.cpp: implementation of the CTAPIEventNotification class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TelePathy.h"
#include "TAPIEventNotification.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



HRESULT STDMETHODCALLTYPE CTAPIEventNotification::Event(TAPI_EVENT  TapiEvent,IDispatch * pEvent)
{ WM_PRIVATETAPIEVENT=49594;

	
    pEvent->AddRef();
    
    PostMessage(
		AfxGetApp()->GetMainWnd()->GetSafeHwnd(),
        WM_PRIVATETAPIEVENT,
        (WPARAM) TapiEvent,
         (LPARAM)pEvent
        );
	
    return S_OK;
}



ULONG STDMETHODCALLTYPE CTAPIEventNotification::AddRef()
{return InterlockedIncrement(&m_cRef);
}


CTAPIEventNotification::CTAPIEventNotification()
{m_cRef=0;
WM_PRIVATETAPIEVENT=49594;//Shoul be same as in DefWindowProc of the CTelePathyDlg Class
}


ULONG STDMETHODCALLTYPE CTAPIEventNotification::Release()
{return InterlockedDecrement(&m_cRef);}



HRESULT STDMETHODCALLTYPE CTAPIEventNotification::QueryInterface(REFIID iid,void **ppv)
{WM_PRIVATETAPIEVENT=49594;
	*ppv = NULL;
   if (iid == IID_IUnknown ||
      iid == IID_IDispatch||
      iid == IID_ITTAPIEventNotification)
   {
      *ppv = static_cast<ITTAPIEventNotification *>(this);
   }
   
   if (*ppv) {
      AddRef();
      return S_OK;
   }
   else return E_NOINTERFACE;
}






