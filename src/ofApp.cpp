#include "ofApp.h"
#include <functional>

// Used to create interactible buttons
typedef std::function<bool(int, int)> mouseClickCallbackFunction;

std::vector<mouseClickCallbackFunction> lineTool;
std::vector<mouseClickCallbackFunction> rectTool;
std::vector<mouseClickCallbackFunction> ellipseTool;
std::vector<mouseClickCallbackFunction> triangleTool;
std::vector<mouseClickCallbackFunction> polygonTool;
std::vector<mouseClickCallbackFunction> convertOFTool;
std::vector<mouseClickCallbackFunction> convertP5Tool;

ofRectangle lineToolButton(0, 0, 70, 70);
ofRectangle rectToolButton(0, 0, 70, 70);
ofRectangle ellipseToolButton(0, 0, 70, 70);
ofRectangle triangleToolButton(0, 0, 70, 70);
ofRectangle polygonToolButton(0, 0, 70, 70);
ofRectangle convertOFButton(0, 0, 120, 50);
ofRectangle convertP5Button(0, 0, 120, 50);



//--------------------------------------------------------------
void ofApp::setup()
{
	// Sets properties GUI for shapes
	propertiesGui.setup("panel");
	propertiesGui.setPosition(ofGetWidth() - 210, 10);
	propertiesGui.add(filled.set("bFill", false));
	propertiesGui.add(width.set("width", 5, 0.1, 10));
	propertiesGui.add(color.set("color", ofColor(0, 0, 0, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)));

	// Sets positions of buttons
	lineToolButton.setPosition(25,25);
	rectToolButton.setPosition(25,115);
	ellipseToolButton.setPosition(25,205);
	triangleToolButton.setPosition(25,295);
	polygonToolButton.setPosition(25,385);
	convertOFButton.setPosition(0, ofGetHeight() - 50);
	convertP5Button.setPosition(150, ofGetHeight() - 50);

	// Clears callbacks
	lineTool.clear();
	rectTool.clear();
	ellipseTool.clear();
	triangleTool.clear();
	polygonTool.clear();
	convertOFTool.clear();
	convertP5Tool.clear();

	// Adds buttons
	lineTool.push_back([](int mx, int my)
	{
		return lineToolButton.inside(mx, my);
	});

	rectTool.push_back([](int mx, int my)
	{
		return rectToolButton.inside(mx, my);
	});

	ellipseTool.push_back([](int mx, int my)
	{
		return ellipseToolButton.inside(mx, my);
	});

	triangleTool.push_back([](int mx, int my)
	{
		return triangleToolButton.inside(mx, my);
	});

	polygonTool.push_back([](int mx, int my)
	{
		return polygonToolButton.inside(mx, my);
	});

	convertOFTool.push_back([](int mx, int my)
	{
		return convertOFButton.inside(mx, my);
	});

	convertP5Tool.push_back([](int mx, int my)
	{
		return convertP5Button.inside(mx, my);
	});

	// Loads images
	lineImg.load("line.png");
	rectImg.load("rect.png");
	elliImg.load("ellipse.png");
	triaImg.load("triangle.png");
	polyImg.load("polygon.png");
	OFImg.load("OF.png");
	P5Img.load("P5.png");
}

//--------------------------------------------------------------
void ofApp::update()
{
	tools.update(filled, width, color); // Constantly updates the current properties in the GUI to the tools
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetBackgroundColor(255);

	tools.draw(); // Draws every shape created

	// Draws a "ghost" (how the shape would look if it was created)
	for (int i = 0; i < (sizeof(tools.shapeTools) / sizeof(tools.shapeTools[0])); i++)
	{
		if (tools.shapeTools[i]->equipped == true)
		{
			tools.ghost(tools.shapeTools[i]->tool, { ofGetMouseX(), ofGetMouseY() });
		}
	}

	toolsGui(lineImg, rectImg, elliImg, triaImg, polyImg);

	propertiesGui.draw();
}

