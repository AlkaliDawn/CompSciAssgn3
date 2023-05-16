#ifndef UNICODE
#define UNICODE
#endif

#ifdef _MSC_VER

#pragma comment(linker, "/entry:WinMainCRTStartup")
#pragma warning(disable : 4996)

#ifdef _WIN64
#pragma comment(linker, "/subsystem:windows,8.00") // for 64-bit Windows
#else
#pragma comment(linker, "/subsystem:windows,4.00") // for 32-bit Windows
#endif

#endif

#include <Windows.h>
#include <random>
#include <unordered_map>
#include <string>
#include <stdexcept>

#define FONT_NAME TEXT("Consolas")
#define FONT_SIZE 20
#define FONT_QUALITY PROOF_QUALITY
#define FONT_WEIGHT FW_MEDIUM
#define FONT_FAMILY FF_DONTCARE

#define CALC_TEXT_FLAGS (DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE) // Define text flags
#define OUTPUT_TEXT_FLAGS (DT_LEFT | DT_TOP | DT_SINGLELINE) // Define output text flags

int MARGIN = 3;

WPARAM wParam = 0;
LPARAM lParam = 0;

HINSTANCE hInstance;
HWND hWnd;

HDC hdc; // Device context
PAINTSTRUCT ps; // Paint struct

HFONT hFont; // Font
HFONT hOldFont; // Old font

HBRUSH green = CreateSolidBrush(RGB(152, 251, 152));    // green
HBRUSH blue = CreateSolidBrush(RGB(76, 167, 212));      // blue
HBRUSH purple = CreateSolidBrush(RGB(198, 76, 212));    // purple
HBRUSH pink = CreateSolidBrush(RGB(237, 47, 136));      // pink
HBRUSH yellow = CreateSolidBrush(RGB(237, 237, 47));    // yellow
HBRUSH terracotta = CreateSolidBrush(RGB(212, 90, 76)); // terracotta

/*  NULL STRING TO INTEGER */
/* Convert an alphanumeric char buffer (string) where each character
 * is null terminated to a numeric, wide, null-terminated string,
 * and then an int which is returned. */
int nullstrtoi(std::string str, int length) {
    
    // Initialize empty string to hold characters temporarily
    std::string a;
    
    // iterate through given string "length" number of times
    for (int i = 0; i < length * 2; i++) {
        
        if (str[i] != '\000' && !(str[i] > 57 || str[i] < 48)) { // if char is numeric && not null
            a += str[i]; // add character to temp string
        }
    }
    
    a += '\000'; // Make string null terminated
    int b; // create int for output
    
    // prevent crashes from empty strings
    try { b = stoi(a); }
    catch (...) { return 0; }
    
    return b; // return int
    
}

wchar_t* itowcs(int i) {
    wchar_t* w = new wchar_t[10]; // NOLINT
    swprintf_s(w, 10, L"%d", i);
    return w;
}

/* GET INTEGER FROM TEXTBOX */
/* Sends Windows messages to a textbox specified by its handle as an argument,
 * to get a char buffer from its field.
 * Returns an integer using nullstrtoi */
int get_int_from_textbox(HWND textbox) {
    
    // get length of characters in text box
    int len = (int)SendMessage(textbox, WM_GETTEXTLENGTH, 0, 0);
    char* buf = new char[len * 2]; // create character buffer of the necessary length
    
    // get text from the textbox
    SendMessage(textbox, WM_GETTEXT, len + 1, reinterpret_cast<LPARAM>(buf));
    
    std::string s(buf, len * 2); // convert char buffer to string
    delete[] buf; // delete buffer
    return nullstrtoi(s, len); // convert string to int and return
}

bool check_input(int var, int low_bound, int high_bound, int &global) {
    
    // if character is in between specified numbers, return true
    if (low_bound < var && var < high_bound) {
        global = var;
        return true;
    }
    
    return false;
    
}

static void paint_init() {
    // get device context
    hdc = BeginPaint(hWnd, &ps);
    
    SetTextColor(hdc, RGB(0, 0, 5));
    
    // make text boxes transparent
    SetBkMode(hdc, TRANSPARENT);
    
    // Initialize font, and assign old system font to a variable in order to restore it after drawing is finished
    hFont = CreateFont(FONT_SIZE, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS,
                       CLIP_DEFAULT_PRECIS, FONT_QUALITY, DEFAULT_PITCH | FONT_FAMILY, FONT_NAME);
    hOldFont = (HFONT)SelectObject(hdc, hFont);
}

