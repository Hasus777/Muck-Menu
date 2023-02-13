#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_internal.h"
#include "IMGUI/imgui_impl_dx9.h"
#include "IMGUI/imgui_impl_win32.h"
#include "externvar.h"
#include "ImFile.h"

HWND Window = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

#define LOADER_NAME "Cheat Loader"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { 
        g_pd3dDevice->Release(); g_pd3dDevice = NULL; 
    }
    if (g_pD3D) {
        g_pD3D->Release(); g_pD3D = NULL; 
    }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT Result = g_pd3dDevice->Reset(&g_d3dpp);
    if (Result == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}