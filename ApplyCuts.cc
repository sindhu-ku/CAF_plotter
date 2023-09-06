#include "ApplyCuts.h"
#include "duneanaobj/StandardRecord/StandardRecord.h"

RecoPart applyCuts(const caf::StandardRecord* sr, int nixn, int npart) {

	RecoPart recp;
        
        recp.contained = sr->common.ixn.dlp[nixn].part.dlp[npart].contained;
        recp.primary = sr->common.ixn.dlp[nixn].part.dlp[npart].primary;

        return recp;

}
RecoIxn applyCuts(const caf::StandardRecord* sr, int nixn) {

	RecoIxn recixn;
        
        recixn.skip_naninf = (!std::isnan(sr->common.ixn.dlp[nixn].vtx.x) && !std::isinf(sr->common.ixn.dlp[nixn].vtx.x) && 
                              !std::isnan(sr->common.ixn.dlp[nixn].vtx.y) && !std::isinf(sr->common.ixn.dlp[nixn].vtx.y) &&
                              !std::isnan(sr->common.ixn.dlp[nixn].vtx.z) && !std::isinf(sr->common.ixn.dlp[nixn].vtx.z));

        return recixn;

}
