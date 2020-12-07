#include <opencv2/opencv.hpp>

struct Matrix {
    std::string name;
    std::vector<double> arr1;
    std::vector<double> arr2;
    int width;
    int height;
};

int index(int x, int y, int width);

unsigned char clamp(double val);

Matrix modify_image(std::uint8_t const *inputImage, std::uint8_t *outputImage, std::uint32_t width, std::uint32_t height, std::vector<Matrix> &ARR);

Matrix create_matrix(std::vector<Matrix> &ARR);

Matrix choose_matrix(std::vector<Matrix> &ARR);

Matrix exit(std::vector<Matrix> &ARR);

Matrix dialog_choose(std::vector<Matrix> &ARR);

void copy_edges(std::uint8_t const *inputImage, std::uint8_t *outputImage, std::uint32_t width, std::uint32_t height, Matrix M);

int dialog(const char *msgs[], int n);

int get_natural_int(int *a);

void save(std::vector<Matrix> &ARR);

std::vector<Matrix> load(std::vector<Matrix> &);

std::vector<Matrix> add_matrix(std::vector<Matrix> &ARR, Matrix M);