#include <stdio.h>
#include <math.h>
#include <limits>
#include <queue>

#define DATA_LEN 3 /*constant for the amount of data we're recieving per line. \
                     [height, bottom radius, neck radius]                      \
                     height is the height of the glass                         \
                     bottomR is the radius of the bottom of the glass          \
                     neckR is the radius of the neck of the glass*/

#define MEDIAN_EPSILON 0.000001

struct Glass
{
    unsigned short height;
    unsigned short bottomRadius;
    unsigned short neckRadius;

    Glass() : height(0),
              bottomRadius(0),
              neckRadius(0)
    {
    }

    Glass &operator=(const Glass &rhs)
    {
        if (this != &rhs)
        {
            height = rhs.height;
            bottomRadius = rhs.bottomRadius;
            neckRadius = rhs.neckRadius;
        }
        return *this;
    }
};

void print_glasses(std::queue<Glass> glasses, unsigned short count);
float calculate_median(const float r, const float R);
bool fits_foundation(const unsigned short foundationNeckRadius, const unsigned short glassBottomRadius);
const std::pair<const Glass *, const unsigned short> intersection(const Glass &foundation, const Glass &nextGlass);
float calculate_height(std::queue<Glass> &glasses, unsigned short count);

int main()
{
    unsigned short count = 0;

    scanf("%hu", &count);
    getchar();

    std::queue<Glass> glasses;
    Glass glass;

    for (unsigned short row = 0; row < count; ++row)
    {
        scanf("%hu", &glass.height);
        scanf("%hu", &glass.bottomRadius);
        scanf("%hu", &glass.neckRadius);

        glasses.push(glass);
        getchar();
    }

    float totalHeight = calculate_height(glasses, count);

    printf("%.6f\n", totalHeight);

    print_glasses(glasses, count);

    return 0;
}

float calculate_median(const float r, const float R)
{
    return (R + r) / 2.0;
}

bool fits_foundation(const unsigned short foundationNeckRadius, const unsigned short glassBottomRadius)
{
    return foundationNeckRadius > glassBottomRadius;
}

const float base_angle_cotg(const Glass &glass)
{
    float neckResidue = static_cast<float>(glass.neckRadius - glass.bottomRadius);

    return (static_cast<float>(glass.height)*2)/neckResidue;
}

/*  Calculates which cups median is closer to one of the radiuses of the other cup.

    @param foudation - Glass struct which is the previous glass in the tower.
    @param nextGlass - Glass struct which is the next glass to be put in the tower.
    
    @return - one of the two glass which has a median closer to one of the radiuses.
 */
const std::pair<const Glass *, const unsigned short> intersection(const Glass &foundation, const Glass &nextGlass)
{
    const Glass *glass = NULL;
    float radius = 0;

    float foundationBaseAngle = base_angle_cotg(foundation);
    float nextGlassBaseAngle = base_angle_cotg(nextGlass);

    
}

float calculate_height(std::queue<Glass> &glasses, unsigned short count)
{
    float totalHeight = 0;
    return totalHeight;
}

void print_glasses(std::queue<Glass> glasses, unsigned short count)
{
    Glass dummy;
    while (!glasses.empty())
    {
        dummy = glasses.front();
        glasses.pop();
        printf("%hu %hu %hu", dummy.height, dummy.bottomRadius, dummy.neckRadius);
        printf("\n");
    }
}
