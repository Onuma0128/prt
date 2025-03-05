#pragma once
#include <d3d12.h>
#pragma comment(lib,"d3d12.lib")
#include "wrl.h"

using Microsoft::WRL::ComPtr;

class DirectXEngine;

class PrimitiveDrawer
{
private:
	static PrimitiveDrawer* instance_;

	PrimitiveDrawer() = default;
	~PrimitiveDrawer() = default;
	PrimitiveDrawer(PrimitiveDrawer&) = delete;
	PrimitiveDrawer& operator=(PrimitiveDrawer&) = delete;

public:
	// シングルトンインスタンスの取得
	static PrimitiveDrawer* GetInstance();

	void Initialize(DirectXEngine* dxEngine);

	void DrawBase();

	void Finalize();

	/*==================== アクセッサ ====================*/

	DirectXEngine* GetDxEngine() const { return dxEngine_; }

private:

	DirectXEngine* dxEngine_ = nullptr;

	ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
	ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;
};