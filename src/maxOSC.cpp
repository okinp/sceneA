#include "maxOSC.h"

#define SAMPLING_FREQUENCY 44100
#define FOURIER_LENGTH 2048
#define FFT_SEND_LENGTH 256
#define TEXT_HEIGHT 10
//--------------------------------------------------------------
void maxOSC::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );

	current_msg_string = 0;
	index = 0;
	outputGraphics = false;	
	binIndex = 0;

	binMin = 5;
	binMax = 256;
	binNumber = binMax - binMin;
	binHeight = 10;
	amplitudeNumber = 128;//number of amplitudes shown on screen
	
	
	midiBinMin = 1;
	midiBinMax = 72;
	
	maxValue = 1.0;
	
	logMode = true;
	logAmplitudeMode = false;
	
	midiMode = false;
	
	midi_log_mode = false;
	
	reIndexFlag = false;

	ofBackground(0,0,0);
	
freqMin = binMin * SAMPLING_FREQUENCY / (float) FOURIER_LENGTH;
freqMax = binMax * SAMPLING_FREQUENCY / (float) FOURIER_LENGTH;
freqLog = log(freqMax) - log(freqMin);
logMin = log(freqMin);

setMidiDifferenceFn();

octaveNames[0] = "C ";
octaveNames[1] = "C#";
octaveNames[2] = "D ";
octaveNames[3] = "D#";
octaveNames[4] = "E ";
octaveNames[5] = "F ";
octaveNames[6] = "F#";
octaveNames[7] = "G ";
octaveNames[8] = "G#";
octaveNames[9] = "A ";
octaveNames[10]= "A#";
octaveNames[11]= "B ";

int midiBin;
for(midiBin = 0;midiBin < 128;midiBin++){
		axisString[midiBin] = octaveNames[midiBin%12]; 
		axisString[midiBin]	+=	ofToString((midiBin - midiBin%12)/12);
		}//end for
	 }

//--------------------------------------------------------------
void maxOSC::update(){
maxValue *= 0.995;


	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
			// unrecognized message: display on the bottom of the screen
	//		string msg_string;
	//		msg_string = m.getAddress();
			if (m.getAddress() == "/spec_diff_data" ){
				if( m.getArgType( 0 ) == OFXOSC_TYPE_FLOAT ){
				
				spectralDifferenceIndex++;
				
				if (spectralDifferenceIndex >= amplitudeNumber)
				spectralDifferenceIndex = 0;
				
				spectral_difference[spectralDifferenceIndex] =  m.getArgAsFloat(0);
				
				
				
				
				}//end if type FLOAT
			}//end spec diff message

			if( m.getAddress() == "/fft_data" ){
			msg_string = "FFT  DATA";
				
				index++;
				index = index % amplitudeNumber;
				for ( int i=0; i<m.getNumArgs(); i++ )
			{
					//index is the index of the fft column
				
					//bin index the index for each frequency - the rows
					binIndex = i;
			
			
			
			if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT ){
					
				
				
					float tmp_val = m.getArgAsFloat(i);
					if (i < 8){
					msg_string += "   [";
					msg_string += ofToString(binIndex);
					msg_string += "]:";
					msg_string += ofToString(tmp_val);
				
					}
					
				
					if(	tmp_val > maxValue && tmp_val > 1 && tmp_val < 1000 )
					{
					maxValue = tmp_val;
					}
					//divide by max value so we have good values for graphing
					
					if (logAmplitudeMode == false){
					amplitudes[index][binIndex] = (tmp_val/maxValue);
					}
					else{
					//check this log max amplitude scale
					amplitudes[index][binIndex] = (log(tmp_val)/log(maxValue));
					}
							
					}//end if float
								
			}//end for
			
			
	//++	msg_string += " max value";
	//++	msg_string += ofToString(maxValue);
				if (midiMode == true){
					//updateMidiValues();
					}
			}//end if  \fft_data
			cout << "from Max" << msg_string <<endl;	
			 freq = msg_string[1];
		///
		
			// add to the list of strings to display
	/*
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
	*/	

	}//end while

	binNumber = binMax - binMin;	
	
		
freqMin = binMin * SAMPLING_FREQUENCY / (float) FOURIER_LENGTH;
freqMax = binMax * SAMPLING_FREQUENCY / (float) FOURIER_LENGTH;
freqLog = log(freqMax) - log(freqMin);
logMin = log(freqMin);



}


