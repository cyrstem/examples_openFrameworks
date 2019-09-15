// Copyright (C) 2018 Cristobal Valenzuela
//
// This file is part of RunwayML.
//
// RunwayML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RunwayML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RunwayML.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================

// RUNWAY
// www.runwayml.com

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    black background
    ofSetBackgroundColor(0);

    width  = 600;
    height = 400;
    
//      Use the localhost and the port 57200 that we define in Runway
  ofxOscSenderSettings sendSettings;
    sendSettings.host = "127.0.0.1";
    sendSettings.port = 57100;
    sendSettings.broadcast = true;
    sender.setup(sendSettings);

    ofxOscReceiverSettings recvSettings;
    recvSettings.port =57200;
    receiver.setup(recvSettings);

//      This are the pair of body connections we want to form.
//      Try creating new ones!
    connections = {
        {"Nose", "Left_Eye"},
        {"Left_Eye", "Left_Ear"},
        {"Nose", "Right_Eye"},
        {"Right_Eye", "Right_Ear"},
        {"Nose", "Neck"},
        {"Right_Shoulder", "Right_Elbow"},
        {"Right_Elbow", "Right_Wrist"},
        {"Left_Shoulder", "Left_Elbow"},
        {"Left_Elbow", "Left_Wrist"},
        {"Right_Hip", "Right_Knee"},
        {"Right_Knee", "Right_Ankle"},
        {"Left_Hip", "Left_Knee"},
        {"Left_Knee", "Left_Ankle"}
    };
}

void ofApp::connect(){
    
}

//--------------------------------------------------------------
void ofApp::update(){

  while(receiver.hasWaitingMessages()){
        // get the next OSC message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        // if it's /data
        if(m.getAddress() == "/data"){
            //        grab the data
            string incoming = m.getArgAsString(0);
            //        parse it to JSON
            data.parse(incoming);

             humans = data["results"]["poses"];


        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Choose between drawing just an ellipse
    // over the body parts or drawing connections
    // between them. or both!
    drawParts();

}

// A function to draw humans body parts as circles
void ofApp::drawParts(){
    //parsin jason like the Processing examples
    const Json:: Value& human = data["poses"];

    for (Json::ArrayIndex i = 0; i < human.size(); i++)
    {
     ofxJSONElement keypoints = human[i];
     for (int k = 0; k < keypoints.size(); k++)
     {
         ofxJSONElement point = keypoints[k];
         float x = point[0].asFloat();
         float y = point[1].asFloat();
         ofDrawEllipse(x *width,y *height,10,10);
     }
     
    }
    
    
}
