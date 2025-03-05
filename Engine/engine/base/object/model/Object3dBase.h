#pragma once
#include <d3d12.h>
#pragma comment(lib,"d3d12.lib")
#include "wrl.h"

using Microsoft::WRL::ComPtr;

class DirectXEngine;

class Object3dBase
{
private:
	static Object3dBase* instance_;

	Object3dBase() = default;
	~Object3dBase() = default;
	Object3dBase(Object3dBase&) = delete;
	Object3dBase& operator=(Object3dBase&) = delete;

public:
	// シングルトンインスタンスの取得
	static Object3dBase* GetInstance();

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