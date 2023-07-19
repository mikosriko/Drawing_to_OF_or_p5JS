#pragma once

#include "ofMain.h"

using namespace glm;

class tools
{
	public:
		// Allows the array below to have multiple types
		struct data
		{
			string tool;
			bool equipped;
			int state;
		};

		// Keeps track of every tool and used for comparison
		data shapeTools[6][3] =
		{
			{"line",		true,	1},
			{"rect",		false,	1},
			{"ellipse",		false,	1},
			{"triangle",	false,	1},
			{"polygon",		false,	1}
		};

		// Updates every property from the GUI if it's outdated
		void update
		(
			bool,
			float,
			ofColor
		);

		// Draws every shape created by user
		void draw();

		// Draws what the shape would look like in real-time if the user would create it
		void ghost
		(
			string,						// Shape
			vec2						// Mouse positions
		);

		// Used for tool equipment or creation (polygon)
		void keyPressed
		(
			int							// Key pressed
		);

		// Used for drawing
		void mousePressed
		(
			int,						// X position of mouse
			int,						// Y position of mouse
			int							// Mouse button pressed
		);

		// Saves shape of drawing
		vector<vector<string>> saveShape
		(
			vector<vector<string>>,		// Shapes
			string						// Current shape
		);

		// Saves positions of drawing
		vector<vector<vec2>> savePos
		(
			vector<vector<vec2>>,		// Positions
			vector<vec2>				// Temporary positions
		);

		// Saves fill property of drawing
		vector<vector<bool>> saveFill
		(
			vector<vector<bool>>,		// Fills
			bool						// Current fill
		);

		// Saves width property of drawing
		vector<vector<float>> saveWidth
		(
			vector<vector<float>>,		// Widths
			float						// Current width
		);

		// Saves colour property of drawing
		vector<vector<ofColor>> saveColor
		(
			vector<vector<ofColor>>,	// Colors
			ofColor						// Current color
		);

		// Temporarily extracted to be used for conversion to code //
		vector<vector<string>> extractShapes();
		vector<vector<vec2>> extractPositions();
		vector<vector<bool>> extractFills();
		vector<vector<float>> extractWidths();
		vector<vector<ofColor>> extractColors();


	private:
		// Stores all properties of shapes and are scanned in the same index for all vectors
		vector<vector<string>> shapes;
		vector<vector<vec2>> positions;
		vector<vector<bool>> fills;
		vector<vector<float>> widths;
		vector<vector<ofColor>> colors;

		// Temporary positions used when user hasn't fully created the shape yet but partially
		vec2 tempPos1 = { 0,0 };
		vector<vec2> tempPos;

		// Keeps track of the current property settings (below values are default)
		bool currentFill = false;
		float currentWidth = 5;
		ofColor currentColor = { 255,255,255,255 };

		vector <string> convertedCode;
};