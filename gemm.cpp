#include <vector>
#include <iostream>

struct Matrix
{
    size_t h_, w_;
    std::vector<std::vector<float>> m_;

    Matrix(size_t h, size_t w)
        : h_(h), w_(w), m_(h_)
    {
        for(auto& l : m_)
        {
            l.resize(w_);
            std::fill(l.begin(), l.end(), 0);
        }
    }

    Matrix(std::vector<std::vector<float>> const& d)
        : h_(d.size()), w_(d[0].size()), m_(d)
    {
    }

    std::vector<float> const& operator [] (size_t lnum) const
    {
        return m_[lnum];
    }

    std::vector<float>& operator [] (size_t lnum)
    {
        return m_[lnum];
    }


    static Matrix mul(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix c(lhs.h_, rhs.w_);

        for (int i = 0 ; i < lhs.h_; i++)
            for (int j = 0 ; j < rhs.w_; j++)
            {
                float s = 0;
                for (int k = 0 ; k < rhs.h_; k++)
                {
                    s += lhs[i][k] * rhs[k][j];
                    //std:: cout << "{" << i << ", " << j << ", " << k << "}" << (*this)[i][k] << std::endl;
                    //std:: cout << "{" << i << ", " << j << ", " << k << "}" << rhs[k][j] << std::endl;
                    //std:: cout << "{" << i << ", " << j << ", " << k << "}" << c << std::endl;
                }
                c[i][j] = s;
            }
        return c;
    }

    Matrix operator+(const Matrix& rhs) const
    {
        Matrix c(h_, rhs.w_);

        for (int i = 0 ; i < h_; i++)
            for (int j = 0 ; j < rhs.w_; j++)
            {
                c[i][j] = (*this)[i][j] + rhs[i][j];
            }
        return c;
    }


    Matrix operator*(const Matrix& rhs) const
    {
        return mul(*this, rhs);
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix const& m)
    {
        for (int i = 0 ; i < m.h_; i++)
        {
            out << m[i][0];
            for (int j = 1 ; j < m.w_; j++)
            {
                std::cout << ", " << m[i][j];
            }
            out << "\n";
        }
        return out;
    }
};


