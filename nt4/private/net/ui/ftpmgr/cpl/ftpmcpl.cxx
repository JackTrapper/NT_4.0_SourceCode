/**********************************************************************/
/**                       Microsoft Windows NT                       **/
/**                Copyright(c) Microsoft Corp., 1993                **/
/**********************************************************************/

/*
    ftpmcpl.cxx
    This is the main module for the FTP Server Control Panel Applet.
    It contains the "CplApplet" function.


    FILE HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.

*/



#define INCL_NET
#define INCL_NETLIB
#define INCL_NETSERVICE
#define INCL_WINDOWS
#define INCL_WINDOWS_GDI
#define INCL_NETERRORS
#define INCL_DOSERRORS
#include <lmui.hxx>

#if defined(DEBUG)
static const CHAR szFileName[] = __FILE__;
#define _FILENAME_DEFINED_ONCE szFileName
#endif

#include <uiassert.hxx>
#include <uitrace.hxx>

#define INCL_BLT_WINDOW
#define INCL_BLT_DIALOG
#define INCL_BLT_CONTROL
#define INCL_BLT_CLIENT
#define INCL_BLT_MSGPOPUP
#define INCL_BLT_EVENT
#define INCL_BLT_MISC
#define INCL_BLT_TIMER
#define INCL_BLT_CC
#include <blt.hxx>

#include <dbgstr.hxx>
#include <uatom.hxx>
#include <regkey.hxx>
#include <lmoloc.hxx>
#include <srvsvc.hxx>

extern "C"
{
    #include <cpl.h>               // Multimedia CPL defs
    #include <ftpmgr.h>
    #include <ftpd.h>
}


extern "C"
{
    //
    //  Control Panel Applet entry point.
    //

    LONG FAR PASCAL CPlApplet( HWND hwndCPl,
                               WORD nMsg,
                               LONG lParam1,
                               LONG lparam2 );

    //
    //  DLL load/unload entry point.
    //

    BOOL FAR PASCAL FtpMgrDllInitialize( HINSTANCE hInstance,
                                         DWORD  nReason,
                                         LPVOID pReserved );

    //
    //  Globals.
    //

    HINSTANCE _hCplInstance = NULL;

}   // extern "C"

#include <ftpmgr.hxx>

//
//  This is the "type" for an applet startup function.
//

typedef APIERR (* PCPL_APPLET_FUNC)( HWND hWnd );


//
//  We'll keep one of these structures for each applet in this DLL.
//

typedef struct _CPL_APPLET
{
    int                 idIcon;
    int                 idName;
    int                 idInfo;
    int                 idHelpFile;
    DWORD               dwHelpContext;
    LONG                lData;
    PCPL_APPLET_FUNC    pfnApplet;

} CPL_APPLET;


//
//  Forward reference prototypes.
//

APIERR RunFtpSvcMgr( HWND hWnd );


//
//  Our applet descriptors.
//

CPL_APPLET CplApplets[] = {
                              {  // FTP Server applet
                                 IDI_FTPCPA_ICON,
                                 IDS_FTPCPA_NAME_STRING,
                                 IDS_FTPCPA_INFO_STRING,
                                 IDS_CPL_HELPFILENAME,
                                 HC_FTPSVCMGR_DIALOG,
                                 0L,
                                 &RunFtpSvcMgr
                              }
                          };

#define NUM_APPLETS ( sizeof(CplApplets) / sizeof(CplApplets[0]) )

/*******************************************************************

    NAME:       InitializeDll

    SYNOPSIS:   Perform DLL initialiazation functions on a
                once-per-process basis.

    ENTRY:      hInstance  - Program instance of the caller.

    EXIT:       If this is the first initialization request for this
                process, then all necessary BLT initializers have
                been invoked.

    RETURNS:    BOOL       - TRUE  = Initialization OK.
                             FALSE = Initialization failed.

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.

********************************************************************/
BOOL InitializeDll( HINSTANCE hInstance )
{
    //
    //  Save the instance handle.
    //

    _hCplInstance = hInstance;

    return TRUE;

}   // InitializeDll


