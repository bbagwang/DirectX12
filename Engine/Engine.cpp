#include "pch.h"
#include "Engine.h"


void Engine::Init(const WindowInfo& InWindowInfo)
{
    _Window = InWindowInfo;
    ResizeWindow(_Window.Width, _Window.Height);

    //그려질 화면 크기를 설정
    _Viewport = { 0,0,static_cast<FLOAT>(_Window.Width),static_cast<FLOAT>(_Window.Height),0.f,1.f };
    _ScissorRect = CD3DX12_RECT(0, 0, _Window.Width, _Window.Height);

    _Device = make_shared<Device>();
    _CmdQueue = make_shared<CommandQueue>();
    _SwapChain = make_shared<SwapChain>();
    _RootSignature = make_shared<RootSignature>();

    _Device->Init();
    _CmdQueue->Init(_Device->GetDevice(), _SwapChain);
    _SwapChain->Init(_Window, _Device->GetDevice(), _Device->GetDXGI(), _CmdQueue->GetCmdQueue());
    _RootSignature->Init(_Device->GetDevice());
}

void Engine::Render()
{
    RenderBegin();

    // TODO : 나머지 물체들을 그려준다.

    RenderEnd();

}

void Engine::RenderBegin()
{
    _CmdQueue->RenderBegin(&_Viewport,&_ScissorRect);
}

void Engine::RenderEnd()
{
    _CmdQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 Width, int32 Height)
{
    _Window.Width = Width;
    _Window.Height = Height;

    RECT Rect = { 0,0,_Window.Width,_Window.Height };
    ::AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
    ::SetWindowPos(_Window.Hwnd, 0, 100, 100, _Window.Width, _Window.Height, 0);
}
