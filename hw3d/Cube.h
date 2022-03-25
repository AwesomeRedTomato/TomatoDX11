#include "pch.h"
#include "Mesh.h"

class Cube
{
public:
	Cube() {}
	shared_ptr<Mesh> Init()
	{
		vertices[0] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f));
		vertices[1] = Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f));
		vertices[2] = Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f));
		vertices[3] = Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f));
		vertices[4] = Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f));
		vertices[5] = Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f));
		vertices[6] = Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f));
		vertices[7] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f));


		// ¾Õ¸é
		idx[0] = 0; idx[1] = 2; idx[2] = 1;
		idx[3] = 2; idx[4] = 3; idx[5] = 1;
		// µÞ¸é
		idx[6] = 1; idx[7] = 3; idx[8] = 5;
		idx[9] = 3; idx[10] = 7; idx[11] = 5;
		// À­¸é
		idx[12] = 2; idx[13] = 6; idx[14] = 3;
		idx[15] = 3; idx[16] = 6; idx[17] = 7;
		// ¾Æ·§¸é
		idx[18] = 4; idx[19] = 5; idx[20] = 7;
		idx[21] = 4; idx[22] = 7; idx[23] = 6;
		// ¿ÞÂÊ¸é
		idx[24] = 0; idx[25] = 4; idx[26] = 2;
		idx[27] = 2; idx[28] = 4; idx[29] = 6;
		// ¿À¸¥ÂÊ¸é
		idx[30] = 0; idx[31] = 1; idx[32] = 4;
		idx[33] = 1; idx[34] = 5; idx[35] = 4;

		shared_ptr<Mesh> mesh = make_unique<Mesh>();
		mesh->Init(vertices, idx);

		return mesh;
	}

public:
	vector<Vertex> vertices;
	vector<uint16_t> idx;
};