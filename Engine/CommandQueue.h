#pragma once

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
    ~CommandQueue();

    void Init(ComPtr<ID3D12Device> Device, shared_ptr<SwapChain> SwapChain, shared_ptr<DescriptorHeap> DescHeap);
    void WaitSync();

    void RenderBegin(const D3D12_VIEWPORT* Viewport, const D3D12_RECT* Rect);
    void RenderEnd();

    ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _CmdQueue; }

private:
    // CommandQueue : DX12�� ����
    // ���ָ� ��û�� ��, �ϳ��� ��û�ϸ� ��ȿ����
    // [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
    ComPtr<ID3D12CommandQueue>          _CmdQueue;
    ComPtr<ID3D12CommandAllocator>      _CmdAlloc;
    ComPtr<ID3D12GraphicsCommandList>   _CmdList;

    // Fence : CPU / GPU ����ȭ�� ���� ������ ����
    ComPtr<ID3D12Fence>         _Fence;
    uint32                      _FenceValue = 0;
    HANDLE                      _FenceEvent = INVALID_HANDLE_VALUE;

    shared_ptr<SwapChain>       _SwapChain;
    shared_ptr<DescriptorHeap>  _DescHeap;

};

