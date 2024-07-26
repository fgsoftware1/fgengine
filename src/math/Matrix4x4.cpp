#include "math/Matrix4x4.hpp"

Matrix4x4 Matrix4x4::Identity = []{
    Matrix4x4 m;
    for(int i = 0; i < 4; i++) {
        m.set(i, i, 1.0f);
    }
    return m;
}();

Matrix4x4 Matrix4x4::Zero = Matrix4x4();

Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data[i][j] = 0.0f;
        }
    }
}

float Matrix4x4::get(int i, int j) const
{
    return data[i][j];
}

void Matrix4x4::set(int i, int j, float value)
{
    data[i][j] = value;
}

std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}