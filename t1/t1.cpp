#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>

struct Point {
    double x;
    double y;
};

std::vector<Point> readFunctionFromFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (file.is_open()) {
        double x, y;
        while (file >> x >> y) {
            points.push_back({ x, y });
        }
        file.close();
    }
    else {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }
    return points;
}

double calculateHausdorffDistance(const std::vector<Point>& function1, const std::vector<Point>& function2) {
    double maxDistance = 0.0;
    std::vector<double> distances(function2.size());

    for (const Point& p1 : function1) {
        for (size_t i = 0; i < function2.size(); ++i) {
            distances[i] = std::abs(p1.y - function2[i].y);
        }

        double minDistance = *std::min_element(distances.begin(), distances.end());

        if (minDistance > maxDistance) {
            maxDistance = minDistance;
        }
    }

    return maxDistance;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Two function files are required." << std::endl;
        return 1;
    }

    std::string functionFile1 = argv[1];
    std::string functionFile2 = argv[2];

    try {
        std::vector<Point> function1 = readFunctionFromFile(functionFile1);
        std::vector<Point> function2 = readFunctionFromFile(functionFile2);

        double distance = calculateHausdorffDistance(function1, function2);

        std::cout << "Hausdorff distance: " << distance << std::endl;

    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}