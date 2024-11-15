# include <iostream> // cout
# include "funcs.hpp"

using namespace std;

int main(void) {
    
    vector<vector<int>> image = read_image("imagem.pgm"); // Read image

    print_int_histogram(histogram_absolute(image)); // Print absolute histogram
    print_double_histogram(histogram_relative(image)); // Print relative histogram
    cout << "\nMedia imagem original: " << calculate_average_color(image) << "\n"; // Print average color
    cout << "Variancia imagem original: " << calculate_variance(image) << "\n"; // Print variance
    cout << "Desvio padrao imagem original: " << calculate_standard_deviation(image) << "\n"; // Print standard deviation
    cout << "----------------------------------------\n";

    vector<vector<int>> inverted_image = create_inverted_image(image); // Create inverted image
    create_image_file(sum_images(inverted_image, image), "INVERTED_SUM_ORIGINAL.ascii.pgm"); // Create inverted+originalimage

    vector<vector<int>> reduced_noise_image = create_reduced_noise_image(image); // Create reduced noise image
    cout << "Media imagem filtrada: " << calculate_average_color(reduced_noise_image) << "\n"; // Print average color of reduced noise image
    cout << "Variancia imagem filtrada: " << calculate_variance(reduced_noise_image) << "\n"; // Print variance of reduced noise image
    cout << "Desvio padrao imagem filtrada: " << calculate_standard_deviation(reduced_noise_image) << "\n"; // Print standard deviation of reduced noise image
    cout << "----------------------------------------\n";

    vector<vector<int>> boxed_reduce_noise_image = create_box_filtering_image(image); // Create box filtering image
    cout << "Media imagem filtrada (box): " << calculate_average_color(boxed_reduce_noise_image) << "\n"; // Print average color of box filtering image
    cout << "Variancia imagem filtrada (box): " << calculate_variance(boxed_reduce_noise_image) << "\n"; // Print variance of box filtering image
    cout << "Desvio padrao imagem filtrada (box): " << calculate_standard_deviation(boxed_reduce_noise_image) << "\n"; // Print standard deviation of box filtering image
    cout << "----------------------------------------\n";

    vector<vector<int>> median_square_filtered_image = create_square_median_filtering_image(image, 2); // r = 2
    cout << "Media imagem filtrada (mediana quadrado): " << calculate_average_color(median_square_filtered_image) << "\n"; // Print average color of square median filtering image
    cout << "Variancia imagem filtrada (mediana quadrado): " << calculate_variance(median_square_filtered_image) << "\n"; // Print variance of square median filtering image
    cout << "Desvio padrao imagem filtrada (mediana quadrado): " << calculate_standard_deviation(median_square_filtered_image) << "\n"; // Print standard deviation of square median filtering image
    cout << "----------------------------------------\n";

    vector<vector<int>> median_diamond_filtered_image = create_diamond_median_filtering_image(image, 2); // r = 2
    cout << "Media imagem filtrada (mediana diamante): " << calculate_average_color(median_diamond_filtered_image) << "\n"; // Print average color of diamond median filtering image
    cout << "Variancia imagem filtrada (mediana diamante): " << calculate_variance(median_diamond_filtered_image) << "\n"; // Print variance of diamond median filtering image
    cout << "Desvio padrao imagem filtrada (mediana diamante): " << calculate_standard_deviation(median_diamond_filtered_image) << "\n"; // Print standard deviation of diamond median filtering image
    cout << "----------------------------------------\n";

    // Uncomment the line to generate r = 4 square median filtering image
    // It is more blurred than r = 2 image
    // vector<vector<int>> median_square_filtered_image_r_3 = create_square_median_filtering_image(image, 4); // r = 4

    return 0;
}
