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

void kde_gpu(std::vector<double>& image, std::vector<double>& density, int width, int height) {
    double* image_ptr = image.data();
    double* density_ptr = density.data();
    int half_window = WINDOW_SIZE / 2;

    #pragma omp target data map(to: image_ptr[0:width*height]) map(from: density_ptr[0:width*height])
    {
        #pragma omp target teams distribute parallel for collapse(2)
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                double sum = 0.0;
                for (int x = std::max(0, i - half_window); x < std::min(height, i + half_window); ++x) {
                    for (int y = std::max(0, j - half_window); y < std::min(width, j + half_window); ++y) {
                        double diff = image_ptr[i * width + j] - image_ptr[x * width + y];
                        sum += gaussian_kernel(diff, BANDWIDTH);
                    }
                }
                density_ptr[i * width + j] = sum;
            }
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
    kde_gpu(image, density, WIDTH, HEIGHT);
    double end = omp_get_wtime();

    std::cout << "Tempo (GPU OpenMP Offloading): " << (end - start) << " segundos\n";
    return 0;
}
