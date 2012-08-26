// TelePathyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TelePathy.h"
#include "TelePathyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelePathyDlg dialog

CTelePathyDlg::CTelePathyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTelePathyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTelePathyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTelePathyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTelePathyDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_MMCONTROL1, m_MMControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTelePathyDlg, CDialog)
	//{{AFX_MSG_MAP(CTelePathyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PLAY, OnBnClickedPlay)
	ON_BN_CLICKED(IDC_RECORD, OnBnClickedRecord)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_MIN, OnBnClickedMin)
	ON_WM_NCHITTEST()
	ON_COMMAND(ID_SETTINGS_HELLO178, OnSettingsHello)
	ON_BN_CLICKED(IDC_MENU, OnBnClickedMenu)
	
	ON_COMMAND(ID_CONFIGURE_MODEM, OnConfigureModem)
	ON_COMMAND(ID_CONFIGURE_SOUND, OnConfigureSound)
	ON_COMMAND(ID_CONFIGURE_POWER, OnConfigurePower)
	ON_COMMAND(ID_SETTINGS_ABOUT188, OnSettingsAbout)
	ON_COMMAND(ID_SETTINGS_EXIT189, OnSettingsExit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelePathyDlg message handlers

BOOL CTelePathyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetLayeredWindowAttributes(RGB(0,0,0), 200, LWA_COLORKEY);//CAN USE LWA_ALPHA ALSO FOR TRANSLUCENCY
	SetWindowText(_T("TelePathy"));

m_bitPlay.AutoLoad(IDC_PLAY,this);
m_bitStop.AutoLoad(IDC_STOP,this);
m_bitRecord.AutoLoad(IDC_RECORD,this);
m_bitMin.AutoLoad(IDC_MIN,this);
m_bitMenu.AutoLoad(IDC_MENU,this);
m_Bitmap.LoadBitmap(IDB_MAIN);
pDC.CreateCompatibleDC(this->GetDC());
pDC.SelectObject(&m_Bitmap);




//////////////FOR OLDER VC++ VERSIONS PLEASE BE SURE TO ADD THE COMMAND /force:multiple TO THE LINKER BEFORE BUILDING

//////////The MCI Control and the Listbox Control (m_List) are hidden behind the 'Cool' UI in the IDD_TELEPATHY_DIALOG 


//////   m_MMControl is the hidden MCI Control used for synchronous playbacks 
/////  of messages onto TAPI outgoing stream and for recording of user's message to played

//////Could've used File/Track Terminals but they are rarely available on most computers////////

m_MMControl.SetNotify(false);
m_MMControl.SetWait(true);
m_MMControl.SetShareable(false);
m_MMControl.SetDeviceType("WaveAudio");
m_MMControl.SetRecordVisible(false);
m_MMControl.SetRecordEnabled(true);
m_MMControl.SetPlayVisible(false);
m_MMControl.SetPlayEnabled(true);
m_MMControl.SetRecordMode(1);
m_MMControl.SetRecordVisible(false);
m_MMControl.SetStopEnabled(true);
m_MMControl.SetUpdateInterval(100);//increase this time if you want wav files smaller in size

m_List.ResetContent();
UpdateData(false);

hr=::CoInitialize(NULL); //Initialze COM and its Thread Apartment
	ASSERT(hr>=0);

///////Setup the TAPI Call Environment/////////
     StartUp();		//Local function
	
UpdateData(false);

this->MyTaskBar(this->m_hWnd,2,this->m_hIcon,"TelePathy! When you are outside");//call the systray handler func. with args specific to this window


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTelePathyDlg::OnPaint() 
{
	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

	}
*/


this->GetDC()->StretchBlt(0,0,300,300,&pDC,0,0,300,300,SRCCOPY);
CDialog::OnPaint();
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTelePathyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




LRESULT CTelePathyDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	
switch(message)

{
case 49594://Our messageID declared in the CTapiEventNotification Class 
		
	{

		switch ( (TAPI_EVENT)wParam)
					
			{

							case TE_CALLSTATE:

								{		


										DISPPARAMS CallParam={NULL, NULL, 0, 0};//argument less Param;
											VARIANT CallResult;
										::VariantInit(&CallResult);
											CallResult.vt=VT_DISPATCH;
										CallResult.pdispVal=NULL;



											VARIANT CallStateResult;
											::VariantInit(&CallStateResult);
											CallStateResult.vt=VT_DISPATCH;
											CallStateResult.pdispVal=NULL;

												//begin code to handle the call


							hr=((IDispatch*)lParam)->QueryInterface(IID_ITCallStateEvent,(void**)&pStateEvent);
							hr=pStateEvent->Invoke( 0x00000001,IID_NULL,GetUserDefaultLCID(),DISPATCH_PROPERTYGET,&CallParam,&CallResult,NULL,NULL);//gets the ITCallInfo ptr	


							hr=((ITCallInfo*)CallResult.pdispVal)->QueryInterface(IID_ITBasicCallControl,(void**)&pBasicCall);
							if(hr!=S_OK){m_List.AddString("basic terminal not acquired");}

	
								///////////////////Check if there is not another similar application running already////////////////////////////
	
									CALL_PRIVILEGE CallPrivilege;
								((ITCallInfo*)CallResult.pdispVal)->get_Privilege( &CallPrivilege);
									if(CallPrivilege!=CP_OWNER)
										{m_List.AddString("Call not owned");this->Shutdown();this->StartUp();return 0;}

										
											//////////////////////////////////////////////////

									
									((ITCallInfo*)CallResult.pdispVal)->get_CallState(&CallState);
										
													switch(CallState)



	{
		case CS_OFFERING: //Call has appeared and is offering to be handled
			{

			
																								
	m_List.AddString("New call has arrived at time:-");
	UpdateData(false);
	if(!IsIconic()){AfxGetApp()->GetMainWnd()->FlashWindow(true);}
//If the App. Window is not hidden it'll be flashed on call
	

((ITCallInfo*)CallResult.pdispVal)->get_Address(&pAddress);
pAddress->get_AddressName(&AddName);
m_List.AddString((CString)AddName);
UpdateData(false);
SysFreeString(AddName);
																	
/*															
DISPPARAMS CallerParam;
VARIANTARG CallerArg[1];
VARIANT CallerResult;

VariantInit(&CallerResult);
CallerResult.vt=VT_BSTR;

CallerArg[0].vt=VT_I4;

CallerParam.cArgs=1;			  //THIS MODULE IS FOR CALLER-ID,DUE TO DIFFERENCE IN HOW CALLERID NUMBERS ARE INTERPRETED IN DIFFERENT COUNTRIES ,THIS MODULE IS ERRORSOME
CallerParam.cNamedArgs=0;			//IF YOU ARE ABLE TO SORT IT OUT YOU CAN MAIL ME AT AmanSunil2002@Yahoo.com
CallerParam.rgdispidNamedArgs=NULL; 
CallerParam.rgvarg=CallerArg;

VariantInit(&(CallerParam.rgvarg[0]));
CallerParam.rgvarg[0].vt=VT_I4;
CallerParam.rgvarg[0].lVal=CIS_CALLERIDNUMBER;																														

((ITCallInfo*)CallResult.pdispVal)->Invoke( 0x00010006,IID_NULL,GetUserDefaultLCID(),DISPATCH_PROPERTYGET,&CallerParam,&CallerResult,NULL,NULL);
		m_List.AddString((CString)(CallerResult.bstrVal));
	UpdateData(false);
*/



		



	if((hr=pBasicCall->QueryInterface(IID_ITStreamControl,(void **) &pStreamControl)) != S_OK)
{m_List.AddString("can't get streamcall ptr");m_List.AddString(itoa(hr,buffer,10));UpdateData(false);}

																		
				m_List.AddString("Connecting");
						UpdateData(false);

						

////////////////////////////////////
//connect and answer the call ////

DISPPARAMS Answer={NULL,NULL,0,0};
VARIANT AnswerResult;
::VariantInit(&AnswerResult);
AnswerResult.vt=VT_EMPTY;
hr=pBasicCall->Invoke( 0x00020004,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&Answer,&AnswerResult,NULL,NULL);
if(hr<S_OK){m_List.AddString("Failed to connect/answer.Error No.:-");m_List.AddString(itoa(hr,buffer,10));this->Shutdown();this->StartUp();return 0;}

/////////////////////////////
				break;
						}
					
			case CS_CONNECTED: //When here, we're connected
			{
					m_List.AddString("Connected");
					UpdateData(false);


if((hr=pStreamControl->EnumerateStreams( &pEnumStreams))!=S_OK)
{m_List.AddString("can't get streamcall ptr");m_List.AddString(itoa(hr,buffer,10));this->Shutdown();this->StartUp();UpdateData(false);return 0;}

while ( S_OK == pEnumStreams->Next( 1, &pStream, NULL) )
    {	
        // Get the media type and direction of this stream.
        long                lMediaType;
		TERMINAL_DIRECTION  dir;
		pStream->get_Name(&StreamName);
		m_List.AddString((CString)StreamName);
		UpdateData(false);
		SysFreeString(StreamName);
		pStream->get_MediaType( &lMediaType );
		pStream->get_Direction( &dir );
		       
		if((lMediaType==8) && (dir == TD_CAPTURE)){break;}
				//select the audio stream that can be played 
		if(pStream) pStream->Release();
	}


HRESULT htr;

					m_MMControl.SetFileName(".\\Record\\Play.wav");
					htr=pStream->SelectTerminal(pTerminalPlay);//Select the terminal for playback created earlier to play the recorded message on to the outgoing stream
					m_MMControl.SetCommand("Open");
					hr=pStream->StartStream();
					if((hr==S_OK)&&(htr==S_OK))
					{
					m_MMControl.SetWait(true);//Playing will be synchronous. We don't want the control to move ahead until the message has been played
					m_MMControl.SetCommand("Play");
					m_MMControl.SetCommand("Stop");
					m_MMControl.SetCommand("Close");//Very Important to close the file to allow playback for the next seesion
					}
					m_List.AddString("message played");
					hr=pStream->StopStream();
					if(hr==S_OK){m_List.AddString("stream stopped");}//m_List.AddString(itoa(hr,buffer,10));}
					UpdateData(false);	
						
					hr=pStream->UnselectTerminal( pTerminalPlay);//Message has been played.Remove the terminal from the stream
					if(hr==S_OK){m_List.AddString("unselected play terminal");UpdateData(false);	}
				
					//Get the current time so as to attach it into the name of the .wav file name that'll be used to record the message coming from other side
					//This makes each wav file uniquely named and also gives information about the time of the call ...Clever!!
					try
					{
					theTime = CTime::GetCurrentTime();
					theTime.GetAsSystemTime(SysTime);
					wsprintf(time,"%u_%u",SysTime.wHour,SysTime.wMinute);
					m_MMControl.SetFileName(  (CString)(".\\Messages\\")  + (CString)"Call at " + (CString)time +(CString)".Wav" );
					}
					catch(...){}


while ( S_OK == pEnumStreams->Next( 1, &pStream, NULL) )
    {	
        // Get the media type and direction of this stream.
        long                lMediaType;
		TERMINAL_DIRECTION  dir;
		pStream->get_Name(&StreamName);
		m_List.AddString((CString)StreamName);
		UpdateData(false);
		SysFreeString(StreamName);
		pStream->get_MediaType( &lMediaType );
		pStream->get_Direction( &dir );
		       
		if((lMediaType==8) && (dir == TD_RENDER)){break;}
			//select the audio stream that can be played 
if(pStream) pStream->Release();
	}


pEnumStreams->Release();


					hr=pStream->SelectTerminal(pTerminalRecord);//Select the terminal for recording created earlier to record the message coming in
					m_MMControl.SetCommand("Open");
					pStream->StartStream();	
					m_MMControl.SetCommand("Record");
					::SetTimer(this->m_hWnd,1,20000,NULL);//begin timer to record the message for next 20 seconds .Increase this time if you expect a chatter calling on
					//when the timer goes off recording stops ,recorded file is saved and the TAPI environment is restarted
					m_List.AddString("Recording begins at:-");
					m_List.AddString((CString)time);
					UpdateData(false);					
					break;
			}
	

	case CS_DISCONNECTED:
			{	
				m_List.AddString("Disconnected Successfully");UpdateData(false);
				
				break;	
			}



			default:break;
				}
//end of code

		break;
}
					
							default:{break;}
					}
			break;
			}


case (MYWM_NOTIFYICON)://this is the message, window recieves on mouseclick on tray icon
{

UINT uID; 
UINT uMouseMsg; 
 
    uID = (UINT) wParam; 
    uMouseMsg = (UINT) lParam; 


	if(uID==2)
	{if(uMouseMsg==WM_LBUTTONDOWN)
		{
		::ShowWindow(this->m_hWnd,SW_SHOWNORMAL);
		::SetForegroundWindow(this->m_hWnd);
		}
	
	}



break;
}


default:break;
}


	
	return CDialog::DefWindowProc(message, wParam, lParam);


}




