#include "PopoverButton.h"
#include <string>

PopoverButton::PopoverButton()
{

}

//change the callback function to take a string as input
void PopoverButton::callBack(string s)
{
    (callbacks->*nextCallBack)(s);
}
