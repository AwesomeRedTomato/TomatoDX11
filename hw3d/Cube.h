#include "pch.h"
#include "Mesh.h"

class Cube
{
public:
	std::shared_ptr<Mesh> Init()
	{
		vertices.resize(24);
		indices.resize(36);

		float w2 = 1.5f;
		float h2 = 1.5f;
		float d2 = 1.5f;

		vertices[0] = Vertex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT2(0.0f, 1.0f));
		vertices[1] = Vertex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT2(0.0f, 0.0f));
		vertices[2] = Vertex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT2(1.0f, 0.0f));
		vertices[3] = Vertex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT2(1.0f, 1.0f));
		//µÞ¸é								
		vertices[4] = Vertex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT2(1.0f, 1.0f));
		vertices[5] = Vertex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT2(0.0f, 1.0f));
		vertices[6] = Vertex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT2(0.0f, 0.0f));
		vertices[7] = Vertex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT2(1.0f, 0.0f));
		//À­¸é								
		vertices[8] = Vertex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT2(0.0f, 1.0f));
		vertices[9] = Vertex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT2(0.0f, 0.0f));
		vertices[10] = Vertex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT2(1.0f, 0.0f));
		vertices[11] = Vertex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT2(1.0f, 1.0f));
		//¾Æ·§¸é														  )
		vertices[12] = Vertex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT2(1.0f, 1.0f));
		vertices[13] = Vertex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT2(0.0f, 1.0f));
		vertices[14] = Vertex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT2(0.0f, 0.0f));
		vertices[15] = Vertex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT2(1.0f, 0.0f));
		//¿ÞÂÊ¸é														   )
		vertices[16] = Vertex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT2(0.0f, 1.0f));
		vertices[17] = Vertex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT2(0.0f, 0.0f));
		vertices[18] = Vertex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT2(1.0f, 0.0f));
		vertices[19] = Vertex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT2(1.0f, 1.0f));
		//¿À¸¥ÂÊ¸é														  )
		vertices[20] = Vertex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT2(0.0f, 1.0f));
		vertices[21] = Vertex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT2(0.0f, 0.0f));
		vertices[22] = Vertex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT2(1.0f, 0.0f));
		vertices[23] = Vertex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT2(1.0f, 1.0f));

		// ¾Õ¸é
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 0; indices[4] = 2; indices[5] = 3;
		// µÞ¸é
		indices[6] = 4; indices[7] = 5; indices[8] = 6;
		indices[9] = 4; indices[10] = 6; indices[11] = 7;
		// À­¸é
		indices[12] = 8; indices[13] = 9; indices[14] = 10;
		indices[15] = 8; indices[16] = 10; indices[17] = 11;
		// ¾Æ·§¸é
		indices[18] = 12; indices[19] = 13; indices[20] = 14;
		indices[21] = 12; indices[22] = 14; indices[23] = 15;
		// ¿ÞÂÊ¸é
		indices[24] = 16; indices[25] = 17; indices[26] = 18;
		indices[27] = 16; indices[28] = 18; indices[29] = 19;
		// ¿À¸¥ÂÊ¸é
		indices[30] = 20; indices[31] = 21; indices[32] = 22;
		indices[33] = 20; indices[34] = 22; indices[35] = 23;


		std::shared_ptr<Mesh> mesh = std::make_unique<Mesh>();
		mesh->Init(vertices, indices);

		return mesh;
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};