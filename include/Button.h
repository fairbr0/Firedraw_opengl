#pragma once
#include <string>

class Button : {
public:
    Button();
    Button(int x, int y, int w, int h, string label, ButtonCallback callbackFunction);
    void setState(bool state);
    void setHighlighted(bool highlighted);
    bool getState();
    bool getHighlighted();
    string getLabel();
    ButtonCallback getCallbackFunction();
private:
    const int x, y, w, h;
    const string label;
    bool state;
    bool highlighted;
    const ButtonCallback callbackFunction;
}
