#ifndef I1I2I3_CLASSE
#define I1I2I3_CLASSE
#include "colorspaceinterface.h"
namespace cs{
/**
 * @brief The I1I2I3 class
 *
 * Statistical independent component system
 *
 * Y.-I. Ohta, T. Kanade, and T. Sakai. Color Information for Region Segmentation.
 * Computer Graphics and Image Processing, 13(3):1112–241, July 1980.
 *
 * I1 in [0;255]
 * I2 in [-127.5;127.5]
 * I3 in  [-127.5;127.5]
 *
 * getC1 : I1 component
 * getC2 : I2 component
 * getC3 : I3 component
 *
 */
class I1I2I3 : public ColorspaceInterface{
public:

    /**
     * @brief I1I2I3 default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    I1I2I3(unsigned int red=255, unsigned int green=255, unsigned int blue=255){
        name="i1i2i3";
        c1Min=0.;
        c2Min=-127.5;
        c3Min=-127.5;
        c1Max=255;
        c2Max=127.5;
        c3Max=127.5;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief convertFromRGB cnvert from rgb to I1I2I3 color space
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

        double s_rgb=red+green+blue;

        //convert from rgb to I1I2I3 color space
        c1=s_rgb/3.;
        c2=double(red)-double(blue);
        c2*=0.5;
        c3=2.*double(red)-double(green)-double(blue);
        c3*=0.25;
    }


};
}
#endif // I1I2I3

