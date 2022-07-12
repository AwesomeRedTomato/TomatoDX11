#pragma once
#include "pch.h"
#include "Mesh.h"

class Sphere
{
public:
	// tangent Ãß°¡ ¿¹Á¤
	std::shared_ptr<Mesh> Init()
	{
		float radius = 0.5f;
		UINT stackCount = 20;
		UINT sliceCount = 20;

		Vertex v;

		v.pos = FLOAT3(0.0f, radius, 0.0f);
		v.uv = FLOAT2(0.5f, 0.0f);
		v.normal = v.pos;
		v.normal.Normalize();
		vertices.push_back(v);

		float stackAngle = XM_PI / stackCount;
		float sliceAngle = XM_2PI / sliceCount;

		float deltaU = 1.0f / static_cast<float>(sliceCount);
		float deltaV = 1.0f / static_cast<float>(stackCount);

		for (UINT y = 1; y <= stackCount - 1; ++y)
		{
			float phi = y * stackAngle;
			
			for (UINT x = 0; x <= sliceCount; ++x)
			{
				float theta = x * sliceAngle;

				v.pos.x = radius * sinf(phi) * cosf(theta);
				v.pos.y = radius * cosf(phi);
				v.pos.z = radius * sinf(phi) * sinf(theta);

				v.uv = FLOAT2(deltaU * x, deltaV * y);

				v.normal = v.pos;
				v.normal.Normalize();

				vertices.push_back(v);
			}
		}

		v.pos = FLOAT3(0.0f, -radius, 0.0f);
		v.uv = FLOAT2(0.5f, 1.0f);
		v.normal = v.pos;
		v.normal.Normalize();
		vertices.push_back(v);

		// ºÏ±Ø ÀÎµ¦½º
		for (UINT i = 0; i <= sliceCount; ++i)
		{
			//  [0]
			//   |  \
			//  [i+1]-[i+2]
			indices.push_back(0);
			indices.push_back(i + 2);
			indices.push_back(i + 1);
		}

		// ¸öÅë ÀÎµ¦½º
		UINT ringVertexCount = sliceCount + 1;
		for (UINT y = 0; y < stackCount - 2; ++y)
		{
			for (UINT x = 0; x < sliceCount; ++x)
			{
				//  [y, x]-[y, x+1]
				//  |		/
				//  [y+1, x]
				indices.push_back(1 + (y)*ringVertexCount + (x));
				indices.push_back(1 + (y)*ringVertexCount + (x + 1));
				indices.push_back(1 + (y + 1) * ringVertexCount + (x));
				//		 [y, x+1]
				//		 /	  |
				//  [y+1, x]-[y+1, x+1]
				indices.push_back(1 + (y + 1) * ringVertexCount + (x));
				indices.push_back(1 + (y)*ringVertexCount + (x + 1));
				indices.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
			}
		}

		// ³²±Ø ÀÎµ¦½º
		UINT bottomIndex = static_cast<UINT>(vertices.size()) - 1;
		UINT lastRingStartIndex = bottomIndex - ringVertexCount;
		for (UINT i = 0; i < sliceCount; ++i)
		{
			//  [last+i]-[last+i+1]
			//  |      /
			//  [bottom]
			indices.push_back(bottomIndex);
			indices.push_back(lastRingStartIndex + i);
			indices.push_back(lastRingStartIndex + i + 1);
		}
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};