static void paint_end() {
    // Restore old font and delete new font
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    DeleteObject(hdc);
    
    // End painting
    EndPaint(hWnd, &ps);
}

class GenericObject {
public:
    int id{};
    
    RECT rect;

    void update() {
            InvalidateRect(hWnd, &rect, TRUE);
    }
    
    RECT below() { // returns a rect below the current one with the same width and height // NOLINT
        RECT r = rect;
        r.top += rect.bottom - rect.top + MARGIN;
        r.bottom += rect.bottom - rect.top + MARGIN;
        return r;
    }
    
    RECT right() { // returns a rect to the right of the current one with the same width and height // NOLINT
        RECT r = rect;
        r.left += rect.right - rect.left + MARGIN;
        r.right += rect.right - rect.left + MARGIN;
        return r;
    }
    
    RECT left() { // returns a rect to the left of the current one with the same width and height // NOLINT
        RECT r = rect;
        r.left -= rect.right - rect.left + MARGIN;
        r.right -= rect.right - rect.left + MARGIN;
        return r;
    }
    
    RECT above() { // returns a rect above the current one with the same width and height // NOLINT
        RECT r = rect;
        r.top -= rect.bottom - rect.top + MARGIN;
        r.bottom -= rect.bottom - rect.top + MARGIN;
        return r;
    }
    
    void move(RECT r) {
        rect = r;
    }
    
    void offset(RECT r) {
        rect.left += r.left;
        rect.right += r.right;
        rect.top += r.top;
        rect.bottom += r.bottom;
    }
    
    void offset(int top, int left, int bottom, int right) {
        rect.left += left;
        rect.right += right;
        rect.top += top;
        rect.bottom += bottom;
    }
    
};

class GenericWindow : public GenericObject {
public:
    HWND hwnd{};
    
    void updatenow() { // NOLINT
        RedrawWindow(hwnd, nullptr, nullptr, RDW_UPDATENOW);
    }
    
    void enable() {
        EnableWindow(hwnd, TRUE);
    }
    
    void disable() {
        EnableWindow(hwnd, FALSE);
    }
    
    
    ~ GenericWindow() {
        DestroyWindow(hwnd);
    }
};

// Refactor this into 3 classes: Button, TextBox, Label
class Button : public GenericWindow {
public:
    wchar_t* text;
    
    Button(RECT rect, wchar_t* window_type, wchar_t* text) {
    
        this->rect = rect;
        this->text = text;
        
        DWORD window_style_flags = WS_CHILD | WS_VISIBLE | WS_BORDER;
        
        hwnd = CreateWindowExW(
                0, L"BUTTON", text,
                window_style_flags,
                rect.left, rect.top, rect.left - rect.right, rect.top - rect.bottom,
                hWnd, (HMENU)id, hInstance, nullptr
        );
    }
    
    bool ispushed() {
        if (HIWORD(wParam) == 0 && (HWND)lParam == this->hwnd) {
            return true;
        }
    }
};

class Textbox : public GenericWindow {
public:
    Textbox(RECT rect, bool isNumeric = false) {
        
        this->rect = rect;

        DWORD window_style_flags = WS_CHILD | WS_VISIBLE | (isNumeric ? ES_NUMBER | WS_BORDER : WS_BORDER);
        
        hwnd = CreateWindowExW(
                0, L"TEXT", nullptr,
                window_style_flags,
                rect.left, rect.top, rect.left - rect.right, rect.top - rect.bottom,
                hWnd, (HMENU)id, hInstance, nullptr
        );
    }
};

class Label : public GenericObject {
public:
    
    wchar_t* text;
    
    DWORD flags{};
    
    Label(RECT rect, wchar_t* text, DWORD flags) {
        // Initialize variables
        this->rect = rect;
        this->text = text;
        this->flags = flags;
    }
    
    void draw() {
        DrawTextW(hdc, text, -1, &rect, flags);
    }
    
    void settext(wchar_t* text) {
        this->text = text;
        this->update();
    }
    
};
