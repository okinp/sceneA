/*
 *  particleSystem.h
 *  BS_test
 *
 *  Created by Tamar Ziv on 8/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PARTICLESYS
#define _PARTICLESYS

#include "ofMain.h"
#include <vector>
#include "ofxVectorMath.h"
#include "ofxVec3f.h"
#include "perlin.h"
#include "pixelParticle.h"

class particleSystem {
	
public:
	particleSystem();
	void setImage(ofImage _img);
	void setup();
	void update();
	void draw();
	void sampleImage(int sampleSize);
	void moveToCenter();
	void moveRandom();
	//void moveRandomH();
	//void moveRandomV();
	void moveBack();
	void movePaused();
	
	bool mustMoveBack, mustMoveToCenter, mustMoveRandom,mustMoveRandomH,mustMoveRandomV, mustMovePaused;	
	ofxVec3f mouseLocation;
	int mouseX, mouseY, pointSize, amount;
	int scaleX, scaleY, scaleZ;
	
private:	
	ofImage img;	
	unsigned char * pixels;
	float thres;
	int cnt, sampleSz;
	int pSize;
	vector <pixelParticle*> particles;
	vector <pixelParticle*>::iterator particleIter;
	
	//bool first;
	//bool moveBack;
	//bool moveToCenter;
	//bool resample;
	//bool moveRight;
	
	ofBaseApp *app;
	
};



#endif