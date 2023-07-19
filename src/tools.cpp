#include "tools.h"

using namespace glm;

void tools::update(bool filled, float width, ofColor color)
{
	// Updates fill if outdated
	if (currentFill != filled)
	{
		currentFill = filled;
	}

	// Updates width property if outdated
	if (currentWidth != width)
	{
		currentWidth = width;
	}

	// Updates colour property if outdated
	if (currentColor != color)
	{
		currentColor = color;
	}
}

// Draws all shapes created by user
void tools::draw()
{
	for (int i = 0; i < positions.size(); i++)
	{
		vector<vec2>temp; // Vector with needed positions to be drawn

		// Grabs needed positions when necessary (polygon draws straight from the vector)
		if (shapes[i][0] != "polygon")
		{
			for (int j = 0; j < positions[i].size(); j++)
			{
				temp.push_back(positions[i][j]);
			}
		}

		// Draws differently based on its shape
		if (shapes[i][0] == "line")
		{
			ofPushMatrix();
			ofSetLineWidth(widths[i][0]);
			ofSetColor(colors[i][0]);
			ofDrawLine(temp[0], temp[1]);
			ofPopMatrix();
		}
		else if (shapes[i][0] == "rect")
		{
			ofPushMatrix();

			if (fills[i][0])
			{
				ofFill();
			}
			else
			{
				ofNoFill();
			}

			ofSetLineWidth(widths[i][0]);
			ofSetColor(colors[i][0]);

			// Works out the width and height based on starting and ending corners of the rectangle
			float tempWidth = temp[1][0] - temp[0][0];
			float tempHeight = temp[1][1] - temp[0][1];

			ofDrawRectangle(temp[0], tempWidth, tempHeight);
			ofPopMatrix();
		}
		else if (shapes[i][0] == "ellipse")
		{
			ofPushMatrix();

			if (fills[i][0])
			{
				ofFill();
			}
			else
			{
				ofNoFill();
			}

			ofSetLineWidth(widths[i][0]);
			ofSetColor(colors[i][0]);
			ofSetCircleResolution(100);

			// Works out the center position of the ellipse
			float truePosX = ((temp[1][0] - temp[0][0]) / 2) + temp[0][0];
			float truePosY = ((temp[1][1] - temp[0][1]) / 2) + temp[0][1];

			float tempWidth = temp[1][0] - temp[0][0];
			float tempHeight = temp[1][1] - temp[0][1];

			ofDrawEllipse(truePosX, truePosY, tempWidth, tempHeight);
			ofPopMatrix();
		}
		else if (shapes[i][0] == "triangle")
		{
			ofPushMatrix();

			if (fills[i][0])
			{
				ofFill();
			}
			else
			{
				ofNoFill();
			}

			ofSetLineWidth(widths[i][0]);
			ofSetColor(colors[i][0]);

			// Bottom left corner
			float tempPosX_1 = temp[0][0];
			float tempPosY_1 = temp[1][1];

			// Top middle corner
			float tempPosX_2 = ((temp[1][0] - temp[0][0]) / 2) + temp[0][0];
			float tempPosY_2 = temp[0][1];

			ofDrawTriangle(tempPosX_1, tempPosY_1, tempPosX_2, tempPosY_2, temp[1][0], temp[1][1]);
			ofPopMatrix();
		}
		else if (shapes[i][0] == "polygon")
		{
			ofPushMatrix();
			ofBeginShape();

			if (fills[i][0])
			{
				ofFill();
			}
			else
			{
				ofNoFill();
			}

			ofSetLineWidth(widths[i][0]);
			ofSetColor(colors[i][0]);

			// Draws every point/vertex created by user
			for (int j = 0; j < positions[i].size(); j++)
			{
				ofVertex(positions[i][j]);
			}

			ofEndShape();
			ofPopMatrix();
		}

		temp.clear();
	}
}

// Draws in real-time how the shape would look if the user would create it
void tools::ghost(string currentShape, vec2 mousePos)
{
	// 0 = line
	// 1 = rect
	// 2 = ellipse
	// 3 = triangle
	// 4 = polygon

	if (currentShape == shapeTools[0]->tool && shapeTools[0]->state == 2) // Line Tool
	{
		ofPushMatrix();
		ofSetLineWidth(currentWidth);
		ofSetColor(currentColor, 50);
		ofDrawLine(tempPos1, mousePos);
		ofPopMatrix();
	}
	else if (currentShape == shapeTools[1]->tool && shapeTools[1]->state == 2) // Rect Tool
	{
		ofPushMatrix();

		if (currentFill)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}

		ofSetLineWidth(currentWidth);
		ofSetColor(currentColor, 50);

		float tempWidth = mousePos[0] - tempPos1[0];
		float tempHeight = mousePos[1] - tempPos1[1];

		ofDrawRectangle(tempPos1, tempWidth, tempHeight);
		ofPopMatrix();
	}
	else if (currentShape == shapeTools[2]->tool && shapeTools[2]->state == 2) // Ellipse Tool
	{
		ofPushMatrix();

		if (currentFill)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}

		ofSetLineWidth(currentWidth);
		ofSetColor(currentColor, 50);
		ofSetCircleResolution(100);

		float truePosX = ((mousePos[0] - tempPos1[0]) / 2) + tempPos1[0];
		float truePosY = ((mousePos[1] - tempPos1[1]) / 2) + tempPos1[1];

		float tempWidth = mousePos[0] - tempPos1[0];
		float tempHeight = mousePos[1] - tempPos1[1];

		ofDrawEllipse(truePosX, truePosY, tempWidth, tempHeight);
		ofPopMatrix();
	}
	else if (currentShape == shapeTools[3]->tool && shapeTools[3]->state == 2) // Triangle Tool
	{
		ofPushMatrix();

		if (currentFill)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}

		ofSetLineWidth(currentWidth);
		ofSetColor(currentColor, 50);

		float tempPosX_1 = tempPos1[0];
		float tempPosY_1 = mousePos[1];

		float tempPosX_2 = ((mousePos[0] - tempPos1[0]) / 2) + tempPos1[0];
		float tempPosY_2 = tempPos1[1];

		ofDrawTriangle(tempPosX_1, tempPosY_1, tempPosX_2, tempPosY_2, mousePos[0], mousePos[1]);
		ofPopMatrix();
	}
	else if (currentShape == shapeTools[4]->tool && shapeTools[4]->state == 2)
	{
		ofPushMatrix();
		ofBeginShape();

		if (currentFill)
		{
			ofFill();
		}
		else
		{
			ofNoFill();
		}

		ofSetLineWidth(currentWidth);
		ofSetColor(currentColor, 50);

		for (int i = 0; i < tempPos.size(); i++)
		{
			ofVertex(tempPos[i]);
		}

		ofVertex(mousePos);
		ofEndShape();
		ofPopMatrix();
	}
}