/*******************************************************************

    NAME:       TerminateDll

    SYNOPSIS:   Perform DLL termination functions on a
                once-per-process basis.

    EXIT:       All necessary BLT terminators have been invoked.

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.

********************************************************************/
VOID TerminateDll( VOID )
{
    //
    //  Just in case we try to do anything goofy.
    //

    _hCplInstance = NULL;

}   // TerminateDll


/*******************************************************************

    NAME:       IsFtpServerInstalled

    SYNOPSIS:   Determines if the FTP Server service is installed.
                This doesn't necessarily mean the service is actually
                running, just that it is installed on the system.

    RETURNS:    BOOL   - TRUE  = FTP Server service is installed.
                         FALSE = FTP Server service isn't installed.

    NOTES:      We could perform this check by trying to open the
                service via the Service Controller, but this would
                cause a lot of extraneous code to get paged in.
                Instead, we'll check for the presence of the registry
                key that controls the service.

    HISTORY:
        KeithMo         09-Apr-1993      Created.

********************************************************************/
BOOL IsFtpServerInstalled( VOID )
{
    BOOL fInstalled = FALSE;    // until proven otherwise...

    //
    //  Open the registry root.
    //

    REG_KEY RootKey( HKEY_LOCAL_MACHINE );

    APIERR err = RootKey.QueryError();

    if( err == NERR_Success )
    {
        //
        //  Open the FTPSVC registry key.
        //

        ALIAS_STR nlsKeyName( (TCHAR *)FTPD_PARAMETERS_KEY );
        UIASSERT( !!nlsKeyName );

        REG_KEY RegKey( RootKey, nlsKeyName );
        err = RegKey.QueryError();

        if( err == NERR_Success )
        {
            //
            //  Since we successfully opened the FTP Server's
            //  parameters key, we'll assume that the service
            //  is indeed installed.
            //

            fInstalled = TRUE;
        }
    }

    return fInstalled;

}   // IsFtpServerInstalled


/*******************************************************************

    NAME:       InitializeAllApplets

    SYNOPSIS:   Called before applet proper is run.

    ENTRY:      hWnd   - Window handle of parent window.

    RETURNS:    BOOL   - TRUE  = Applet should be installed.
                         FALSE = Applet cannot be installed.

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.
        KeithMo         09-Apr-1993      Don't init if service not installed.
        JonN            05-Oct-1994      Added lParam parameters to CPL_INIT, CPL_TERM
        JonN            22-Sep-1995      Only called when applet is run

********************************************************************/
BOOL InitializeAllApplets( HWND hWnd, LONG lParam1, LONG lParam2 )
{
    TRACEEOL( "FTPMGR.CPL: InitializeAllApplets enter" );
    //
    //  Before we do anything, check to see if the FTP Server service
    //  is installed.  If it isn't there's not much point in running
    //  this applet.
    //

    if( !IsFtpServerInstalled() )
    {
        return FALSE;
    }

    //
    //  Initialize all of the NetUI goodies.
    //

    APIERR err = BLT::Init( _hCplInstance,
                            IDRSRC_FTPMGR_BASE, IDRSRC_FTPMGR_LAST,
                            IDS_UI_FTPMGR_BASE, IDS_UI_FTPMGR_LAST );

    TRACEEOL( "FTPMGR.CPL: InitializeAllApplets BLT::Init returns " << err );

    if( err == NERR_Success )
    {
        TRACEEOL( "FTPMGR.CPL: InitializeAllApplets BLT::_MASTER_TIMER::Init next" );

        err = BLT_MASTER_TIMER::Init();

        TRACEEOL( "FTPMGR.CPL: InitializeAllApplets BLT::_MASTER_TIMER::Init returns " << err );

        if( err != NERR_Success )
        {
            //
            //  BLT initialized OK, but BLT_MASTER_TIMER
            //  failed.  So, before we bag-out, we must
            //  deinitialize BLT.
            //

            BLT::Term( _hCplInstance );
        }
    }

    if( err == NERR_Success )
    {
        err = BLT::RegisterHelpFile( _hCplInstance,
                                     IDS_CPL_HELPFILENAME,
                                     HC_UI_FTPMGR_BASE,
                                     HC_UI_FTPMGR_LAST );

        if( err != NERR_Success )
        {
            //
            //  This is the only place where we can safely
            //  invoke MsgPopup, since we *know* that all of
            //  the BLT goodies were initialized properly.
            //
            ::MsgPopup( hWnd, err );

            BLT::Term( _hCplInstance );
        }
    }

    TRACEEOL( "FTPMGR.CPL: InitializeAllApplets exit" );

    return err == NERR_Success;

}   // InitializeAllApplets