////////////This method starts a new session for call recieval without needing the application to restart///
void CTelePathyDlg::StartUp()
{
	try

	{

hr=::CoCreateInstance(
    CLSID_TAPI,
    NULL,
    CLSCTX_INPROC_SERVER,			///Create TAPI Root Object
    IID_ITTAPI,
    (LPVOID *)&gpTapi
    );

ASSERT(hr>=0);


// Initialize TAPI/////
hr=gpTapi->Initialize();
ASSERT(hr>=0);

hr=gpTapi->EnumerateAddresses( &pEnumAddress);
ASSERT(hr>=0);


BSTR Provider,Address;
ULONG Number=0;

while (S_OK== pEnumAddress->Next( 1, &pAddress, &Number) ) 
{

pAddress->get_ServiceProviderName(&Provider);
	if((CString)Provider=="unimdm.tsp")
		{
		    pAddress->get_AddressName(&Address);
			m_List.AddString((CString)Provider);//add the modem service provider's name
			m_List.AddString((CString)Address);//add the TAPI Address name that will serve our requests
			SysFreeString(Provider);
			SysFreeString(Address);
			UpdateData(false);
				break;
		}
SysFreeString(Provider);
SysFreeString(Address);
pAddress->Release();
}

pEnumAddress->Release();


/////////////Querying ConnectionPoint////////////


hr=gpTapi->QueryInterface(
     IID_IConnectionPointContainer,
     (void **)&pCPC
     );

ASSERT(hr>=0);


// Get the ITTAPIEventNOtification interface pointer from the container.

hr=pCPC->FindConnectionPoint(
     IID_ITTAPIEventNotification,
     &pCP
     );

ASSERT(hr>=0);
pCPC->Release();



pEventNotification=new CTAPIEventNotification;

pEventNotification->QueryInterface(
    IID_IUnknown,
    (void **)&pUnk
    );



// Call the advise method to give TAPI
// the IUnknown pointer for the event handler.
hr=pCP->Advise(pUnk,
     (ULONG *)&gulAdvise
     );

ASSERT(hr>=0);
pCP->Release();

///////////////  Putting Event Filter to notify which kind of Call-notifications we want///////////////
///Using IDispatch interface rather than IUnknown b'coz 'EventFilter' method is not refrenced in some old Visual C++ (6.0) Header & Proxy Libraries(tapi3.h and TapiT3IID.LIB)
/////////////    Other functions called using Invoke follow the suit//////////

mydisp=DISPID_PROPERTYPUT;
OLECHAR FAR *func1=L"EventFilter";

params.rgvarg=varg;
VariantInit(&params.rgvarg[0]);
unsigned int err;
params.cArgs=1;
params.cNamedArgs=1;
params.rgvarg[0].vt=VT_I4;
params.rgvarg[0].lVal=TE_CALLNOTIFICATION|TE_CALLSTATE ;
params.rgdispidNamedArgs=&mydisp;;
::VariantInit(&result);
result.vt=VT_EMPTY;


gpTapi->GetIDsOfNames(IID_NULL,&func1,1,LOCALE_USER_DEFAULT,&disp);
hr=gpTapi->Invoke (disp,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_PROPERTYPUT,&params,NULL,NULL,&err);

ASSERT(hr>=0);

///////////////Registering Call Notifications using IDispatch as well//////////

OLECHAR FAR *func2=L"RegisterCallNotifications";

VARIANTARG vargreg[5];
parms.rgvarg=vargreg;
for(int a=0;a<5;a++){VariantInit(&parms.rgvarg[a]);}
parms.cArgs=5;
parms.cNamedArgs=0;
parms.rgdispidNamedArgs=NULL;
parms.rgvarg[4].vt=VT_DISPATCH;
parms.rgvarg[4].pdispVal=pAddress;
pAddress->QueryInterface(IID_IDispatch,(void**)(&(parms.rgvarg[4].pdispVal)));
parms.rgvarg[3].vt=VT_BOOL;
parms.rgvarg[3].boolVal=VARIANT_TRUE;
parms.rgvarg[2].vt=VT_BOOL;
parms.rgvarg[2].boolVal=VARIANT_TRUE;
parms.rgvarg[1].vt=VT_I4;
parms.rgvarg[1].lVal=8;//we want only audio call notifications
parms.rgvarg[0].vt=VT_I4;
parms.rgvarg[0].lVal=gulAdvise;


::VariantInit(&regresult);
regresult.vt=VT_I4;
regresult.lVal=0;


gpTapi->GetIDsOfNames(IID_NULL,&func2,1,LOCALE_USER_DEFAULT,&disp);
hr=gpTapi->Invoke(disp,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD,&parms,&regresult,NULL,NULL);
glRegister=regresult.lVal;
ASSERT(hr>=0);


////////////////////////////////////////////////////////////////////

hr=pAddress->QueryInterface(IID_ITTerminalSupport,(void **)&pTerminalSupport);

ASSERT(hr>=0);
/////////////////////////////////////////////////////////////////////



IEnumTerminal *pEnumTerminal;
BSTR TermName;


///////get the the terminal for recording/////////////////

hr=pTerminalSupport->EnumerateStaticTerminals(&pEnumTerminal);
ASSERT(hr>=0);

while(S_OK==(pEnumTerminal->Next(1,&pTerminalRecord,NULL)))
{ 

DISPPARAMS Render={NULL,NULL,0,0};
RenderResult.vt=VT_I4;
::VariantInit(&RenderResult);
hr=pTerminalRecord->Invoke(0x00000006,IID_NULL,GetUserDefaultLCID(),DISPATCH_PROPERTYGET,&Render,&RenderResult,NULL,NULL);
ASSERT(hr>=0);
if(RenderResult.lVal==TD_RENDER){ pTerminalRecord->get_Name(&TermName);break;}
pTerminalRecord->Release();
} ///end of while loop


m_List.AddString((CString)TermName+" for recording");
SysFreeString(TermName);
pEnumTerminal->Release();

///////get the the terminal for playback/////////////////


pTerminalSupport->EnumerateStaticTerminals(&pEnumTerminal);
while(S_OK==(pEnumTerminal->Next(1,&pTerminalPlay,NULL)))
{ 

DISPPARAMS Render={NULL,NULL,0,0};
RenderResult.vt=VT_I4;
::VariantInit(&RenderResult);
hr=pTerminalPlay->Invoke(0x00000006,IID_NULL,GetUserDefaultLCID(),DISPATCH_PROPERTYGET,&Render,&RenderResult,NULL,NULL);
ASSERT(hr>=0);
if(RenderResult.lVal==TD_CAPTURE){ pTerminalPlay->get_Name(&TermName);break;}


} ///end of while loop

m_List.AddString((CString)TermName+" for playback");
SysFreeString(TermName);
pEnumTerminal->Release();

m_List.AddString("");
	m_List.AddString("-------------------------------------------------------------");
	m_List.AddString("");
	m_List.AddString("Ready for new Call");UpdateData(false);
	
	}

	catch(...)
	{
{m_List.AddString("Fatal Error.Failed to create TAPI environment.Exiting..");WriteLog();exit(0);}

	}


}

