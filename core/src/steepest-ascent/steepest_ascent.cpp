#include <steepest-ascent/steepest_ascent.h>
#include <common/random.h>

namespace core
{
    SteepestAscent::SteepestAscent(const SmallestBoundaryPolygonProblem& sbpp, const SearchSpace& searchSpace, const Parameter& parameter)
        : m_sbpp{ sbpp },
        m_parameter{ parameter },
        m_searchSpace{ searchSpace },
        m_stuck{ false }
    {
        m_curr = findGoodPolygon();
    }

    SteepestAscent::~SteepestAscent()
    {
    }

    void SteepestAscent::step()
    {
        std::vector<Point> cand = getBestNeighbor();

        if (fitness(cand) <= fitness(m_curr))
            m_curr = cand;
        else
            m_stuck = true;

        ++m_iteration;
    }

    float SteepestAscent::getBoundaryLength() const
    {
        return fitness(m_curr);
    }

    std::vector<Point> SteepestAscent::getBestNeighbor() const
    {
        // Get all valid neighbors
        std::vector<std::vector<Point>> validNeighbors{};
        validNeighbors.reserve(m_curr.size() * 4);  // 4 directions
        for (size_t i = 0; i < m_curr.size(); ++i)
        {
            for (int dx : {-1, 1})
            {
                for (int dy : {-1, 1})
                {
                    Point offsetPoint{
                        .x = m_curr[i].x + dx * m_parameter.getEpsilon(),
                        .y = m_curr[i].y + dy * m_parameter.getEpsilon()
                    };

                    std::vector<Point> neighbor{ m_curr };
                    neighbor[i] = offsetPoint;
                    if (isValidPolygon(neighbor))
                        validNeighbors.push_back(neighbor);
                }
            }
        }

        // Choose one with best fitness
        std::vector<Point> best{ m_curr };
        float bestFitness = std::numeric_limits<float>::max();
        for (const auto& neighbor : validNeighbors)
        {
            float neighborFitness = fitness(neighbor);
            if (neighborFitness < bestFitness)
            {
                best = neighbor;
                bestFitness = neighborFitness;
            }
        }

        return best;
    }

    bool SteepestAscent::isValidPolygon(const std::vector<Point>& boundary) const
    {
        for (const auto& point : boundary)
        {
            if (!(point.x >= m_searchSpace.x.min && point.x <= m_searchSpace.x.max
                && point.y >= m_searchSpace.y.min && point.y <= m_searchSpace.y.max)
                || m_sbpp.constraint(boundary) < 0.0f)
            {
                return false;
            }
        }

        return true;
    }

    float SteepestAscent::fitness(const std::vector<Point>& boundary) const
    {
        return m_sbpp.objective(boundary);
    }

    std::vector<Point> SteepestAscent::findGoodPolygon() const
    {
        return std::vector<Point> {
            Point{ .x = 0.0f, .y = 0.0f },
                Point{ .x = m_searchSpace.x.max, .y = 0.0f },
                Point{ .x = m_searchSpace.x.max, .y = m_searchSpace.y.max },
                Point{ .x = 0.0f, .y = m_searchSpace.y.max }
        };

        // const auto& points = m_sbpp.getPoints();

        // Point centroid = findCentroid();

        // Point furthestPoint = findFurthestPoint(centroid);

        // float distanceToFurthest = std::sqrt(std::pow(furthestPoint.x - centroid.x, 2) + std::pow(furthestPoint.y - centroid.y, 2));

        // float circleRadius = distanceToFurthest + m_parameter.getDistanceFromFurthest();

        // float squareSideLength = std::sqrt(2) * circleRadius;
        // float halfSquareSide = squareSideLength / 2.0f;

        // std::vector<Point> startingPolygon{
        //     Point {.x = centroid.x - halfSquareSide, .y = centroid.y - halfSquareSide},
        //     Point {.x = centroid.x + halfSquareSide, .y = centroid.y - halfSquareSide},
        //     Point {.x = centroid.x + halfSquareSide, .y = centroid.y + halfSquareSide},
        //     Point {.x = centroid.x - halfSquareSide, .y = centroid.y + halfSquareSide}
        // };

        // return startingPolygon;
    }

    Point SteepestAscent::findCentroid() const
    {
        const auto& points = m_sbpp.getPoints();

        float sumX = 0.0f;
        float sumY = 0.0f;
        for (const auto& point : points)
        {
            sumX += point.x;
            sumY += point.y;
        }

        float centroidX = sumX / points.size();
        float centroidY = sumY / points.size();
        return Point(centroidX, centroidY);
    }

    Point SteepestAscent::findFurthestPoint(const Point& centroid) const
    {
        const auto& points = m_sbpp.getPoints();

        float maxDistance = 0.0f;
        Point furthestPoint;
        for (const auto& point : points)
        {
            float distance = std::sqrt(std::pow(point.x - centroid.x, 2) + std::pow(point.y - centroid.y, 2));
            if (distance > maxDistance)
            {
                maxDistance = distance;
                furthestPoint = point;
            }
        }
        return furthestPoint;
    }
}
