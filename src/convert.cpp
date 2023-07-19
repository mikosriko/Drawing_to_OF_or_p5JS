#include "convert.h"

using namespace glm;

vector <string> convert::toOpenFrameworks(vector<vector<string>> shapes, vector<vector<vec2>> positions, vector<vector<bool>> fills, vector<vector<float>> widths, vector<vector<ofColor>> colors)
{
	for (int i = 0; i < positions.size(); i++)
	{
		stringstream ssTempPos1;
		stringstream ssTempPos2;
		stringstream ssWidth;
		stringstream ssColor;
#
		// First vec2
		for (auto it = positions[i].begin(); it != positions[i].end() - 1; it++)
		{
			if (it != positions[i].begin())
			{
				ssTempPos1 << ",";
			}
			ssTempPos1 << *it;
		}

		// Second vec2
		for (auto it = positions[i].begin() + 1; it != positions[i].end(); it++)
		{
			if (it != positions[i].begin() + 1)
			{
				ssTempPos2 << ",";
			}
			ssTempPos2 << *it;
		}

		// Line Width
		for (auto it = widths[i].begin(); it != widths[i].end(); it++)
		{
			ssWidth << *it;
		}

		// Color
		for (auto it = colors[i].begin(); it != colors[i].end(); it++)
		{
			ssColor << *it;
		}

		convertedCode.push_back("ofPushMatrix();");

		if (shapes[i][0] == "polygon")
		{
			convertedCode.push_back("ofBeginShape();");
		}

		if (shapes[i][0] != "line" && fills[i][0])
		{
			convertedCode.push_back("ofFill();");
		}
		else if (shapes[i][0] != "line" && fills[i][0] == false)
		{
			convertedCode.push_back("ofNoFill();");
		}

		convertedCode.push_back("ofSetLineWidth(" + ssWidth.str() + ");");
		convertedCode.push_back("ofSetColor(" + ssColor.str() + ");");

		if (shapes[i][0] == "ellipse")
		{
			convertedCode.push_back("ofSetCircleResolution(100);");
		}

		if (shapes[i][0] == "line")
		{
			convertedCode.push_back("ofDrawLine(" + ssTempPos1.str() + "," + ssTempPos2.str() + ");");
		}
		else if (shapes[i][0] == "rect")
		{
			float tempWidth = positions[i][1][0] - positions[i][0][0];
			float tempHeight = positions[i][1][1] - positions[i][0][1];

			stringstream ssTempWidth;
			stringstream ssTempHeight;

			ssTempWidth << tempWidth;
			ssTempHeight << tempHeight;

			convertedCode.push_back("ofDrawRectangle(" + ssTempPos1.str() + "," + ssTempWidth.str() + "," + ssTempHeight.str() + ");");
		}
		else if (shapes[i][0] == "ellipse")
		{
			float truePosX = ((positions[i][1][0] - positions[i][0][0]) / 2) + positions[i][0][0];
			float truePosY = ((positions[i][1][1] - positions[i][0][1]) / 2) + positions[i][0][1];

			float tempWidth = positions[i][1][0] - positions[i][0][0];
			float tempHeight = positions[i][1][1] - positions[i][0][1];

			stringstream ssTruePosX;
			stringstream ssTruePosY;
			stringstream ssTempWidth;
			stringstream ssTempHeight;

			ssTruePosX << truePosX;
			ssTruePosY << truePosY;
			ssTempWidth << tempWidth;
			ssTempHeight << tempHeight;

			convertedCode.push_back("ofDrawEllipse(" + ssTruePosX.str() + "," + ssTruePosY.str() + "," + ssTempWidth.str() + "," + ssTempHeight.str() + ");");
		}
		else if (shapes[i][0] == "triangle")
		{
			// Bottom left corner
			float tempPosX_1 = positions[i][0][0];
			float tempPosY_1 = positions[i][1][1];

			// Top middle corner
			float tempPosX_2 = ((positions[i][1][0] - positions[i][0][0]) / 2) + positions[i][0][0];
			float tempPosY_2 = positions[i][0][1];

			stringstream ssTempPosX_1;
			stringstream ssTempPosY_1;
			stringstream ssTempPosX_2;
			stringstream ssTempPosY_2;

			ssTempPosX_1 << tempPosX_1;
			ssTempPosY_1 << tempPosY_1;
			ssTempPosX_2 << tempPosX_2;
			ssTempPosY_2 << tempPosY_2;

			convertedCode.push_back("ofDrawTriangle(" + ssTempPosX_1.str() + "," + ssTempPosY_1.str() + "," + ssTempPosX_2.str() + "," + ssTempPosY_2.str() + "," + ssTempPos2.str() + ");");
		}
		else if (shapes[i][0] == "polygon")
		{
			for (auto it = positions[i].begin(); it != positions[i].end(); it++)
			{
				stringstream ssTempPos;
				ssTempPos << *it;

				convertedCode.push_back("ofVertex(" + ssTempPos.str() + ");");
			}
		}

		if (shapes[i][0] == "polygon")
		{
			convertedCode.push_back("ofEndShape();");
		}
		convertedCode.push_back("ofPopMatrix();");
		convertedCode.push_back("");
	}
	
	return convertedCode;
}

