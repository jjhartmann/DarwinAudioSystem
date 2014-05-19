/*
  ==============================================================================

    MainWindow.cpp
    Created: 6 Apr 2014 2:43:10pm
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#include "MainWindow.h"





MainWindow::MainWindow()
		: DocumentWindow(	"Darwin Audio App",
							Colours::lightgrey,
							DocumentWindow::allButtons,
							true)
	{
		// Create an instance of our main content component, and add it 
		// to our window.

        setContentOwned(new GUIComponent(), true);
		centreWithSize(getWidth(), getHeight());

		setVisible(true);
        setResizable(false, false);
}

MainWindow::~MainWindow()
	{
		// (the content component will be deleted automatically, so no need to do it here)
       

	}

	//==============================================================================
void MainWindow::closeButtonPressed()
	{
		// When the user presses the close button, we'll tell the app to quit. This 
		// window will be deleted by our shutdown() method
		// 
		JUCEApplication::getInstance()->systemRequestedQuit();
	}



