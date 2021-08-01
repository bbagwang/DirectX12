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

    // - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU가 직접 실행하는 명령 목록
    Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_CmdAlloc));

    // GPU가 하나인 시스템에서는 0으로
    // DIRECT or BUNDLE
    // Allocator
    // 초기 상태 (그리기 명령은 nullptr 지정)
    Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _CmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_CmdList));

    // CommandList는 Close / Open 상태가 있는데
    // Open 상태에서 Command를 넣다가 Close한 다음 제출하는 개념
    _CmdList->Close();

    // CreateFence
    // - CPU와 GPU의 동기화 수단으로 쓰인다
    Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_Fence));
    _FenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
    //fence 값을 증가시켜 명령을 이 fence 지점을 마킹하도록 함.
    _FenceValue++;

    // 명령 대기열에 명령을 추가하여 새 펜스 포인트를 설정.
    // GPU 타임라인에 있기 때문에, GPU가 완료될 때까지 새 펜스 지점이 설정되지 않는다.
    // 이 Signal() 이전에 모든 명령을 처리함.
    _CmdQueue->Signal(_Fence.Get(), _FenceValue);

    //GPU가 이 펜스 지점까지 명령을 완료할 때까지 기다린다.
    if (_Fence->GetCompletedValue() < _FenceValue)
    {
        //GPU가 현재 펜스에 도달하면 이벤트를 발생시킨다.
        _Fence->SetEventOnCompletion(_FenceValue, _FenceEvent);

        //GPU가 현재 펜스 이벤트에 도달할 때까지 기다림.
        ::WaitForSingleObject(_FenceEvent, INFINITE);
    }
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* Viewport, const D3D12_RECT* Rect)
{
    _CmdAlloc->Reset();
    _CmdList->Reset(_CmdAlloc.Get(), nullptr);

    D3D12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        _SwapChain->GetBackRTVBuffer().Get(),
        D3D12_RESOURCE_STATE_PRESENT, // 화면 출력
        D3D12_RESOURCE_STATE_RENDER_TARGET); // 외주 결과물

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
        D3D12_RESOURCE_STATE_RENDER_TARGET, // 외주 결과물
        D3D12_RESOURCE_STATE_PRESENT); // 화면 출력

    _CmdList->ResourceBarrier(1, &Barrier);
    _CmdList->Close();

    // 커맨드 리스트 수행
    ID3D12CommandList* CmdListArr[] = { _CmdList.Get() };
    _CmdQueue->ExecuteCommandLists(_countof(CmdListArr), CmdListArr);

    _SwapChain->Present();

    // Wait until frame commands are complete.  This waiting is inefficient and is
    // done for simplicity.  Later we will show how to organize our rendering code
    // so we do not have to wait per frame.
    WaitSync();

    _SwapChain->SwapIndex();
}
