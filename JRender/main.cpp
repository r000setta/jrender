#include "render.h"
#include "transform.h"
int main() {
	jrender::Matrix4x4 mat = jrender::Matrix4x4();
	jrender::Transform trans = jrender::Transform(mat);
	std::cout << trans;
}