////////////this method cleans up all the resources held by one call session and recreates the environment for next call recieval//////
void CTelePathyDlg::Shutdown()
{


try{

VariantInit(&DisconnectResult);
DisconnectResult.vt=VT_EMPTY;

DisconnectParams.rgvarg=DisconnectArg;

DisconnectParams.cArgs=1;
DisconnectParams.cNamedArgs=0;
DisconnectParams.rgdispidNamedArgs=NULL;

VariantInit(DisconnectParams.rgvarg);
DisconnectParams.rgvarg[0].vt=VT_I4;
DisconnectParams.rgvarg[0].lVal=0;
if(pBasicCall) hr=pBasicCall->Invoke( 0x00020005,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&DisconnectParams,&DisconnectResult,NULL,NULL);//Disconnect();
if(hr!=S_OK){m_List.AddString("not disconnected");m_List.AddString(itoa(hr,buffer,10));}
if(hr==S_OK){m_List.AddString("disconnecting..");}
			UpdateData(false);


VariantInit(&UnRegResult);
UnRegResult.vt=VT_EMPTY;

UnRegParams.rgvarg=UnRegArg;
UnRegParams.cArgs=1;
UnRegParams.cNamedArgs=0;
UnRegParams.rgdispidNamedArgs=NULL;

VariantInit(&(UnRegParams.rgvarg[0]));
UnRegParams.rgvarg[0].vt=VT_I4;
UnRegParams.rgvarg[0].lVal=glRegister;

hr=gpTapi->Invoke(0x00010004,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&UnRegParams,&UnRegResult,NULL,NULL);//UnRegister Notifications
ASSERT(hr>=0);
hr=gpTapi->Shutdown();
ASSERT(hr>=0);



///Forget about Release() ,just set all the previously held TAPI resources to NULL;//////////
////// The number of TAPI instances held by any of the interfaces is not more than 2 in anycase///////

////////Not the most efficient way to release but I'm working on when,where and by how many does TAPI AddRef()s its interfaces
//////////////Suggestions will be welcomed!!////////////

gpTapi=NULL;
pTerminalSupport=NULL;
pEnumAddress=NULL;
pAddress=NULL;
pTerminalPlay=NULL;
pTerminalRecord=NULL;
pUnk=NULL;
pEventNotification=NULL;
pStateEvent=NULL;
pEvent=NULL;
pCallInfo=NULL;
pBasicCall=NULL;
pStreamControl=NULL;
pEnumStreams=NULL;
pStream=NULL;

	}
	catch(...){m_List.AddString("Fatal Error.Failed to create TAPI environment.Exiting..");WriteLog();exit(0);}



}