// User is able to select tools with the number keys
void tools::keyPressed(int key)
{
	if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5')
	{
		int tempIndex;

		if		(key == '1')	{ tempIndex = 0; }
		else if (key == '2')	{ tempIndex = 1; }
		else if (key == '3')	{ tempIndex = 2; }
		else if (key == '4')	{ tempIndex = 3; }
		else if (key == '5')	{ tempIndex = 4; }

		// Equips the required tool and unequips the rest
		for (int i = 0; i < (sizeof(shapeTools) / sizeof(shapeTools[0])); i++)
		{
			if (i != tempIndex)
			{
				shapeTools[i]->equipped = false;
			}
			else
			{
				shapeTools[i]->equipped = true;
			}
		}
	}

	// When user uses the polygon tool, they can finish the shape once they press ENTER/RETURN
	if (key == OF_KEY_RETURN)
	{
		if (shapeTools[4]->equipped == true && shapeTools[4]->state == 2)
		{
			shapes = saveShape(shapes, shapeTools[4]->tool);
			positions = savePos(positions, tempPos);
			fills = saveFill(fills, currentFill);
			widths = saveWidth(widths, currentWidth);
			colors = saveColor(colors, currentColor);

			tempPos.clear();
			shapeTools[4]->state = 1;
		}
	}
}

// Updates the vectors when user has placed new points of the shapes, or cancelled the drawing
void tools::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < (sizeof(shapeTools) / sizeof(shapeTools[0])); i++)
	{
		if (i != 4 && shapeTools[i]->equipped == true && button == 0) // When user presses left click which creates a new point of the shape being drawn
		{
			if (shapeTools[i]->state == 1)
			{
				tempPos1 = { x,y };
				shapeTools[i]->state = 2;
			}
			else if (shapeTools[i]->state == 2)
			{
				vector<vec2> temp = { tempPos1, {x,y} }; // Saves the first point and the second point into one vector

				shapes = saveShape(shapes, shapeTools[i]->tool);
				positions = savePos(positions, temp);
				fills = saveFill(fills, currentFill);
				widths = saveWidth(widths, currentWidth);
				colors = saveColor(colors, currentColor);

				tempPos.clear();
				shapeTools[i]->state = 1;
			}
		}
		else if (shapeTools[i]->equipped == true && button == 2) // When user presses right click which cancels the drawing
		{
			tempPos.clear();
			shapeTools[i]->state = 1;
		}
	}

	if (shapeTools[4]->equipped == true && button == 0) // When user uses polygon, it keeps track of multiple positions instead of fixed 2 like the rest of the tools
	{
		if (tempPos.empty())
		{
			tempPos.push_back({ x,y });
			shapeTools[4]->state = 2;
		}
		else
		{
			if (shapeTools[4]->state == 2) // Will constantly add new positions until user presses ENTER/RETURN
			{
				tempPos.push_back({ x,y });
			}
		}
	}
}

// Saves the shape of each drawing
vector<vector<string>> tools::saveShape(vector<vector<string>> shapes, string currentShape)
{
	vector<string>temp;

	temp.push_back(currentShape);
	shapes.push_back(temp);
	temp.clear();

	return shapes;
}

// Saves the positions of each drawing
vector<vector<vec2>> tools::savePos(vector<vector<vec2>> positions, vector<vec2> tempPos)
{
	positions.push_back(tempPos);

	return positions;
}

// Saves the fill property of each drawing
vector<vector<bool>> tools::saveFill(vector<vector<bool>> fills, bool tempFill)
{
	vector<bool>temp;

	temp.push_back(tempFill);
	fills.push_back(temp);

	temp.clear();

	return fills;
}

// Saves the width property of each drawing
vector<vector<float>> tools::saveWidth(vector<vector<float>> widths, float tempWidth)
{
	vector<float>temp;

	temp.push_back(tempWidth);
	widths.push_back(temp);

	temp.clear();

	return widths;
}

// Saves the colour property of each drawing
vector<vector<ofColor>> tools::saveColor(vector<vector<ofColor>> colors, ofColor tempColor)
{
	vector<ofColor>temp;

	temp.push_back(tempColor);
	colors.push_back(temp);

	temp.clear();

	return colors;
}

// Temporarily extracted to be used for conversion to code //
vector<vector<string>> tools::extractShapes()
{
	return shapes;
}

vector<vector<vec2>> tools::extractPositions() 
{
	return positions;
}

vector<vector<bool>> tools::extractFills() 
{
	return fills;
}

vector<vector<float>> tools::extractWidths()
{
	return widths;
}

vector<vector<ofColor>> tools::extractColors()
{
	return colors;
}