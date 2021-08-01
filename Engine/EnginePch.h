#pragma once

// Include
#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

// DirectX
#include "d3dx12.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

// Library
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// Definition
#define SWAP_CHAIN_BUFFER_COUNT 2

// Engine Macro
#define DEVICE              GEngine->GetDevice()->GetDevice()
#define CMD_LIST            GEngine->GetCmdQueue()->GetCmdList()
#define ROOT_SIGNATURE      GEngine->GetRootSignature()->GetSignature()

// Type Definition
using int8      = __int8;
using int16     = __int16;
using int32     = __int32;
using int64     = __int64;
using uint8     = unsigned __int8;
using uint16    = unsigned __int16;
using uint32    = unsigned __int32;
using uint64    = unsigned __int64;
using Vec2      = XMFLOAT2;
using Vec3      = XMFLOAT3;
using Vec4      = XMFLOAT4;
using Matrix    = XMMATRIX;

// Struct
struct WindowInfo
{
    HWND    Hwnd;       //출력 윈도우 핸들
    int32   Width;      //가로
    int32   Height;     //세로
    bool    bWindowed;   //창모드인가
};

struct Vertex
{
    Vec3 Pos;
    Vec4 Color;
};

// Extern
extern unique_ptr<class Engine> GEngine;
