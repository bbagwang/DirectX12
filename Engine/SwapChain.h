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
    void Init(const WindowInfo& Info, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue);
    void Present();
    void SwapIndex();

    ComPtr<IDXGISwapChain> GetSwapChain() { return _SwapChain; }
    ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _RenderTargets[index]; }

    uint32 GetCurrentBackBufferIndex() { return _BackBufferIndex; }
    ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return _RenderTargets[_BackBufferIndex]; }

private:
    ComPtr<IDXGISwapChain>  _SwapChain;
    ComPtr<ID3D12Resource>  _RenderTargets[SWAP_CHAIN_BUFFER_COUNT];
    uint32                  _BackBufferIndex = 0;
};
