#include "common.h"

fp3dpoint antistereographic(const fp3dpoint& pt) {
    assert((cmprtr::compare(pt.Z(), 0)));
    fptype factor = 1/(1+pt.sqlength());
    fp3dpoint result = fp3dpoint(2*pt.X()*factor, 2*pt.Y()*factor, (pt.sqlength()-1)*factor);
    return result;
}

circle projectedCircle(fp3dpoint planeCenter, fptype radius) {
    static fp3dpoint const zeroPoint = fp3dpoint(0, 0, 0);
    fp3dpoint a, b;
    if(planeCenter == zeroPoint) {
        a = fp3dpoint(1, 0, 0) * radius;
        b = fp3dpoint(-1, 0, 0) * radius;
    } else {
        a = planeCenter + normalized(planeCenter) * radius;
        b = planeCenter + normalized(planeCenter) * (-radius);
    }
    fp3dpoint a1 = antistereographic(a), b1 = antistereographic(b);
    assert((cmprtr::compare(a1.sqlength(), 1.0)));
    assert((cmprtr::compare(b1.sqlength(), 1.0)));
    fp3dpoint center = normalized((a1+b1) * 0.5);
    fptype sp = a1 * b1;
    fptype angle = acos(sp) / 2;
    return std::make_pair<fp3dpoint, fptype>(center, angle);
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream ratios("out/ratios.txt");
    int cnt;
    fptype rad_factor, r1;
    while(!fin.eof()) {
        fptype sum_plane = 0, tot_plane, sum_sphere = 0, tot_sphere;
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
            circle projCircle = projectedCircle(currentPoint, rad_factor * (i+1));
            fp3dpoint center = projCircle.first;
            fptype sphrad = projCircle.second;
            assert((cmprtr::compare(center.sqlength(), 1.0)));
            //fout<<i+1<<" ";
            //center.print(fout);
            fptype R, phi, theta;
            R = center.length();
            phi = atan2(center.Y(),center.X());
            theta = acos(center.Z()/R);
            fout<<phi<<" "<<theta<<" "<<sphrad<<std::endl;
            sum_plane += sqr(rad_factor * j);
            sum_sphere += 2 * (1 - cos(sphrad));
        }
        tot_sphere = 2;
        tot_plane = 1;
        ratios<<"N: "<<cnt<<"; Ratio in plane: "<<(sum_plane/tot_plane)<<
            "; Ratio on sphere: "<<(sum_sphere/tot_sphere)<<std::endl;
        fout.close();
    }
    return 0;
}
