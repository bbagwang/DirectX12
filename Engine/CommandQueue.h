#pragma once

class SwapChain;

class CommandQueue
{
public:
    ~CommandQueue();

    void Init(ComPtr<ID3D12Device> Device, shared_ptr<SwapChain> SwapChain);
    void WaitSync();

    void RenderBegin(const D3D12_VIEWPORT* Viewport, const D3D12_RECT* Rect);
    void RenderEnd();

    ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _CmdQueue; }
    ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _CmdList; }

private:
    // CommandQueue : DX12에 등장
    // 외주를 요청할 때, 하나씩 요청하면 비효율적
    // [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
    ComPtr<ID3D12CommandQueue>          _CmdQueue;
    ComPtr<ID3D12CommandAllocator>      _CmdAlloc;
    ComPtr<ID3D12GraphicsCommandList>   _CmdList;

    // Fence : CPU / GPU 동기화를 위한 간단한 도구
    ComPtr<ID3D12Fence>         _Fence;
    uint32                      _FenceValue = 0;
    HANDLE                      _FenceEvent = INVALID_HANDLE_VALUE;

    shared_ptr<SwapChain>       _SwapChain;
};

