#pragma once

#include "ofMain.h"
#include "web.h"
#include "kinect.h"
#include "sound.h"
#include "text.h"
#include "ofxSimpleTimer.h"
#include "jsonManager.h"
#include "ofxGui.h"
#include "ofxJSON.h"



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();
		void startAnew();
		void stateManager();
		void peopleOutManager();


		ofxSimpleTimer timerDetectionStill;
		ofxSimpleTimer timerPeopleOut;
		float currentTime;

		jsonManager counterUser;
		ofEasyCam cam;
		web web;
		kinect kinect;
		sound sound;
		text text;
		ofImage base;
		ofShader shader;
		ofShader shaderweb;
		Boolean imageSaved;
		Boolean restart;


		ofxPanel gui;
		ofxFloatSlider radius;
		ofxFloatSlider random_base;
		ofxFloatSlider b;
		ofxFloatSlider c;

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

};