//--------------------------------------------------------------
void maxOSC::draw(){
/*
if (midiMode == false){

if (logMode == false){
	drawFFT();
	}
	else{
	drawLogFFT();
	}
	printAxes(logMode);
	
	}
	else{
	//MIDI mode
	drawMIDIbins();
	}
	
	drawSpecDiff();
	printInfo();
*/
}

void maxOSC::printMessages(){
	string buf;
	buf = "listening for osc messages on port" + ofToString( PORT );
	ofDrawBitmapString( buf, 10, 20 );

	/*
	for ( int i=0; i<NUM_MSG_STRINGS; i++ )
	{
	ofDrawBitmapString( msg_strings[i], 10, 40+15*i );
	}
	*/
}

void maxOSC::printAxes(bool use_logMode){	
	/*
	ofSetColor(255,255,255);
	
	if (logMode == false){
		for ( int i=binMin; i<binMax; i+=8 )
	{
int frequency = (int)	((i+0.5) * SAMPLING_FREQUENCY / (float) FOURIER_LENGTH);
		//draw red markers of exact position
		//i = binmax - 1 gives zero
		ofSetColor(255,0,0);
		ofRect( ofGetWidth()-12, (int) ( ( (float) screenHeight/ (float) binNumber) * (binMax-i-1) ) + (binHeight/2) , 12, 2);
		
		ofSetColor(255,255,255);
	ofDrawBitmapString( ofToString(frequency), ofGetWidth()-40, (int) ( ( (float) screenHeight/ (float) binNumber) * (binMax-i-1) ) + (binHeight/2));
	}
	}//end if not log
	else{
	for (int y=0;y<12;y++){
	//frequency at that exact position
	float yFreq = (int) (freqMin * pow((freqMax/freqMin),(y/(double)12)) );//tmpBin * SAMPLING_FREQUENCY / FOURIER_LENGTH;
		ofSetColor(255,0,0);
		ofRect( ofGetWidth()-12, (int)  ( (float) screenHeight * (12 - y) / (float) 12 ) , 12, 2);
		ofSetColor(255,255,255);
	ofDrawBitmapString( ofToString((int)yFreq), ofGetWidth()-40, (int) ((TEXT_HEIGHT/2) + ( (float) screenHeight * (12 - y) / (float) 12 )) );

	}
	
	}//end else
	*/
}

void maxOSC::printInfo(){	
	ofSetColor(255,255,255);
	string myString = "Max Value: ";
	myString += ofToString(maxValue);
	myString += "    min bin: ";
	myString += ofToString(binMin);
	myString += "    max bin: ";
	myString += ofToString(binMax);
	myString += "    Log mode: ";
	myString += ofToString(logMode);
	myString += "    Log Amp mode: ";
	myString += ofToString(logAmplitudeMode);

	ofDrawBitmapString( myString  , 10, ofGetHeight() - 10);	

	myString = "Midi mode: ";
	myString += ofToString(midiMode);
	myString += "   Midi [48]: ";
	myString += ofToString(midiValues[index][48]);

	myString += "Midi log mode: ";
	myString += ofToString(midi_log_mode);	
	

	ofDrawBitmapString( myString  , 10, ofGetHeight() - 30);
	
	
	ofDrawBitmapString( msg_string  , 10, 30);
	
}

//--------------------------------------------------------------
void maxOSC::keyPressed  (int key){

	if (key == OF_KEY_UP){
	binMin++;
	binMax++;

	}

	if (key == OF_KEY_DOWN && binMin > 0){
	binMin--;
	binMax--;

	}		


	if (key == OF_KEY_RIGHT && binMax > binMin + 1){
	binMax--;
	}		

	if (key == OF_KEY_LEFT && binMax < 256){
	binMax++;
	}		

	if (key == 'L' || key == 'l'){
	logMode = !logMode;
	}

	if (key == 'p' || key == 'P'){
	logAmplitudeMode = !logAmplitudeMode;
	}

	if (key == 'm' || key == 'M'){
	midiMode = !midiMode;
	}
		
	if (key == 'x' || key == 'X'){
	midi_log_mode = !midi_log_mode;
	}
		

if ((key == '=' || key == '+') && amplitudeNumber < 248){
	amplitudeNumber += 8;
	}

if ((key == '-' || key == '_') && amplitudeNumber > 12){
	amplitudeNumber -= 8;
	}		

}


