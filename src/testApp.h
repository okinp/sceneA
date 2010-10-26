#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include <vector>
#include "ofxVec3f.h"
#include "perlin.h"
#include "particleSystem.h"
#include "ofxSvgLoader.h"
#include "maxOSC.h"
#include "ofxMostPixelsEver.h"


struct bezier {
	
	ofxVec2f start;
	ofxVec2f end;
	ofxVec2f cp1;
	ofxVec2f cp2;
};

class testApp : public ofBaseApp, public mpeClientListener{
	
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
	void windowResized(int w, int h);
	void sampleImage(int sampleSize);
	void extractData();
	void extractBeziers();
	void frameEvent();
	vector < vector <ofxVec2f> > extractedShapes;
	
	particleSystem myParticles;
	maxOSC myMaxOSC;
	//ofxSVG svgFile;
	ofxSvgLoader svgPaths;
	
	bool moveToCenter, moveBack, moveRandom, paused, movePaused;

	int sampleS;
	
	vector <bezier> theBeziers;
private:
	mpeClientTCP client;
};

#endif
	
