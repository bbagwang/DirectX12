#pragma once

// ��ȯ �罽
// [���� ����]
// - ���� ���� ���� �ִ� ��Ȳ�� ����
// - � �������� ��� ������� ������
// - GPU�� ������ ��� (����)
// - ����� �޾Ƽ� ȭ�鿡 �׷��ش�

// [���� �����]�� ��� ����?
// - � ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź�غ���
// - Ư�� ���̸� ���� -> ó���� �ǳ��ְ� -> ������� �ش� ���̿� �޴´� OK
// - �츮 ȭ�鿡 Ư�� ����(���� �����) ������ش�

// [?]
// - �׷��� ȭ�鿡 ���� ����� ����ϴ� ���߿�, ���� ȭ�鵵 ���ָ� �ðܾ� ��
// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����
// - Ư�� ���̸� 2�� ����, �ϳ��� ���� ȭ���� �׷��ְ�, �ϳ��� ���� �ñ��...
// - Double Buffering!

// - [0] [1]
// ���� ȭ�� [1]  <-> GPU �۾��� [1] BackBuffer

class SwapChain
{
public:
    void Init(const WindowInfo& Info, ComPtr<ID3D12Device> Device, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue);
    void Present();
    void SwapIndex();

    ComPtr<IDXGISwapChain> GetSwapChain() { return _SwapChain; }
    ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _RtvBuffer[index]; }

    ComPtr<ID3D12Resource> GetBackRTVBuffer() { return _RtvBuffer[_BackBufferIndex]; }

    D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() {return _RtvHandle[_BackBufferIndex]; }

private:
    void CreateSwapChain(const WindowInfo& Info, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue);
    void CreateRTV(ComPtr<ID3D12Device> Device);

private:
    ComPtr<IDXGISwapChain>          _SwapChain;

    ComPtr<ID3D12Resource>          _RtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
    ComPtr<ID3D12DescriptorHeap>    _RtvHeap;
    D3D12_CPU_DESCRIPTOR_HANDLE     _RtvHandle[SWAP_CHAIN_BUFFER_COUNT];

    uint32      _BackBufferIndex = 0;
};
