

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>


int main() {
	cv::VideoCapture capWebcam(0);		

	if (capWebcam.isOpened() == false) {			
		std::cout << "error: capWebcam not accessed successfully\n\n";	// if not, print error message to std out
		return(0);														// and exit program
	}

	cv::Mat matOriginal;		// input image
	cv::Mat matGrayscale;		// grayscale of input image
	cv::Mat matBlurred;			// intermediate blured image
	cv::Mat matCanny;			// Canny edge image

	char charCheckForEscKey = 0;

	while (charCheckForEscKey != 27 && capWebcam.isOpened()) { 		
		bool blnFrameReadSuccessfully = capWebcam.read(matOriginal);	

		if (!blnFrameReadSuccessfully || matOriginal.empty()) {		
			std::cout << "error: frame not read from webcam\n";		
			break;													
		}

		cv::cvtColor(matOriginal, matGrayscale, CV_BGR2GRAY);		

		cv::GaussianBlur(matGrayscale,			// input image
			matBlurred,							// output image
			cv::Size(5, 5),						// smoothing window width and height in pixels
			1.8);								// sigma value, determines how much the image will be blurred

		cv::Canny(matBlurred,			// input image
			matCanny,					// output image
			50,							// low threshold
			100);						// high threshold

													// declare windows
		cv::namedWindow("Original", CV_WINDOW_NORMAL);	
		cv::namedWindow("Canny", CV_WINDOW_NORMAL);		
														
		cv::imshow("Original", matOriginal);		
		cv::imshow("Canny", matCanny);

		charCheckForEscKey = cv::waitKey(1);		
	}	// end while

	return(0);
}
