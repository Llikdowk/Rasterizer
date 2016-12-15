//
// Created by Llikdowk on 26-Nov-16.
//

#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "FrameBuffer.h"
#include "Color.h"
#include "MeshRenderer.h"
#include <vector>
#include <memory>

class Object { // TODO: test
public:
	Transform transform;

	virtual ~Object();
	void setParent(Object* parent);
	Matrix4 getMatrix() const;
	Matrix4 getInverseMatrix() const;

protected:
	Object* parent = nullptr;
	std::vector<Object*> children;
};


class Camera : public Object {
public:
	int width, height;
	Matrix4 projection;

	virtual ~Camera() {
	}

	Camera(int width, int height, float d, FrameBuffer* fb);
	FrameBuffer& getFrameBuffer();

private:
	FrameBuffer* frameBuffer;
};


class ObjectRenderable : public Object {

public:
	ObjectRenderable(Camera&, const Mesh&);
	ObjectRenderable(const ObjectRenderable&) = delete;
	ObjectRenderable operator=(const ObjectRenderable&) = delete;
	void draw() const;

	Color color = Color::Cyan;

private:
	Camera& camera;
	const Mesh& mesh;
	std::unique_ptr<MeshRenderer> renderer;
};
