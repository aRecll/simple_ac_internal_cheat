
#include <iostream>

#include "menu.h"
#include "../offsets/constants.h"
#include "gl/GL.h"
#include "gl/GLU.h"
#include "../features/esp.h"
#include "../features/aimbot.h"
#include "settings.h"
#include "menutabs.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"

const ImVec2 initWindowSize = ImVec2(200, 200);
bool showMenu = false;
bool initialized = false;
bool contextCreated = false;
HWND gameWindow;
HGLRC myContext;
HGLRC gameContext;
HDC gHDC;
WNDPROC origonalWndProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK newWNDPROC(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (showMenu) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd,uMsg,wParam, lParam))
			return 0;
        switch (uMsg) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_INPUT :
            return 0;
        }
	}
    return (CallWindowProc(origonalWndProc, hWnd, uMsg, wParam, lParam));
}



void Menu::init(HDC hdc)
{
    ImGui::CreateContext();
    gameWindow= WindowFromDC(hdc);
   // gameWindow = FindWindowA(NULL, "AssaultCube");
    origonalWndProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)newWNDPROC);


    ImGui_ImplWin32_Init(gameWindow);
    ImGui_ImplOpenGL2_Init();
    ImGui::StyleColorsClassic();


    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    io.Fonts->AddFontDefault();


    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
    ImGui::SetNextWindowSize(initWindowSize);
    initialized = true;
#ifdef _DEBUG
   std::cout << "menu is init" << std::endl;
#endif
}
void setupContext(HDC &hdc) {
    myContext = wglCreateContext(hdc);
    wglMakeCurrent(hdc, myContext);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

   
    glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    contextCreated = true;
}
BOOL __stdcall newSwapBuffers(HDC hdc) {
    if (!initialized) {
        Menu::init(hdc);
        return originalSwapBuffers(hdc);
    }
  //  std::cout << "we in newSwapBuffers\n";
    
    gameContext = wglGetCurrentContext();

    if (!contextCreated) 
        setupContext(hdc);
    

   
    wglMakeCurrent(hdc, myContext);

    Menu::startRender();
    Menu::render();
    ESP::drawESP();
    aim::aimbot();
    Menu::endRender();

   
    wglMakeCurrent(hdc, gameContext);

    return originalSwapBuffers(hdc);
}


void Menu::startRender()
{
    ImGui_ImplOpenGL2_NewFrame();

    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Menu::endRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
void Menu::toggleMenu()
{   
    // if (!initialized) return;
    showMenu = !showMenu;
    ImGuiIO& io = ImGui::GetIO();
    if (showMenu) ClipCursor(NULL);
    originalSetRelativeMouseMode(!showMenu);
    io.WantCaptureMouse = showMenu;
    io.WantCaptureKeyboard = showMenu;
    io.MouseDrawCursor = showMenu;
#ifdef _DEBUG
    std::cout << "menu switch" << std::endl;
#endif
    /*if (showMenu) originalSetRelativeMouseMode(false);
    else originalSetRelativeMouseMode(true);*/

}

void Menu::render()
{
    if (!showMenu)
        return;
   // ClipCursor(NULL); 
    ImGui::Begin("Menu",&showMenu);
    if (ImGui::BeginTabBar("Tool")) {
        espTab();
        statsTab();
        aimbotTab();
        testTab();
        ImGui::EndTabBar();
    }
    ImGui::End();
}
BOOL WINAPI hClipCursor(const RECT* lpRect) {
    if (showMenu) return oClipCursor(NULL); 
    return oClipCursor(lpRect);
}

BOOL WINAPI hSetCursorPos(int X, int Y) {
    if (showMenu) {
        
        return TRUE;
    }
   
    return oSetCursorPos(X, Y);
}