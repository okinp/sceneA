/*
 *  pixelParticle.h
 *  BS_test
 *
 *  Created by Tamar Ziv on 8/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _PIXELPARTICLE_
#define _PIXELPARTICLE_
#include "ofxVec3f.h"
class pixelParticle  {
public:
	pixelParticle(ofxVec3f _posInit, ofxVec3f _color);
	void goToTarget(ofxVec3f _posTarg);
	void setAccel(ofxVec3f _acc = ofxVec3f(0.0f, 0.0f, 0.0f));
	void update();
	void draw();
	ofxVec3f posInit;
	ofxVec3f posCurr;
	ofxVec3f posTarg;
	ofxVec3f acc;
	ofxVec3f vel;
	ofxVec3f color;
	float damping;
};

#endif
