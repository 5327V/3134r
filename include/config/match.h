#pragma once

enum struct matchColor{
    RED,
    BLUE
};

enum struct compSwitch{
    AUTON,
    DRIVER,
    DISABLED
};
extern matchColor actualMatchColor;
extern compSwitch compTime;