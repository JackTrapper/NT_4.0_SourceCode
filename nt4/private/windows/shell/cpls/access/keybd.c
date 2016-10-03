/*******************************************************************
 *    DESCRIPTION: Keyboard Dialog handler
 *******************************************************************/


#include "Access.h"


// *******************************************************************
// KeyboardDialog handler
// *******************************************************************
BOOL WINAPI KeyboardDlg (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   STICKYKEYS sk;       // Tmp holder for settings.
   FILTERKEYS fk;
   TOGGLEKEYS tk;
   BOOL fProcessed = TRUE;

   switch (uMsg) {
      case WM_INITDIALOG:
         CheckDlgButton(hwnd, IDC_STK_ENABLE, (g_sk.dwFlags & SKF_STICKYKEYSON) ? TRUE : FALSE);
         if (!(g_sk.dwFlags & SKF_AVAILABLE)) {
            EnableWindow(GetDlgItem(hwnd, IDC_STK_SETTINGS), FALSE);
            EnableWindow(GetDlgItem(hwnd, IDC_STK_ENABLE), FALSE);
         }

         CheckDlgButton(hwnd, IDC_FK_ENABLE, (g_fk.dwFlags & FKF_FILTERKEYSON) ? TRUE : FALSE);

         CheckDlgButton(hwnd, IDC_TK_ENABLE, (g_tk.dwFlags & TKF_TOGGLEKEYSON) ? TRUE : FALSE);
         if (!(g_tk.dwFlags & TKF_AVAILABLE)) {
            EnableWindow(GetDlgItem(hwnd, IDC_TK_SETTINGS), FALSE);
            EnableWindow(GetDlgItem(hwnd, IDC_TK_ENABLE), FALSE);
         }

         CheckDlgButton(hwnd, IDC_SHOWEXTRAKYBDHELP, g_fExtraKeyboardHelp);
         if (g_fWinNT) ShowWindow(GetDlgItem(hwnd, IDC_SHOWEXTRAKYBDHELP), SW_HIDE);
         break;

    case WM_HELP:  // F1
         WinHelp(((LPHELPINFO) lParam)->hItemHandle, __TEXT("access.hlp"), HELP_WM_HELP, (DWORD) (LPSTR) g_aIds);
         break;

    case WM_CONTEXTMENU:   // right mouse click
         WinHelp((HWND) wParam, __TEXT("access.hlp"), HELP_CONTEXTMENU, (DWORD) (LPSTR) g_aIds);
         break;

    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wParam, lParam)) {
            case IDC_STK_ENABLE:
               g_sk.dwFlags ^= SKF_STICKYKEYSON;
               SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_FK_ENABLE:
               g_fk.dwFlags ^= FKF_FILTERKEYSON;
               SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_TK_ENABLE:
               g_tk.dwFlags ^= TKF_TOGGLEKEYSON;
               SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_STK_SETTINGS:
               sk = g_sk;
               if (DialogBox(g_hinst, MAKEINTRESOURCE(IDD_STICKYSETTINGS), hwnd, StickyKeyDlg) == IDCANCEL)
                  g_sk = sk;
               else SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_FK_SETTINGS:
               fk = g_fk;
               if (DialogBox(g_hinst, MAKEINTRESOURCE(IDD_FILTERSETTINGS), hwnd, FilterKeyDlg) == IDCANCEL)
                  g_fk = fk;
               else SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_TK_SETTINGS:
               tk = g_tk;
               if (DialogBox(g_hinst, MAKEINTRESOURCE(IDD_TOGGLESETTINGS), hwnd, ToggleKeySettingsDlg) == IDCANCEL) {
                  g_tk = tk;
               } else SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;

            case IDC_SHOWEXTRAKYBDHELP:
               g_fExtraKeyboardHelp = !g_fExtraKeyboardHelp;
               CheckDlgButton(hwnd, IDC_SHOWEXTRAKYBDHELP, g_fExtraKeyboardHelp);
               SendMessage(GetParent(hwnd), PSM_CHANGED, (WPARAM) hwnd, 0);
               break;
         }
         break;


      case WM_NOTIFY:
         switch (((NMHDR *)lParam)->code) {
            case PSN_APPLY: SetAccessibilitySettings(); break;
         }
         break;

      default: fProcessed = FALSE; break;
   }

   return(fProcessed);
}


///////////////////////////////// End of File /////////////////////////////////
