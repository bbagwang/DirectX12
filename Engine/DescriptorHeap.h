#pragma once

// [��ȼ�]
// ���ָ� �ñ� �� �̷� ���� �������� ���� �Ѱ���� �ϴµ�,
// �ƹ� ���·γ� ��û�ϸ� �� �˾ƸԴ´�
// - ���� ���ҽ��� � �뵵�� ����ϴ��� �Ĳ��ϰ� ��� �Ѱ��ִ� �뵵
// DX12 ���������� View ��� �ҷ���
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