//////////When a call has been recieved we'd want to setup the TAPI Environment agin for the next call
void CTelePathyDlg::OnTimer(UINT nIDEvent) 
{
if(nIDEvent==1)
	{
	m_MMControl.SetCommand("Save");
	m_MMControl.SetCommand("Stop");
	m_MMControl.SetCommand("Close");
	pStream->StopStream();
	pStream->UnselectTerminal( pTerminalRecord);
	this->Shutdown();
	this->StartUp();
	
	}
	

	CDialog::OnTimer(nIDEvent);
}


void CTelePathyDlg::OnClose() 
{
	CString StrExit="            This will minimize TallyPathy to systray.."  ;
StrExit.Format(StrExit + "\nPress OK to minimize to Systray , Cancel to exit ");
	if( MessageBox( StrExit,"TelePathy!",MB_OKCANCEL)==IDOK)
	{ShowWindow(SW_MINIMIZE);return;}	
	
	
	else
	{
		::CoUninitialize();	

////////////Write the contents of m_List to log before exiting
				WriteLog();


Shell_NotifyIcon(NIM_DELETE,&tnid);//THIS CLEANS UP THE OUR SYSTRAY RESOURCES ON EXIT
	
	
	}
	CDialog::OnClose();
}


void CTelePathyDlg::OnSize(UINT nType, int cx, int cy) //if the user has chosen to minimize call the  OnTray() function
{
	CDialog::OnSize(nType, cx, cy);
	
if (IsIconic())
{OnTray();}


}

