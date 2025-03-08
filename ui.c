#include <Windows.h>
#include "ui.h"

const char g_szClassName[] = "EDColonyTracker";
HWND hComboBox, hComboBox2, hMaterialList, hUserMaterialInput, hResultText;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // Create a combo box to select Tier
        hComboBox = CreateWindowW(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            20, 20, 200, 100, hwnd, (HMENU)1, NULL, NULL);
        PopulateTier(hComboBox);

        // Second Combo Box Containing Structure Categories
        hComboBox2 = CreateWindowW(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            20, 60, 200, 100, hwnd, (HMENU)2, NULL, NULL);

        // Placeholder: Additional UI elements like lists and buttons can be added here
        break;
    }
    case WM_COMMAND: {
        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 1) {
            // Enable the second combo box when option is selected in the first combo box
            EnableWindow(hComboBox2, TRUE);
            // Populate the second combo box with items (placeholder)
            SendMessage(hComboBox2, CB_RESETCONTENT, 0, 0);
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Option 1");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Option 2");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Option 3");
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void PopulateTier(HWND hWndComboBox) {
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Tier 1");
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Tier 2");
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Tier 3");
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
    WNDCLASSEX wc = { 0 };
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"EDColonyTracker";

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, L"EDColonyTracker", L"Elite Dangerous Colony Tracker", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return (int)Msg.wParam;
}
