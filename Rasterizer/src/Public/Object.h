//
// Created by Llikdowk on 26-Nov-16.
//

#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "FrameBuffer.h"
#include "Color.h"
#include "RenderMesh.h"
#include <vector>

class Object { // TODO: test
public:
	static const Object nullObject;
	Transform transform;

	virtual ~Object();
	void setParent(Object* parent);
	Matrix4 getMatrix() const;
	Matrix4 getInverseMatrix() const;

protected:
	const Object* parent = &nullObject;
	std::vector<Object*> children;
};


class Camera : public Object {
public:
	int width, height;
	Matrix4 projection;
	Camera(int width, int height, float d, FrameBuffer* fb);
	FrameBuffer& getFrameBuffer();

private:
	FrameBuffer* frameBuffer;
};


class ObjectRenderable : public Object {
public:
	ObjectRenderable(Camera&, const Mesh&);
	void draw() const;

private:
	Camera& camera;
	const Mesh& mesh;
	RenderMesh renderer;

	void drawPixel(float x, float y, Color color) const;
	void drawPixel(int x, int y, Color color) const;
	void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const;
	void drawLine(Vector2 v, Vector2 w, Color color) const;
};