#pragma once

#include "ofMain.h"

using namespace glm;

class convert {
	public:
		vector <string> toOpenFrameworks
		(
			vector<vector<string>>,		// Shapes
			vector<vector<vec2>>,		// Positions
			vector<vector<bool>>,		// Fills
			vector<vector<float>>,		// Widths
			vector<vector<ofColor>>		// Colors
		);
		vector <string> toP5JS
		(
			vector<vector<string>>,		// Shapes
			vector<vector<vec2>>,		// Positions
			vector<vector<bool>>,		// Fills
			vector<vector<float>>,		// Widths
			vector<vector<ofColor>>		// Colors
		);
		void clearCode();

	private:
		vector <string> convertedCode;
};

