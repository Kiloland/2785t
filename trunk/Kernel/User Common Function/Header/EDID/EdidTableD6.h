//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#define _EDID_D6_TYPE_SEL                               _EDID_DP_1920_1080_60HZ


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D6[] =
{
#if(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_60HZ)
#include "./EDID/EdidDp/EDID_DP_1920x1080@60.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_60HZ_HDR)
#include "./EDID/EdidDp/EDID_DP_1920x1080@60_HDR.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_60HZ_MACBOOK)
#include "./EDID/EdidDp/EDID_DP_1920x1080@60_MACBOOK.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_30HZ_144HZ_FREESYNC)
#include "./EDID/EdidDp/EDID_DP_1920x1080_FREESYNC(30,144).h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_50HZ_75HZ_FREESYNC)
#include "./EDID/EdidDp/EDID_DP_1920x1080_FREESYNC(50,75).h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_2560_1440_60HZ_DELL)
#include "./EDID/EdidDp/EDID_DP_2560x1440@60_DELL.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_2560_1440_60HZ_HDR)
#include "./EDID/EdidDp/EDID_DP_2560x1440@60_HDR.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_2560_1440_144HZ_NIVIDIA_GTX770)
#include "./EDID/EdidDp/EDID_DP_2560x1440@144_NIVIDIA_GTX770.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_30HZ_DELL)
#include "./EDID/EdidDp/EDID_DP_3840x2160@30_DELL.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ_AOC)
#include "./EDID/EdidDp/EDID_DP_3840x2160@60_AOC.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ_BENQ)
#include "./EDID/EdidDp/EDID_DP_3840x2160@60_BENQ.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ_RTK)
#include "./EDID/EdidDp/EDID_DP_3840x2160@60_RTK.h"
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ_HDR)
#include "./EDID/EdidDp/EDID_DP_3840x2160@60_HDR.h"
#endif
};

#endif
