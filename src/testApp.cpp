#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("lava test");
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(true);
	ofSetVerticalSync(true);
	
	//client.setup("settings.xml", this);
	myParticles.sampleImage(2);
	moveToCenter = false;
	moveBack = false;
	paused = false;
	sampleS = 1;
	
	myMaxOSC.setup();
	svgPaths.loadFile("test6.svg");
	extractData();
	
	//Start client
	//client.start();
}

//--------------------------------------------------------------
void testApp::update(){
	
	
	//Update
	myParticles.update();
	myMaxOSC.update();
	myParticles.scaleY = (int)myMaxOSC.freq;
	
}
//--------------------------------------------------------------
void testApp::draw(){
	//Draw
	myParticles.draw();
	glPointSize(2);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	for (int i=0; i<extractedShapes.size(); i++) {
		vector<ofxVec2f> shapeA = extractedShapes[i];
		for (int j=i; j<extractedShapes.size(); j++) {
			vector<ofxVec2f> shapeB = extractedShapes[j];
			//
			for (int k=0; k<shapeA.size(); k++) {
				if (k<shapeB.size()) {
					glColor3f(1,0,0);
					glVertex2f(shapeA[k].x, shapeA[k].y);
					glVertex2f(shapeB[k].x, shapeB[k].y);
				}
			}
		}
	}
	glEnd();
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
	if (key == '['){
		//client.broadcast("[");
		--myParticles.pointSize;
		
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	if (key == ']'){
		//client.broadcast("]");
		++myParticles.pointSize;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == '>'){
		//client.broadcast(">");
		++myParticles.amount;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	if (key == '<') {
		//client.broadcast("<");
		if (myParticles.amount !=1) {
			--myParticles.amount;
		}
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == '}'){
		//client.broadcast("}");
		++sampleS;
		myParticles.sampleImage(sampleS);
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	if (key == '{') {
		//client.broadcast("{");
		--sampleS;
		myParticles.sampleImage(sampleS);
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'x') {
		//client.broadcast("x");
		++myParticles.scaleX;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'X') {
		//client.broadcast("X");
		--myParticles.scaleX;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'y') {
		//client.broadcast("y");
		++myParticles.scaleY;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'Y') {
		//client.broadcast("Y");
		--myParticles.scaleY;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'z') {
		//client.broadcast("z");
		
		++myParticles.scaleZ;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'Z') {
		//client.broadcast("Z");
		--myParticles.scaleZ;
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	
	if (key == 'c') {
		//client.broadcast("C");
		myParticles.mustMoveBack = false;
		myParticles.mustMoveToCenter = true;
		myParticles.mustMoveRandom = false;
		myParticles.mustMovePaused = false;
		
		//cout << "mC is: " << moveToCenter << "and mB is: "<< moveBack << endl;
	}
	if (key == 'r') {
		//client.broadcast("r");
		myParticles.mustMoveBack = false;
		myParticles.mustMoveToCenter = false;
		myParticles.mustMoveRandom = true;
		myParticles.mustMovePaused = false;
	}
}

void testApp::extractData()
{
	for (int i =0; i< svgPaths.shapes.size(); i++){
		vector <ofxVec2f> shapePoints;
		for (int j=0; j< svgPaths.shapes[i].pt.size(); j++){
			shapePoints.push_back(ofxVec2f(svgPaths.shapes[i].pt[j].p.x, svgPaths.shapes[i].pt[j].p.y));
		}
		extractedShapes.push_back(shapePoints);
	}
}
void testApp::extractBeziers()
{
	//	//build up our vector containing the bezier curves
	//	for (int i =0; i< svgPaths.shapes.size(); i++){
	//		for (int j=0; j< svgPaths.shapes[i].pt.size(); j++){
	//			//////////
	//			ofBeginShape();
	//			ofxSvgPointType type;
	//			ofPoint p, c1, c2;
	//			if( type == OFX_POINT ){
	//				ofVertex(p.x, p.y);
	//			}
	//			else if( type == OFX_BEZIER_POINT ){
	//				ofBezierVertex(svgPaths.shapes[i].pt[j].c1.x, svgPaths.shapes[i].pt[j].c1.y, svgPaths.shapes[i].pt[j].c2.x, svgPaths.shapes[i].pt[j].c2.y, svgPaths.shapes[i].pt[j].p.x, svgPaths.shapes[i].pt[j].p.y);
	//				//ofVertex(p3.x, p3.y);
	//			}
	//			
	//			ofEndShape(false);
	//			
	//			
	//			
	//			
	//			
	//			//////////
	//			/*
	//			 glVertex2f(svgPaths.shapes[i].pt[j].p.x, svgPaths.shapes[i].pt[j].p.y);
	//			 glVertex2f(svgPaths.shapes[i].pt[j].c1.x, svgPaths.shapes[i].pt[j].c1.y);
	//			 glVertex2f(svgPaths.shapes[i].pt[j].c2.x, svgPaths.shapes[i].pt[j].c2.y);
	//			 */
	//		}
	//		//ofSetColor(255,255,255);
	//		//svgPaths.shapes[i].draw();
	//	}
	//	glEnd();
	//	/*
	//	 glColor3f(1, 1, 1);
	//	 glBegin(GL_LINES);
	//	 for (int i=0; i<extractedShapes.size(); i++) {
	//	 vector<ofxVec2f> shapeA = extractedShapes[i];
	//	 for (int j=i; j<extractedShapes.size(); j++) {
	//	 vector<ofxVec2f> shapeB = extractedShapes[j];
	//	 //
	//	 for (int k=0; k<shapeA.size(); k++) {
	//	 if (k<shapeB.size()) {
	//	 glColor3f(1,0,0);
	//	 glVertex2f(shapeA[k].x, shapeA[k].y);
	//	 glVertex2f(shapeB[k].x, shapeB[k].y);
	//	 }
	//	 }
	//	 }
	//	 }
	//	 glEnd();
	//	 */
	//	
	//}
	//
	//	
	//	
	//	
}
//--------------------------------------------------------------
void testApp::keyReleased  (int key){
	
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