/*******************************************************************

    NAME:       TerminateAllApplets

    SYNOPSIS:   Called after applet is run.

    ENTRY:      hWnd - Window handle of parent window.

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.
        JonN            04-Oct-1994      Added lParam parameters to CPL_INIT, CPL_TERM
        JonN            22-Sep-1995      Only called when applet is run

********************************************************************/
VOID TerminateAllApplets( HWND hWnd, LONG lParam1, LONG lParam2 )
{
    UNREFERENCED( hWnd );

    TRACEEOL( "FTPMGR.CPL: TerminateAllApplets enter" );
    //
    //  Kill the NetUI goodies.
    //

    BLT::DeregisterHelpFile( _hCplInstance, 0 );
    TRACEEOL( "FTPMGR.CPL: TerminateAllApplets BLT::_MASTER_TIMER::Term next" );
    BLT_MASTER_TIMER::Term();
    TRACEEOL( "FTPMGR.CPL: TerminateAllApplets BLT::_MASTER_TIMER::Term complete" );
    BLT::Term( _hCplInstance );

    TRACEEOL( "FTPMGR.CPL: TerminateAllApplets exit" );

}   // TerminateAllApplets

/*******************************************************************

    NAME:       AutoStartFtpServer

    SYNOPSIS:   Check the state of the FTP Server service.  If it
                isn't started, ask the user if it should be started.
                If the user wants us to start the service, start it.

    ENTRY:      hWnd    - Window handle of parent window.

    RETURNS:    BOOL - TRUE  == FTP Server service is running.
                       FALSE == FTP Server service isn't running.
                                This may indicate either an error
                                or the user didn't want the service
                                started.  If an error occurs, this
                                routine is responsible for displaying
                                it to the user.

    HISTORY:
        KeithMo         09-Apr-1993     Created.

********************************************************************/
BOOL AutoStartFtpServer( HWND hWnd )
{
    BOOL fStarted = FALSE;      // until proven otherwise...

    //
    //  Get the "display name" for the local machine.
    //

    LOCATION loc( LOC_TYPE_LOCAL );
    NLS_STR  nlsDisplayName;

    APIERR err = loc.QueryError();
    err = err ? err : nlsDisplayName.QueryError();
    err = err ? err : loc.QueryDisplayName( &nlsDisplayName );

    if( err == NERR_Success )
    {
        //
        //  Determine the state of the service.
        //

        GENERIC_SERVICE * psvc = new GENERIC_SERVICE( hWnd,
                                                      NULL,
                                                      nlsDisplayName,
                                                      (TCHAR *)FTPD_SERVICE_NAME );

        err = ( psvc == NULL ) ? ERROR_NOT_ENOUGH_MEMORY
                               : psvc->QueryError();

        if( err == NERR_Success )
        {
            fStarted = psvc->IsInstalled( &err );

            if( !fStarted && ( err == NERR_Success ) )
            {
                //
                //  Service isn't started.  See if the user wants us
                //  to start it.
                //

                if( ::MsgPopup( hWnd,
                                IDS_START_FTPSVC_NOW,
                                MPSEV_WARNING,
                                MP_YESNO,
                                MP_YES ) == IDYES )
                {
                    err = psvc->Start();

                    if( err == NERR_ServiceInstalled )
                    {
                        //
                        //  Somebody must have started the service
                        //  behind our backs...
                        //

                        err = NERR_Success;
                    }

                    if( err == NERR_Success )
                    {
                        //
                        //  Whew!
                        //

                        fStarted = TRUE;
                    }
                }
            }
        }

        delete psvc;
    }

    //
    //  If anything tragic occurred, tell the user.
    //

    if( err != NERR_Success )
    {
        ::MsgPopup( hWnd, err );
    }

    return fStarted;

}   // AutoStartFtpServer


