#pragma once


class Mesh
{
public:
    void Init(vector<Vertex>& Vec);
    void Render();

private:
    ComPtr<ID3D12Resource>      _VertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW    _VertexBufferView = {};
    uint32 _VertexCount = 0;
};
