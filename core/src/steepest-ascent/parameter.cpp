#include <steepest-ascent/parameter.h>

#include <iostream>

namespace core
{
    Parameter::Parameter()
    {

    }

    Parameter::~Parameter()
    {

    }

    void Parameter::setEpsilon(float value)
    {
        if (value >= 0.0f)
            m_epsilon = value;
        else
            std::cerr << "Parameter 'epsilon' has to be a positive real number";
    }

    void Parameter::setDistanceFromFurthest(int value)
    {
        if (value >= 0)
            m_distanceFromFurthest = value;
        else
            std::cerr << "Parameter 'distanceFromFurthest' has to be a positive integer";
    }
}
