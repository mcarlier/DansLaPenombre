#include "webSample.h"
int webSample::NumWebSample = 0;
void webSample::setup(){
  NumWebSample++;
  index = NumWebSample;
  position = ofVec3f(0);
  speed = 6;
  size =(rand()%3)+2;
  susuImg.load("dot.png");
  end = false;
  timerappearance.setup(100);

}

void webSample::update(){
  if(state==2){
    update_appeared();
  }
  else if(state==1){
    update_detected();
  }
  else{
    update_rest();
  }
}

//draw sphere around the webSample.
void  webSample::drawSusu(ofShader shader,float soundeffect){
  float a = 10*size + (soundeffect*1000)*5;
  shader.begin();
  susuImg.draw(position.x-(a/2),position.y-(a/2),a,a);
  shader.end();
}

//Draw the web
void webSample::drawWeb(){
  ofSetColor(ofColor::black);
  mesh.drawWireframe();
}
void webSample::changeState(int newState){
  state = newState;
  if(state==0){
     setup_rest();
  }
  else if(state==1){
    setup_detected();
  }
  else if (state == 2){
    setup_appeared();
  }
}

void webSample::setup_rest(){
      needToReachstart = true;
}

void webSample::setup_detected(){
    needToReachstart = true;
}
void webSample::setup_appeared(){
  state_appeared = 0;
  needToReachstart = true;
}
void webSample::update_rest(){
  if(!needToReachstart){
    position.x=ofMap( ofNoise( (ofGetElapsedTimef() +(index)) ), 0, 5, 0, -700)+305;
    position.y=ofMap( ofNoise( (1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
  }
  else{
    start.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 5, 0, -700)+305;
    start.y=ofMap(ofNoise( (1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
    reachStart();
  }
}

//detected
void webSample::update_detected(){
  if(!needToReachstart){
      position.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 1, 0, -700)+570;
      position.y=ofMap(ofNoise((1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
  }
  else{
    start.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 1, 0, -700)+570;
    start.y=ofMap(ofNoise((1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
    reachStart();
  }
}

void webSample::update_appeared(){
  if(!needToReachstart){
    if(state_appeared!=0){
      position+= direction_appeared*speed;
      reachEnd_appeared();
    }
  }
  else{
    position +=tostart_appeared.normalize()*speed;
    reachStart_appeared();
  }
}
void webSample::clear(){
  mesh.clear();
  ofMeshFace t;
  currentTriangle_appeared = t;
}


//Add triangle to the mesh when the drawing is end_appeared
void webSample::addTriangle_appeared(ofMeshFace points){
  if(end_appeared.length()-points.getVertex(0).length()!=0){
    needToReachstart = true;
    tostart_appeared = points.getVertex(0)-position;
  }
  if(!end){
    mesh.addVertex(currentTriangle_appeared.getVertex(0));
    mesh.addTexCoord(currentTriangle_appeared.getTexCoord(0));
    mesh.addVertex(currentTriangle_appeared.getVertex(1));
    mesh.addTexCoord(currentTriangle_appeared.getTexCoord(1));
    mesh.addVertex(currentTriangle_appeared.getVertex(2));
    mesh.addTexCoord(currentTriangle_appeared.getTexCoord(2));
  }
  else{
    meshEnd.addVertex(currentTriangle_appeared.getVertex(0));
    meshEnd.addTexCoord(currentTriangle_appeared.getTexCoord(0));
    meshEnd.addVertex(currentTriangle_appeared.getVertex(1));
    meshEnd.addTexCoord(currentTriangle_appeared.getTexCoord(1));
    meshEnd.addVertex(currentTriangle_appeared.getVertex(2));
    meshEnd.addTexCoord(currentTriangle_appeared.getTexCoord(2));
    lastFace.clear();
    lastFace.addVertex(currentTriangle_appeared.getVertex(0));
    lastFace.addTexCoord(currentTriangle_appeared.getTexCoord(0));
    lastFace.addVertex(currentTriangle_appeared.getVertex(1));
    lastFace.addTexCoord(currentTriangle_appeared.getTexCoord(1));
    lastFace.addVertex(currentTriangle_appeared.getVertex(2));
    lastFace.addTexCoord(currentTriangle_appeared.getTexCoord(2));
    timerappearance.stop();
    timerappearance.start(false);
  }


  currentTriangle_appeared = points;
  changeStatus_appeared(1);
}

//0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
void webSample::changeStatus_appeared(int newStatus){
  if (newStatus==0){
  }
  else if (newStatus==1){
    start_appeared = currentTriangle_appeared.getVertex(0);
    end_appeared = currentTriangle_appeared.getVertex(1);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  else if (newStatus==2){
    start_appeared = currentTriangle_appeared.getVertex(1);
    end_appeared = currentTriangle_appeared.getVertex(2);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  else if (newStatus==3){
    start_appeared = currentTriangle_appeared.getVertex(2);
    end_appeared = currentTriangle_appeared.getVertex(0);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  state_appeared = newStatus;
}

//Test if the webSample excedded end_appeared position
void webSample::reachEnd_appeared(){
  ofVec3f PS,ES;
  PS = position-start_appeared;
  ES = end_appeared - start_appeared ;
  if(PS.length()>ES.length()){
     position = end_appeared;
     changeStatus_appeared((state_appeared+1)%4);
   }
}
void webSample::reachStart(){
  ofVec3f direction = start-position;
  position +=direction.normalize()*speed;
  if (ofDist(start.x,start.y,position.x,position.y)<2) {
    needToReachstart = false;
  }
}
// Test if the webSample reach her new start_appeared
void webSample::reachStart_appeared(){
  ofVec3f PS;
  PS = position-start_appeared;
  if(PS.dot(tostart_appeared) >= 0){
    needToReachstart = false;
  }
}
