#include "pch.h"
#include "SwapChain.h"
#include "Engine.h"


void SwapChain::Init(const WindowInfo& Info, ComPtr<ID3D12Device> Device, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue)
{

    CreateSwapChain(Info, Dxgi, CmdQueue);
    CreateRTV(Device);
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

void SwapChain::CreateSwapChain(const WindowInfo& Info, ComPtr<IDXGIFactory> Dxgi, ComPtr<ID3D12CommandQueue> CmdQueue)
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
        _SwapChain->GetBuffer(i, IID_PPV_ARGS(&_RtvBuffer[i]));
    }
}

void SwapChain::CreateRTV(ComPtr<ID3D12Device> Device)
{
    // [������ ��]���� RTV ����
    // DX11�� RTV(RenderTargetView), DSV(DepthStencilView), 
    // CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)�� ����!

    int32 RtvHeapSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_DESCRIPTOR_HEAP_DESC RtvDesc;
    RtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    RtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
    RtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    RtvDesc.NodeMask = 0;

    // ���� ������ �����ͳ��� �迭�� ����
    // RTV ��� : [ ] [ ]
    Device->CreateDescriptorHeap(&RtvDesc, IID_PPV_ARGS(&_RtvHeap));

    D3D12_CPU_DESCRIPTOR_HANDLE RtvHeapBegin = _RtvHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
    {
        _RtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(RtvHeapBegin, i * RtvHeapSize);
        Device->CreateRenderTargetView(_RtvBuffer[i].Get(), nullptr, _RtvHandle[i]);
    }
}
