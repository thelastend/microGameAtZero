//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "checkBox.h"
#include "checkBoxImage.h"


/**
 * @brief Construct a new CHECKBOX::CHECKBOX object
 * 
 * @param settings check box settings
 */
CHECKBOX::CHECKBOX(checkBox_ui settings)
{
    checkSettings = settings;
    checkSettings.checkBox = checkOff;
}
    

/**
 * @brief Destroy the CHECKBOX::CHECKBOX object
 * 
 */
CHECKBOX::~CHECKBOX()
{

}


/**
 * @brief This function set the checkbox status.
 * 
 * @param check if true  the checkbox is checked otherwise is not checked
 */
void CHECKBOX::changeCheck(bool check)
{
    checkSettings.check = check;
    if(check)
        checkSettings.checkBox = checkOn;
    else
        checkSettings.checkBox = checkOff;
    
}


/**
 * @brief This function returns the checkbox settings.
 * 
 * @return checkBox_ui checkbox setting structure
 */
checkBox_ui CHECKBOX::getCheckSettings()
{
    return checkSettings;
}


/**
 * @brief This function set the hidden flag of the checkbox.
 * 
 * @param hiden if true the checkbox is hidden otherwise it will be shown.
 */
void CHECKBOX::setHidden(bool hidden)
{
    checkSettings.hidden = hidden;
}


/**
 * @brief This function returns the hidden status of the checkbox.
 * 
 * @return true checkbox is hidden
 * @return false checkbox is not hidden
 */
bool CHECKBOX::getHidden()
{
    return checkSettings.hidden;
}