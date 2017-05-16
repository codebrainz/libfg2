#include <libfg2/libfg2.h>

const int fg_major_version = FG_MAJOR_VERSION;
const int fg_minor_version = FG_MINOR_VERSION;
const int fg_micro_version = FG_MICRO_VERSION;

int fg_check_version(int maj, int min, int mic)
{
    return (
        (maj > fg_major_version) ||
        (maj == fg_major_version && min > fg_minor_version) ||
        (maj == fg_major_version && min == fg_minor_version && mic == fg_micro_version)
    );
}
