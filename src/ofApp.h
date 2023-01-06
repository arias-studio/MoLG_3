#pragma once
/* ---------------------------------------------------------- */
#include "ofMain.h"
#include "ofxOpenCv.h"
/* ---------------------------------------------------------- */
class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	/* ---------------------------------------------------------- */
private:
	ofVideoGrabber webcam;
	ofxCvColorImage blurred;
	ofxCvColorImage blurred_text;
	ofxCvColorImage cam_img;
	ofImage wet_glass;
	vector<ofImage> mask_vector;
	ofImage mask;
	vector<ofImage> mask_vector_inv;
	ofImage mask_inv;
	// ----------------
	const float time_limit = 45.0;
	const float time_transition = 15.0;
	const int screen_width = ofGetScreenWidth();
	const int screen_height = ofGetScreenHeight();
	// ----------------
	uint8_t image_index;
	float time;
	float opacity;
	float opacity_inv;
};