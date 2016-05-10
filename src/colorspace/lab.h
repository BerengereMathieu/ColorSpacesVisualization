#ifndef LAB_CLASSE
#define LAB_CLASSE


#include "./colorspaceinterface.h"
#include "xyz.h"

#include <iostream>
namespace cs{
/**
 * @brief The LAB class
 *
 * Luminance-chrominance systems
 *
 * G. Sharma and H. J. Trusell. Digital Color Imaging.
 * IEEE Transactions on Image Processing, 6(7):901–932, July 1997
 *
 * Reference white in RGB : (255,255,255)
 *
 * L in [0;100]
 * a in [-137.72; 96.84]
 * b in [-99.23; 115.65]
 *
 * getC1 : l component
 * getC2 : a component
 * getC3 : b component
 */
class LAB : public ColorspaceInterface{
public:

    /**
     * @brief LAB default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    LAB(unsigned int red=255, unsigned int green=255, unsigned int blue=255){
        name="Lab";
        c1Min=0.;
        c2Min=-137.72;
        c3Min=-99.23;
        c1Max=100.;
        c2Max=96.84;
        c3Max=115.65;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief createFromRGB cnvert from rgb to LAB color space
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

        double l,a,b;
        double yr=xyz.getC2()/yb;

        if(yr>0.008856){
            l=116*pow(yr,1./3.)-16;
        }else{
            l=903.3*yr;
        }
        a=500*(f(xyz.getC1()/xb) - f(xyz.getC2()/yb) );
        a=min(a,c2Max);
        a=max(a,c2Min);


        b=500*(f(xyz.getC2()/yb) - f(xyz.getC3()/zb));
        b=min(b,c3Max);
        b=max(b,c3Min);

        c1=l;
        c2=a;
        c3=b;

    }


private:
    double f(double x){
        if(x>0.008856){
            return pow(x,1./3.);
        }else{
            return 7.787*x+16./116.;
        }
    }

};
}

#endif // LAB

