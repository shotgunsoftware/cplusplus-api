//******************************************************************************
// Copyright (c) 2009 Tippett Studio. All rights reserved.
// $Id$ 
//******************************************************************************

#include <Shotgun/utils.h>

namespace Shotgun {

// *****************************************************************************
std::string tolower(const std::string& s)
{
    std::string ss(s);
    std::transform(s.begin(), s.end(), ss.begin(), ::tolower);
    return ss;
}


// *****************************************************************************
std::string toupper(const std::string& s)
{
    std::string ss(s);
    std::transform(s.begin(), s.end(), ss.begin(), ::toupper);
    return ss;
}


}  //  End namespace Shotgun
