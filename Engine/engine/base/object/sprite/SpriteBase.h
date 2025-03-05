#pragma once
#include <d3d12.h>
#pragma comment(lib,"d3d12.lib")
#include "wrl.h"

using Microsoft::WRL::ComPtr;

class DirectXEngine;

class SpriteBase
{
private:
	static SpriteBase* instance_;

	SpriteBase() = default;
	~SpriteBase() = default;
	SpriteBase(SpriteBase&) = delete;
	SpriteBase& operator=(SpriteBase&) = delete;

public:
	// シングルトンインスタンスの取得
	static SpriteBase* GetInstance();

	void Initialize(DirectXEngine* dxEngine);

	void DrawBase();

	void Finalize();


	// ゲッター
	DirectXEngine* GetDxEngine() const { return dxEngine_; }

private:

	DirectXEngine* dxEngine_ = nullptr;

	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
	// パイプラインステート
	ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;
};