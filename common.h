#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <utility>
#include "deps/simple3dgeom/include/simple3dgeom.h"
using namespace simple3dgeom;

typedef double fptype;
typedef DefaultNumberComparator<fptype, -7> cmprtr;
typedef Point3D<fptype, cmprtr > fp3dpoint;
typedef MutablePoint3D<fptype, cmprtr > mutfp3dpoint;
typedef std::pair<fp3dpoint, fptype> circle;

#endif // COMMON_H_INCLUDED
