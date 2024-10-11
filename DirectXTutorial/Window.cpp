#include "Window.h"

#include "EngineTime.h"
// Window* window = nullptr;



Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_CREATE:
    {
        Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        
        window->setHWND(hwnd);
        window->onCreate();
        break;
    }

    case WM_DESTROY:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }

    case WM_SETFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onFocus();
        break;
    }

    case WM_KILLFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onKillFocus();
        break;
    }

    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
}

bool Window::init()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hInstance = NULL;

    /*ADDED L to resolve LPCWSTR error*/
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;

    // Window proecedure events
    wc.lpfnWndProc = &WndProc;

    // Class registration
    if (!::RegisterClassEx(&wc))
        return false;

    //if (!window)
    //    window = this;


    // Window creation
    /*m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        NULL, NULL, NULL, NULL);*/
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        NULL, NULL, NULL, this);



    if (!m_hwnd)
        return false;

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    
    m_is_run = true;
    return true;
}




bool Window::broadcast()
{
    MSG msg;
    EngineTime::tick();

    // Update only occurs when the time matches the expecred ms per frame
    if (EngineTime::getDeltaTime() >= timePerFrame) {
        this->onUpdate();

        while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        std::cout << "d: " << EngineTime::getDeltaTime() << "\tTotal " << EngineTime::getTotalTime() << std::endl;

        // Updates the lastFrame to now        
        EngineTime::LogFrameStart();
        // Refreshes the deltaTime
        EngineTime::ResetDeltaTime();
    }
    Sleep(1);
    //EngineTime::LogFrameEnd();

    return true;
}

bool Window::release() {
    std::cout << "\nReleased window";
    if (!::DestroyWindow(m_hwnd))
        return false;
    
    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

Window::~Window()
{
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::setHWND(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

void Window::onCreate()
{
    EngineTime::initialize();

    CalcWindowRect();
}

void Window::onUpdate()
{
    CalcWindowRect();
}

void Window::onDestroy()
{
    std::cout << "\nDestroyed window";
    m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

void Window::CalcWindowRect()
{
    m_windowWidth = (this->getClientWindowRect().right - this->getClientWindowRect().left);
    m_windowHeight = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
}