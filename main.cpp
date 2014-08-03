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
    fptype rad_factor, r1;
    while(!fin.eof()) {
        fin>>cnt;
        if(fin.eof()) {
            break;
        }
        std::cout<<"Input: "<<cnt<<std::endl;
        fin>>r1;
        rad_factor = 1.0 / r1;
        //std::vector<fp3dpoint> points;
        char fname[100];
        sprintf(fname, "out/output%d.txt", cnt);
        std::ofstream fout(fname);
        for(int i=0; i<cnt; i++) {
            mutfp3dpoint currentPoint;
            int j;
            fptype x,y;
            fin>>j>>x>>y;
            assert(j == i+1);
            currentPoint.setX(x); currentPoint.setY(y);
            assert(rad_factor * (i+1) <= 1.0);
            fp3dpoint center = centerOfProjectedCircle(currentPoint, rad_factor * (i+1));
            //fout<<i+1<<" ";
            //center.print(fout);
            fptype R, phi, theta;
            R = center.length();
            phi = atan2(center.Y(),center.X());
            theta = acos(center.Z()/R);
            fout<<phi<<" "<<theta<<" "<<(rad_factor * (i+1))<<std::endl;
        }
        fout.close();
    }
    return 0;
}
