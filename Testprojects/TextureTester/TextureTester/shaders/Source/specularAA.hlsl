#include "texandtexflags.h"

Texture2D<float4> normalMap : register(t0);

RWTexture2DArray<float4> outputLEANMap : register(u0);

float3 FetchNormal(uint2 u2SamplePos)
{
	float3 f3Normal = normalize((normalMap[u2SamplePos].xyz * 2.f - 1.f)/10.f);

	return f3Normal;
}

[numthreads(TGSIZE, TGSIZE, 1)]
void GenerateLEANMap(uint3 u3GroupID : SV_GroupID, uint3 u3DispatchThreadID : SV_DispatchThreadID, 
					 uint3 u3GroupThreadID : SV_GroupThreadID, uint uGroupIndex : SV_GroupIndex)
{
	uint2 u2SamplePos = u3GroupID.xy * uint2(TGSIZE, TGSIZE) + u3GroupThreadID.xy;

	float3 f3N = FetchNormal(u2SamplePos);
	float2 f2B = f3N.xy / (pow(10, fA) * f3N.z);
	float3 f3M = float3(f2B.x * f2B.x, f2B.y * f2B.y, f2B.x * f2B.y);
	float fCleanM = f2B.x * f2B.x + f2B.y * f2B.y;

	outputLEANMap[uint3(u2SamplePos, 0)] = float4(f2B, 0.f, 1.f);
	outputLEANMap[uint3(u2SamplePos, 1)] = float4(f3M, fCleanM);
}