vector <string> convert::toP5JS(vector<vector<string>> shapes, vector<vector<vec2>> positions, vector<vector<bool>> fills, vector<vector<float>> widths, vector<vector<ofColor>> colors)
{
	for (int i = 0; i < positions.size(); i++)
	{
		stringstream ssTempPos1;
		stringstream ssTempPos2;
		stringstream ssWidth;
		stringstream ssColor;
#
		// First vec2
		for (auto it = positions[i].begin(); it != positions[i].end() - 1; it++)
		{
			if (it != positions[i].begin())
			{
				ssTempPos1 << ",";
			}
			ssTempPos1 << *it;
		}

		// Second vec2
		for (auto it = positions[i].begin() + 1; it != positions[i].end(); it++)
		{
			if (it != positions[i].begin() + 1)
			{
				ssTempPos2 << ",";
			}
			ssTempPos2 << *it;
		}

		// Line Width
		for (auto it = widths[i].begin(); it != widths[i].end(); it++)
		{
			ssWidth << *it;
		}

		// Color
		for (auto it = colors[i].begin(); it != colors[i].end(); it++)
		{
			ssColor << *it;
		}

		convertedCode.push_back("push();");

		if (shapes[i][0] == "polygon")
		{
			convertedCode.push_back("beginShape();");
		}

		if (shapes[i][0] != "line" && fills[i][0])
		{
			convertedCode.push_back("fill(" + ssColor.str() + ");");
			convertedCode.push_back("noStroke()");
		}
		else if (shapes[i][0] != "line" && fills[i][0] == false)
		{
			convertedCode.push_back("noFill();");
			convertedCode.push_back("noStroke()");
		}

		convertedCode.push_back("strokeWeight(" + ssWidth.str() + ");");

		if (fills[i][0] == false)
		{
			convertedCode.push_back("color(" + ssColor.str() + ");");
		}

		if (shapes[i][0] == "line")
		{
			convertedCode.push_back("line(" + ssTempPos1.str() + "," + ssTempPos2.str() + ");");
		}
		else if (shapes[i][0] == "rect")
		{
			float tempWidth = positions[i][1][0] - positions[i][0][0];
			float tempHeight = positions[i][1][1] - positions[i][0][1];

			stringstream ssTempWidth;
			stringstream ssTempHeight;

			ssTempWidth << tempWidth;
			ssTempHeight << tempHeight;

			convertedCode.push_back("rect(" + ssTempPos1.str() + "," + ssTempWidth.str() + "," + ssTempHeight.str() + ");");
		}
		else if (shapes[i][0] == "ellipse")
		{
			float truePosX = ((positions[i][1][0] - positions[i][0][0]) / 2) + positions[i][0][0];
			float truePosY = ((positions[i][1][1] - positions[i][0][1]) / 2) + positions[i][0][1];

			float tempWidth = positions[i][1][0] - positions[i][0][0];
			float tempHeight = positions[i][1][1] - positions[i][0][1];

			stringstream ssTruePosX;
			stringstream ssTruePosY;
			stringstream ssTempWidth;
			stringstream ssTempHeight;

			ssTruePosX << truePosX;
			ssTruePosY << truePosY;
			ssTempWidth << tempWidth;
			ssTempHeight << tempHeight;

			convertedCode.push_back("ellipse(" + ssTruePosX.str() + "," + ssTruePosY.str() + "," + ssTempWidth.str() + "," + ssTempHeight.str() + ");");
		}
		else if (shapes[i][0] == "triangle")
		{
			// Bottom left corner
			float tempPosX_1 = positions[i][0][0];
			float tempPosY_1 = positions[i][1][1];

			// Top middle corner
			float tempPosX_2 = ((positions[i][1][0] - positions[i][0][0]) / 2) + positions[i][0][0];
			float tempPosY_2 = positions[i][0][1];

			stringstream ssTempPosX_1;
			stringstream ssTempPosY_1;
			stringstream ssTempPosX_2;
			stringstream ssTempPosY_2;

			ssTempPosX_1 << tempPosX_1;
			ssTempPosY_1 << tempPosY_1;
			ssTempPosX_2 << tempPosX_2;
			ssTempPosY_2 << tempPosY_2;

			convertedCode.push_back("triangle(" + ssTempPosX_1.str() + "," + ssTempPosY_1.str() + "," + ssTempPosX_2.str() + "," + ssTempPosY_2.str() + "," + ssTempPos2.str() + ");");
		}
		else if (shapes[i][0] == "polygon")
		{
			for (auto it = positions[i].begin(); it != positions[i].end(); it++)
			{
				stringstream ssTempPos;
				ssTempPos << *it;

				convertedCode.push_back("vertex(" + ssTempPos.str() + ");");
			}
		}

		if (shapes[i][0] == "polygon")
		{
			convertedCode.push_back("endShape();");
		}
		convertedCode.push_back("pop();");
		convertedCode.push_back("");
	}

	return convertedCode;
}

void convert::clearCode()
{
	convertedCode.clear();
}