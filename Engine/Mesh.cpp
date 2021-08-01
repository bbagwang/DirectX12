#include "pch.h"
#include "Mesh.h"
#include "Engine.h"


void Mesh::Init(vector<Vertex>& Vec)
{
    _VertexCount = static_cast<uint32>(Vec.size());
    uint32 BufferSize = _VertexCount * sizeof(Vertex);

    D3D12_HEAP_PROPERTIES HeapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(BufferSize);

    DEVICE->CreateCommittedResource(
        &HeapProperty,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&_VertexBuffer));

    // Copy the triangle data to the vertex buffer.
    void* VertexDataBuffer = nullptr;
    CD3DX12_RANGE ReadRange(0, 0); // We do not intend to read from this resource on the CPU.
    _VertexBuffer->Map(0, &ReadRange, &VertexDataBuffer);
    ::memcpy(VertexDataBuffer, &Vec[0], BufferSize);
    _VertexBuffer->Unmap(0, nullptr);

    // Initialize the vertex buffer view.
    _VertexBufferView.BufferLocation = _VertexBuffer->GetGPUVirtualAddress();
    _VertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
    _VertexBufferView.SizeInBytes = BufferSize; // 버퍼의 크기	
}

void Mesh::Render()
{
    CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CMD_LIST->IASetVertexBuffers(0, 1, &_VertexBufferView); // Slot: (0~15)
    CMD_LIST->DrawInstanced(_VertexCount, 1, 0, 0);
}
