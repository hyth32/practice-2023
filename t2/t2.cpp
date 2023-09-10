#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <fstream>

struct Function {
    std::vector<double> x;
    std::vector<double> y;
};

Function generatePiecewiseConstantFunction(double start, double end, int breakpoints) {
    Function function;
    double step = (end - start) / breakpoints;
    double value = 0.0;
    for (double x = start; x <= end; x += step) {
        function.x.push_back(x);
        function.y.push_back(value);
        value += 1.0 / breakpoints;
    }
    return function;
}

double calculateHausdorffDistance(const Function& function1, const Function& function2) {
    double maxDistance = 0.0;
    for (int i = 0; i < function1.x.size(); i++) {
        double minDistance = std::numeric_limits<double>::max();
        for (int j = 0; j < function2.x.size(); j++) {
            double distance = std::abs(function1.y[i] - function2.y[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
        if (minDistance > maxDistance) {
            maxDistance = minDistance;
        }
    }
    return maxDistance;
}

double calculateMean(const std::vector<double>& values) {
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

double calculateMeanDistance(const Function& function1, const Function& function2) {
    double mean1 = calculateMean(function1.y);
    double mean2 = calculateMean(function2.y);
    return std::abs(mean1 - mean2);
}

double calculateVariance(const std::vector<double>& values) {
    double mean = calculateMean(values);
    double sum = 0.0;
    for (double value : values) {
        sum += std::pow(value - mean, 2);
    }
    return sum / values.size();
}

double calculateVarianceDistance(const Function& function1, const Function& function2) {
    double variance1 = calculateVariance(function1.y);
    double variance2 = calculateVariance(function2.y);
    return std::abs(variance1 - variance2);
}

std::vector<Function> generateRandomFunctions(int count, int minBreakpoints, int maxBreakpoints) {
    std::vector<Function> functions;
    for (int i = 0; i < count; i++) {
        int breakpoints = rand() % (maxBreakpoints - minBreakpoints + 1) + minBreakpoints;
        double start = 0.0;
        double end = 1.0;
        Function function = generatePiecewiseConstantFunction(start, end, breakpoints);
        functions.push_back(function);
    }
    return functions;
}

void writeDistanceDataToFile(const std::string& filename, const std::vector<Function>& functions) {
    std::ofstream outfile(filename);
    for (int i = 0; i < functions.size(); i++) {
        for (int j = i + 1; j < functions.size(); j++) {
            double hausdorffDistance = calculateHausdorffDistance(functions[i], functions[j]);
            double meanDistance = calculateMeanDistance(functions[i], functions[j]);
            double varianceDistance = calculateVarianceDistance(functions[i], functions[j]);
            outfile << hausdorffDistance << " " << meanDistance << " " << varianceDistance << std::endl;
        }
    }
    outfile.close();
}

int main() {
    int minBreakpoints = 3;
    int maxBreakpoints = 10;

    std::vector<Function> functions = generateRandomFunctions(100, minBreakpoints, maxBreakpoints);
    writeDistanceDataToFile("graph.dat", functions);

    std::cout << "Файл graph.dat создан." << std::endl;

    return 0;
}