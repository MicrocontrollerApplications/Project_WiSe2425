#ifndef _PLIB_H
#define _PLIB_H

#if defined(__18F24K22)
    #include "PLIB/plib18fxxk22.h"
#elif defined(__18F25K22)
    #include "PLIB/plib18fxxk22.h"
#elif defined(__18F26K22)
    #include "PLIB/plib18fxxk22.h"
#elif defined(__18F45K22)
    #include "PLIB/plib18fxxk22.h"
#elif defined(__18F46K22)
    #include "PLIB/plib18fxxk22.h"
#elif defined(__18F27J53)
    #include "PLIB/plib18fxxj53.h"

#else
    #error Unknown processor!
#endif

#endif  /*_PLIB_H*/