/*******************************************************************

    NAME:       RunFtpSvcMgr

    SYNOPSIS:   Invoke the main dialog of the FTP Server Control
                Panel Applet.

    ENTRY:      hWnd    - Window handle of parent window.

    RETURNS:    APIERR

    HISTORY:
        YiHsinS         18-Mar-1993     Created
        KeithMo         09-Apr-1993     Autostart FTP service.

********************************************************************/
APIERR RunFtpSvcMgr( HWND hWnd )
{
    //
    //  If the service isn't started, ask the user if
    //  it should be started.
    //

    if( !AutoStartFtpServer( hWnd ) )
    {
        //
        //  The user doesn't want to play right now.
        //

        return NERR_Success;
    }

    AUTO_CURSOR autocur;

    // In the control panel applet, we will only be focusing on
    // the local machine.

    POPUP::SetCaption( IDS_FTPCPA_CAPTION );

    FTP_SVCMGR_DIALOG * pDlg = new FTP_SVCMGR_DIALOG( hWnd,
                                                      NULL ); // local computer

    APIERR err = ( pDlg == NULL ) ? ERROR_NOT_ENOUGH_MEMORY
                                  : pDlg->QueryError();

    if ( err == NERR_Success )
        err = pDlg->Process();

    delete pDlg;
    pDlg = NULL;

    if( err != NERR_Success )
    {
        if ( err == RPC_S_SERVER_UNAVAILABLE )
            err = IERR_FTP_SERVICE_UNAVAILABLE;
        ::MsgPopup( hWnd, err );
    }

    POPUP::ResetCaption();
    return err;

}   // RunFtpSvcMgr


BOOL strLoad( INT idString, WCHAR * pszBuffer, INT cchBuffer )
{
    int result = ::LoadString( ::_hCplInstance,
                                idString,
                                pszBuffer,
                                cchBuffer );

    return ( result > 0 ) && ( result < cchBuffer );

}   // strLoad


