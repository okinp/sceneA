/*
 *  pixelParticle.cpp
 *  BS_test
 *
 *  Created by Tamar Ziv on 8/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "pixelParticle.h"

pixelParticle::pixelParticle(ofxVec3f _posInit, ofxVec3f _color)
{
	posInit = _posInit;
	posCurr = _posInit;
	posTarg = _posInit;
	color = _color;
	vel = ofxVec3f(0.0f,0.0f,0.0f);
	acc = ofxVec3f(0.0f,0.0f,0.0f);
	damping = 0.08;
	
}
void pixelParticle::goToTarget(ofxVec3f _posTarg)
{
	posTarg = _posTarg;
}
void pixelParticle::update()
{
	acc = posTarg - posCurr;
	float mag = acc.length();
	acc = acc.normalize();
	acc *= mag*damping;
	vel += acc;
	posCurr += acc;
	vel *=0;

}
void pixelParticle::setAccel(ofxVec3f _acc)
{
	acc += _acc;	
}
void pixelParticle::draw()
{
	//cout << posCurr.x << endl;
	glColor3f(color.x, color.y, color.z);
	glVertex3f(posCurr.x, posCurr.y, posCurr.z);
	
}
