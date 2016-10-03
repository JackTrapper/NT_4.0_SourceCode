/*++

Copyright (c) 1994  Microsoft Corporation

Module Name:

    error.c

Abstract:

    Wininet error handlers

Author:

    Richard L Firth (rfirth) 03-Nov-1995

Revision History:

    03-Nov-1995 rfirth
        Created

--*/

#include "ftpcatp.h"

//
// data
//

BOOL NoAlerts = TRUE;

//
// external data
//

extern BOOL Verbose;

//
// private prototypes
//

char* map_error(DWORD);
void get_last_internet_error(void);
LPSTR get_error_string(DWORD);

//
// functions
//

void print_error(char* func, char* format, ...) {

    va_list argptr;
    char buf[256];
    DWORD error;

    error = GetLastError();
    va_start(argptr, format);
    vsprintf(buf, format, argptr);
    printf("error: %s: %s returns %d [%s]\n", func, buf, error, map_error(error));
    va_end(argptr);
    if (error == ERROR_INTERNET_EXTENDED_ERROR) {
        get_last_internet_error();
    }
}

#define ERROR_CASE(error)  case error: return # error

char* map_error(DWORD error) {
    switch (error) {

    //
    // Windows base errors
    //

    ERROR_CASE(ERROR_SUCCESS);
    ERROR_CASE(ERROR_INVALID_FUNCTION);
    ERROR_CASE(ERROR_FILE_NOT_FOUND);
    ERROR_CASE(ERROR_PATH_NOT_FOUND);
    ERROR_CASE(ERROR_ACCESS_DENIED);
    ERROR_CASE(ERROR_INVALID_HANDLE);
    ERROR_CASE(ERROR_NOT_ENOUGH_MEMORY);
    ERROR_CASE(ERROR_NO_MORE_FILES);
    ERROR_CASE(ERROR_INVALID_PASSWORD);
    ERROR_CASE(ERROR_INVALID_PARAMETER);
    ERROR_CASE(ERROR_BUFFER_OVERFLOW);
    ERROR_CASE(ERROR_NO_MORE_SEARCH_HANDLES);
    ERROR_CASE(ERROR_INVALID_TARGET_HANDLE);
    ERROR_CASE(ERROR_CALL_NOT_IMPLEMENTED);
    ERROR_CASE(ERROR_INSUFFICIENT_BUFFER);
    ERROR_CASE(ERROR_INVALID_NAME);
    ERROR_CASE(ERROR_INVALID_LEVEL);
    ERROR_CASE(ERROR_BAD_PATHNAME);
    ERROR_CASE(ERROR_BUSY);
    ERROR_CASE(ERROR_ALREADY_EXISTS);
    ERROR_CASE(ERROR_FILENAME_EXCED_RANGE);
    ERROR_CASE(ERROR_MORE_DATA);
    ERROR_CASE(ERROR_NO_MORE_ITEMS);
    ERROR_CASE(ERROR_INVALID_ADDRESS);
    ERROR_CASE(ERROR_OPERATION_ABORTED);
    ERROR_CASE(ERROR_IO_PENDING);
    ERROR_CASE(RPC_S_INVALID_STRING_BINDING);
    ERROR_CASE(RPC_S_WRONG_KIND_OF_BINDING);
    ERROR_CASE(RPC_S_INVALID_BINDING);
    ERROR_CASE(RPC_S_PROTSEQ_NOT_SUPPORTED);
    ERROR_CASE(RPC_S_INVALID_RPC_PROTSEQ);
    ERROR_CASE(RPC_S_INVALID_STRING_UUID);
    ERROR_CASE(RPC_S_INVALID_ENDPOINT_FORMAT);
    ERROR_CASE(RPC_S_INVALID_NET_ADDR);
    ERROR_CASE(RPC_S_NO_ENDPOINT_FOUND);
    ERROR_CASE(RPC_S_INVALID_TIMEOUT);
    ERROR_CASE(RPC_S_OBJECT_NOT_FOUND);
    ERROR_CASE(RPC_S_ALREADY_REGISTERED);
    ERROR_CASE(RPC_S_TYPE_ALREADY_REGISTERED);
    ERROR_CASE(RPC_S_ALREADY_LISTENING);
    ERROR_CASE(RPC_S_NO_PROTSEQS_REGISTERED);
    ERROR_CASE(RPC_S_NOT_LISTENING);
    ERROR_CASE(RPC_S_UNKNOWN_MGR_TYPE);
    ERROR_CASE(RPC_S_UNKNOWN_IF);
    ERROR_CASE(RPC_S_NO_BINDINGS);
    ERROR_CASE(RPC_S_NO_PROTSEQS);
    ERROR_CASE(RPC_S_CANT_CREATE_ENDPOINT);
    ERROR_CASE(RPC_S_OUT_OF_RESOURCES);
    ERROR_CASE(RPC_S_SERVER_UNAVAILABLE);
    ERROR_CASE(RPC_S_SERVER_TOO_BUSY);
    ERROR_CASE(RPC_S_INVALID_NETWORK_OPTIONS);
    ERROR_CASE(RPC_S_NO_CALL_ACTIVE);
    ERROR_CASE(RPC_S_CALL_FAILED);
    ERROR_CASE(RPC_S_CALL_FAILED_DNE);
    ERROR_CASE(RPC_S_PROTOCOL_ERROR);
    ERROR_CASE(RPC_S_UNSUPPORTED_TRANS_SYN);
    ERROR_CASE(RPC_S_UNSUPPORTED_TYPE);
    ERROR_CASE(RPC_S_INVALID_TAG);
    ERROR_CASE(RPC_S_INVALID_BOUND);
    ERROR_CASE(RPC_S_NO_ENTRY_NAME);
    ERROR_CASE(RPC_S_INVALID_NAME_SYNTAX);
    ERROR_CASE(RPC_S_UNSUPPORTED_NAME_SYNTAX);
    ERROR_CASE(RPC_S_UUID_NO_ADDRESS);
    ERROR_CASE(RPC_S_DUPLICATE_ENDPOINT);
    ERROR_CASE(RPC_S_UNKNOWN_AUTHN_TYPE);
    ERROR_CASE(RPC_S_MAX_CALLS_TOO_SMALL);
    ERROR_CASE(RPC_S_STRING_TOO_LONG);
    ERROR_CASE(RPC_S_PROTSEQ_NOT_FOUND);
    ERROR_CASE(RPC_S_PROCNUM_OUT_OF_RANGE);
    ERROR_CASE(RPC_S_BINDING_HAS_NO_AUTH);
    ERROR_CASE(RPC_S_UNKNOWN_AUTHN_SERVICE);
    ERROR_CASE(RPC_S_UNKNOWN_AUTHN_LEVEL);
    ERROR_CASE(RPC_S_INVALID_AUTH_IDENTITY);
    ERROR_CASE(RPC_S_UNKNOWN_AUTHZ_SERVICE);
    ERROR_CASE(EPT_S_INVALID_ENTRY);
    ERROR_CASE(EPT_S_CANT_PERFORM_OP);
    ERROR_CASE(EPT_S_NOT_REGISTERED);
    ERROR_CASE(RPC_S_NOTHING_TO_EXPORT);
    ERROR_CASE(RPC_S_INCOMPLETE_NAME);
    ERROR_CASE(RPC_S_INVALID_VERS_OPTION);
    ERROR_CASE(RPC_S_NO_MORE_MEMBERS);
    ERROR_CASE(RPC_S_NOT_ALL_OBJS_UNEXPORTED);
    ERROR_CASE(RPC_S_INTERFACE_NOT_FOUND);
    ERROR_CASE(RPC_S_ENTRY_ALREADY_EXISTS);
    ERROR_CASE(RPC_S_ENTRY_NOT_FOUND);
    ERROR_CASE(RPC_S_NAME_SERVICE_UNAVAILABLE);
    ERROR_CASE(RPC_S_INVALID_NAF_ID);
    ERROR_CASE(RPC_S_CANNOT_SUPPORT);
    ERROR_CASE(RPC_S_NO_CONTEXT_AVAILABLE);
    ERROR_CASE(RPC_S_INTERNAL_ERROR);
    ERROR_CASE(RPC_S_ZERO_DIVIDE);
    ERROR_CASE(RPC_S_ADDRESS_ERROR);
    ERROR_CASE(RPC_S_FP_DIV_ZERO);
    ERROR_CASE(RPC_S_FP_UNDERFLOW);
    ERROR_CASE(RPC_S_FP_OVERFLOW);
    ERROR_CASE(RPC_X_NO_MORE_ENTRIES);
    ERROR_CASE(RPC_X_SS_CHAR_TRANS_OPEN_FAIL);
    ERROR_CASE(RPC_X_SS_CHAR_TRANS_SHORT_FILE);
    ERROR_CASE(RPC_X_SS_IN_NULL_CONTEXT);
    ERROR_CASE(RPC_X_SS_CONTEXT_DAMAGED);
    ERROR_CASE(RPC_X_SS_HANDLES_MISMATCH);
    ERROR_CASE(RPC_X_SS_CANNOT_GET_CALL_HANDLE);
    ERROR_CASE(RPC_X_NULL_REF_POINTER);
    ERROR_CASE(RPC_X_ENUM_VALUE_OUT_OF_RANGE);
    ERROR_CASE(RPC_X_BYTE_COUNT_TOO_SMALL);
    ERROR_CASE(RPC_X_BAD_STUB_DATA);


    //
    // WinInet errors
    //

    ERROR_CASE(ERROR_INTERNET_OUT_OF_HANDLES);
    ERROR_CASE(ERROR_INTERNET_TIMEOUT);
    ERROR_CASE(ERROR_INTERNET_EXTENDED_ERROR);
    ERROR_CASE(ERROR_INTERNET_INTERNAL_ERROR);
    ERROR_CASE(ERROR_INTERNET_INVALID_URL);
    ERROR_CASE(ERROR_INTERNET_UNRECOGNIZED_SCHEME);
    ERROR_CASE(ERROR_INTERNET_NAME_NOT_RESOLVED);
    ERROR_CASE(ERROR_INTERNET_PROTOCOL_NOT_FOUND);
    ERROR_CASE(ERROR_INTERNET_INVALID_OPTION);
    ERROR_CASE(ERROR_INTERNET_BAD_OPTION_LENGTH);
    ERROR_CASE(ERROR_INTERNET_OPTION_NOT_SETTABLE);
    ERROR_CASE(ERROR_INTERNET_SHUTDOWN);
    ERROR_CASE(ERROR_INTERNET_INCORRECT_USER_NAME);
    ERROR_CASE(ERROR_INTERNET_INCORRECT_PASSWORD);
    ERROR_CASE(ERROR_INTERNET_LOGIN_FAILURE);
    ERROR_CASE(ERROR_INTERNET_INVALID_OPERATION);
    ERROR_CASE(ERROR_INTERNET_OPERATION_CANCELLED);
    ERROR_CASE(ERROR_INTERNET_INCORRECT_HANDLE_TYPE);
    ERROR_CASE(ERROR_INTERNET_NOT_PROXY_REQUEST);
    ERROR_CASE(ERROR_INTERNET_REGISTRY_VALUE_NOT_FOUND);
    ERROR_CASE(ERROR_INTERNET_BAD_REGISTRY_PARAMETER);
    ERROR_CASE(ERROR_INTERNET_NO_DIRECT_ACCESS);
    ERROR_CASE(ERROR_INTERNET_NO_CONTEXT);
    ERROR_CASE(ERROR_INTERNET_NO_CALLBACK);
    ERROR_CASE(ERROR_INTERNET_REQUEST_PENDING);

    ERROR_CASE(ERROR_FTP_TRANSFER_IN_PROGRESS);
    ERROR_CASE(ERROR_FTP_DROPPED);

    ERROR_CASE(ERROR_GOPHER_PROTOCOL_ERROR);
    ERROR_CASE(ERROR_GOPHER_NOT_FILE);
    ERROR_CASE(ERROR_GOPHER_DATA_ERROR);
    ERROR_CASE(ERROR_GOPHER_END_OF_DATA);
    ERROR_CASE(ERROR_GOPHER_INVALID_LOCATOR);
    ERROR_CASE(ERROR_GOPHER_INCORRECT_LOCATOR_TYPE);
    ERROR_CASE(ERROR_GOPHER_NOT_GOPHER_PLUS);
    ERROR_CASE(ERROR_GOPHER_ATTRIBUTE_NOT_FOUND);
    ERROR_CASE(ERROR_GOPHER_UNKNOWN_LOCATOR);

    ERROR_CASE(ERROR_HTTP_HEADER_NOT_FOUND);
    ERROR_CASE(ERROR_HTTP_DOWNLEVEL_SERVER);
    ERROR_CASE(ERROR_HTTP_INVALID_SERVER_RESPONSE);


    //
    // Windows sockets errors
    //

    ERROR_CASE(WSAEINTR);
    ERROR_CASE(WSAEBADF);
    ERROR_CASE(WSAEACCES);
    ERROR_CASE(WSAEFAULT);
    ERROR_CASE(WSAEINVAL);
    ERROR_CASE(WSAEMFILE);
    ERROR_CASE(WSAEWOULDBLOCK);
    ERROR_CASE(WSAEINPROGRESS);
    ERROR_CASE(WSAEALREADY);
    ERROR_CASE(WSAENOTSOCK);
    ERROR_CASE(WSAEDESTADDRREQ);
    ERROR_CASE(WSAEMSGSIZE);
    ERROR_CASE(WSAEPROTOTYPE);
    ERROR_CASE(WSAENOPROTOOPT);
    ERROR_CASE(WSAEPROTONOSUPPORT);
    ERROR_CASE(WSAESOCKTNOSUPPORT);
    ERROR_CASE(WSAEOPNOTSUPP);
    ERROR_CASE(WSAEPFNOSUPPORT);
    ERROR_CASE(WSAEAFNOSUPPORT);
    ERROR_CASE(WSAEADDRINUSE);
    ERROR_CASE(WSAEADDRNOTAVAIL);
    ERROR_CASE(WSAENETDOWN);
    ERROR_CASE(WSAENETUNREACH);
    ERROR_CASE(WSAENETRESET);
    ERROR_CASE(WSAECONNABORTED);
    ERROR_CASE(WSAECONNRESET);
    ERROR_CASE(WSAENOBUFS);
    ERROR_CASE(WSAEISCONN);
    ERROR_CASE(WSAENOTCONN);
    ERROR_CASE(WSAESHUTDOWN);
    ERROR_CASE(WSAETOOMANYREFS);
    ERROR_CASE(WSAETIMEDOUT);
    ERROR_CASE(WSAECONNREFUSED);
    ERROR_CASE(WSAELOOP);
    ERROR_CASE(WSAENAMETOOLONG);
    ERROR_CASE(WSAEHOSTDOWN);
    ERROR_CASE(WSAEHOSTUNREACH);
    ERROR_CASE(WSAENOTEMPTY);
    ERROR_CASE(WSAEPROCLIM);
    ERROR_CASE(WSAEUSERS);
    ERROR_CASE(WSAEDQUOT);
    ERROR_CASE(WSAESTALE);
    ERROR_CASE(WSAEREMOTE);
    ERROR_CASE(WSAEDISCON);
    ERROR_CASE(WSASYSNOTREADY);
    ERROR_CASE(WSAVERNOTSUPPORTED);
    ERROR_CASE(WSANOTINITIALISED);
    ERROR_CASE(WSAHOST_NOT_FOUND);
    ERROR_CASE(WSATRY_AGAIN);
    ERROR_CASE(WSANO_RECOVERY);
    ERROR_CASE(WSANO_DATA);

    default:
        return "?";
    }
}

