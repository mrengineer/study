#include <iostream>
#include <iomanip>
#include <cmath>

namespace global_cfg
{
    const size_t MAX_POINTS = 100;
}

// простая структура точки
struct point
{
    double x;
    double y;
};

// расстояние между точками
double distance_between(point a, point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return std::sqrt(dx * dx + dy * dy);
}

// сколько точек в шаре
size_t count_points_in_ball(const point* points,
                            size_t count,
                            point center,
                            double radius)
{
    size_t inside_count = 0;

    for (size_t i = 0; i < count; i++)
    {
        double dist = distance_between(center, points[i]);
        if (dist <= radius)
            inside_count++;
    }

    return inside_count;
}

int main()
{
    size_t points_count = 0;

    std::cout << "Enter number of points (<=100): ";
    std::cin >> points_count;

    if (points_count == 0 || points_count > global_cfg::MAX_POINTS)
    {
        std::cout << "wrong number of points\n";
        return 1;
    }

    point points[global_cfg::MAX_POINTS];

    std::cout << "Enter point coordinates (x y):\n";
    for (size_t i = 0; i < points_count; i++)
    {
        std::cin >> points[i].x >> points[i].y;
    }

    double radius = 0.0;
    std::cout << "Enter ball radius R: ";
    std::cin >> radius;

    if (radius < 0.0)
    {
        std::cout << "radius cant be negative\n";
        return 1;
    }

    size_t min_inside = points_count + 1;
    size_t best_index = 0;

    for (size_t i = 0; i < points_count; i++)
    {
        // считаем для этой точки
        size_t current_count =
            count_points_in_ball(points, points_count, points[i], radius);

        if (current_count < min_inside)
        {
            min_inside = current_count;
            best_index = i;
        }
    }

    std::cout << "\nResult point:\n";
    std::cout << "x = " << points[best_index].x
              << " y = " << points[best_index].y << "\n";

    std::cout << "points inside ball: "
              << min_inside << "\n";

    return 0;
}
