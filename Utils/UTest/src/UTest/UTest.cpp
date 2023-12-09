#include "UTest.h"

#include <stdio.h>
#include <stdlib.h>

namespace nkentsuu {
    int RunTest() {
        int32_t result = (UNIT_TEST.Run());

        LOG_TEST.Trace("Presser sur une touche pour continuer...");
        getchar();
        return (result);
    }
}