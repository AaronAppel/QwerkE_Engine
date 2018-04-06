#include "Debugger.h"
#include "../Shared_Generic/Utilities/PrintFunctions.h"

Debugger::Debugger()
{
}

Debugger::~Debugger()
{
}

void Debugger::ToggleConsole()
{
    m_ConsoleIsOpen = !m_ConsoleIsOpen;
    if (m_ConsoleIsOpen)
    {
        ConsolePrint("\nConsole opened!");
    }
    else
    {
        ConsolePrint("\nConsole closed!");
    }
}

void Debugger::SetConsoleVisible(bool visibility)
{
    m_ConsoleIsOpen = visibility;
    if (m_ConsoleIsOpen)
    {
        ConsolePrint("\nConsole opened!");
    }
    else
    {
        ConsolePrint("\nConsole closed!");
    }
}