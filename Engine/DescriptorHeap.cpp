#include "pch.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"


void DescriptorHeap::Init(ComPtr<ID3D12Device> Device, shared_ptr<SwapChain> SwapChain)
{
    _SwapChain = SwapChain;

    // [서술자 힙]으로 RTV 생성
    // DX11의 RTV(RenderTargetView), DSV(DepthStencilView), 
    // CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)를 전부!

    _RtvHeapSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_DESCRIPTOR_HEAP_DESC RtvDesc;
    RtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    RtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
    RtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    RtvDesc.NodeMask = 0;

    // 같은 종류의 데이터끼리 배열로 관리
    // RTV 목록 : [ ] [ ]
    Device->CreateDescriptorHeap(&RtvDesc, IID_PPV_ARGS(&_RtvHeap));

    D3D12_CPU_DESCRIPTOR_HANDLE RtvHeapBegin = _RtvHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
    {
        _RtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(RtvHeapBegin, i * _RtvHeapSize);
        Device->CreateRenderTargetView(SwapChain->GetRenderTarget(i).Get(), nullptr, _RtvHandle[i]);
    }
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetBackBufferView()
{
    return GetRTV(_SwapChain->GetCurrentBackBufferIndex());
}
