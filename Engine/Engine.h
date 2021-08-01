#pragma once


class Engine
{
public:
    void Init(const WindowInfo& InWindowInfo);
    void Render();

public:
    void RenderBegin();
    void RenderEnd();

    void ResizeWindow(int32 Width, int32 Height);

private:
    WindowInfo _Window;
    D3D12_VIEWPORT _Viewport = {};
    D3D12_RECT _ScissorRect = {};

    shared_ptr<class Device> _Device;
    shared_ptr<class CommandQueue> _CmdQueue;
    shared_ptr<class SwapChain> _SwapChain;
    shared_ptr<class DescriptorHeap> _DescHeap;
};

