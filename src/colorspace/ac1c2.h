#ifndef AC1C2_CLASSE
#define AC1C2_CLASSE
#include "colorspaceinterface.h"
#include "iostream"
namespace cs{
/**
 * @brief The AC1C2 class
 *
 * Color space create to better fit human vision
 *
 * M. J. Swain et D. H. Ballard. Color Indexing. International Journal of Computer Vision,
 * IJCV, 7(1):11–32, novembre 1991. => need better source
 *
 * A  in [0;255]
 * C1 in [-255*sqrt(3)/2;255*sqrt(3)/2]
 * C2 in [-255,255]
 *
 * getC1 : A component
 * getC2 : C1 component
 * getC3 : C2 component
 */
class AC1C2 : public ColorspaceInterface{
public:
    /**
     * @brief AC1C2 default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    AC1C2(unsigned int red=255,unsigned int green=255,unsigned int blue=255){
        name="AC1C2";
        c1Min=0.;
        c2Min=255*(-sqrt(3)/2.);
        c3Min=-255.;
        c1Max=255.;
        c2Max=255*(sqrt(3)/2.);
        c3Max=255.;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief convertFromRGB cnvert from rgb to AC1C2 space
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
        c1=(red+green+blue)/3.;
        c2=(sqrt(3.)/2.)*(double(red)-double(green));
        c3=blue-double(red+green)*0.5;

        c2=round(c2*1000.)/1000.;

    }





};
}
#endif // AC1C2_CLASSE

