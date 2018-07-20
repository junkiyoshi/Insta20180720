#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius_span = 50;
	int deg_span = 10;

	this->cam.begin();

	for (int radius = radius_span; radius < 360; radius += radius_span) {

		for (int deg = 0; deg < 360; deg += deg_span) {

			ofPoint noise_point((radius + radius_span * 0.5) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius + radius_span * 0.5) * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
			float noise_value = ofNoise(noise_point.x * 0.005, noise_point.y * 0.005, ofGetFrameNum() * 0.005);
			int z = noise_value * radius;

			ofColor body_color(ofMap(noise_value, 0, 1, 39, 255));
			ofSetColor(body_color);

			ofPoint p1(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z);
			ofPoint p2(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD), z);
			ofPoint p3((radius + radius_span) * cos((deg + deg_span) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span) * DEG_TO_RAD), z);
			ofPoint p4((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD), z);
		
			ofBeginShape();
			ofVertex(p1);
			ofVertex(p2);
			ofVertex(p3);
			ofVertex(p4);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(p1);
			ofVertex(p2);
			ofVertex(p2 - ofPoint(0, 0, z));
			ofVertex(p1 - ofPoint(0, 0, z));
			ofEndShape(true);

			ofBeginShape();
			ofVertex(p2);
			ofVertex(p3);
			ofVertex(p3 - ofPoint(0, 0, z));
			ofVertex(p2 - ofPoint(0, 0, z));
			ofEndShape(true);

			ofBeginShape();
			ofVertex(p3);
			ofVertex(p4);
			ofVertex(p4 - ofPoint(0, 0, z));
			ofVertex(p3 - ofPoint(0, 0, z));
			ofEndShape(true);

			ofBeginShape();
			ofVertex(p1);
			ofVertex(p4);
			ofVertex(p4 - ofPoint(0, 0, z));
			ofVertex(p1 - ofPoint(0, 0, z));
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}