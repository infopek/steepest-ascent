#pragma once

#include <steepest-ascent/smallest_boundary_polygon.h>
#include <steepest-ascent/parameter.h>
#include <common/search_space.h>

#include <vector>

namespace core
{
    class SteepestAscent
    {
    public:
        SteepestAscent(const SmallestBoundaryPolygonProblem& sbpp, const Parameter& parameter, const SearchSpace& searchSpace);
        ~SteepestAscent();

        void step();

        float getBoundaryLength() const;

        inline int getIteration() const { return m_iteration; }
        inline bool isStuck() const { return m_stuck; }

        inline const std::vector<Point>& getBoundary() const { return m_curr; }
        inline float getConstraint() const { return m_sbpp.constraint(m_curr); }

    private:
        std::vector<Point> getBestNeighbor() const;

        float fitness(const std::vector<Point>& boundary) const;

        /// @brief Finds a good starting square for the algorithm. Assumes 4 vertices :(.
        /// @return 
        std::vector<Point> findGoodPolygon() const;

        Point findCentroid() const;

        Point findFurthestPoint(const Point& centroid) const;

        bool isValidPolygon(const std::vector<Point>& boundary) const;

    private:
        SmallestBoundaryPolygonProblem m_sbpp{};
        SearchSpace m_searchSpace{};
        Parameter m_parameter{};

        bool m_stuck{};
        std::vector<Point> m_curr{};

        int m_iteration{};
    };
}

