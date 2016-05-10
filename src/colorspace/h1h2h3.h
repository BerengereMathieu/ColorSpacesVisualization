#ifndef H1H2H3_CLASSE
#define H1H2H3_CLASSE
#include "colorspaceinterface.h"
namespace cs{
/**
 * @brief The H1H2H3 class
 *
 * Statistical independent component system
 *
 * J. P. Braquelaire and L. Brun. Comparison and optimization of methods
 * of color image quantization.
 * IEEE Transactions on Image Processing, 6(7):1048–1052, July 1997
 *
 * H1  in [0;510]
 * H2 in [-255;255]
 * H3 in [-255,255]
 *
 * getC1 : H1 component
 * getC2 : H2 component
 * getC3 : H3 component
 *
 */
class H1H2H3 : public ColorspaceInterface{
public:
    /**
     * @brief H1H2H3 default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    H1H2H3(unsigned int red=255,unsigned int green=255,unsigned int blue=255){
        name="H1H2H3";
        c1Min=0.;
        c2Min=-255.;
        c3Min=-255.;
        c1Max=510.;
        c2Max=255.;
        c3Max=255.;

        convertFromRGB(red,green,blue);

    }

    /**
    * @brief convertFromRGB convert from rgb to the H1H2H3 space
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

        //convert from rgb to H1H2H3 color space
        c1=red+green;
        c2=double(red)-double(green);
        c3=double(blue)-0.5*c1;
    }




};
};
#endif // H1H2H3_CLASSE

