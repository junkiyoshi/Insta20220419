#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();
	ofSetLineWidth(3);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float span = 10;
	float threshold = 0.45;
	float noise_param = 0.01;

	for (float x = -200; x <= 200; x += span) {

		for (float y = -200; y <= 200; y += span) {

			for (float z = -200; z <= 0; z += span) {

				auto noise_value = ofNoise(x * noise_param, y * noise_param, z * noise_param * 0.05 + ofGetFrameNum() * 0.01);

				if (noise_value < threshold) { continue; }

				auto noise_value_1 = ofNoise((x - span) * noise_param, y * noise_param, z * noise_param * 0.05 + ofGetFrameNum() * 0.01);
				auto noise_value_2 = ofNoise(x * noise_param, (y + span) * noise_param, z * noise_param * 0.05 + ofGetFrameNum() * 0.01);
				auto noise_value_3 = ofNoise((x + span) * noise_param, y * noise_param, z * noise_param * 0.05 + ofGetFrameNum() * 0.01);
				auto noise_value_4 = ofNoise(x * noise_param, (y - span) * noise_param, z * noise_param * 0.05 + ofGetFrameNum() * 0.01);


				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(x - span * 0.5, y - span * 0.5, z));
				vertices.push_back(glm::vec3(x - span * 0.5, y + span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y + span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y - span * 0.5, z));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				if (noise_value_1 < threshold || x == -200) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_2 < threshold || y == 200) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_3 < threshold || x == 200) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_4 < threshold || y == -200) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(255);
	this->face.draw();

	ofSetColor(0);
	this->line.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}