#include <iostream>

#include "include/fgengine.h"
#include "include/math/Math.hpp"
#include "include/utils/String.hpp"
#include "include/math/Vector2.hpp"

using namespace std;

int main()
{
	string out;
	float deg = 15.0f;
	
	out = fgengine::utils::StringFormat::ToString(fgengine::math::toRadians(deg));
	cout << out << endl;

	return 0;
}