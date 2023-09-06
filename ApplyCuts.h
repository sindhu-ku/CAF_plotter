#ifndef APPLYCUTS_H
#define APPLYCUTS_H

#include "duneanaobj/StandardRecord/StandardRecord.h"

struct RecoPart {
	bool contained;
        bool primary;
};
struct RecoIxn {
	bool skip_naninf;
};
        
RecoPart applyCuts(const caf::StandardRecord* sr, int nixn, int npart);
RecoIxn applyCuts(const caf::StandardRecord* sr, int nixn);
#endif // APPLYCUTS_H