/*******************************************************************

    NAME:       CPlApplet

    SYNOPSIS:   Exported function to start the FTP Server Control
                Panel Applet.

    ENTRY:      hwndCPl   - Window handle of parent.

                nMsg      - CPL user message (see CPL.H
                            in WINDOWS\SHELL\CONTROL\H).

                lParam1   - Message-specific pointer.

                lParam2   - Message-specific pointer.

    RETURNS:    LONG

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.
        JonN            04-Oct-1994      Added lParam parameters to CPL_INIT, CPL_TERM
        JonN            22-Sep-1995      BLT::Init only called when applet is run

********************************************************************/
LONG FAR PASCAL CPlApplet( HWND hwndCPl,
                           WORD nMsg,
                           LONG lParam1,
                           LONG lParam2 )
{
    LPCPLINFO    pCplInfo;
    LPNEWCPLINFO pNewInfo;
    LONG         nResult = 0;

    switch( nMsg )
    {
    case CPL_INIT:
        //
        //  This message is sent to indicate that CPlApplet() was found.
        //
        //  lParam1 is not used, but we pass it anyway.
        //
        //  lParam2 is -1 iff the DLL will be used only to confirm the
        //  number of applets.
        //
        //  Return TRUE if applet should be installed, FALSE otherwise.
        //
        //  Before we do anything, check to see if the FTP Server service
        //  is installed.  If it isn't there's not much point in running
        //  this applet.
        //

        return IsFtpServerInstalled();

    case CPL_GETCOUNT:
        //
        //  This message is set to determine the number of applets contained
        //  in this DLL.
        //
        //  lParam1 and lParam2 are not used.
        //
        //  Return the number of applets contained in this DLL.
        //

        return NUM_APPLETS;

    case CPL_INQUIRE:
        //
        //  This message is sent once per applet to retrieve information
        //  about each applet.
        //
        //  lParam1 is the applet number to register.
        //
        //  lParam2 is a pointer to a CPLINFO structure.  The CPLINFO
        //  structure's idIcon, idName, idInfo, and lData fields should
        //  be initialized as appropriate for the applet.
        //
        //  There is no return value.
        //

        pCplInfo = (LPCPLINFO)lParam2;

        if( lParam1 < NUM_APPLETS )
        {
            CPL_APPLET * pApplet = &CplApplets[lParam1];

            pCplInfo->idIcon = pApplet->idIcon;
            pCplInfo->idName = pApplet->idName;
            pCplInfo->idInfo = pApplet->idInfo;
            pCplInfo->lData  = pApplet->lData;
        }
        break;

    case CPL_SELECT:
        //
        //  This message is sent when the applet's icon has been
        //  selected.
        //
        //  lParam1 is the applet number that was selected.
        //
        //  lParam2 is the applet's lData value.
        //
        //  There is no return value.
        //

        break;

    case CPL_DBLCLK:
        //
        //  This message is sent when the applet's icon has been
        //  double-clicked.  This message should initiate the
        //  applet's dialog box.
        //
        //  lParam1 is the applet number that was selected.
        //
        //  lParam2 is the applet's lData value.
        //
        //  There is no return value.
        //

        if( lParam1 < NUM_APPLETS )
        {
            if ((LONG)InitializeAllApplets( hwndCPl, lParam1, lParam2 ))
            {
                (CplApplets[lParam1].pfnApplet)( hwndCPl );
                TerminateAllApplets( hwndCPl, lParam1, lParam2 );
            }
            else
            {
                ASSERT( FALSE );
            }
        }
        break;

    case CPL_STOP:
        //
        //  This message is sent once for each applet when the
        //  control panel is shutting down.  This message should
        //  initiate applet specific cleanup.
        //
        //  lParam1 is the applet number being stopped.
        //
        //  lParam2 is the applet's lData value.
        //
        //  There is no return value.
        //

        break;

    case CPL_EXIT:
        //
        //  This message is sent just before the control panel calls
        //  FreeLibrary.  This message should initiate non applet
        //  specific cleanup.
        //
        //  lParam1 is not used, but we pass it anyway.
        //
        //  lParam2 is -1 iff the DLL was used only to confirm the
        //  number of applets.
        //
        //  There is no return value.
        //

        break;

    case CPL_NEWINQUIRE:
        //
        //  This message is basically the same as CPL_INQUIRE, except
        //  lParam2 points to a NEWCPLINFO structure.  This message will
        //  be sent *before* CPL_INQUIRE.  If the applet returns a non
        //  zero value, then CPL_INQUIRE will not be sent.
        //
        //  lParam1 is the applet number to register.
        //
        //  lParam2 is a pointer to a NEWCPLINFO structure.
        //
        //  Return TRUE this message was handled, otherwise return FALSE.
        //

        pNewInfo = (LPNEWCPLINFO)lParam2;

        if( lParam1 < NUM_APPLETS )
        {
            CPL_APPLET * pApplet = &CplApplets[lParam1];

            pNewInfo->dwSize        = sizeof(*pNewInfo);
            pNewInfo->dwFlags       = 0;
            pNewInfo->dwHelpContext = pApplet->dwHelpContext;
            pNewInfo->lData         = pApplet->lData;

            pNewInfo->hIcon = ::LoadIcon( ::_hCplInstance,
                                          MAKEINTRESOURCE( pApplet->idIcon ) );

            if( ( pNewInfo->hIcon != NULL ) &&
                strLoad( pApplet->idName,
                         pNewInfo->szName,
                         sizeof(pNewInfo->szName) ) &&
                strLoad( pApplet->idInfo,
                         pNewInfo->szInfo,
                         sizeof(pNewInfo->szInfo) ) &&
                strLoad( pApplet->idHelpFile,
                         pNewInfo->szHelpFile,
                         sizeof(pNewInfo->szHelpFile) ) )
            {
                nResult = TRUE;
            }
        }
        break;

    default:
        //
        //  Who knows.  Ignore it.
        //

        break;
    }

    return nResult;

}   // CPlApplet


