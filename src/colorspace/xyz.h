#ifndef XYZ_CLASSE
#define XYZ_CLASSE
#include "colorspaceinterface.h"
namespace cs{
/**
 * @brief The XYZ class
 *
 * Primary system
 *
 * N. Vandenbroucke, L. Macaire, and J.-G. Postaire.
 * Color systems coding for color image processing.
 * In International Conference on Color in Graphics and Image Processing,
 * pages 180–185, Saint-Etienne,France, October 2000
 *
 * X in [0;250.16]
 * Y in [0;255]
 * Z in [0;301.41]
 *
 * getC1 : X component
 * getC2 : Y component
 * getC3 : Z component
 */
class XYZ : public ColorspaceInterface{
public:

    /**
     * @brief XYZ default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    XYZ(unsigned int red=255, unsigned int green=255, unsigned int blue=255){
        name="xyz";
        c1Min=0.;
        c2Min=0.;
        c3Min=0.;
        c1Max=250.16;
        c2Max=255.;
        c3Max=301.41;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief convertFromRGB cnvert from rgb to XYZ color space
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
        c1=red*0.607+green*0.174+blue*0.200;
        c2=red*0.299+green*0.587+blue*0.114;
        c3=green*0.066+blue*1.116;
    }


};
}

#endif // XYZ_CLASSE

