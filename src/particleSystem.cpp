/*
 *  particleSystem.cpp
 *  BS_test
 *
 *  Created by Tamar Ziv on 8/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "particleSystem.h"

particleSystem::particleSystem() {
	setup();
	
}

//--------------------------------------------------------------
void particleSystem::setup(){
	
	img.loadImage("square_crack2.gif");
//	img.loadImage("testSmall3.gif");

	//img.setImageType(OF_IMAGE_GRAYSCALE);
	img.setImageType(OF_IMAGE_GRAYSCALE);
	pixels = img.getPixels();
	thres = 100;
	cnt=0;
	app = ofGetAppPtr();
	mustMoveBack = false;
	mustMoveToCenter = false;
	mustMoveRandom = false;
	mustMovePaused = false;

	amount = 1;
	pointSize = 1;

}

//--------------------------------------------------------------
void particleSystem::update(){
	
	
	mouseLocation = ofxVec3f (ofGetAppPtr()->mouseX,ofGetAppPtr()->mouseY,0);
	mouseX = mouseLocation.x;
	mouseY = mouseLocation.y;
	
	if (mustMoveBack) {
		moveBack();
		mustMoveBack = !mustMoveBack;
	}
	if (mustMoveToCenter) {
		moveToCenter();
		//mustMoveToCenter = !mustMoveToCenter;
	}
	
	if (mustMoveRandom) {
		moveRandom();
 		//mustMoveRandom = !mustMoveRandom;
	} 
	/*
	if (mustMoveRandomH) {
		moveRandomH();
 		//mustMoveRandomH = !mustMoveRandomH;
	} 
	if (mustMoveRandomV) {
		moveRandomV();
 		//mustMoveRandomV = !mustMoveRandomV;
	} 
	*/
	
	if (mustMovePaused) {
		movePaused(); 	
		mustMovePaused = !mustMovePaused;
	}
	
	
	particleIter = particles.begin();
	while (particleIter!= particles.end()){
		(*particleIter)->update();
		++particleIter;
	}
}
void particleSystem::moveToCenter()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget(ofxVec3f((*particleIter)->posCurr.x+ofRandom(-abs((*particleIter)->posInit.x)/amount,abs((*particleIter)->posInit.x)/amount), ofGetScreenHeight()/2,0)+ofRandom(abs(ofGetScreenHeight()/2-(*particleIter)->posCurr.y), -abs(ofGetScreenHeight()/2-(*particleIter)->posCurr.y)));
		++particleIter;
	}
}

void particleSystem::moveRandom()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget((*particleIter)->posCurr + ofxVec3f(ofRandom(-mouseX/amount, +mouseX/amount), ofRandom(-mouseY/amount, mouseY/amount),0));
		++particleIter;
	}
}
/*

void particleSystem::moveRandomH()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget(ofxVec3f(((*particleIter)->posCurr.x + ofRandom(-mouseX/amount, mouseX/amount)),(*particleIter)->posCurr.y,0));		
		++particleIter;
	}
}

void particleSystem::moveRandomV()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget(ofxVec3f ( ((*particleIter)->posCurr.x), ((*particleIter)->posCurr.y + ofRandom(-mouseY/amount, mouseY/amount)),0));
		++particleIter;
	}
}

*/





void particleSystem::movePaused()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget((*particleIter)->posCurr);
		++particleIter;
	}
}

void particleSystem::moveBack()
{
	particleIter = particles.begin();
	while (particleIter!=particles.end()){
		(*particleIter)->goToTarget((*particleIter)->posInit);
		++particleIter;
	}	
}

void particleSystem::sampleImage(int sampleSize) {

	particles.clear();
	for (int y=0; y< img.getHeight(); y+=sampleSize)
	{
		for (int x=0; x< img.getWidth(); x+=sampleSize) {
			if ((float) pixels[y*(int)img.getWidth()+x] >=thres) {
				pixelParticle* p = new pixelParticle(ofxVec3f(x,y,0), ofxVec3f(1.0f,1.0f,1.0f ));
				particles.push_back(p);
			} 
			
		}
		
	}
}

//--------------------------------------------------------------
void particleSystem::draw(){
	
	//glScale(1+scaleX, 1+scaleY, 1+scaleZ);
	glPointSize(pointSize);
	glPushMatrix();
	glScaled(1+abs(scaleX), 1+abs(scaleY), 1+abs(scaleZ));
	
	glBegin(GL_POINTS);

	particleIter = particles.begin();
	while (particleIter!= particles.end()){
		(*particleIter)->draw();
		++particleIter;
	}
	glEnd();
	glPopMatrix();
}