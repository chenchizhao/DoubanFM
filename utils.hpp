#include "douban_types.h"

inline static bool compareChannels( const DoubanChannel &a, const DoubanChannel &b )
{
    return a.seq_id < b.seq_id;
}
