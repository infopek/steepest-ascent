#pragma once

#include "parameter_defaults.h"

namespace core
{
    class Parameter
    {
    public:
        Parameter();
        ~Parameter();

        inline float getEpsilon() const { return m_epsilon; }
        inline int getDistanceFromFurthest() const { return m_distanceFromFurthest; }

        void setEpsilon(float value);
        void setDistanceFromFurthest(int value);

    private:
        float m_epsilon{ epsilonDefault };
        int m_distanceFromFurthest{ distanceToFurthestDefault };
    };
}