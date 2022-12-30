#include "utility.h"

double convert2NDC(double pos, bool isX) {
    if (isX)
        return pos / SCR_WIDTH * 2 - 1;
    else
        return 1 - pos / SCR_WIDTH * 2;
}
