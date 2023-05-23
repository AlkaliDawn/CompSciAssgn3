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

#define CALC_TEXT_FLAGS DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE // Define text flags
#define OUTPUT_TEXT_FLAGS DT_LEFT | DT_TOP | DT_SINGLELINE // Define output text flags

int Default_Width = 53;

int MARGIN = 3;

WPARAM wParam = 0;
LPARAM lParam = 0;

HINSTANCE hInstance; // Window handle for the main window defined in WinMain
HWND hWnd; // Window handle for reference when processing in WndProc

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

/*  NULL WIDE CHARACTER STRING TO WIDE CHARACTER STRING  */
/* Convert an alphanumeric char buffer (string) where each character
 * is null terminated to a wide, null-terminated string. */
wchar_t* nwcstowcs(wchar_t* wstr, int length) {
    
    // Initialize empty string to hold characters temporarily
    auto* a = new wchar_t[length + 1];
    
    // iterate through given string "length" number of times
    for (int i = 0; i < length * 2; i++) {
        if (wstr[i] == '\000' && wstr[i-1] == '\000') break;
        
        if (wstr[i] != '\000' && !(wstr[i] > 57 || wstr[i] < 48)) { // if char is numeric && not null
            wcscat(a, &wstr[i]); // add character to temp string
        }
    }
    
    a += '\000'; // Make string null terminated
    return a;// return
}