/*******************************************************************

    NAME:       FtpMgrDllInitialize

    SYNOPSIS:   This DLL entry point is called when processes & threads
                are initialized and terminated, or upon calls to
                LoadLibrary() and FreeLibrary().

    ENTRY:      hInstance    - A handle to the DLL.

                nReason      - Indicates why the DLL entry
                               point is being called.

                pReserved    - Reserved.

    RETURNS:    BOOL         - TRUE  = DLL init was successful.
                               FALSE = DLL init failed.

    NOTES:      The return value is only relevant during processing of
                DLL_PROCESS_ATTACH notifications.

    HISTORY:
        YiHsinS         22-Mar-1993      Templated from Keithmo's srvmcpl.cxx.

********************************************************************/

BOOL FAR PASCAL FtpMgrDllInitialize( HINSTANCE hInstance,
                                     DWORD  nReason,
                                     LPVOID pReserved )
{
    UNREFERENCED( pReserved );

    BOOL fResult = TRUE;

    switch( nReason  )
    {
    case DLL_PROCESS_ATTACH:
        //
        //  This notification indicates that the DLL is attaching to
        //  the address space of the current process.  This is either
        //  the result of the process starting up, or after a call to
        //  LoadLibrary().  The DLL should us this as a hook to
        //  initialize any instance data or to allocate a TLS index.
        //
        //  This call is made in the context of the thread that
        //  caused the process address space to change.
        //

        fResult = InitializeDll( hInstance );
        break;

    case DLL_PROCESS_DETACH:
        //
        //  This notification indicates that the calling process is
        //  detaching the DLL from its address space.  This is either
        //  due to a clean process exit or from a FreeLibrary() call.
        //  The DLL should use this opportunity to return any TLS
        //  indexes allocated and to free any thread local data.
        //
        //  Note that this notification is posted only once per
        //  process.  Individual threads do not invoke the
        //  DLL_THREAD_DETACH notification.
        //

        TerminateDll();
        break;

    case DLL_THREAD_ATTACH:
        //
        //  This notfication indicates that a new thread is being
        //  created in the current process.  All DLLs attached to
        //  the process at the time the thread starts will be
        //  notified.  The DLL should use this opportunity to
        //  initialize a TLS slot for the thread.
        //
        //  Note that the thread that posts the DLL_PROCESS_ATTACH
        //  notification will not post a DLL_THREAD_ATTACH.
        //
        //  Note also that after a DLL is loaded with LoadLibrary,
        //  only threads created after the DLL is loaded will
        //  post this notification.
        //

        break;

    case DLL_THREAD_DETACH:
        //
        //  This notification indicates that a thread is exiting
        //  cleanly.  The DLL should use this opportunity to
        //  free any data stored in TLS indices.
        //

        break;

    default:
        //
        //  Who knows?  Just ignore it.
        //

        break;
    }

    return fResult;


}   // FtpMgrDllInitialize