void CTelePathyDlg::OnTray()  //delegate the call to MyTaskBar function and hide the UI
{

	this->MyTaskBar(this->m_hWnd,2,this->m_hIcon,"TelePathy! When you are outside ");//call the systray handler func. with args specific to this window
	ShowWindow(SW_HIDE);	
	
}

BOOL CTelePathyDlg::MyTaskBar(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip)
{

BOOL res; 
    
    tnid.cbSize = sizeof(NOTIFYICONDATA); 
    tnid.hWnd = hwnd; //handle to the window that'll recieve the callback
    tnid.uID = uID; //unique id for our tray icon
    tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; //kind of resources/messages we want the systray to notify/allocate to our systray request
    tnid.uCallbackMessage = MYWM_NOTIFYICON; //The message MYWM_NOTIFYICON will be posted to the window with handle hwnd on clicking the tray icon 
    tnid.hIcon = hicon; //icon handle that'll be displayed in the tray
    if (lpszTip) 
        lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip)); 
    else 
        tnid.szTip[0] = '\0'; 
 
    res = Shell_NotifyIcon(NIM_ADD, &tnid); //notify the rundll32.exe to recieve the NOTIFYICONDATA data in tnid to allocate a seat in the tray
 
    if (hicon) 
        DestroyIcon(hicon); 
 
    return res; 




}



