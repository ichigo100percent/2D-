#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <algorithm>
using namespace std;


struct Vector2
{
	float x, y;
	Vector2() = default;
	Vector2(float _x, float _y) : x(_x), y(_y) {}
};
struct Vector3
{
	float x, y, z;
	Vector3() = default;
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct VertexData
{
	Vector3 color;
	Vector3 pos;

	VertexData() = default;
	VertexData(Vector3 _pos, Vector3 _col) : pos(_pos), color(_col) {}
};

Vector3 convert(const Vector3& _pos)
{
	Vector3 ret;
	// 0 ~ 800 -> 0 ~ 1
	ret.x = _pos.x / 800;
	ret.y = _pos.y / 600;
	// NDC 좌표계
	// 0 ~ 1 -> -1 ~ 1
	ret.x = ret.x * 2.0f - 1.0f;
	ret.y = (ret.y * 2.0f - 1.0f);
	ret.z = _pos.z;

	return ret;
}

int main()
{
	RECT rect
	{
		100,100, 200,200
	};

	vector<VertexData> vertices(6);
	vector<VertexData> ndc_vertices(6);
	vertices[0].pos = { (float)rect.left, (float)rect.top, 0 };
	vertices[1].pos = { (float)rect.right, (float)rect.top, 0 };
	vertices[2].pos = { (float)rect.right, (float)rect.bottom, 0 };

	vertices[3].pos = { (float)rect.right, (float)rect.bottom, 0 };
	vertices[4].pos = { (float)rect.left, (float)rect.bottom, 0 };
	vertices[5].pos = { (float)rect.left, (float)rect.top, 0 };

	//ndc_vertices[2] = convert(vertices[2]);

	transform(begin(vertices), end(vertices), begin(ndc_vertices),
		[](const VertexData& _pos)
		{
			return VertexData(convert(_pos.pos), _pos.color);
		});

	for (auto& n : ndc_vertices)
	{
		cout << n.pos.x << " " << n.pos.y << endl;
	}


	return 0;
}