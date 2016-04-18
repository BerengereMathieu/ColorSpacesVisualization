#ifndef YC1C2_CLASSE
#define YC1C2_CLASSE
#include "colorspaceinterface.h"
#include "iostream"
namespace cs{
/**
 * @brief The YC1C2 class
 *
 * Color space create to better fit human vision
 *
 * T. Carron. Segmentation d’images couleur dans la base Teinte Luminance Saturation :
 * approche numerique et symbolique. These de doctorat, Universite de Savoie, France, d́ecembre 1995.
 *
 * Y  in [0 ; 255]
 * C1 in [-255 ; 255]
 * C2 in [-255*sqrt(3)/2;255*sqrt(3)/2]
 *  *
 * getC1 : Y component
 * getC2 : C1 component
 * getC3 : C2 component
 */
class YC1C2 : public ColorspaceInterface{
public:
    /**
     * @brief YC1C2 default constructor
     *
     * Default color is white (in RGB color space : 255,255,255)
     *
     * @param[in] red
     * @param[in] green
     * @param[in] blue
     */
    YC1C2(unsigned int red=255, unsigned int green=255, unsigned int blue=255){
        name="YC1C2";
        c1Min=0.;
        c2Min=-255.;
        c3Min=255*(-sqrt(3)/2.);
        c1Max=255.;
        c2Max=255.;
        c3Max=255*(sqrt(3)/2.);

        convertFromRGB(red,green,blue);
    }

    /**
    * @brief convertFromRGB cnvert from rgb to YC1C2 color space
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
        c2=red-double(green+blue)*0.5;
        c2=round(c2*1000.)/1000.;
        c3=(sqrt(3.)/2.)*(double(blue)-double(green));


    }



    /**
    * @brief distance compute normalized ([0;1]) distance between two colors
    *
    * If other color is from an other color space, start by convert it
    *
    *  distance = l2 norm
    * @param[in] other an other color
    * @return normalized ([0;1]) distance
    */
    virtual double distance(ColorspaceInterface* other) const{
        YC1C2* o;
        if(other->getName()!=name){
            //convert to right color space
            unsigned red,green,blue;
            other->getRGB(red,green,blue);
            o=new YC1C2();
            o->convertFromRGB(red,green,blue);

        }else{
            o=(YC1C2*)other;
        }

        double d=l2Norm(o);
        delete o;
        return d;
    }


    /**
    * @brief normalizedDistance compute normalized ([0;1]) distance between two colors
    *
    * If other color is from an other color space, start by convert it
    * @param[in] other an other color
    * @return distance
    */
    virtual double normalizedDistance(ColorspaceInterface* other) const{

        YC1C2* o;
        if(other->getName()!=name){
            //convert to right color space
            unsigned red,green,blue;
            other->getRGB(red,green,blue);
            o=new YC1C2();
            o->convertFromRGB(red,green,blue);
        }else{
            o=(YC1C2*)other;
        }


        double d=normalizedl2Norm(o);
        delete o;
        return d;
    }



};
}
#endif // YC1C2_CLASSE

