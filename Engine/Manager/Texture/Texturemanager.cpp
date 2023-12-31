#include "Texturemanager.h"

void Texturemanager::Initialize()
{
	dirctXCommon_ = DirectXCommon::GetInstance();
	descriptorSizeDSV = dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	descriptorSizeRTV = dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSizeSRV = dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureIndex_ = 0;
}

Texturemanager* Texturemanager::GetInstance()
{
	static Texturemanager instance;
	return &instance;
}

uint32_t Texturemanager::Load(const std::string& filePath)
{
	textureIndex_++;
	LoadTexture(filePath,textureIndex_);
	return textureIndex_;
}


const D3D12_GPU_DESCRIPTOR_HANDLE Texturemanager::GetGPUHandle(uint32_t textureHandle)
{
	D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle =textureSrvHandleGPU_[textureHandle];
	return GPUHandle;
}





//テクスチャデータを読み込む
DirectX::ScratchImage Texturemanager::LoadTexture(const std::string& filePath)
{

	//テクスチャファイルを読んでうろグラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	//ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));
	return mipImages;
}
//テクスチャリソースを作る
Microsoft::WRL::ComPtr<ID3D12Resource> Texturemanager::CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
	//メタデータをもとにResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);//texturの幅
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);//mipmapの数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);//奥行or配列テクスチャの配列数
	resourceDesc.Format = metadata.format;//TextureのFormat
	resourceDesc.SampleDesc.Count = 1;//サンプリングカウント.1固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);//テクスチャの次元数
	//利用するheapの設定。非常に特殊な運用
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;//細かい設定を行う
	//heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//WriteBackポリシーでCPUアクセス可能
	//heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//プロセッサの近くに配置
	//Resourceの作成
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));
	return resource;
}


void Texturemanager::LoadTexture(const std::string& filePath, uint32_t index)
{

	DirectX::ScratchImage mipImage = LoadTexture(filePath);
	const DirectX::TexMetadata& metadata = mipImage.GetMetadata();
	textureResource[index] = CreateTextureResource(dirctXCommon_->GetDevice().Get(), metadata);
	UploadtextureData(textureResource[index].Get(), mipImage, index);
	//metaDataを元にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);

	//SRVを作成するDescripterHeapの場所を決める
	textureSrvHandleGPU_[index] = GettextureSrvHandleGPU(dirctXCommon_->GetSrvHeap().Get(), descriptorSizeSRV, index + 1);//direct_->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	textureSrvHandleCPU_[index] = GettextureSrvHandleCPU(dirctXCommon_->GetSrvHeap().Get(), descriptorSizeSRV, index + 1);
	//先頭はIMGUIが使ってるからその次を使う
	textureSrvHandleCPU_[index].ptr += dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	textureSrvHandleGPU_[index].ptr += dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	dirctXCommon_->GetDevice()->CreateShaderResourceView(textureResource[index].Get(), &srvDesc, textureSrvHandleCPU_[index]);

}

D3D12_CPU_DESCRIPTOR_HANDLE Texturemanager::GettextureSrvHandleCPU(ID3D12DescriptorHeap* descriptorheap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorheap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE Texturemanager::GettextureSrvHandleGPU(ID3D12DescriptorHeap* descriptorheap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorheap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}



[[nodiscard]]
Microsoft::WRL::ComPtr<ID3D12Resource> Texturemanager::UploadtextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, uint32_t index) {
	std::vector<D3D12_SUBRESOURCE_DATA>subresource;
	DirectX::PrepareUpload(dirctXCommon_->GetDevice().Get(), mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresource);
	uint64_t  intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresource.size()));
	intermediateResource[index] = dirctXCommon_->CreateBufferResource(dirctXCommon_->GetDevice().Get(), intermediateSize);
	UpdateSubresources(dirctXCommon_->GetCommandList().Get(), texture, intermediateResource[index].Get(), 0, 0, UINT(subresource.size()), subresource.data());

	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	dirctXCommon_->GetCommandList()->ResourceBarrier(1, &barrier);
	return intermediateResource[index];


}
