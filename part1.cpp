#include "win32helper.h"

// Define the primary window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Declare the entry point function
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) // **************** WINMAIN **************** //
{
    // Seed srand
    std::random_device rd;
    srand(rd());
    for (int i = 0; i < rand(); i++) {
        rand();
    }
    
    // Initialize global variables
    hInstance = hInst;
    
    // Define the window class
    WNDCLASSEXW wcex;
    
    // Initialize window class variables
    ZeroMemory(&wcex, sizeof(WNDCLASSEXW)); // Zero the memory of the window class
    wcex.cbSize = sizeof(WNDCLASSEXW); // Set the size of the window class
    wcex.style = CS_HREDRAW | CS_VREDRAW; // Set the style of the window class
    wcex.lpfnWndProc = WndProc; // Set the window procedure
    wcex.hInstance = hInstance; // Set the instance handle
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Set the cursor
    wcex.hbrBackground = green; // Set the background color
    wcex.lpszClassName = L"MyWindowClass"; // Set the class name
    RegisterClassEx(&wcex); // Register the window class
    
    // Create the window
    hWnd = CreateWindowEx(
            0, // Optional window styles
            L"MyWindowClass", // Window class
            L"Dice Roller v3.3", // Window caption
            WS_OVERLAPPEDWINDOW, // Window style
            
            CW_USEDEFAULT, CW_USEDEFAULT, 740, 480, // Size and position
            
            nullptr, // Parent window
            nullptr, // Menu
            hInstance, // Instance handle
            nullptr // Additional application data
    );
    
    // If CreateWindow fails, return error code
    if (!hWnd)
        return -1;
    
    // Show and update the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    // Enter the message loop
    MSG msg; // Message struct
    while (GetMessage(&msg, nullptr, 0, 0)) // Get messages from the queue
    {
        TranslateMessage(&msg); // Translate virtual-key messages into character messages
        DispatchMessage(&msg); // Dispatch message to the window procedure
    }
    
    // Clean up and exit
    return (int)msg.wParam;
    
} // **************** WINMAIN **************** //

// Define the window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // **************** WNDPROC **************** //
{
    switch (message)
    {
        //////////////////// DESTROY ////////////////////
        case WM_DESTROY:
        {
            PostQuitMessage(0); // Post a quit message to the message queue
            break;
        }
            //////////////////// DESTROY ////////////////////
            
            
            //////////////////// CREATE ////////////////////
        case WM_CREATE:
        {
            paint_init();
            
            Label label = Label();
            
            paint_end();
            break;
        }
            //////////////////// CREATE ////////////////////
            
            
            //////////////////// PAINT ////////////////////
        case WM_PAINT:
        {
            // Get device context (screen area)
            paint_init();
            
            // Draw background
            FillRect(hdc, &ps.rcPaint, green);
            
            
            
            paint_end();
            break;
        }
            //////////////////// PAINT ////////////////////
            
            
            //////////////////// COMMAND ////////////////////
        case WM_COMMAND:
        {
        
        
        }
            //////////////////// COMMAND ////////////////////
        
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam); // Ignore any unhandled messages
        }
        
    }
    
    return 0; // Return 0 after processing normal Windows messages
    
} // **************** WNDPROC **************** //