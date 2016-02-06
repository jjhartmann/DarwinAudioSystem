/*
  ==============================================================================

    AThumb.h
    Created: 6 Apr 2014 12:06:22am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#ifndef ATHUMB_H_INCLUDED
#define ATHUMB_H_INCLUDED
#include "JuceHeader.h"




#endif  // ATHUMB_H_INCLUDED


class AThumb : 
    public Component,
    public ChangeListener,
    private Timer,
    private ScrollBar::Listener

{
public:
    AThumb(AudioFormatManager& formatManager, AudioTransportSource& transportSource_);
    ~AThumb();
    void setFile(const File& aFile);
    void setRange(Range<double> nRange);
    void paint(Graphics& g) override;
    void scrollBarMoved(ScrollBar* scrollbarMoved, double newRStart) override;
    void resized() override;
    void changeListenerCallback(ChangeBroadcaster*) override;


private:
    AudioTransportSource& transportSouce;
    ScrollBar scrollbar;

    AudioThumbnailCache thumbCache;
    AudioThumbnail thumbnail;
    Range<double> viewableR;
    DrawableRectangle currentPositionMark;



    void timerCallback() override;
    bool canMoveTransport() const noexcept;
    void updateCursorPostion();
    float timeToHere(const float x) const;
};