void maxOSC::drawFFT	(){
	
	/*
int width = (int) (screenWidth/ (float) amplitudeNumber);

float height = ((float) screenHeight/ (float) binNumber);
binHeight = height;

for (int Xvalue = 0;Xvalue < amplitudeNumber; Xvalue++){
//noteIndex is the binIndex value
	for (int noteIndex = binMin; noteIndex < binMax; noteIndex++){

		int Xindex = (index-Xvalue+amplitudeNumber)%amplitudeNumber;

		ofFill();	
	//	int	amplitudeColor = min(255,(int) (255 * amplitudes[Xindex][noteIndex]));
	//	ofSetColor(0, amplitudeColor, 0);
		setMultiColor( amplitudes[Xindex][noteIndex]);
		ofRect(width*(amplitudeNumber - Xvalue-1),((binMax-noteIndex-1)*height),width,(int)height);//60**
	
		}
	}
	
//	ofSetColor(200,0,0);
}

void maxOSC::updateMidiValues(){

int fftBin = 0;
	
for (int midiBin = 0;midiBin<128;midiBin++){
//code now done in set up routine
	
	midiValues [index][midiBin] = (midiDifferenceFn[midiBin] * amplitudes[index][midiFFTbin[midiBin]+1]) 
									+ ((1-midiDifferenceFn[midiBin]) * amplitudes[index][midiFFTbin[midiBin]]);
	
//	midiValues [index][midiBin] = (difference * amplitudes[index][fftBin+1]) 
//									+ ((1-difference) * amplitudes[index][fftBin]);
					
													/*
	midiString[midiBin] = "F: ";				
	midiString[midiBin] += ofToString(frequency);
	midiString[midiBin] += " result: ";				
	midiString[midiBin] += ofToString(midiValues[index][midiBin]);												
	midiString[midiBin] +=" diff [";
	midiString[midiBin] += ofToString(midiBin);
	midiString[midiBin] += "] = ";
	midiString[midiBin] += ofToString(1-difference);
	midiString[midiBin] += " Low f: ";
	midiString[midiBin] += ofToString(binFrequency);
	midiString[midiBin] += " :+: ";
	midiString[midiBin] += ofToString(amplitudes[index][fftBin]);	
	midiString[midiBin] += " top f: ";
	midiString[midiBin] += ofToString(nextBinFrequency);	
	midiString[midiBin] += " := ";
	midiString[midiBin] += ofToString(amplitudes[index][fftBin+1]);		
							
	
	}//end for
	*/
}

void maxOSC::setMultiColor(float amplitude){
		//black, green, yellow, red
		//red scaled between 0.5 and 1
		//green between 0 and rising to max at 0.5 holding as red rises then scale down
		if (amplitude > 1)
		amplitude = 1;
		
		float red = max((double) 0, amplitude - 0.5);
		red /= 0.5;
		
		float green = min((double) 1, amplitude/0.75); 
		
		if (amplitude > 0.65){
		green = (1 - amplitude)/0.35;
		}
		
//		int	amplitudeColor = min(255,(int) (255 * amplitudes[Xindex][noteIndex]));
		ofSetColor((int)(red*255), (int)(green*255), 0);
}



void maxOSC::drawMIDIbins	(){
/*
int width = (int) (screenWidth/ (float) amplitudeNumber);

int midiBinNumber = midiBinMax - midiBinMin;

float height = ((float) screenHeight/ (float) midiBinNumber);
binHeight = height;

for (int Xvalue = 0;Xvalue < amplitudeNumber; Xvalue++){
//noteIndex is the binIndex value
	for (int midiBin = midiBinMin; midiBin < midiBinMax; midiBin++){

		int Xindex = (index-Xvalue+amplitudeNumber) % amplitudeNumber;

		ofFill();	
//	ofSetColor((20*Xvalue)%255,0,100);
	setMultiColor(midiValues[Xindex][midiBin]);
//ofRect(10*Xvalue,100+Xvalue,100,100);
	ofRect(width*(amplitudeNumber - Xvalue -1) , (int)((midiBinMax-1 - midiBin)*height), width, (int) height );//60**
		
		ofSetColor(255,255,255);

		ofDrawBitmapString(axisString[midiBin], screenWidth - 100, (int)((midiBinMax - midiBin)*height - 4));
		
/*
		ofSetColor(200,255,255);
		string freqString = ofToString(440 * pow(2 , (midiBin - 57)/(float)12  ));
		ofDrawBitmapString(freqString, screenWidth - 660, (int)((midiBinMax - midiBin)*height - 1));
		
		ofSetColor(200,255,255);
		string newString = ofToString(midiValues[index][midiBin]);
		ofDrawBitmapString(newString, screenWidth - 500, (int)((midiBinMax - midiBin)*height - 1));
*/
//	ofSetColor(200,0,0);

//info on the difference function - we can call this in setup though
//	ofDrawBitmapString( midiString[midiBin]  , 100, (int)((midiBinMax-1 - midiBin)*ofGetHeight()/((float)midiBinMax-midiBinMin) ) );	
		//}
	//}
	
}



