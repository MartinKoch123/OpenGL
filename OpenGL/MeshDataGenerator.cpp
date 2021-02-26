#include "MeshDataGenerator.h"


namespace MeshDataGenerator {

	
	std::vector<Vertex> square() {
		std::vector<Vertex> data;
		addQuad(&data, glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.0f));
		return data;
	}

	std::vector<Vertex> cylinder(float height, unsigned int numberEdges) {
		std::vector<Vertex> data;
		
		if (height <= 0 || numberEdges <= 2)
			return data;
		float angle = 2 * PI / (float)numberEdges;
		glm::vec3 centerTop;
		glm::vec3 centerBot;
		glm::vec3 outBot;
		glm::vec3 outTop;
		glm::vec3 outBot2;
		glm::vec3 outTop2;

		for (unsigned int i = 0; i < numberEdges; i++) {
			centerTop = glm::vec3(0.0f, height / 2.0f, 0.0f);
			centerBot = glm::vec3(0.0f, -height / 2.0f, 0.0f);
			outBot = glm::vec3(cos(angle*(float)i), -height / 2.0f, sin(angle*(float)i));
			outTop = glm::vec3(cos(angle*(float)i), height / 2.0f, sin(angle*(float)i));
			outBot2 = glm::vec3(cos(angle*(float)(i + 1)), -height / 2.0f, sin(angle*(float)(i + 1)));
			outTop2 = glm::vec3(cos(angle*(float)(i + 1)), height / 2.0f, sin(angle*(float)(i + 1)));

			addTriangle(&data, outBot, outBot2, centerBot);
			addTriangle(&data, outTop, centerTop, outTop2);
			addQuad(&data, outBot, outTop, outTop2, outBot2);
		}
		return data;
	}

	std::vector<Vertex> sphere(unsigned int numberEdges) {
		std::vector<Vertex> data;
		std::vector<Vertex> newPartTop;
		std::vector<Vertex> newPartBot;

		if (numberEdges <= 2)
			return data;
		float angle = 0.5f * PI / (float)numberEdges;

		for (unsigned int i = 0; i < numberEdges; i++) {
			newPartTop = spherePart(numberEdges, angle*(float)i, angle*((float)i + 1));
			newPartBot = spherePart(numberEdges, angle*(float)i, angle*((float)i + 1));
			rotate(&newPartBot, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			if (i % 2) {
				rotate(&newPartTop, PI / (float)numberEdges, glm::vec3(0.0f, 1.0f, 0.0f));
				rotate(&newPartBot, PI / (float)numberEdges, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			attach(&data, &newPartTop);
			attach(&data, &newPartBot);
		}
		return data;

	}

	std::vector<Vertex> spherePart(unsigned int n, float innerAngle, float outerAngle) {
		std::vector<Vertex> data;

		if (n <= 2)
			return data;
		float angle = 2 * PI / (float)n;

		glm::vec3 inner;
		glm::vec3 inner2;
		glm::vec3 outer;
		glm::vec3 outer2;
		for (unsigned int i = 0; i < n; i++) {

			inner = glm::vec3(sin(innerAngle)*cos(angle*(float)i), cos(innerAngle), sin(innerAngle)*sin(angle*(float)i));
			inner2 = glm::vec3(sin(innerAngle)*cos(angle*(float)(i + 1)), cos(innerAngle), sin(innerAngle)*sin(angle*(float)(i + 1)));
			outer = glm::vec3(sin(outerAngle)*cos(angle*((float)i + 0.5f)), cos(outerAngle), sin(outerAngle)*sin(angle*((float)i + 0.5f)));
			outer2 = glm::vec3(sin(outerAngle)*cos(angle*((float)i + 1.5f)), cos(outerAngle), sin(outerAngle)*sin(angle*((float)i + 1.5f)));

			if (innerAngle != 0.0f) {
				addTriangle(&data, inner, inner2, outer);
			}
			addTriangle(&data, inner2, outer2, outer);
		}
		
		return data;
	}

	std::vector<Vertex> pyramid(unsigned int n) {
		std::vector<Vertex> data;
		if (n <= 2)
			return data;
		float angle = 2.0f * PI / n;
		glm::vec3 centerBot = glm::vec3(0.0f);
		glm::vec3 outBot;
		glm::vec3 outBot2;
		glm::vec3 tip = glm::vec3(0.0f, 1.0f, 0.0f);

		float rotationAlpha = PI / 2.0f - atan(1.0f / cos(angle / 2));
		for (unsigned int i = 0; i < n; i++) {

			outBot = glm::vec3(cos(angle*(float)i), 0.0f, sin(angle*(float)i));
			outBot2 = glm::vec3(cos(angle*(float)(i + 1)), 0.0f, sin(angle*(float)(i + 1)));

			addTriangle(&data, outBot, outBot2, centerBot);
			addTriangle(&data, outBot, tip, outBot2);
		}
		return data;
	}

	std::vector<Vertex> cube() {
		std::vector<Vertex> data;
		glm::vec3 frontRightBot = glm::vec3(-0.5f, -0.5f, 0.5f);
		glm::vec3 frontLeftBot = glm::vec3(-0.5f, -0.5f, -0.5f);
		glm::vec3 frontRightTop = glm::vec3(-0.5f, 0.5f, 0.5f);
		glm::vec3 frontLeftTop = glm::vec3(-0.5f, 0.5f, -0.5f);
		glm::vec3 backRightBot = glm::vec3(0.5f, -0.5f, 0.5f);
		glm::vec3 backLeftBot = glm::vec3(0.5f, -0.5f, -0.5f);
		glm::vec3 backRightTop = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 backLeftTop = glm::vec3(0.5f, 0.5f, -0.5f);

		addQuad(&data, frontRightBot, frontRightTop, frontLeftTop, frontLeftBot);
		addQuad(&data, backRightBot, backLeftBot, backLeftTop, backRightTop);
		addQuad(&data, frontRightTop, backRightTop, backLeftTop, frontLeftTop);
		addQuad(&data, backRightBot, frontRightBot, frontLeftBot, backLeftBot);
		addQuad(&data, frontRightTop, frontRightBot, backRightBot, backRightTop);
		addQuad(&data, frontLeftTop, backLeftTop, backLeftBot, frontLeftBot);

		return data;
	}

	std::vector<TextureVertex> textureSquare() {
		std::vector<Vertex> vertexData = square();
		std::vector<TextureVertex> texVertexData;
		
		for (unsigned int i = 0; i < vertexData.size(); i++) {
			texVertexData.push_back(TextureVertex(vertexData[i].position, vertexData[i].normal, glm::vec2(1.0f)));
		}

		texVertexData[0].textureCoordinates = glm::vec2(0.0f, 0.0f);
		texVertexData[1].textureCoordinates = glm::vec2(1.0f, 0.0f);
		texVertexData[2].textureCoordinates = glm::vec2(1.0f, 1.0f);
		texVertexData[3].textureCoordinates = glm::vec2(1.0f, 1.0f);
		texVertexData[4].textureCoordinates = glm::vec2(0.0f, 1.0f);
		texVertexData[5].textureCoordinates = glm::vec2(0.0f, 0.0f);
		return texVertexData;
	}

	std::vector<TextureVertex> textureCube() {
		std::vector<Vertex> vertexData = cube();
		std::vector<TextureVertex> texVertexData;
		if (vertexData.size() != 36)
			return texVertexData;

		for (unsigned int i = 0; i < vertexData.size(); i++) {
			texVertexData.push_back(TextureVertex(vertexData[i].position, vertexData[i].normal, glm::vec2(1.0f)));
		}

		for (unsigned int i = 0; i < 6; i++) {
			texVertexData[i * 6 + 0].textureCoordinates = glm::vec2(0.0f, 0.0f);
			texVertexData[i * 6 + 1].textureCoordinates = glm::vec2(1.0f, 0.0f);
			texVertexData[i * 6 + 2].textureCoordinates = glm::vec2(1.0f, 1.0f);
			texVertexData[i * 6 + 3].textureCoordinates = glm::vec2(1.0f, 1.0f);
			texVertexData[i * 6 + 4].textureCoordinates = glm::vec2(0.0f, 1.0f);
			texVertexData[i * 6 + 5].textureCoordinates = glm::vec2(0.0f, 0.0f);

		}
		return texVertexData;
	}

	std::vector<MaterialVertex> toMaterialVertex(std::vector<Vertex> data, Material material) {
		std::vector<MaterialVertex> newData;
		for (unsigned int i = 0; i < data.size(); i++) {
			newData.push_back(MaterialVertex(data[i].position, data[i].normal, material));
		}
		return newData;
	}

	void addTriangle(std::vector<Vertex>* data, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3) {
		glm::vec3 normal = normalOfTriangle(point1, point2, point3);
		data->push_back(Vertex(point1, normal));
		data->push_back(Vertex(point2, normal));
		data->push_back(Vertex(point3, normal));
	}

	void addQuad(std::vector<Vertex>* data, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4) {
		addTriangle(data, point1, point2, point3);
		addTriangle(data, point3, point4, point1);
	}

	void rotate(std::vector<Vertex>* data, float angle, glm::vec3 axis) {
		for (unsigned int i = 0; i < data->size(); i++) {
			data->at(i).position = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, axis) * glm::vec4(data->at(i).position, 1.0f));
			data->at(i).normal = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, axis) * glm::vec4(data->at(i).normal, 1.0f));
		}
	}

	void attach(std::vector<Vertex>* base, std::vector<Vertex>* add) {
		base->insert(base->begin(), add->begin(), add->end());
	}


	void quadrangleToTriangles(std::vector<Vertex>* data) {
		if (data == NULL || data->size() != 4) {
			data->clear();
			return;
		}
		data->insert(data->begin() + 3, data->at(0));
		data->insert(data->begin() + 3, data->at(2));
	}
};
