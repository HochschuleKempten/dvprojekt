#pragma once

#include <d3d11.h>
// #include "d3dx11.h"
// #include <d3dx10.h>

namespace Vektoria
{
// TODO: Umwandlung in Smart Allocating

class BufferMap
{
protected:
	static const int BUFFER_INCREASE = 10000;
	int m_iTop;
	int m_iCount;
	ID3D11Buffer **m_ppBuffers;
public:
	BufferMap();
	int AddBuffer(ID3D11Buffer *pbuffer);
	ID3D11Buffer *SubBuffer(int i);
	ID3D11Buffer *GetBuffer(int i);
	void OverwriteBuffer(int i, ID3D11Buffer * pbuffer);
};

}