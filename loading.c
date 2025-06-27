#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HFONT hFontBig, hFontSmall;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "NimbleOsWindowClass";

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL; 

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "NimbleOs Loading",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // emperor gay vc desgraçado
    hFontBig = CreateFontA(48,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
                           DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                           DEFAULT_PITCH | FF_SWISS, "Arial");
    hFontSmall = CreateFontA(24,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                             DEFAULT_PITCH | FF_SWISS, "Arial");

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    DeleteObject(hFontBig);
    DeleteObject(hFontSmall);

    return 0;
}

void DrawTextCentered(HDC hdc, RECT rect, LPCSTR text, HFONT font) {
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetTextColor(hdc, RGB(255,255,255));
    SetBkMode(hdc, TRANSPARENT);
    DrawTextA(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    SelectObject(hdc, oldFont);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hbmBuffer = NULL;
    static HDC hdcBuffer = NULL;
    static int bufferWidth = 0;
    static int bufferHeight = 0;

    switch (uMsg) {
    case WM_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        if (hdcBuffer) {
            DeleteDC(hdcBuffer);
            hdcBuffer = NULL;
        }
        if (hbmBuffer) {
            DeleteObject(hbmBuffer);
            hbmBuffer = NULL;
        }

        HDC hdcWindow = GetDC(hwnd);
        hdcBuffer = CreateCompatibleDC(hdcWindow);
        ReleaseDC(hwnd, hdcWindow);

        hbmBuffer = CreateCompatibleBitmap(GetDC(hwnd), width, height);
        SelectObject(hdcBuffer, hbmBuffer);

        bufferWidth = width;
        bufferHeight = height;

        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdcWindow = BeginPaint(hwnd, &ps);

        if (!hdcBuffer) {
            FillRect(hdcWindow, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
            DrawTextCentered(hdcWindow, ps.rcPaint, "NimbleOs", hFontBig);
            DrawTextCentered(hdcWindow, ps.rcPaint, "loading", hFontSmall);
        } else {
            HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
            RECT rect = {0, 0, bufferWidth, bufferHeight};
            FillRect(hdcBuffer, &rect, hBrush);
            DeleteObject(hBrush);

            RECT topRect = rect;
            topRect.bottom = topRect.top + bufferHeight / 2;
            RECT bottomRect = rect;
            bottomRect.top = topRect.bottom;

            DrawTextCentered(hdcBuffer, topRect, "NimbleOs", hFontBig);
            DrawTextCentered(hdcBuffer, bottomRect, "loading", hFontSmall);

            BitBlt(hdcWindow, 0, 0, bufferWidth, bufferHeight,
                   hdcBuffer, 0, 0, SRCCOPY);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        if (hdcBuffer) DeleteDC(hdcBuffer);
        if (hbmBuffer) DeleteObject(hbmBuffer);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}
