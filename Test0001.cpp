#include "Images.h"

int main(int argc, char **argv) {
	Images images = Images::Images();
	if (!images.Load()){ return 1; }
	if (!images.ExportGrayscale()) { return 2; }
	images.OutputColorPixels();
	images.Show();
	waitKey(0);
	return 0;
}
