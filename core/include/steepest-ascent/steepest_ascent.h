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
        SteepestAscent(const SmallestBoundaryPolygonProblem& sbpp, const SearchSpace& searchSpace, const Parameter& parameter);
        ~SteepestAscent();

        void step();

        float getBoundaryLength() const;

        inline int getIteration() const { return m_iteration; }
        inline bool isStuck() const { return m_stuck; }

        inline const std::vector<Point>& getBoundary() const { return m_curr; }
        inline float getConstraint() const { return m_sbpp.constraint(m_curr); }

    private:
        /// @brief Finds the valid neighbors of the current polygon, and then picks the one with the best fitness. 
        /// @return Neighboring polygon with best fitness.
        std::vector<Point> getBestNeighbor() const;

        /// @return Fitness of a polygon.
        float fitness(const std::vector<Point>& boundary) const;

        /// @brief Finds a good starting square for the algorithm.
        /// @return A rectangle as big as the screen size (the other method would either become stuck or not adhere to constraints).
        std::vector<Point> findGoodPolygon() const;

        /// @brief Finds the centroid of the points which are to be bounded.
        /// @return Centroid (point).
        Point findCentroid() const;

        /// @param centroid Centroid of points which are to be bounded.
        /// @return Point which is the furthest away from centroid.
        Point findFurthestPoint(const Point& centroid) const;

        /// @brief Checks if given boundary is valid in the search space, and if it adheres to the constraint(s).
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

