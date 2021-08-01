#pragma once

// [�ϰ� �����] ���� �ηµ��� �� �ؾ����� ���
class Shader
{
public:
    void Init(const wstring& path);
    void Update();

private:
    void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
    void CreateVertexShader(const wstring& path, const string& name, const string& version);
    void CreatePixelShader(const wstring& path, const string& name, const string& version);

private:
    ComPtr<ID3DBlob>        _VSBlob;
    ComPtr<ID3DBlob>        _PSBlob;
    ComPtr<ID3DBlob>        _ErrBlob;

    ComPtr<ID3D12PipelineState>         _PipelineState;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC  _PipelineDesc = {};
};