#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace cv;

double calculateAccuracy(Mat& orignalImg, Mat& decodedImg) {
	int totalPixels = orignalImg.rows * orignalImg.cols;
	double pixels = 0;
	for (int i = 0; i < orignalImg.rows; i++) {
		for (int j = 0; j < orignalImg.cols; j++) {
			int a = orignalImg.at<uchar>(i, j);
			int b = decodedImg.at<uchar>(i, j);
			pixels += pow((orignalImg.at<uchar>(i, j) - decodedImg.at<uchar>(i, j)), 2);
		}
	}
	
	double x = pixels / totalPixels;
	double z = 255.0;
	double accuracy = 100.0 * (1.0 - (x / z*z));
	
	return accuracy;
	
}

int main(int argc, char** argv)
{
	// Read the image file
	Mat orignalImage = imread("C:\\Users\Hp EliteBook\source\repos\OpenCV_3\OpenCV_3\\t1.bmp", IMREAD_GRAYSCALE);
	Mat decodedImage = imread("C:\\Users\Hp EliteBook\source\repos\OpenCV_3\OpenCV_3\\t1.bmp", IMREAD_GRAYSCALE);
	
	// Check for failure
	if (orignalImage.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		system("pause");
		return -1;
	}
	
	//image failure Decode
	if (decodedImage.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		system("pause");
		return -1;
	}

	// Calculate accuracy
	double accuracy = calculateAccuracy(orignalImage, decodedImage);
	std::cout << "Accuracy: " << accuracy << std::endl;
	
	
	// Show our image inside it.
	imshow("Orignal Image", orignalImage);
	imshow("Decoded Image", decodedImage);
	
	// Wait for any keystroke in the window
	waitKey(0);
	return 0;
}
	
	