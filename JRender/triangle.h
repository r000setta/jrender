#pragma once
#ifndef JRENDER_SHAPES_TRIANGLE_H
#define JRENDER_SHAPES_TRIANGLE_H

#include "shape.h"
#include <map>

namespace jrender {
	struct TriangleMesh {
		TriangleMesh(const Transform& ObjectToWorld, int nTriangles,
			const int* vertexIndices, int nVertices, const Point3f* P,
			const Vector3f* S, const Normal3f* N, const Point2f* uv,
			//const std::shared_ptr<Texture<Float>>& alphaMask,
			//const std::shared_ptr<Texture<Float>>& shadowAlphaMask,
			const int* faceIndices);

		const int nTriangles, nVertices;
		std::vector<int> vertexIndices;
		std::unique_ptr<Point3f[]> p;
		std::unique_ptr<Normal3f[]> n;
		std::unique_ptr<Vector3f[]> s;
		std::unique_ptr<Point2f[]> uv;
		std::vector<int> faceIndices;
	};

	class Triangle :public Shape {
	public:
		Bounds3f ObjectBound() const;
		Bounds3f WorldBound() const;
		Float Area() const;
	private:
		void GetUVs(Point2f uv[3]) const {
			if (mesh->uv) {
				uv[0] = mesh->uv[v[0]];
				uv[1] = mesh->uv[v[1]];
				uv[2] = mesh->uv[v[2]];
			}
			else {
				uv[0] = Point2f(0, 0);
				uv[1] = Point2f(1, 0);
				uv[2] = Point2f(1, 1);
			}
		}

		std::shared_ptr<TriangleMesh> mesh;
		const int* v;
		int faceIndex;
	};
}

#endif // !JRENDER_SHAPES_TRIANGLE_H
