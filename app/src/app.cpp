#include <common/point.h>
#include <common/random.h>
#include <steepest-ascent/smallest_boundary_polygon.h>
#include <steepest-ascent/steepest_ascent.h>
#include <visualizer/visualizer.h>

#include <iostream>
#include <vector>

using namespace core;
using namespace vis;

std::vector<Point> generateRandomPoints(int numPoints, const SearchSpace& searchSpace)
{
    std::vector<Point> points;
    float padding = 150.0f;
    points.reserve(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        points.push_back({
            .x = random::get(searchSpace.x.min + padding, searchSpace.x.max - padding),
            .y = random::get(searchSpace.y.min + padding, searchSpace.y.max - padding)
            });
    }

    return points;
}

int main()
{
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;

    const SearchSpace searchSpace{
        .x = Interval {
            .min = 0,
            .max = windowWidth
        },
        .y = Interval {
            .min = 0,
            .max = windowHeight
        }
    };

    const int numPoints = 6;
    const std::vector<core::Point> points = generateRandomPoints(numPoints, searchSpace);

    SmallestBoundaryPolygonProblem sbpp(searchSpace);
    sbpp.savePointsToFile("points.txt", points);
    sbpp.loadPointsFromFile("points.txt");

    Parameter parameter{};
    SteepestAscent sa(sbpp, searchSpace, parameter);

    Visualizer visualizer(sa, sbpp, windowWidth, windowHeight);
    visualizer.draw();
}