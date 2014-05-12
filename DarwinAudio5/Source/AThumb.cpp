/*
  ==============================================================================

    AThumb.cpp
    Created: 6 Apr 2014 12:06:22am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#include "AThumb.h"
// ===========================
// Constructor
AThumb::AThumb(AudioFormatManager& formatManager, AudioTransportSource& transportSource_)
: 
transportSouce(transportSource_),
scrollbar(false),
thumbCache(5),
thumbnail(512, formatManager, thumbCache)
{
	thumbnail.addChangeListener(this);

	addAndMakeVisible(scrollbar);
	scrollbar.setRangeLimits(viewableR);
	scrollbar.setAutoHide(false);
	scrollbar.addListener(this);


	currentPositionMark.setFill(Colours::white.withAlpha(0.85f));
	addAndMakeVisible(currentPositionMark);

}

//==========================================================================
// Deconstructor
AThumb::~AThumb()
{
	scrollbar.removeListener(this);
	thumbnail.removeChangeListener(this);
}

// ==========================================================================
// SetFile: Take in audio file and create thumbnail with waveform information
void AThumb::setFile(const File& aFile)
{
	if (aFile.existsAsFile()){
		thumbnail.setSource(new FileInputSource(aFile));
		const Range<double> newR(0.0, thumbnail.getTotalLength());
		scrollbar.setRangeLimits(newR);
		setRange(newR);

		startTimer(1000 / 40);
	}
}

//==========================================================================
// SetRange: set range of viewable area
void AThumb::setRange(Range<double> nRange)
{
	viewableR = nRange;
	scrollbar.setCurrentRange(viewableR);
	updateCursorPostion();
	repaint();
}

//==========================================================================
//Create the objects and viewable area
void AThumb::paint(Graphics& g)
{
	g.fillAll(Colours::darkgrey);
	g.setColour(Colours::lightblue);

	if (thumbnail.getTotalLength() > 0.0){
		Rectangle<int> thumbArea(getLocalBounds());
		thumbArea.removeFromBottom(scrollbar.getHeight() + 5);
		thumbnail.drawChannels(g, thumbArea.reduced(2), viewableR.getStart(), viewableR.getEnd(), 1.0f);
	}
	else {
		g.setFont(14);
		g.drawFittedText("No Audio Has Been Selected. Please Reselect File", getLocalBounds(), Justification::centred, 2);

	}
}

//==========================================================================
// If Scrollbar has moved, set new start. 
void AThumb::scrollBarMoved(ScrollBar* scrollbarhasMoved, double newRStart)
{
	if (scrollbarhasMoved == &scrollbar){
		setRange(viewableR.movedToStartAt(newRStart));
	}
}

//==========================================================================
// Set the size and bounds for the waveform container 
void AThumb::resized()
{
	scrollbar.setBounds(getLocalBounds().removeFromBottom(14).reduced(2));
}


void AThumb::changeListenerCallback(ChangeBroadcaster*)
{
	repaint();
}


void AThumb::timerCallback()
{
	if (canMoveTransport())
	{
		updateCursorPostion();
	}
	else
	{
		setRange(viewableR.movedToStartAt(transportSouce.getCurrentPosition()) - (viewableR.getLength() / 2.0));
	}
}

void AThumb::updateCursorPostion()
{
	currentPositionMark.setVisible(transportSouce.isPlaying() || isMouseButtonDown());
	currentPositionMark.setRectangle(Rectangle<float> (timeToHere(transportSouce.getCurrentPosition()) - 0.75f, 0.0f, 1.5f, (float)(getHeight() - scrollbar.getHeight())));
}


float AThumb::timeToHere(const float x) const 
{
	return getWidth() * (float)((x - viewableR.getStart()) / (viewableR.getLength()));
}

bool AThumb::canMoveTransport() const noexcept
{
	return !(transportSouce.isPlaying());
}
