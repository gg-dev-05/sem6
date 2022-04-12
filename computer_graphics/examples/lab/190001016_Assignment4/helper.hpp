// 190001016
// Garvit Galgat

/**
 * @brief take user inputs
 *
 * @param radius
 * @param x
 * @param y
 */
void input(int &radius, int &x, int &y) {
    std::cout << "Center of circle\n";
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    std::cout << "Radius: ";
    std::cin >> radius;
}
/**
 * @brief add points to points vector for other octants w.r.t the one
 * already present in points vector
 *
 * @param points vector of pair containing points present in 1st octant
 */
void recurseForOctants(std::vector<std::pair<int, int>> &points) {
    int totalElements = points.size();

    // 2nd Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({points[i].second, points[i].first});
    }

    // 3rd Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({-points[i].second, points[i].first});
    }

    // 4th Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({-points[i].first, points[i].second});
    }

    // 5th Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({-points[i].first, -points[i].second});
    }

    // 6th Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({-points[i].second, -points[i].first});
    }

    // 7th Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({points[i].second, -points[i].first});
    }

    // 8th Octant
    for (int i = 0; i < totalElements; i++) {
        points.push_back({points[i].first, -points[i].second});
    }
}

/**
 * @brief shift origin w.r.t x center and y center
 *
 * @param points vector of pair containing points
 * @param xCenter x coordinate of new origin
 * @param yCenter y coordinate of new origin
 */
void shiftOrigin(std::vector<std::pair<int, int>> &points, int xOrigin, int yOrigin) {
    for (auto &i : points) {
        i.first += xOrigin;
        i.second += yOrigin;
    }
}