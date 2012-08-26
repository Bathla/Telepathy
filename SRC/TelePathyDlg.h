// TelePathyDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mci.h"
//}}AFX_INCLUDES

#if !defined(AFX_TELEPATHYDLG_H__4BD9019C_B19C_4460_9EFA_06F9A155B3A5__INCLUDED_)
#define AFX_TELEPATHYDLG_H__4BD9019C_B19C_4460_9EFA_06F9A155B3A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTelePathyDlg dialog
#include "OBJBASE.H"
#include "tapi3.h"
#include "ole2.h"
#include "uuids.h"
#include "TAPIEventNotification.h"
#include "iostream.h"
#include "fstream.h"

#define MYWM_NOTIFYICON 49600 //This'll be used to minimize the app to systray



const BSTR CLSID_String_MediaStreamTerminal = SysAllocString(L"{E2F7AEF7-4971-11D1-A671-006097C9A2E8}");

const BSTR CLSID_String_FilePlaybackTerminal = SysAllocString(L"{0CB9914C-79CD-47DC-ADB0-327F47CEFB20}");

const BSTR CLSID_String_FileRecordingTerminal = SysAllocString(L"{521F3D06-C3D0-4511-8617-86B9A783DA77}");



class CTelePathyDlg : public CDialog
{
// Construction
public:
	void WriteLog();
	BOOL MyTaskBar(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	void OnTray();
	void Shutdown();
	void StartUp();
	CTelePathyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTelePathyDlg)
	enum { IDD = IDD_TELEPATHY_DIALOG };
	CListBox	m_List;
	Cmci	m_MMControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelePathyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTelePathyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDC pDC;
	CPoint m_pPoint;
	CBitmap m_Bitmap;
	RECT rct;
NOTIFYICONDATA tnid; 

CString PrevFile;
fstream CallLog;
	
BSTR AddName,StreamName;

	VARIANT RenderResult;
	VARIANT Media;
	VARIANT_BOOL MediaType;

ITTAPI * gpTapi;
IEnumAddress* pEnumAddress;
ITTerminalSupport * pTerminalSupport;
ITAddress* pAddress;
ITTerminal*pTerminalRecord;
ITTerminal*pTerminalPlay;

long                         gulAdvise;  // Globally declared
IConnectionPointContainer   * pCPC;
IConnectionPoint            * pCP;
IUnknown                    * pUnk;
long glRegister;
CTAPIEventNotification* pEventNotification;
ITCallStateEvent * pStateEvent;
ITCallNotificationEvent *pEvent;
ITCallInfo * pCallInfo;
ITBasicCallControl *    pBasicCall;
HRESULT hr;
char buffer[12],time[30];
VARIANT MedTypeResult,ClassTypeResult;
ITStreamControl * pStreamControl;
IEnumStream * pEnumStreams;
ITStream    * pStream;
SYSTEMTIME SysTime;
CTime theTime;
DISPID disp;
VARIANTARG varg[1],TerminalVarg[3];
VARIANT result,regresult,TerminalRecordResult,TerminalPlayResult;

DISPID mydisp; //default property setting,imp to implement
DISPPARAMS params,parms,TerminalParam;

VARIANT DisconnectResult;
VARIANTARG DisconnectArg[1];
DISPPARAMS DisconnectParams;

DISPPARAMS CallControl;
VARIANT CallResult;
VARIANTARG CallArg[3];


TERMINAL_STATE TermState;
DISPPARAMS SelectParam;
VARIANT SelectResult;
VARIANTARG SelectArg[1];
CALL_STATE CallState;

VARIANT UnRegResult;
DISPPARAMS UnRegParams;
VARIANTARG UnRegArg[1];

CBitmapButton m_bitPlay;
CBitmapButton m_bitStop;
CBitmapButton m_bitRecord;
CBitmapButton m_bitMin;
CBitmapButton m_bitMenu;

public:
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedRecord();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedMin();
	afx_msg UINT OnNcHitTest(CPoint point);
		
	afx_msg void OnSettingsHello();
	afx_msg void OnBnClickedMenu();
	
	
	afx_msg void OnConfigureModem();
	afx_msg void OnConfigureSound();
	afx_msg void OnConfigurePower();
	afx_msg void OnSettingsAbout();
	afx_msg void OnSettingsExit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELEPATHYDLG_H__4BD9019C_B19C_4460_9EFA_06F9A155B3A5__INCLUDED_)
