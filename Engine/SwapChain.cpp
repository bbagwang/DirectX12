#include "pch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& Info, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue)
{
    // ������ ���� ���� ������
    _SwapChain.Reset();

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = static_cast<uint32>(Info.Width); // ������ �ػ� �ʺ�
    sd.BufferDesc.Height = static_cast<uint32>(Info.Height); // ������ �ػ� ����
    sd.BufferDesc.RefreshRate.Numerator = 60; // ȭ�� ���� ����
    sd.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ������ ���÷��� ����
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1; // ��Ƽ ���ø� OFF
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �ĸ� ���ۿ� �������� �� 
    sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT; // ����+�ĸ� ����
    sd.OutputWindow = Info.Hwnd;
    sd.Windowed = Info.bWindowed;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ���� �ĸ� ���� ��ü �� ���� ������ ���� ����
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    Dxgi->CreateSwapChain(CmdQueue.Get(), &sd, &_SwapChain);

    for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
    {
        _SwapChain->GetBuffer(i, IID_PPV_ARGS(&_RenderTargets[i]));
    }
}

void SwapChain::Present()
{
    // Present The Frame
    _SwapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
    _BackBufferIndex = (_BackBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}