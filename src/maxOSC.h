#ifndef _MAXOSC
#define _MAXOSC

#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20
#define FFT_SEND_LENGTH 256

//--------------------------------------------------------
class maxOSC  {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void drawFFT();
		void drawLogFFT();
		void printMessages();
		void printAxes(bool use_logMode);	
		void printInfo();
		void setMultiColor(float f);
		void drawMIDIbins	();
	
		void updateMidiValues();
		void setMidiDifferenceFn();
		
		void drawSpecDiff();
		ofTrueTypeFont		font;
		float freq;

		

private:
		ofxOscReceiver	receiver;

		int				current_msg_string;

		int				index;
		float			amplitudes[256][FFT_SEND_LENGTH];
		int				binIndex;
		int				fft_data_index;
		float			fft_data[128][128];
		
		float			spectral_difference[128];
		int				spectralDifferenceIndex;
		
		float			binNumber;
		
		float			midiValues[128][128];
		
		float			midiDifferenceFn[128];
		int				midiFFTbin[128];
		
		float			maxValue;
		
		int				amplitudeNumber;
		bool			outputGraphics;
		bool			midi_log_mode;
		string			msg_string;
		float			timers[NUM_MSG_STRINGS];

		int				mouseX, mouseY;
		string			mouseButtonState;

		string			octaveNames[12];
		string			axisString[128];

		int binMin ;
		int binMax ;

		float binHeight;


		int midiBinMin ;
		int midiBinMax ;
				
		bool reIndexFlag;
		bool logMode;
		bool logAmplitudeMode;
		bool midiMode;
		
		string midiString[128];
		
		float freqMin ;
		float freqMax ;
		float freqLog ;
		float logMin ;
};

#endif
