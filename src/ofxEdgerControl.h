#pragma once

#define CAMIP "http://10.11.12.13"

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "FrameTask.h"
#include "StatusTask.h"
#include "DownloaderTask.h"


class ofxEdgerControl
{
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    void toggleCapture();
    
    string getCamState() {return camState;}
    
    void newState(int & i);
    void newFlag(int & i);
    void newLevel(int & i);
    
    template <typename ListenerClass, typename ListenerMethod>
    void addDownloadStartedListener(ListenerClass *listener, ListenerMethod method) {
        ofAddListener(captureDownloader.downloadStarted, listener, method);
    }
    template <typename ListenerClass, typename ListenerMethod>
    void addDownloadProgressListener(ListenerClass *listener, ListenerMethod method) {
        ofAddListener(captureDownloader.downloadProgress, listener, method);
    }
    template <typename ListenerClass, typename ListenerMethod>
    void addDownloadFinishedListener(ListenerClass *listener, ListenerMethod method) {
        ofAddListener(captureDownloader.downloadFinished, listener, method);
    }
    
    void downloadStart(float & i);
    void downloadFinish(string & file);
    void downloadProgress(float & i);
    
    void onGuiEvent(ofxUIEventArgs& e);
    
    void setGuiVisible(bool visible);
    void toggleGuiVisible();
    
private:
    
    FrameTask frameTask;
    StatusTask cameraStatus;
    DownloaderTask captureDownloader;
    
    void setupUI();
    ofxUISuperCanvas* ui;
    ofxUITextArea* uiStatus;
    
    deque<string> triggerQue;
    deque<string> saveQue;
    string camState, pCamState;
    float saveProgress;
    float loadProgress;
    
    float desiredFramerate, desiredWidth, desiredHeight;
    float desiredISO, desiredShutter, desiredDuration;
    float preTrigger;
    
    bool capture, configure, download;

    bool visible;
};