void ofApp::toolsGui(ofImage lineImg, ofImage rectImg, ofImage elliImg, ofImage triaImg, ofImage polyImg)
{
	ofPushMatrix();
	ofSetLineWidth(3);

	// Each tool will have a different style depending if it's equipped or not
	if (tools.shapeTools[0]->equipped == true)
	{
		ofSetColor(200);
		ofDrawRectangle(20, 20, 80, 80);

		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(20, 20, 80, 80);

		lineImg.draw(25, 25);
	}
	else
	{
		ofFill();
		ofSetColor(100);
		ofDrawRectangle(25, 25, 70, 70);

		lineImg.draw(25, 25);
	}

	ofFill();
	ofSetColor(100);

	if (tools.shapeTools[1]->equipped == true)
	{
		ofSetColor(200);
		ofDrawRectangle(20, 110, 80, 80);

		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(20, 110, 80, 80);

		rectImg.draw(25, 115);
	}
	else
	{
		ofFill();
		ofSetColor(100);
		ofDrawRectangle(25, 115, 70, 70);

		rectImg.draw(25, 115);
	}

	if (tools.shapeTools[2]->equipped == true)
	{
		ofSetColor(200);
		ofDrawRectangle(20, 200, 80, 80);

		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(20, 200, 80, 80);

		elliImg.draw(25, 205);
	}
	else
	{
		ofFill();
		ofSetColor(100);
		ofDrawRectangle(25, 205, 70, 70);

		elliImg.draw(25, 205);
	}

	if (tools.shapeTools[3]->equipped == true)
	{
		ofSetColor(200);
		ofDrawRectangle(20, 290, 80, 80);

		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(20, 290, 80, 80);

		triaImg.draw(25, 295);
	}
	else
	{
		ofFill();
		ofSetColor(100);
		ofDrawRectangle(25, 295, 70, 70);

		triaImg.draw(25, 295);
	}

	if (tools.shapeTools[4]->equipped == true)
	{
		ofSetColor(200);
		ofDrawRectangle(20, 380, 80, 80);

		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(20, 380, 80, 80);

		polyImg.draw(25, 385);
	}
	else
	{
		ofFill();
		ofSetColor(100);
		ofDrawRectangle(25, 385, 70, 70);

		polyImg.draw(25, 385);
	}

	ofPopMatrix();

	// Convert GUI
	ofPushMatrix();
	ofDrawRectangle(0, ofGetHeight() - 50, 120, 50);
	OFImg.draw(0, ofGetHeight() - 50);
	ofDrawRectangle(150, ofGetHeight() - 50, 120, 50);
	P5Img.draw(150, ofGetHeight() - 50);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	tools.keyPressed(key);

	if (key == ' ')
	{
		vector <string> code = convert.toOpenFrameworks(tools.extractShapes(), tools.extractPositions(), tools.extractFills(), tools.extractWidths(), tools.extractColors());

		for (int i = 0; i < code.size(); i++)
		{
			cout << code[i] << endl;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	// Each interaction equips the tool and unequips the rest
	for (auto callbackFunction : lineTool)
	{
		if (callbackFunction(x, y))
		{
			tools.shapeTools[0]->equipped = true;
			tools.shapeTools[1]->equipped = false;
			tools.shapeTools[2]->equipped = false;
			tools.shapeTools[3]->equipped = false;
			tools.shapeTools[4]->equipped = false;
		}
	}

	for (auto callbackFunction : rectTool)
	{
		if (callbackFunction(x, y))
		{
			tools.shapeTools[0]->equipped = false;
			tools.shapeTools[1]->equipped = true;
			tools.shapeTools[2]->equipped = false;
			tools.shapeTools[3]->equipped = false;
			tools.shapeTools[4]->equipped = false;
		}
	}

	for (auto callbackFunction : ellipseTool)
	{
		if (callbackFunction(x, y))
		{
			tools.shapeTools[0]->equipped = false;
			tools.shapeTools[1]->equipped = false;
			tools.shapeTools[2]->equipped = true;
			tools.shapeTools[3]->equipped = false;
			tools.shapeTools[4]->equipped = false;
		}
	}

	for (auto callbackFunction : triangleTool)
	{
		if (callbackFunction(x, y))
		{
			tools.shapeTools[0]->equipped = false;
			tools.shapeTools[1]->equipped = false;
			tools.shapeTools[2]->equipped = false;
			tools.shapeTools[3]->equipped = true;
			tools.shapeTools[4]->equipped = false;
		}
	}

	for (auto callbackFunction : polygonTool)
	{
		if (callbackFunction(x, y))
		{
			tools.shapeTools[0]->equipped = false;
			tools.shapeTools[1]->equipped = false;
			tools.shapeTools[2]->equipped = false;
			tools.shapeTools[3]->equipped = false;
			tools.shapeTools[4]->equipped = true;
		}
	}

	// Converts all the saved positions and properties of the drawings to OpenFrameworks code, then copies straight to clipboard
	for (auto callbackFunction : convertOFTool)
	{
		if (callbackFunction(x, y))
		{
			vector <string> code = convert.toOpenFrameworks(tools.extractShapes(), tools.extractPositions(), tools.extractFills(), tools.extractWidths(), tools.extractColors());

			for (int i = 0; i < code.size(); i++)
			{
				cout << code[i] << endl;
			}

			stringstream ssCode;
			std::copy(code.begin(), code.end(), std::ostream_iterator<std::string>(ssCode, "\n"));
			size_t len = strlen(ssCode.str().c_str());

			OpenClipboard(0);
			EmptyClipboard();
			HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, ssCode.str().size() + 1);
			if (!hg) {
				CloseClipboard();
				return;
			}
			memcpy(GlobalLock(hg), ssCode.str().c_str(), ssCode.str().size() + 1);
			GlobalUnlock(hg);
			SetClipboardData(CF_TEXT, hg);
			CloseClipboard();
			GlobalFree(hg);

			convert.clearCode();
		}
	}

	// Converts all the saved positions and properties of the drawings to P5JS code, then copies straight to clipboard
	for (auto callbackFunction : convertP5Tool)
	{
		if (callbackFunction(x, y))
		{
			vector <string> code = convert.toP5JS(tools.extractShapes(), tools.extractPositions(), tools.extractFills(), tools.extractWidths(), tools.extractColors());

			for (int i = 0; i < code.size(); i++)
			{
				cout << code[i] << endl;
			}

			stringstream ssCode;
			std::copy(code.begin(), code.end(), std::ostream_iterator<std::string>(ssCode, "\n"));
			size_t len = strlen(ssCode.str().c_str());

			OpenClipboard(0);
			EmptyClipboard();
			HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, ssCode.str().size() + 1);
			if (!hg) {
				CloseClipboard();
				return;
			}
			memcpy(GlobalLock(hg), ssCode.str().c_str(), ssCode.str().size() + 1);
			GlobalUnlock(hg);
			SetClipboardData(CF_TEXT, hg);
			CloseClipboard();
			GlobalFree(hg);

			convert.clearCode();
		}
	}
	
	tools.mousePressed(x,y,button); // When user creates points of the shapes
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