void get_last_internet_error() {

    DWORD buflen;
    char buffer[256];
    DWORD category;

    buflen = sizeof(buffer);
    if (InternetGetLastResponseInfo(&category, buffer, &buflen)) {
        print_response(buffer, buflen, FALSE);
    } else {

        DWORD error;

        error = GetLastError();
        if (Verbose || (error != ERROR_INSUFFICIENT_BUFFER)) {
            printf(get_error_string(error), error, buflen);
        }
        if (error == ERROR_INSUFFICIENT_BUFFER) {

            LPSTR errbuf;

            if ((errbuf = malloc(buflen)) != NULL) {
                if (InternetGetLastResponseInfo(&category, errbuf, &buflen)) {
                    print_response(errbuf, buflen, FALSE);
                } else {
                    error = GetLastError();
                    printf(get_error_string(GetLastError()), error, buflen);
                }
                free(errbuf);
            } else {
                printf("error: get_last_internet_error: malloc(%d) failed\n", buflen);
            }
        }
    }
}

LPSTR get_error_string(DWORD error) {

    static LPSTR errText_1 = "error: get_last_internet_error: InternetGetLastResponseInfo() returns error %d (buflen = %d)\n";
    static LPSTR errText_2 = "error: get_last_internet_error: InternetGetLastResponseInfo() returns error %d\n";

    return (error == ERROR_INSUFFICIENT_BUFFER) ? errText_1 : errText_2;
}

void print_response(LPSTR buffer, DWORD buflen, BOOL isMessage) {
    if (Verbose || !isMessage) {
        printf("InternetGetLastResponseInfo() returns %d bytes\n", buflen);
    }
    if (buflen != 0) {
        if (isMessage) {

            int mode;

            mode = _setmode(1, _O_BINARY);
            _write(1, buffer, buflen);
            _setmode(1, mode);
        } else {
            printf("Text = \"%s\"\n", buffer);
        }
    }
    if (strlen(buffer) != buflen) {
        alert();
        printf("error: print_response: InternetGetLastResponseInfo(): buflen = %d; strlen(buffer) = %d\n",
                buflen,
                strlen(buffer)
                );
    }
}

void alert() {
    if (!NoAlerts) {
        putchar('\a');
    }
}