void maxOSC::drawLogFFT	(){

/*

//int width = (int) (screenWidth/ (float) amplitudeNumber);

int lastHeight = 0;

for (int Xvalue = 0;Xvalue < amplitudeNumber; Xvalue++){

	int Xindex = (index-Xvalue+amplitudeNumber)%amplitudeNumber;
		
	//incremental - try using the bins individually first
for (int tmpBin = binMin;tmpBin < binMax;tmpBin++){

	float binFreq = (tmpBin+0.5) * SAMPLING_FREQUENCY / FOURIER_LENGTH;
//	float binHeight = screenHeight * (log(binFreq) - logMin) / freqLog; 
	
	float interBinHeight = abs((int)binHeight - lastHeight);
	
	
	
		ofFill();	
//		int	amplitudeColor = min(255,(int) (255 * amplitudes[Xindex][tmpBin]));
//		ofSetColor(0, amplitudeColor, 0);
		setMultiColor( amplitudes[Xindex][tmpBin]);
			//previous bin height used =  (int)( screenHeight / (float) binMax ) )
		ofRect(width*(amplitudeNumber - Xvalue-1), screenHeight - (int) binHeight , width,(int)interBinHeight);
		
		lastHeight = (int)binHeight;
		
	}//end for bin number		
}//end for x value
*/
 
}

void maxOSC::drawSpecDiff(){
/*	float width = screenWidth / (float) amplitudeNumber;
	
	for (int Xvalue = 0;Xvalue < amplitudeNumber; Xvalue++){
	
	int Xindex = (spectralDifferenceIndex-Xvalue+amplitudeNumber) % amplitudeNumber;
	int previousIndex = (Xindex+amplitudeNumber-1) % amplitudeNumber;
	ofSetColor(55,100,255);
	int scale_factor = 1.3;
	ofLine((int) (width*(amplitudeNumber - Xvalue - 1)), screenHeight - (scale_factor*spectral_difference[previousIndex]), 
			(int) (width*(amplitudeNumber - Xvalue)), screenHeight - (scale_factor*spectral_difference[Xindex]) );
	
	}
*/
 }


//--------------------------------------------------------------
void maxOSC::mouseMoved(int x, int y ){



}

//--------------------------------------------------------------
void maxOSC::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void maxOSC::mousePressed(int x, int y, int button){



}

//--------------------------------------------------------------
void maxOSC::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void maxOSC::windowResized(int w, int h){


}


void maxOSC::setMidiDifferenceFn(){

int fftBin = 0;
	
for (int midiBin = 0;midiBin<128;midiBin++){

	float frequency = 440 * pow(2 , (midiBin - 57)/(float)12  );//frequency corresonding to current MIDI bin
	
	while (		((fftBin+1.5) *  SAMPLING_FREQUENCY / FOURIER_LENGTH ) < frequency){
	//find the lower bin so mid frequency is below the MIDI frequency we want
	fftBin++;
	}

	float binFrequency = ( (fftBin+0.5) *  SAMPLING_FREQUENCY / (float) FOURIER_LENGTH );
	//binF = frequency of lower bin
	
	float nextBinFrequency = ( (fftBin+1.5) *  SAMPLING_FREQUENCY / (float) FOURIER_LENGTH );	
	float difference = 0;
if (midi_log_mode == false){	
	midiDifferenceFn[midiBin] =  ((frequency - binFrequency) *  FOURIER_LENGTH / (float) SAMPLING_FREQUENCY) ;
	}
	else{
	midiDifferenceFn[midiBin] =  (log(frequency) - log(binFrequency)) / (log(nextBinFrequency) - log(binFrequency));
		}

midiFFTbin[midiBin] = fftBin;
	
	}//end for

}
