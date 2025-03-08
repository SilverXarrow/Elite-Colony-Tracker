/*
 * Elite Dangerous Colony Tracker - Basic WinAPI GUI
 *
 * This program sets up a simple WinAPI-based GUI with a main window,
 * a menu system, and categorized structure selection for planetary and orbital structures.
 * It includes tier-based selection, a list of required materials, an input box for materials delivered,
 * and a display for remaining materials needed, which updates dynamically.
 */

#include <windows.h>
#include <stdio.h>
#include "structure_data.h"  // Include the new structure data header

 // Global variables
const char g_szClassName[] = "EDColonyTracker";
HWND hTierComboBox, hCategoryComboBox, hStructureComboBox, hMaterialList, hUserMaterialInput, hResultText, hStructureName;

// Function prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void PopulateTiers(HWND);
void PopulateCategories(HWND);
void PopulateStructures(HWND, int, int);
void DisplayMaterials(HWND, int);
void UpdateRemainingMaterials(HWND);

int deliveredMaterials[3] = { 0 };

// WinMain - Entry point of a Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { 0 };
    HWND hwnd;
    MSG Msg;

    // Define window class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;

    // Register window class
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the main application window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, g_szClassName, "Elite Dangerous Colony Tracker", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Window Procedure - Handles window messages
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        hTierComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            20, 20, 200, 100, hwnd, (HMENU)1, NULL, NULL);
        PopulateTiers(hTierComboBox);

        hCategoryComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            20, 60, 200, 100, hwnd, (HMENU)2, NULL, NULL);

        hStructureComboBox = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            20, 100, 200, 100, hwnd, (HMENU)3, NULL, NULL);

        hStructureName = CreateWindow("STATIC", "Structure: ", WS_CHILD | WS_VISIBLE,
            20, 140, 200, 20, hwnd, NULL, NULL, NULL);

        hMaterialList = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 170, 200, 100, hwnd, (HMENU)4, NULL, NULL);

        hUserMaterialInput = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            250, 170, 100, 20, hwnd, (HMENU)5, NULL, NULL);

        hResultText = CreateWindow("STATIC", "Remaining Materials: ", WS_CHILD | WS_VISIBLE,
            250, 200, 200, 20, hwnd, NULL, NULL, NULL);
        break;
    }
    case WM_COMMAND: {
        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 1) {
            EnableWindow(hCategoryComboBox, TRUE);
        }
        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 2) {
            int selectedTier = SendMessage(hTierComboBox, CB_GETCURSEL, 0, 0);
            int selectedCategory = SendMessage(hCategoryComboBox, CB_GETCURSEL, 0, 0);
            PopulateStructures(hStructureComboBox, selectedTier, selectedCategory);
        }
        if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 3) {
            int selectedIndex = SendMessage(hStructureComboBox, CB_GETCURSEL, 0, 0);
            SetWindowText(hStructureName, structures[selectedIndex].name);
            DisplayMaterials(hMaterialList, selectedIndex);
        }
        if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == 5) {
            UpdateRemainingMaterials(hwnd);
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

void PopulateTiers(HWND hWndComboBox) {
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)"Tier 1");
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)"Tier 2");
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)"Tier 3");
}

void PopulateCategories(HWND hWndComboBox) {
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)"Planetary Structures");
    SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)"Orbital Structures");
}

void PopulateStructures(HWND hWndComboBox, int tier, int category) {
    SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
    for (int i = 0; i < NUM_STRUCTURES; i++) {
        if (structures[i].tier == tier && structures[i].category == category) {
            void PopulateStructures(HWND hWndComboBox, int tier, int category); {
                SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
                for (int i = 0; i < NUM_STRUCTURES; i++) {
                    if (structures[i].tier == tier && structures[i].category == category) {
                        SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)structures[i].name);
                    }
                }
            }
            void PopulateStructures(HWND hWndComboBox, int tier, int category); {
                void PopulateStructures(HWND hWndComboBox, int tier, int category); {
                    SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
                    for (int i = 0; i < NUM_STRUCTURES; i++) {
                        if (structures[i].tier == tier && structures[i].category == category) {
                            SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)structures[i].name);
                        }
                    }
                }
                SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
                for (int i = 0; i < NUM_STRUCTURES; i++) {
                    if (structures[i].tier == tier && structures[i].category == category) {
                        SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)structures[i].name);
                    }
                }
            }
            SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)structures[i].name);
        }
    }
}