int main()
{
    {
        Matrix a({ {  0,  1,  2,  3,  4,  5,  6,  7},
                {  8,  9, 10, 11, 12, 13, 14, 15},
                { 16, 17, 18, 19, 20, 21, 22, 23},
                { 24, 25, 26, 27, 28, 29, 30, 31},
                { 32, 33, 34, 35, 36, 37, 38, 39},
                { 40, 41, 42, 43, 44, 45, 46, 47},
                { 48, 49, 50, 51, 52, 53, 54, 55},
                { 56, 57, 58, 59, 60, 61, 62, 63}});

        Matrix b({ { 42,  6, 40, 37, 42, 65, 61, 79},
                { 27, 96, 20, 12, 42, 46, 88, 22},
                { 51, 13, 20, 10,  4,  9, 40, 12},
                { 93,  1, 89, 51, 51, 74, 56, 74},
                { 22, 62, 34, 96, 36, 32, 84, 57},
                { 57, 92, 74, 99, 21, 25, 90, 86},
                { 31, 95, 73, 45, 70, 45, 99, 40},
                { 49, 88,  7, 33, 65, 37, 80, 51} });

        Matrix expected({
            { 1310,  2019,  1320,  1565,  1327,  1068,  2276,  1523 },
            { 4286,  5643,  4176,  4629,  3975,  3732,  7060,  4891 },
            { 7262,  9267,  7032,  7693,  6623,  6396, 11844,  8259 },
            {10238, 12891,  9888, 10757,  9271,  9060, 16628, 11627 },
            {13214, 16515, 12744, 13821, 11919, 11724, 21412, 14995 },
            {16190, 20139, 15600, 16885, 14567, 14388, 26196, 18363 },
            {19166, 23763, 18456, 19949, 17215, 17052, 30980, 21731 },
            {22142, 27387, 21312, 23013, 19863, 19716, 35764, 25099 } });

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        Matrix c = a * b;
        std::cout << "c = a * b = " << c << std::endl;

        for(int i = 0; i < c.h_; i++)
            for(int j = 0; j < c.w_; j++)
                if (c[i][j] != expected[i][j])
                    std::cout << "[" << i << ", " << j << "] = " << c[i][j] << " expected " << expected[i][j] << std::endl;


        Matrix a0({ {  0,  1,  2,  3 },
                    {  8,  9, 10, 11 },
                    { 16, 17, 18, 19 },
                    { 24, 25, 26, 27 }} );

        Matrix a1({ {  4,  5,  6,  7 },
                    { 12, 13, 14, 15 },
                    { 20, 21, 22, 23 },
                    { 28, 29, 30, 31 }} );

        Matrix a2({ { 32, 33, 34, 35 },
                    { 40, 41, 42, 43 },
                    { 48, 49, 50, 51 },
                    { 56, 57, 58, 59 }});

        Matrix a3({ { 36, 37, 38, 39 },
                    { 44, 45, 46, 47 },
                    { 52, 53, 54, 55 },
                    { 60, 61, 62, 63 }});

        Matrix b0({ { 42,  6, 40, 37},
                    { 27, 96, 20, 12},
                    { 51, 13, 20, 10},
                    { 93,  1, 89, 51}});
        Matrix b2({ { 42, 65, 61, 79},
                    { 42, 46, 88, 22},
                    {  4,  9, 40, 12},
                    { 51, 74, 56, 74}});

        Matrix b1({ { 22, 62, 34, 96 },
                    { 57, 92, 74, 99 },
                    { 31, 95, 73, 45 },
                    { 49, 88,  7, 33 } });

        Matrix b3({ { 36, 32, 84, 57},
                    { 21, 25, 90, 86},
                    { 70, 45, 99, 40},
                    { 65, 37, 80, 51} });


        Matrix c4(8, 8);
        Matrix c0 = a0 * b0  + a1 * b1;
        Matrix c1 = a0 * b2  + a1 * b3;
        Matrix c2 = a2 * b0  + a3 * b1;
        Matrix c3 = a2 * b2  + a3 * b3;
        std::cout << "c0 = " << c0 << std::endl;
        std::cout << "c1 = " << c1 << std::endl;
        std::cout << "c2 = " << c2 << std::endl;
        std::cout << "c3 = " << c3 << std::endl;

        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                c4[0* 4 + i][ 0 * 4 + j] = c0[i][j];

        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                c4[0* 4 + i][ 1 * 4 + j] = c1[i][j];

        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                c4[1* 4 + i][ 0 * 4 + j] = c2[i][j];

        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                c4[1* 4 + i][ 1 * 4 + j] = c3[i][j];

        std::cout << "c4 = " << c4 << std::endl;
    }

    {
        Matrix a_8x9(
        {{ 27, 40, 30, 23, 48, 24, 83, 89, 98},
        { 81, 22, 14,  1, 98,  5, 44,  2, 56},
        { 43, 85, 46, 39, 83, 37, 93, 95, 38},
        { 13, 56, 99, 44, 21, 41, 75, 25, 39},
        { 63, 64, 85, 99, 94,  8,  7, 85, 88},
        { 73,  8, 18,  5, 56, 61, 36, 39, 92},
        { 96,  2, 82, 68,  7, 22, 56, 53, 93},
        { 64, 38, 32, 48, 58,  5, 86, 84, 46} });


        Matrix b_9x8(
        {{ 61, 64, 99, 32, 71, 94, 21, 40 },
        { 70, 22,  9, 92, 77, 40, 93, 25 },
        { 87, 63, 54,  8, 15, 57,  5, 48 },
        { 79,  7, 49, 23, 36, 46,  5,  4 },
        { 52, 28, 83, 65, 61, 28, 55,  8 },
        { 59, 31, 14, 92, 60, 55,  6, 67 },
        { 97,  5, 50, 96, 41, 33, 16, 18 },
        { 52, 48, 41,  9, 74, 54, 44, 63 },
        {  2, 92, 88, 85, 24, 56, 86, 15 }});

        Matrix c_8x8 = a_8x9 * b_9x8;

        Matrix a0_4x4(
        {{ 27, 40, 30, 23},
        { 81, 22, 14,  1},
        { 43, 85, 46, 39},
        { 13, 56, 99, 44}});

        Matrix a1_4x4(
        {{ 48, 24, 83, 89},
        { 98,  5, 44,  2},
        { 83, 37, 93, 95},
        { 21, 41, 75, 25} });

        Matrix a2_4x4(
        {{ 63, 64, 85, 99},
        { 73,  8, 18,  5},
        { 96,  2, 82, 68},
        { 64, 38, 32, 48} });

        Matrix a3_4x4(
        {{ 94,  8,  7, 85},
        { 56, 61, 36, 39},
        {  7, 22, 56, 53},
        { 58,  5, 86, 84} });

        Matrix ar_8x1(
        {{ 98 },
        { 56 },
        { 38 },
        { 39 },
        { 88 },
        { 92 },
        { 93 },
        { 46 } });



        Matrix b0_4x4(
        {{ 61, 64, 99, 32},
         { 70, 22,  9, 92},
         { 87, 63, 54,  8},
         { 79,  7, 49, 23}});

        Matrix b1_4x4(
        {{ 71, 94, 21, 40 },
         { 77, 40, 93, 25 },
         { 15, 57,  5, 48 },
         { 36, 46,  5,  4 }});

        Matrix b2_4x4(
        {{ 52, 28, 83, 65 },
         { 59, 31, 14, 92 },
         { 97,  5, 50, 96 },
         { 52, 48, 41,  9 }});

        Matrix b3_4x4(
        {{ 61, 28, 55,  8 },
         { 60, 55,  6, 67 },
         { 41, 33, 16, 18 },
         { 74, 54, 44, 63 }});

        Matrix br_1x8(
        {{  2, 92, 88, 85, 24, 56, 86, 15 }});


        Matrix cr = ar_8x1 * br_1x8;

        Matrix c0_4x4 = a0_4x4 * b0_4x4 + a1_4x4 * b2_4x4;
        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                cr[0* 4 + i][ 0 * 4 + j] += c0_4x4[i][j];


        Matrix c1_4x4 = a0_4x4 * b1_4x4 + a1_4x4 * b3_4x4;
        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                cr[0* 4 + i][ 1 * 4 + j] += c1_4x4[i][j];

        Matrix c2_4x4 = a2_4x4 * b0_4x4 + a3_4x4 * b2_4x4;
        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                cr[1* 4 + i][ 0 * 4 + j] += c2_4x4[i][j];


        Matrix c3_4x4 = a2_4x4 * b1_4x4 + a3_4x4 * b3_4x4;
        for(int i= 0 ; i < 4; i++)
            for(int j= 0 ; j < 4; j++)
                cr[1* 4 + i][ 1 * 4 + j] += c3_4x4[i][j];


        std::cout << "cr = " << cr << std::endl;

        Matrix expected = Matrix::mul(a_8x9, b_9x8);

        for(int i = 0; i < cr.h_; i++)
            for(int j = 0; j < cr.w_; j++)
                if (cr[i][j] != expected[i][j])
                    std::cout << "[" << i << ", " << j << "] = " << cr[i][j] << " expected " << expected[i][j] << std::endl;
}

}


