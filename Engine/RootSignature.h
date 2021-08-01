#pragma once


class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> Device);

public:
	ComPtr<ID3D12RootSignature>	GetSignature() { return _Signature; }

private:
    ComPtr<ID3D12RootSignature> _Signature;
};
