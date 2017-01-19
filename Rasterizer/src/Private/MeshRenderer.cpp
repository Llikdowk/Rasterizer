//
// Created by Llikdowk on 27-Nov-16.
//

#include <Color.h>
#include <cmath>
#include "MeshRenderer.h"
//#include "Profiler.h"
using namespace lmath;

void NaiveRenderer::drawPixel(float x, float y, Color color) const {
	//assert(x >= 0.0f && x <= 1.0f);
	//assert(y >= 0.0f && y <= 1.0f);
	static float ratio =
			frameBuffer.width / static_cast<float>(frameBuffer.height); // TODO reset when resolution is changed
	static float border = (ratio - 1) / 2.0f;

	if (x >= -border && x <= ratio - border && y >= 0.0f &&
		y <= 1.0f) { // fixme! not working when vertical > horizontal
		drawPixel(static_cast<int>((border + x) * (frameBuffer.height - 1)),
				  static_cast<int>(y * (frameBuffer.height - 1)), color);
	}
}

void NaiveRenderer::drawPixel(int x, int y, Color color) const {
	frameBuffer.setPixel(x, y, Color::encode(color));
}

void NaiveRenderer::drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const {
	//PROFILE_SCOPED()
	float xStep = std::abs((xB - xA) / frameBuffer.width);
	float yStep = std::abs((yB - yA) / frameBuffer.height);
	float step = std::max(xStep, yStep);
	step *= 1.0 / std::sqrt((xB - xA) * (xB - xA) + (yB - yA) * (yB - yA));

	for (float t = 0.0f; t <= 1.0f; t += step) {
		Color c = utils::lerp(colorA, colorB, t);
		float x = utils::lerp(xA, xB, t);
		float y = utils::lerp(yA, yB, t);
		drawPixel(x, y, c);
	}
}

void NaiveRenderer::drawLine(Vector2 v, Vector2 w, Color color) const {
	drawLine(v.x, v.y, w.x, w.y, color, color);
}
