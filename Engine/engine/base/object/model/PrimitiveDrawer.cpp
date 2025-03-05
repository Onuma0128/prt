#include "PrimitiveDrawer.h"

#include "DirectXEngine.h"
#include "PipelineState.h"
#include "Camera.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

PrimitiveDrawer* PrimitiveDrawer::instance_ = nullptr;

PrimitiveDrawer* PrimitiveDrawer::GetInstance()
{
	if (instance_ == nullptr) {
		instance_ = new PrimitiveDrawer;
	}
	return instance_;
}

void PrimitiveDrawer::Initialize(DirectXEngine* dxEngine)
{
	dxEngine_ = dxEngine;

	rootSignature_ = dxEngine_->GetPipelineState()->CreateLine3dRootSignature();
	pipelineState_ = dxEngine_->GetPipelineState()->CreateLine3dPipelineState();
}

void PrimitiveDrawer::DrawBase()
{
	auto commandList = dxEngine_->GetCommandList();
	commandList->SetGraphicsRootSignature(rootSignature_.Get());
	commandList->SetPipelineState(pipelineState_.Get());
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}

void PrimitiveDrawer::Finalize()
{
	delete instance_;
	instance_ = nullptr;
}

