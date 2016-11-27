#include "Canvas.h"
#include <iostream>

Canvas::Canvas(int width, int height)
	: 
	width(width), 
	height(height),
	framebuffer(FrameBuffer(width, height))
{
	init();
}

void Canvas::init() {
	framebuffer.clear(Color::encode(Color::Black));
}

void Canvas::draw(s_t deltaTime) {
	static s_t elapsedTime = deltaTime;
	elapsedTime += deltaTime;

	framebuffer.clear(Color::encode(Color::Black));

	Camera camera(width, height, .5f, &framebuffer); // TODO: transform into object
	camera.transform.translate(0, 0, -2);
	//camera.transform.rotate_y(elapsedTime);

	float s = sinf(elapsedTime);
	ObjectRenderable cube(camera, Mesh::cube);
	cube.transform.translate(s, 0, 0);
	ObjectRenderable cube2(camera, Mesh::cube);
	cube2.setParent(&cube);
	cube2.transform.scale(.25f,.25f,.25f);
	cube2.transform.rotate_y(3.141519f/4.0f + s);

	std::vector<ObjectRenderable> objects;
	objects.push_back(cube);
	objects.push_back(cube2);
	for (auto object_it = objects.begin(); object_it != objects.end(); ++object_it) {
		(*object_it).draw();
	}
}


const FrameBuffer& Canvas::getFrameBuffer() const {
	return framebuffer;
}