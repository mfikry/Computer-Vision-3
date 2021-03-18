#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"


using namespace cv;
using namespace std;

int i = 0;
int j = 0;

int main(int argc, char** argv) {

	//1. Load Gambar
	Mat image = imread("media/garden.jpg");
	//2. Konversi RGB ke XYZ
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			Vec3b intensity = image.at<Vec3b>(i, j);
			float sB = intensity.val[0];
			float sG = intensity.val[1];
			float sR = intensity.val[2];

			float v_red = (sR / 255);
			float v_green = (sG / 255);
			float v_blue = (sB / 255);

			if (v_red > 0.04045) {
				v_red = pow(((v_red + 0.055) / 1.055), 2.4);
			}
			else { v_red = v_red / 12.92; }
			if (v_green > 0.04045) {
				v_green = pow(((v_green + 0.055) / 1.055), 2.4);
			}
			else {
				v_green = v_green / 12.92;
			}
			if (v_blue > 0.04045) {
				v_blue = pow(((v_blue + 0.055) / 1.055), 2.4);
			}
			else {
				v_blue = v_blue / 12.92;
			}

			v_red = v_red * 100;
			v_green = v_green * 100;
			v_blue = v_blue * 100;

			float X = v_red * 0.4124 + v_green * 0.3576 + v_blue * 0.1805;
			float Y = v_red * 0.2126 + v_green * 0.7152 + v_blue * 0.0722;
			float Z = v_red * 0.0193 + v_green * 0.1192 + v_blue * 0.9505;

			Vec3b color = image.at<Vec3b>(i, j);
			color[0] = Z;
			color[1] = Y;
			color[2] = X;
			image.at<Vec3b>(i, j) = color;
		}
	}
	imshow("Konversi RGB ke XYZ", image);
	imwrite("media/Konversi RGB ke XYZ.jpg", image);

	//3. Konversi ke xy
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			Vec3b intensity = image.at<Vec3b>(i, j);
			float Z = intensity.val[0];
			float Y = intensity.val[1];
			float X = intensity.val[2];

			float xy_Y = Y/2;
			float xy_x = X / (X + Y + Z);
			float xy_y = Y / (X + Y + Z);

			Vec3b color = image.at<Vec3b>(i, j);
			color[0] = xy_y;
			color[1] = xy_x;
			color[2] = xy_Y;
			image.at<Vec3b>(i, j) = color;
		}
	}
	imshow("Konversi XYZ ke xy", image);
	imwrite("media/Konversi XYZ ke xy.jpg", image);

	//5. Konversi kembali ke XYZ
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			Vec3b intensity = image.at<Vec3b>(i, j);
			float y = intensity.val[0];
			float x = intensity.val[1];
			float Y = intensity.val[2];

			float XYZ_X = x * (Y / y);
			float XYZ_Y = Y;
			float XYZ_Z = (1 - x - y) * (Y / y);

			Vec3b color = image.at<Vec3b>(i, j);
			color[0] = XYZ_Z;
			color[1] = XYZ_Y;
			color[2] = XYZ_X;
			image.at<Vec3b>(i, j) = color;
		}
	}
	imshow("Konversi xy ke XYZ", image);
	imwrite("media/Konversi xy ke XYZ.jpg", image);

	//6. Konversi kembali ke RGB
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
		Vec3b intensity = image.at<Vec3b>(i, j);
		float Z = intensity.val[0];
		float Y = intensity.val[1];
		float X = intensity.val[2];

		float var_X = X / 100;
		float var_Y = Y / 100;
		float var_Z = Z / 100;

		float var_R = var_X * 3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
		float var_G = var_X * -0.9689 + var_Y * 1.8758 + var_Z * 0.0415;
		float var_B = var_X * 0.0557 + var_Y * -0.2040 + var_Z * 1.0570;

			if (var_R > 0.0031308) {
				var_R = 1.055 * (pow(var_R, (1 / 2.4))) - 0.055;
			}
			else {
				var_R = 12.92 * var_R;
			}
			if (var_G > 0.0031308) {
				var_G = 1.055 * (pow(var_G, (1 / 2.4))) - 0.055;
			}
			else {
				var_G = 12.92 * var_G;
			}
			if (var_B > 0.0031308) {
				var_B = 1.055 * (pow(var_B, (1 / 2.4))) - 0.055;
			}
			else {
				var_B = 12.92 * var_B;
			}

			float s_R = var_R * 255;
			float s_G = var_G * 255;
			float s_B = var_B * 255;

			Vec3b colorfinal = image.at<Vec3b>(i, j);
			colorfinal[0] = s_B;
			colorfinal[1] = s_G;
			colorfinal[2] = s_R;
			image.at<Vec3b>(i, j) = colorfinal;
		}
	}
	imshow("Konversi XYZ ke RGB", image);
	imwrite("media/Konversi XYZ ke RGB.jpg", image);

	waitKey(0);

	return 0;
}