#include <UtilFunc/PluginInc.h>
#include "Cx_FrameWndFactory.h"

Cx_FrameWndFactory::Cx_FrameWndFactory()
{
}

Cx_FrameWndFactory::~Cx_FrameWndFactory()
{
}

void Cx_FrameWndFactory::OnQuit()
{
}

bool Cx_FrameWndFactory::CreateSDIFrame()
{
    return true;
}

bool Cx_FrameWndFactory::CreateMDIFrame()
{
    return true;
}

bool Cx_FrameWndFactory::ProcessShellCommand()
{
    return true;
}
