#pragma once


class Device
{
public:
    void Init();

    ComPtr<IDXGIFactory> GetDXGI() { return _Dxgi; }
    ComPtr<ID3D12Device> GetDevice() { return _Device; }

private:
    // COM(Component Object Model)
    // - DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
    // - COM ��ü(COM �������̽�)�� ���. ���λ����� �츮���� ������
    // - ComPtr ������ ����Ʈ ������

    ComPtr<ID3D12Debug> _DebugController;
    ComPtr<IDXGIFactory> _Dxgi;     //ȭ�� ���� ��ɵ�
    ComPtr<ID3D12Device> _Device;   //���� ��ü ����
};