wchar_t* itowcs(int i) {
    wchar_t* w = new wchar_t[10]; // NOLINT
    swprintf_s(w, 10, L"%d", i);
    return w;
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
    std::string id;
    
    RECT rect;
    
    virtual void update() {
            InvalidateRect(hWnd, &rect, TRUE);
    }
    
    RECT below(int height) { // returns a rect below the current one with the same width and height // NOLINT
        RECT r = rect;
        r.top = rect.bottom + MARGIN;
        r.bottom = r.top + height;
        return r;
    }
    
    RECT right(int width) { // returns a rect to the right of the current one with the same width and height // NOLINT
        RECT r = rect;
        r.left = rect.right + MARGIN;
        r.right = r.left + width;
        return r;
    }
    
    RECT left(int width) { // returns a rect to the left of the current one with the same width and height // NOLINT
        RECT r = rect;
        r.right = rect.left - MARGIN;
        r.left = r.right - width;
        return r;
    }
    
    RECT above(int height) { // returns a rect above the current one with the same width and height // NOLINT
        RECT r = rect;
        r.bottom = rect.top + MARGIN;
        r.top = rect.bottom - height;
        return r;
    }
    
    RECT below() { // returns a rect below the current one with the same width and height // NOLINT
        RECT r = rect;
        r.top = rect.bottom + MARGIN;
        r.bottom = rect.bottom;
        return r;
    }
    
    RECT right() { // returns a rect to the right of the current one with the same width and height // NOLINT
        RECT r = rect;
        int width = rect.right - rect.left;
        r.left = rect.right + MARGIN;
        r.right = r.left + width;
        return r;
    }
    
    RECT left() { // returns a rect to the left of the current one with the same width and height // NOLINT
        RECT r = rect;
        int width = rect.right - rect.left;
        r.right = rect.left - MARGIN;
        r.left = r.right - width;
        return r;
    }
    
    RECT above() { // returns a rect above the current one with the same width and height // NOLINT
        RECT r = rect;
        int height = rect.bottom - rect.top;
        r.bottom = rect.top + MARGIN;
        r.top = rect.bottom - height;
        return r;
    }
    
    void set_pos(RECT r) {
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
    
    ~ GenericObject() {
        delete[] this;
    }
};

class GenericWindow : public GenericObject {
public:
    HWND hwnd{};
    
    void updatenow() { // NOLINT
        this->update();
        RedrawWindow(this->hwnd, nullptr, nullptr, RDW_UPDATENOW);
    }
    
    void enable() {
        EnableWindow(this->hwnd, TRUE);
    }
    
    void disable() {
        EnableWindow(this->hwnd, FALSE);
    }
    
    void show() {
        ShowWindow(this->hwnd, SW_SHOW);
        this->update();
        this->enable();
        this->updatenow();
    }
    
    void hide() {
        ShowWindow(this->hwnd, SW_HIDE);
        this->update();
        this->disable();
        this->updatenow();
    }
    
//    ~ GenericWindow() {
//        DestroyWindow(hwnd);
//    }
};

// Refactor this into 3 classes: Button, TextBox, Label
class Button : public GenericWindow {
public:
    
    wchar_t* text;
    
    bool wasClicked{};
    
    Button(RECT rect, wchar_t* text, int rectright = Default_Width) {
    
        this->rect = rect;
        this->rect.right = rect.left + rectright;
        this->text = text;
    
        this->wasClicked = false;
        
        
        DWORD window_style_flags = WS_CHILD | WS_VISIBLE | WS_BORDER;
        
        hwnd = CreateWindowW(
                 TEXT("BUTTON"), text,
                window_style_flags,
                rect.left, rect.top, rect.right - rect.left, rect.bottom,
                hWnd, nullptr, hInstance, nullptr
        );
        
        
        
        this->updatenow();
        
    }
    
    bool ispushed() {
        std::cout << "methodwparam is " << HIWORD(wParam) << std::endl;
        std::cout << "methodlparam is " << (HWND)lParam << std::endl;
        if (HIWORD(wParam) == 0 && (HWND)lParam == hwnd) {
            return true;
        }
        else return false;
    }
    
};

class Textbox : public GenericWindow {
public:
    
    DWORD window_style_flags;
    
    Textbox(RECT rect, bool isNumeric = false, int rectright = Default_Width) {
        this->rect = rect;
        this->rect.right = rect.left + rectright;
    
        
        if (isNumeric)
            window_style_flags = WS_CHILD | WS_VISIBLE | WS_BORDER;
        else
            window_style_flags = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER;
        
        hwnd = CreateWindowW(
                 TEXT("EDIT"), nullptr,
                 window_style_flags,
                rect.left, rect.top, rect.right - rect.left, rect.bottom,
                hWnd, nullptr, hInstance, nullptr
        );
        
        std::cout << "HWND of textbox is " << hwnd << std::endl;

        this->updatenow();
        
    }
    
    wchar_t* getwstring() {
        GetWindowTextLengthW(hwnd);
        auto* buffer = new wchar_t[100];
        GetWindowTextW(hwnd, buffer, 100);
        return buffer;
    }
    
    int getint() {
        GetWindowTextLengthW(hwnd);
        auto* buffer = new wchar_t[100];
        GetWindowTextW(hwnd, buffer, 100);
        //convert to int
        return _wtoi(nwcstowcs(buffer, 100));
    }
    
    int getdouble() {
        GetWindowTextLengthW(hwnd);
        auto* buffer = new wchar_t[100];
        GetWindowTextW(hwnd, buffer, 100);
        //convert to double
        return std::wcstod(nwcstowcs(buffer, 100), nullptr);
    }
    
};

class Label : public GenericObject {
public:
    
    wchar_t* text;
    
    DWORD flags;
    
    Label(RECT rect, wchar_t* text, DWORD flags) {
        // Initialize variables
        this->rect = rect;
        this->text = text;
        this->flags = flags;
        this->update();

    }
    
    void draw() {
        DrawTextW(hdc, text, -1, &rect, flags);
    }
    
    void update() override {
        DrawTextW(hdc, this->text, -1, &this->rect, CALC_TEXT_FLAGS);
        InvalidateRect(hWnd, &rect, TRUE);
        DrawTextW(hdc, text, -1, &rect, flags);
    }
    
    void settext(wchar_t* newtext) {
        this->text = newtext;
        DrawTextW(hdc, this->text, -1, &rect, CALC_TEXT_FLAGS);
        this->update();
    }
    
};