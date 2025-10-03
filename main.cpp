#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <string>

using namespace Eigen;
using namespace std;

#define A 1.0
#define B 9.0
#define C 0.0
#define D 17.0

#define lower_x 1.0
#define upper_x 9.0

#define lower_u -6.0
#define upper_u 3.0

VectorXf solve_linear(int count_elements){

    float L = (upper_x - lower_x) / (float)count_elements;
    int math_dimension = count_elements+1;

    MatrixXf A_matrix(math_dimension, math_dimension);
    VectorXf b_vector(math_dimension);

    A_matrix.setZero();
    b_vector.setZero();

    for (int i = 0; i < math_dimension-1; i++){
        A_matrix(i, i) += -A/L - B/2.;
        A_matrix(i, i + 1) += A/L + B/2.;
        A_matrix(i + 1, i) += A/L - B/2.;
        A_matrix(i + 1, i + 1) += -A/L + B/2.;

        b_vector(i) += -D * (L/2.);
        b_vector(i + 1) += -D * (L/2.);
    }

    A_matrix.row(0).setZero();
    A_matrix(0,0) = 1;
    b_vector(0) = lower_u;

    A_matrix.row(math_dimension-1).setZero();
    A_matrix(math_dimension-1, math_dimension-1) = 1;
    b_vector(math_dimension-1) -= A*upper_u;

    return A_matrix.fullPivHouseholderQr().solve(b_vector);
}

VectorXf solve_cubic(float count_elements){

    float L = (upper_x - lower_x) / (float)count_elements;
    int math_dimension = 3 * count_elements+1;

    MatrixXf A_matrix(math_dimension, math_dimension);
    VectorXf b_vector(math_dimension);

    A_matrix.setZero();
    b_vector.setZero();

    for (int i = 0; i < math_dimension - 3; i += 3){
        A_matrix(i, i) += -A * (37.0 / (10.0 * L)) - B / 2.0;
        A_matrix(i, i+1) += A * (189.0 / (40.0 * L)) + B * (57.0 / 80.0);
        A_matrix(i, i+2) += -A * (27.0 / (20.0 * L)) - B * (3.0 / 10.0);
        A_matrix(i, i+3) += A * (13.0 / (40.0 * L)) + B * (7.0 / 80.0);

        A_matrix(i+1, i) += A * (189.0 / (40.0 * L)) - B * (57.0 / 80.0);
        A_matrix(i+1, i+1) += -A * (54.0 / (5.0 * L));
        A_matrix(i+1, i+2) += A * (297.0 / (40.0 * L)) + B * (81.0 / 80.0);
        A_matrix(i+1, i+3) += -A * (27.0 / (20.0 * L)) - B * (3.0 / 10.0);

        A_matrix(i+2, i) += -A * (27.0 / (20.0 * L)) + B * (3.0 / 10.0);
        A_matrix(i+2, i+1) += A * (297.0 / (40.0 * L)) - B * (81.0 / 80.0);
        A_matrix(i+2, i+2) += A * (54.0 / (5.0 * L));
        A_matrix(i+2, i+3) += A * (189.0 / (40.0 * L)) + B * (57.0 / 80.0);

        A_matrix(i+3, i) += A * (13.0 / (40.0 * L)) - B * (7.0 / 80.0);
        A_matrix(i+3, i+1) += -A * (27.0 / (20.0 * L)) + B * (3.0 / 10.0);
        A_matrix(i+3, i+2) += A * (189.0 / (40.0 * L)) - B * (57.0 / 80.0);
        A_matrix(i+3, i+3) += -A * (37.0 / (10.0 * L)) + B / 2.0;

        b_vector(i) -= D * (L / 8.0);
        b_vector(i+1) -= D * ((3.0 * L) / 8.0);
        b_vector(i+2) -= D * ((3.0 * L) / 8.0);
        b_vector(i+3) -= D * (L / 8.0);
    }

    A_matrix.row(0).setZero();
    A_matrix(0,0) = 1;
    b_vector(0) = lower_u;

    A_matrix.row(math_dimension - 1).setZero();
    A_matrix(math_dimension -1, math_dimension - 1) = 1;
    b_vector(math_dimension - 1) -= A*upper_u;

    return A_matrix.fullPivHouseholderQr().solve(b_vector);
}

void writeVectorToFile(const VectorXf& vec, const string& type, const string& count) {
    string filename = type + count+".txt";
    std::ofstream file(filename);
    if (file.is_open()) {
        file << vec << std::endl;
        file.close();
    }
}

int main(int args, char* argv[]){
    int count = stoi(argv[1]);
    string count_name = argv[1];
    VectorXf linear;
    VectorXf cubic;

    linear = solve_linear(count);
    cubic = solve_cubic(count);

    writeVectorToFile(linear, "linear", count_name);
    writeVectorToFile(cubic, "cubic", count_name);

    return 0;
}
