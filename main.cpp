#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include "deps/simple3dgeom/include/simple3dgeom.h"
using namespace simple3dgeom;

typedef double fptype;
typedef Point3D<fptype, DefaultNumberComparator<fptype, -9> > fp3dpoint;
typedef MutablePoint3D<fptype, DefaultNumberComparator<fptype, -9> > mutfp3dpoint;

fp3dpoint antistereographic(const fp3dpoint& pt) {
    assert((DefaultNumberComparator<fptype,9>::compare(pt.Z(), 0)));
    fptype factor = 1/(1+pt.sqlength());
    fp3dpoint result = fp3dpoint(2*pt.X()*factor, 2*pt.Y()*factor, (pt.sqlength()-2)*factor);
    return result;
}

fp3dpoint centerOfProjectedCircle(fp3dpoint planeCenter, fptype radius) {
    static fp3dpoint zeroPoint = fp3dpoint(0, 0, 0);
    fp3dpoint a, b;
    if(planeCenter == zeroPoint) {
        a = fp3dpoint(1, 0, 0) * radius;
        b = fp3dpoint(-1, 0, 0) * radius;
    } else {
        a = planeCenter + normalized(planeCenter) * radius;
        b = planeCenter + normalized(planeCenter) * (-radius);
    }
    fp3dpoint a1 = antistereographic(a), b1 = antistereographic(b1);
    return normalized((a1+b1) * 0.5);
}

int main() {
    std::ifstream fin("input.txt");
    int cnt;
    fptype radius;
    while(!fin.eof()) {
        fin>>cnt;
        if(fin.eof()) {
            break;
        }
        std::cout<<"Input: "<<cnt<<std::endl;
        fin>>radius;
        //std::vector<fp3dpoint> points;
        char fname[100];
        sprintf(fname, "out/output%d.txt", cnt);
        fptype rad_factor = 1/radius;
        std::ofstream fout(fname);
        for(int i=0; i<cnt; i++) {
            mutfp3dpoint currentPoint;
            fptype x,y;
            fin>>x>>y;
            currentPoint.setX(x); currentPoint.setY(y);
            currentPoint = currentPoint * rad_factor;
            fp3dpoint center = centerOfProjectedCircle(currentPoint, 1.0 * (i+1));
            fout<<i+1<<" ";
            center.print(fout);
        }
        fout.close();
    }
    return 0;
}