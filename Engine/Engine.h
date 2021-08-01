#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"

class Engine
{
public:
    void Init(const WindowInfo& InWindowInfo);
    void Render();

public:
    void RenderBegin();
    void RenderEnd();

    void ResizeWindow(int32 Width, int32 Height);

public:
    shared_ptr<Device> GetDevice() { return _Device; }
    shared_ptr<CommandQueue> GetCmdQueue() { return _CmdQueue; }
    shared_ptr<SwapChain> GetSwapChain() { return _SwapChain; }
    shared_ptr<RootSignature> GetRootSignature() { return _RootSignature; }

private:
    WindowInfo _Window;
    D3D12_VIEWPORT _Viewport = {};
    D3D12_RECT _ScissorRect = {};

    shared_ptr<Device> _Device;
    shared_ptr<CommandQueue> _CmdQueue;
    shared_ptr<SwapChain> _SwapChain;
    shared_ptr<RootSignature> _RootSignature;
};

