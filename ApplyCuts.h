#ifndef APPLYCUTS_H
#define APPLYCUTS_H

#include "duneanaobj/StandardRecord/StandardRecord.h"

struct RecoPart {
	bool contained;
        bool primary;
};
struct RecoTrack {
	bool muon;
};
struct RecoIxn {
	bool skip_naninf;
};
        
RecoPart applyCuts(const caf::StandardRecord* sr, int nixn, int npart);
RecoTrack applyCuts(const caf::StandardRecord* sr, int nixn, int ntrack, int partid);
RecoIxn applyCuts(const caf::StandardRecord* sr, int nixn);
#endif // APPLYCUTS_H