void CTelePathyDlg::WriteLog()
{


///////////Create a log of call progress////////
UpdateData(false);
CString ListBuffer;
try{

CallLog.open(".\\Log\\CallLog.txt",ios::out|ios::app|ios::ate);
for(int Log=0;Log < m_List.GetCount();Log++)
	{
		m_List.GetText(Log,ListBuffer);
		CallLog.write(ListBuffer,ListBuffer.GetLength());
		CallLog<<"\n";
	}

CallLog<<"\n\n\n";
CallLog.close();
}

catch(...){}




}

void CTelePathyDlg::OnBnClickedPlay()
{
PrevFile=m_MMControl.GetFileName();
m_MMControl.SetFileName(".\\Record\\Play.wav");
m_MMControl.SetCommand("Open");
m_MMControl.SetWait(true);
m_MMControl.SetCommand("Play");
m_MMControl.SetCommand("Stop");
m_MMControl.SetCommand("Close");
m_MMControl.SetFileName(PrevFile);
}

void CTelePathyDlg::OnBnClickedRecord()
{
	PrevFile=m_MMControl.GetFileName();
m_MMControl.SetFileName(".\\Record\\Play.wav");
m_MMControl.SetCommand("Open");
m_MMControl.SetCommand("Record");
}

void CTelePathyDlg::OnBnClickedStop()
{
m_MMControl.SetCommand("Save");
m_MMControl.SetCommand("Stop");
m_MMControl.SetCommand("Close");
m_MMControl.SetFileName(PrevFile);	
}

