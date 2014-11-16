#include "common.h"

#define P_FPTYPE "%.9lg"
#define S_FPTYPE "%lf"

#define SANITY_CHECKS

int main() {
#ifdef SKIP_FIRST_LINE
    scanf("%*lf %*lf %*lf");
#endif // SKIP_FIRST_LINE
    int nv, N = 0;
    fptype Ro, azim, incl, cap_r;
    mutfp3dpoint pt;
    fptype caps_area = 0;
    fptype sphere_area;
    fptype dist;
    std::vector<fp3dpoint> points;
    std::vector<fptype> radii;
    while(4 == (nv = scanf(S_FPTYPE" "S_FPTYPE" "S_FPTYPE" "S_FPTYPE,
                           &Ro, &azim, &incl, &cap_r))) {
        pt.setSpherical(Ro, azim, incl);
#ifdef SANITY_CHECKS
        fptype Ro1, azim1, incl1;
        Ro1 = pt.radius(); azim1 = pt.azimuth(); incl1 = pt.inclination();
        mutfp3dpoint pt2; pt2.setSpherical(Ro1, azim1, incl1);
        assert(cmprtr::compare(Ro1, Ro));
        assert(cmprtr::compare(pt2.X(), pt.X()));
        assert(cmprtr::compare(pt2.Y(), pt.Y()));
        assert(cmprtr::compare(pt2.Z(), pt.Z()));
#endif // SANITY_CHECKS
        points.push_back(pt);
        radii.push_back(cap_r);
        caps_area += 2 * (1 - cos(cap_r / Ro));
        sphere_area = 4;
        N++;
    }
#ifndef CHECK_OVERLAP
    fp3dpoint p1, p2;
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            p1 = points[i], p2 = points[j];
            dist = Ro * acos((p1 * p2) / (Ro * Ro));
            if(cmprtr::compare2(dist, radii[i] + radii[j]) == 1) {
                std::cout<<"Overlap: i="<<i<<"; j="<<j<<"; "<<std::endl;
                std::cout<<"dist="<<dist<<"; r_i="<<radii[i]<<"; r_j="<<radii[j]<<"; r_i+r_j="<<radii[i]+radii[j]<<std::endl;
            }
        }
    }
#endif // CHECK_OVERLAP
    std::cout<<"Number of points: "<<N<<std::endl;
    std::cout<<"Density: "<<caps_area/sphere_area<<std::endl;
    return 0;
}
