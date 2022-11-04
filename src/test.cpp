#include "include/math/Vector3.hpp"

int main(int argc, const char * argv[]){
    fgengine::math::Vector3 v(0,1,0);
    fgengine::math::Vector3 axis(1,0,0);

	fgengine::math::Vector3 rotatedVector=v.rotateVectorAboutAngleAndAxis(90,axis);

	v.show();
	axis.show();
	rotatedVector.show();

    return 0;
}
