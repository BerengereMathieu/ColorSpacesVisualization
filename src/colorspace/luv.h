#ifndef LUV_CLASSE
#define LUV_CLASSE

#include "./colorspaceinterface.h"
#include "xyz.h"

namespace cs{
/**
 * @brief The LUV class
 *
 * Luminance-chrominance systems
 *
 * G. Sharma and H. J. Trusell. Digital Color Imaging.
 * IEEE Transactions on Image Processing, 6(7):901–932, July 1997
 *
 * Reference white in RGB : (255,255,255)
 *
 * L in [0;100]
 * u in [-131.95; 220.8]
 * b in [-139.05; 121.47]
 *
 * getC1 : l component
 * getC2 : u component
 * getC3 : v component
 */
class LUV : public ColorspaceInterface{
public:

    /**
     * @brief LUV default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    LUV(unsigned int red=255, unsigned int green=255, unsigned int blue=255){
        name="luv";
        c1Min=0.;
        c2Min=-131.95;
        c3Min=-139.05;
        c1Max=100.;
        c2Max=220.8;
        c3Max=121.47;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief createFromRGB cnvert from rgb to LUV color space
    * @param[in] r red in [0;255]
    * @param[in] g green in [0;255]
    * @param[in] b blue in [0;255]
    */
    virtual void convertFromRGB(unsigned int red, unsigned int green, unsigned int blue){
        checkRGB(red,green,blue);

        //store rgb color
        r=red;
        g=green;
        b=blue;

        //convert from rgb to xyz color space
        cs::XYZ xyz;

        //reference white for default white (r=2555, v=255 and b=255)
        double xb=xyz.getC1();
        double yb=xyz.getC2();
        double zb=xyz.getC3();

        xyz.convertFromRGB(red,green,blue);

        double l,u,v;
        double yr=xyz.getC2()/yb;

        if(yr>0.008856){
            l=116*pow(yr,1./3.)-16;
        }else{
            l=903.3*yr;
        }
        double ut=4*xyz.getC1()/(xyz.getC1()+15*xyz.getC2()+3*xyz.getC3());
        double utb=4*xb/(xb+15*yb+3*zb);
        u=13*l*(ut-utb);
        u=min(u,c2Max);
        u=max(u,c2Min);


        double vt=9*xyz.getC2()/(xyz.getC1()+15*xyz.getC2()+3*xyz.getC3());
        double vtb=9*yb/(xb+15*yb+3*zb);
        v=13*l*(vt-vtb);
        v=min(v,c3Max);
        v=max(v,c3Min);

        c1=l;
        c2=u;
        c3=v;

    }




};
}
#endif // LUV

