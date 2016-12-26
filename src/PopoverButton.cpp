#include "PopoverButton.h"
#include <string>

PopoverButton::PopoverButton()
{

}

void PopoverButton::callBack(string s)
{
    (callbacks->*nextCallBack)(s);
}
