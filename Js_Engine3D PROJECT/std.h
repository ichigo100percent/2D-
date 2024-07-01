#pragma once

// STL
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm> 
#include <assert.h>
#include <tchar.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <bitset>

// DX
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include "SimpleMath.h"
#include "DirectXTex.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#pragma comment( lib, "DirectXTex.lib")
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment( lib, "DirectXTK_D.lib")
#else
#pragma comment( lib, "DirectXTK_R.lib")
#endif

using namespace DirectX;
using namespace Microsoft::WRL;

#include "Entity.h"
#include "value.h"
#include "type.h"
#include "struct.h"
#include "macro.h"
