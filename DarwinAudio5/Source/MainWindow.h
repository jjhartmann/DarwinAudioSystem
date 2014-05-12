/*
  ==============================================================================

    MainWindow.h
    Created: 6 Apr 2014 2:43:10pm
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
#include "GUIComponent.h"

#endif  // MAINWINDOW_H_INCLUDED


// ============================================================================
// Main Window
class MainWindow : public DocumentWindow
{
public:
	//==============================================================================
	MainWindow();
	~MainWindow();
	void closeButtonPressed();
	
};