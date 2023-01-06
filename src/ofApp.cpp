#include "ofApp.h"

/* -------------------------- SETUP ------------------------- */
void ofApp::setup()
{
	// EDIT THIS VALUES
	webcam.setDeviceID(1);
	// ----------------
	ofSetWindowTitle("Machines of Loving Grace 3.0. Cristian Arias. 2023");
	ofSetWindowShape(screen_width, screen_height);
	ofSetFrameRate(60);
	webcam.initGrabber(screen_width, screen_height);
	// ----------------
	time = 0.0;
	opacity = 0.0;
	opacity_inv = 1.0;
	image_index = 0;
	// ----------------
	for (int i = 0; i < 9; i++)
	{
		mask_vector.push_back(ofImage());
		mask_vector[i].load("mask_" + ofToString(i) + ".bmp");
		mask_vector[i].setImageType(OF_IMAGE_COLOR_ALPHA);

		mask_vector_inv.push_back(ofImage());
		mask_vector_inv[i].load("mask_" + ofToString(i) + "_inv.bmp");
		mask_vector_inv[i].setImageType(OF_IMAGE_COLOR_ALPHA);
	}
	// ----------------
	wet_glass.load("wet_glass.png");
	wet_glass.setImageType(OF_IMAGE_COLOR_ALPHA);
	blurred.allocate(screen_width, screen_height); // PUEDE GENERAR ERROR!!!
}

/* ------------------------- UPDATE ------------------------- */
void ofApp::update()
{
	webcam.update();
	// ----------------
	if (time <= time_limit)
	{
		time += ofGetLastFrameTime();
		// ----------------
		if (time <= time_transition)
		{
			opacity += ofGetLastFrameTime() / time_transition;
			opacity = ofClamp(opacity, 0.0, 1.0);
		}
		// ----------------
		else if (time < time_limit - time_transition)
		{
			opacity = 1.0;
		}
		// ----------------
		else
		{
			opacity -= ofGetLastFrameTime() / time_transition;
			opacity = ofClamp(opacity, 0.0, 1.0);
		}
	}
	// ----------------
	if (time >= time_limit)
	{
		time = 0.0;
		image_index++;
	}
	// ----------------
	if (image_index >= 9)
	{
		image_index = 0;
	}
	opacity_inv = 1.0 - opacity;
	// ----------------
	mask = mask_vector[image_index];
	mask.getPixels().setChannel(1, mask.getPixels().getChannel(0));
	mask.resize(screen_width, screen_height);
	mask.update();

	mask_inv = mask_vector_inv[image_index];
	mask_inv.getPixels().setChannel(1, mask_inv.getPixels().getChannel(0));
	mask_inv.resize(screen_width, screen_height);
	mask_inv.update();
	// ----------------
	if (webcam.isFrameNew())
	{
		blurred.setFromPixels(webcam.getPixels());
		blurred.mirror(0, 1);
		blurred.resize(screen_width, screen_height);

		cam_img.setFromPixels(webcam.getPixels());
		cam_img.mirror(0, 1);
		cam_img.resize(screen_width, screen_height);

		for (int i = 0; i < 3; i++)
		{
			blurred.blur(50);
		}
		blurred_text = blurred;
		blurred_text.getTexture().setAlphaMask(mask_inv.getTexture());
		blurred.getTexture().setAlphaMask(mask.getTexture());
	}
	// FRAME RATE
	// std::stringstream strm;
	// strm << "FPS: " << ofGetFrameRate();
	// ofSetWindowTitle(strm.str());
}

/* -------------------------- DRAW -------------------------- */
void ofApp::draw()
{
	ofSetColor(255, 255, 255, 255);
	cam_img.draw(0, 0);
	blurred.draw(0, 0);
	ofSetColor(255, 255, 255, 255 * opacity_inv);
	blurred_text.draw(0, 0);
	ofSetColor(255, 255, 255, 255);
	wet_glass.draw(0, 0);
	//  ----------------
	if (ofGetWindowMode() != OF_FULLSCREEN)
	{
		ofDrawBitmapString("MACHINES OF LOVING GRACE 3.0", 30, 30);
		ofDrawBitmapString("Cristian Arias, 2023", 30, 50);
		ofDrawBitmapString("---", 30, 90);
		ofDrawBitmapString("FULL SCREEN:", 30, 130);
		ofDrawBitmapString("Press (F) or the left mouse button", 30, 150);
		ofDrawBitmapString("CLOSE:", 30, 190);
		ofDrawBitmapString("Press (Q), (ESC) or the right mouse button", 30, 210);

		// ofDrawBitmapString("---", 30, 250);
		// ofDrawBitmapString("time: " + ofToString(time), 30, 290);
		// ofDrawBitmapString("opacity: " + ofToString(opacity), 30, 310);
		// ofDrawBitmapString("opacity: " + ofToString(opacity_inv), 30, 330);
		// ofDrawBitmapString("index: " + ofToString(image_index), 30, 350);
	}
}

/* ----------------------- KEY PRESSED ---------------------- */
void ofApp::keyPressed(int key)
{
	if (key == 'f')
	{
		ofToggleFullscreen();

		if (ofGetWindowMode() == OF_FULLSCREEN)
		{
			ofHideCursor();
		}
		else
		{
			ofShowCursor();
		}
	}

	if (key == 'q')
	{
		OF_EXIT_APP(0);
	}
}

/* ---------------------- MOUSE PRESSED --------------------- */
void ofApp::mousePressed(int x, int y, int button)
{
	if (button == OF_MOUSE_BUTTON_LEFT)
	{
		ofToggleFullscreen();
		if (ofGetWindowMode() == OF_FULLSCREEN)
		{
			ofHideCursor();
		}
		else
		{
			ofShowCursor();
		}
	}
	if (button == OF_MOUSE_BUTTON_RIGHT)
	{
		OF_EXIT_APP(0);
	}
}

/* ------------------------ NOT USED ------------------------ */
void ofApp::keyReleased(int key)
{
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}