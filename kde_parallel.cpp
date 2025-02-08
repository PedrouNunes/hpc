#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

#define WIDTH 256
#define HEIGHT 256
#define BANDWIDTH 1.0
#define WINDOW_SIZE 5

inline double gaussian_kernel(double x, double bandwidth) {
    return exp(-0.5 * (x * x) / (bandwidth * bandwidth)) / (sqrt(2.0 * M_PI) * bandwidth);
}

void kde_parallel(const std::vector<double>& image, std::vector<double>& density, int width, int height) {
    int half_window = WINDOW_SIZE / 2;

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double sum = 0.0;
            for (int x = std::max(0, i - half_window); x < std::min(height, i + half_window); ++x) {
                for (int y = std::max(0, j - half_window); y < std::min(width, j + half_window); ++y) {
                    double diff = image[i * width + j] - image[x * width + y];
                    sum += gaussian_kernel(diff, BANDWIDTH);
                }
            }
            density[i * width + j] = sum;
        }
    }
}

int main() {
    std::vector<double> image(WIDTH * HEIGHT, 0.0);
    std::vector<double> density(WIDTH * HEIGHT, 0.0);

    srand(42);
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        image[i] = rand() % 256;
    }

    double start = omp_get_wtime();
    kde_parallel(image, density, WIDTH, HEIGHT);
    double end = omp_get_wtime();

    std::cout << "Tempo (Multicore OpenMP): " << (end - start) << " segundos\n";
    return 0;
}
