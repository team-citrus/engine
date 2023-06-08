/*
*   name: src/graphics/windows_window.c
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Functions for Win32 windows
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "core/os.h"

#ifdef CITRUS_ENGINE_WINDOWS

#include <Windows.h>
#include "core/windowsGlobals.h"
#include "core/extensions.h"
#include "graphics/vkInit.h"

NEVER_INLINE CALLBACK LRESULT handleChangeToWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_ACTIVATEAPP:
        // TODO: cosas

        case WM_CHILDACTIVATE:
        // TODO: cosas

        case WM_QUIT:
        case WM_CLOSE:
        // TODO: cosas

        case WM_QUERYOPEN:
        // TODO: cosas

        case WM_SHOWWINDOW:
        // TODO: cosas

        case WM_SIZE:
        {

        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        vkCreateSwapChain(width, height);

        }
        return 0;

        default:
        break;
    }
}

void winit()
{
    WNDCLASS wclass;
    wclass.lpszClassName = L"La sola ventana."; // El uso de UTF16 por parte de Windows es muy tonto. ¿Por qué no usa UTF-8 como el resto del mundo?
    wclass.lpfnWndProc = handleChangeToWindow;
    wclass.hInstance = hinstance;

    RegisterClass(&wclass);

    hwnd = CreateWindowExW(
        0, L"La sola ventana.", /* TODO: lpWindowName */, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hinstance, NULL
    );
}

#endif
