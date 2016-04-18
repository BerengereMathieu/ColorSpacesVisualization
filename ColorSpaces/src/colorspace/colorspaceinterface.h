#ifndef COLORSPACEINTERFACE
#define COLORSPACEINTERFACE
#include <stdexcept>
#include <string>
using namespace std;

namespace cs{
/**
 * @brief The ColorspaceInterface abstract class
 *
 * Main ressources for color spaces implementation :
 *  + "Mise en correspondance stereoscopique d’images couleur
 *     en presence d’occultations", phd manuscript of Sylvie Chambon
 *     Toulouse, France, december 2003
 *     Available here :
 *     https://www.irit.fr/~Alain.Crouzil/chambon/PUBLICATIONS/theseSylvieChambon.pdf
 * +  "Color stereo matching using correlation measures", Sylvie Chambon and Alain Crouzil
 *     Available here : https://www.irit.fr/~Alain.Crouzil/PUBLICATIONS/ChambonCSIMTA2004.pdf
 */
class ColorspaceInterface{
public:


    /**
     * @brief convertFromRGB cnvert from rgb to the given color space
     * @param[in] r red in [0;255]
     * @param[in] g green in [0;255]
     * @param[in] b blue in [0;255]
     */
    virtual void convertFromRGB(unsigned int red, unsigned int green, unsigned int blue)=0;

    /**
     * @brief getC1
     * @return first channel value
     */
    double getC1() const{
        return c1;
    }

    /**
     * @brief getC2
     * @return second channel value
     */
    double getC2() const{
        return c2;
    }

    /**
     * @brief getC3
     * @return third channel value
     */
    double getC3() const{
        return c3;
    }

    /**
     * @brief getColor get color
     * @param[out] c1 first channel
     * @param[out] c2 second channel
     * @param[out] c3 third channel
     */
    void getColor(double& c1,double & c2, double & c3){
        c1=getC1();
        c2=getC2();
        c3=getC3();
    }

    /**
     * @brief getNormalizedC1
     * @return normalized ([0;1]) value for first channel
     */
    double getNormalizedC1() const{
        if(c1Max - c1Min==0){
            throw runtime_error("c1Max - c1Min==0");
        }
        return (c1 - c1Min)/(c1Max - c1Min);
    }

    /**
     * @brief getNormalizedC2
     * @return normalized ([0;1]) value for second channel
     */
    double getNormalizedC2() const{
        if(c2Max - c2Min==0){
            throw runtime_error("c2Max - c2Min==0");
        }
        return (c2 - c2Min)/(c2Max - c2Min);
    }


    /**
     * @brief getNormalizedC3
     * @return normalized ([0;1]) value for first channel
     */
    double getNormalizedC3() const{
        if(c3Max - c3Min==0){
            throw runtime_error("c3Max - c3Min==0");
        }
        return (c3 - c3Min)/(c3Max - c3Min);
    }
    /**
     * @brief getNormalizedColor get normalized ([0;1]) color
     * @param[out] c1 normalized ([0;1]) value for first channel
     * @param[out] c2 normalized ([0;1]) value for second channel
     * @param[out] c3 normalized ([0;1]) value for third channel
     */
    void getNormalizedColor(double& c1,double & c2, double & c3) const{
        c1=getNormalizedC1();
        c2=getNormalizedC2();
        c3=getNormalizedC3();

    }

    /**
     * @brief getRGB return color in RGB color space
     * @param[out] red
     * @param[out] green
     * @param[out] blue
     */
    void getRGB(unsigned int red,unsigned int green, unsigned int blue) const{
        red=r;
        green=g;
        blue=b;
    }

    /**
     * @brief distance compute normalized ([0;1]) distance between two colors
     *
     * If other color is from an other color space, start by convert it
     *
     * @param[in] other an other comlor
     * @return normalized ([0;1]) distance
     */
    virtual double distance(ColorspaceInterface* other) const =0;


    /**
     * @brief normalizedDistance compute normalized ([0;1]) distance between two colors
     *
     * If other color is from an other color space, start by convert it
     * @param[in] other an other comlor
     * @return distance
     */
    virtual double normalizedDistance(ColorspaceInterface* other) const =0;


    /**
     * @brief getName get color space name
     * @return color space name
     */
    string getName() const{
        return name;
    }
protected:
    //helper functions
    /**
     * @brief checkRGB  test validty of red, green and blue value
     *
     * red must be in [0;255]
     * green must be in [0;255]
     * blue must be in [0;255]
     *
     * @param[in] r red in [0;255]
     * @param[in] g green in [0;255]
     * @param[in] b blue in [0;255]
     */
    void checkRGB(unsigned int red, unsigned int green, unsigned int blue) const{
        if(red>255) throw runtime_error("red value greater than 255");
        if(green>255) throw runtime_error("gren value greater than 255");
        if(blue>255) throw runtime_error("blue value greater than 255");
    }

    /**
     * @brief l2Norm compute l2 norm between two colors
     * @param[in] o an other color
     * @return sqrt( (c1i-c1j)^2 + (c2i-c2j)^2 + (c3i-c3j)^2 )
     */
    double l2Norm(ColorspaceInterface* o) const{
        if(name!=o->getName()){
            throw runtime_error("color from different color spaces");
        }
        return sqrt(pow(c1-o->getC1(),2)+pow(c2-o->getC2(),2) + pow(c3-o->getC3(),2));
    }

    /**
     * @brief normalizedl2Norm compute normalized distance between the two colors
     *
     * The distance is proportional to the l2 norm
     * The distance preserve proportion between each channel
     *
     * For example, channel with greater range has a more important weight      *
     * @param[in] o an other color
     * @return
     */
    double normalizedl2Norm(ColorspaceInterface *o) const{
        if(name!=o->getName()){
            throw runtime_error("color from different color spaces");
        }
        //compute normalized distance for each component
        double d1=pow(getNormalizedC1()-o->getNormalizedC1(),2);
        double d2=pow(getNormalizedC1()-o->getNormalizedC1(),2);
        double d3=pow(getNormalizedC1()-o->getNormalizedC1(),2);

        //compute weighted sum
        double w1=pow(c1Max-c1Min,2);
        double w2=pow(c2Max-c2Min,2);
        double w3=pow(c3Max-c3Min,2);
        double t=w1+w2+w3;
        w1/=t;
        w2/=t;
        w3/=t;


        return w1*d1+w2*d2+w3*d3;

    }

    double c1;/*!< first channel*/
    double c2;/*!< second channel*/
    double c3;/*!< third channel*/

    unsigned int r;/*!< red value in rgb color space*/
    unsigned int g;/*!< green value in rgb color space*/
    unsigned int b;/*!< blue value in rgb color space*/

    double c1Min;/*!< minimal possible value for c1 */
    double c1Max;/*!< maximal possible value for c1 */
    double c2Min;/*!< minimal possible value for c2 */
    double c2Max;/*!< maximal possible value for c2 */
    double c3Min;/*!< minimal possible value for c3 */
    double c3Max;/*!< maximal possible value for c3 */

    string name;/*!< color space name*/

};
}

#endif // COLORSPACEINTERFACE