void CTelePathyDlg::OnBnClickedMin()
{
	PostMessage(WM_CLOSE);
}

UINT CTelePathyDlg::OnNcHitTest(CPoint point)
{
	UINT uDef=(UINT)Default();
	if(uDef==HTCLIENT) return HTCAPTION;

	return CDialog::OnNcHitTest(point);
}




void CTelePathyDlg::OnSettingsHello()
{
	WinExec("Notepad.exe .\\Log\\CallLog.txt",SW_SHOW);

}


void CTelePathyDlg::OnBnClickedMenu()
{	
	CPoint m_pPoint(10,10);
	ClientToScreen(&m_pPoint);
	CMenu menu;
	menu.LoadMenu(IDR_MYMENU);
	CMenu* pContext=menu.GetSubMenu(0);
	pContext->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,m_pPoint.x,m_pPoint.y,AfxGetMainWnd());
    

}

void CTelePathyDlg::OnConfigureModem()
{
	WinExec("control.exe telephon.cpl",SW_SHOW);
}

void CTelePathyDlg::OnConfigureSound()
{
	WinExec("control.exe mmsys.cpl",SW_SHOW);
}

void CTelePathyDlg::OnConfigurePower()
{
	WinExec("control.exe powercfg.cpl",SW_SHOW);
}


void CTelePathyDlg::OnSettingsAbout()
{
	MessageBox("TelePathy! When you are outside\nEMail :Amansunil2002@Yahoo.com");
}

void CTelePathyDlg::OnSettingsExit()
{
	PostMessage(WM_CLOSE);

}
