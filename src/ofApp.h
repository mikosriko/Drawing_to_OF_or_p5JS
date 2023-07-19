#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "tools.h"
#include "convert.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Creates both of the classes
		tools tools;
		convert convert;

		// Properties GUI
		ofxPanel propertiesGui;
		ofParameter<bool> filled;
		ofParameter<float> width;
		ofParameter<ofColor> color;

		// GUI
		void toolsGui(ofImage lineImg, ofImage rectImg, ofImage elliImg, ofImage triaImg, ofImage polyImg);
		void convertGui();

		// All images
		ofImage lineImg;
		ofImage rectImg;
		ofImage elliImg;
		ofImage triaImg;
		ofImage polyImg;
		ofImage OFImg;
		ofImage P5Img;
};
