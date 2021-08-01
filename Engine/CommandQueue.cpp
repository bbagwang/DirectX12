#include "pch.h"
#include "CommandQueue.h"

#include "SwapChain.h"

CommandQueue::~CommandQueue()
{
    ::CloseHandle(_FenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> Device, shared_ptr<SwapChain> SwapChain)
{
    _SwapChain = SwapChain;

    D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
    QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&_CmdQueue));

    // - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU�� ���� �����ϴ� ��� ���
    Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_CmdAlloc));

    // GPU�� �ϳ��� �ý��ۿ����� 0����
    // DIRECT or BUNDLE
    // Allocator
    // �ʱ� ���� (�׸��� ����� nullptr ����)
    Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _CmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_CmdList));

    // CommandList�� Close / Open ���°� �ִµ�
    // Open ���¿��� Command�� �ִٰ� Close�� ���� �����ϴ� ����
    _CmdList->Close();

    // CreateFence
    // - CPU�� GPU�� ����ȭ �������� ���δ�
    Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_Fence));
    _FenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
    //fence ���� �������� ����� �� fence ������ ��ŷ�ϵ��� ��.
    _FenceValue++;

    // ��� ��⿭�� ����� �߰��Ͽ� �� �潺 ����Ʈ�� ����.
    // GPU Ÿ�Ӷ��ο� �ֱ� ������, GPU�� �Ϸ�� ������ �� �潺 ������ �������� �ʴ´�.
    // �� Signal() ������ ��� ����� ó����.
    _CmdQueue->Signal(_Fence.Get(), _FenceValue);

    //GPU�� �� �潺 �������� ����� �Ϸ��� ������ ��ٸ���.
    if (_Fence->GetCompletedValue() < _FenceValue)
    {
        //GPU�� ���� �潺�� �����ϸ� �̺�Ʈ�� �߻���Ų��.
        _Fence->SetEventOnCompletion(_FenceValue, _FenceEvent);

        //GPU�� ���� �潺 �̺�Ʈ�� ������ ������ ��ٸ�.
        ::WaitForSingleObject(_FenceEvent, INFINITE);
    }
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* Viewport, const D3D12_RECT* Rect)
{
    _CmdAlloc->Reset();
    _CmdList->Reset(_CmdAlloc.Get(), nullptr);

    D3D12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        _SwapChain->GetBackRTVBuffer().Get(),
        D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
        D3D12_RESOURCE_STATE_RENDER_TARGET); // ���� �����

    _CmdList->ResourceBarrier(1, &Barrier);

    // Set the viewport and scissor rect.  This needs to be reset whenever the command list is reset.
    _CmdList->RSSetViewports(1, Viewport);
    _CmdList->RSSetScissorRects(1, Rect);

    // Specify the buffers we are going to render to.
    D3D12_CPU_DESCRIPTOR_HANDLE BackBufferView = _SwapChain->GetBackRTV();
    _CmdList->ClearRenderTargetView(BackBufferView, Colors::LightSteelBlue, 0, nullptr);
    _CmdList->OMSetRenderTargets(1, &BackBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
    D3D12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        _SwapChain->GetBackRTVBuffer().Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET, // ���� �����
        D3D12_RESOURCE_STATE_PRESENT); // ȭ�� ���

    _CmdList->ResourceBarrier(1, &Barrier);
    _CmdList->Close();

    // Ŀ�ǵ� ����Ʈ ����
    ID3D12CommandList* CmdListArr[] = { _CmdList.Get() };
    _CmdQueue->ExecuteCommandLists(_countof(CmdListArr), CmdListArr);

    _SwapChain->Present();

    // Wait until frame commands are complete.  This waiting is inefficient and is
    // done for simplicity.  Later we will show how to organize our rendering code
    // so we do not have to wait per frame.
    WaitSync();

    _SwapChain->SwapIndex();
}
