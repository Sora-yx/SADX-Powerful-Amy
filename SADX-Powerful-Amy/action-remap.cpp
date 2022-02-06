#include "pch.h"

Buttons BounceButton = Buttons_B;
Buttons LightDashButton = Buttons_Y;
Buttons SpinDashButton = Buttons_X;
Buttons HammerJumpButton = Buttons_B;
Buttons HammerAttackButton = Buttons_Y;


void ActionRemap_Config(const IniFile* config)
{
    BounceButton = (Buttons)config->getInt("Controller", "BounceButton", Buttons_B);
    LightDashButton = (Buttons)config->getInt("Controller", "LightDashButton", Buttons_Y);
    SpinDashButton = (Buttons)config->getInt("Controller", "SpinDashButton", Buttons_X);
    HammerJumpButton = (Buttons)config->getInt("Controller", "HammerJumpButton", Buttons_B);
    HammerAttackButton = (Buttons)config->getInt("Controller", "HammerAttackButton", Buttons_Y);
}

void init_ActionRemap() {
    if (HammerAttackButton > 0) {    
        WriteData((Buttons**)0x489561, &HammerAttackButton);       
        WriteData((Buttons**)0x485806, &HammerAttackButton);        
        WriteData((Buttons**)0x4894CF, &HammerAttackButton);

    }

    if (HammerJumpButton > 0) {
        WriteData((Buttons**)0x4857b6, &HammerJumpButton);
    }

 
    return;
}