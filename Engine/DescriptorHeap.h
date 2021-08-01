#pragma once

// [기안서]
// 외주를 맡길 때 이런 저런 정보들을 같이 넘겨줘야 하는데,
// 아무 형태로나 요청하면 못 알아먹는다
// - 각종 리소스를 어떤 용도로 사용하는지 꼼꼼하게 적어서 넘겨주는 용도
// DX12 이전까지는 View 라고 불렸음
// Descriptor (DX12) = View (~DX11)

class DescriptorHeap
{
public:
    void Init(ComPtr<ID3D12Device> Device, shared_ptr<class SwapChain> SwapChain);

    D3D12_CPU_DESCRIPTOR_HANDLE     GetRTV(int32 idx) { return _RtvHandle[idx]; }

    D3D12_CPU_DESCRIPTOR_HANDLE     GetBackBufferView();

private:
    ComPtr<ID3D12DescriptorHeap>    _RtvHeap;
    uint32                          _RtvHeapSize = 0;
    D3D12_CPU_DESCRIPTOR_HANDLE     _RtvHandle[SWAP_CHAIN_BUFFER_COUNT];

    shared_ptr<class SwapChain>     _SwapChain;
};
