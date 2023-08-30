#include "ApplyCuts.h"

bool ApplyCuts(const caf::StandardRecord* sr, int nixn, int npart){
	bool contained = sr->common.ixn.dlp[nixn].part.dlp[npart].contained;
	bool iscc = sr->mc.nu[nixn].iscc;
	return (!contained && iscc);
}
