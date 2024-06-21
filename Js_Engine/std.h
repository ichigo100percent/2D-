#pragma once

// STL
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm> 
#include <assert.h>
#include <tchar.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <atlconv.h>


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

#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};

#include "Entity.h"
#include "value.h"
#include "type.h"
#include "struct.h"
#include "macro.h"





