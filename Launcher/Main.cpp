#include "Source/Launcher/Launcher.h"



int main()
{
    Launcher launcher;
    launcher.Start();

    while (true)
    {
        if (!launcher.Update())
            break;

        Sleep(10);
    }

    launcher.Stop();
}