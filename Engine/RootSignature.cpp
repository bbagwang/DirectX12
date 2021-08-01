#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> Device)
{
	D3D12_ROOT_SIGNATURE_DESC SigDesc = CD3DX12_ROOT_SIGNATURE_DESC(D3D12_DEFAULT);
	SigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> BlobSignature;
	ComPtr<ID3DBlob> BlobError;
	::D3D12SerializeRootSignature(&SigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &BlobSignature, &BlobError);
	Device->CreateRootSignature(0, BlobSignature->GetBufferPointer(), BlobSignature->GetBufferSize(), IID_PPV_ARGS(&_Signature));

}
