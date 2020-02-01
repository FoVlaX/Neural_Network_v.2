#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include "matrix.h"
using namespace std;

inline uint32_t read_header(const std::unique_ptr<char[]>& buffer, size_t position) {
	auto header = reinterpret_cast<uint32_t*>(buffer.get());

	auto value = *(header + position);
	return (value << 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0X0000FF00) | (value >> 24);
}


inline std::unique_ptr<char[]> read_mnist_file(const std::string& path, uint32_t key) {
	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file) {
		std::cout << "Error opening file" << std::endl;
		return {};
	}

	auto size = file.tellg();
	std::unique_ptr<char[]> buffer(new char[size]);

	//Read the entire file at once
	file.seekg(0, std::ios::beg);
	file.read(buffer.get(), size);
	file.close();

	auto magic = read_header(buffer, 0);

	if (magic != key) {
		std::cout << "Invalid magic number, probably not a MNIST file" << std::endl;
		return {};
	}

	auto count = read_header(buffer, 1);

	if (magic == 0x803) {
		auto rows = read_header(buffer, 2);
		auto columns = read_header(buffer, 3);

		if (size < count * rows * columns + 16) {
			std::cout << "The file is not large enough to hold all the data, probably corrupted" << std::endl;
			return {};
		}
	}
	else if (magic == 0x801) {
		if (size < count + 8) {
			std::cout << "The file is not large enough to hold all the data, probably corrupted" << std::endl;
			return {};
		}
	}

	return buffer;
}


template <typename Label = uint8_t>
vector<Label> read_mnist_label_file(const std::string& path) {


	auto buffer = read_mnist_file(path, 0x801);

	if (buffer) {
		auto count = read_header(buffer, 1);

		//Skip the header
		//Cast to unsigned char is necessary cause signedness of char is
		//platform-specific
		auto label_buffer = reinterpret_cast<unsigned char*>(buffer.get() + 8);

		std::vector<Label> labels(count);

		for (size_t i = 0; i < count; ++i) {
			auto label = *label_buffer++;
			labels[i] = static_cast<Label>(label);
		}

		return labels;
	}
	return {};
}


int ReverseInt(int i){
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}
void ReadMNIST(string str,int NumberOfImages, int DataOfAnImage, vector<matrix<double>>& arr){
	arr.resize(NumberOfImages, matrix<double>(DataOfAnImage,1));
	ifstream file(str,ios::binary);
	if (file.is_open()){
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);
		for (int i = 0; i < number_of_images; ++i){
			for (int r = 0; r < n_rows; ++r){
				for (int c = 0; c < n_cols; ++c){
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					arr[i][(n_rows * r) + c][0] = (double)temp/256;
				}
			}
		}
	}
}