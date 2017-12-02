#include "global.h"
#include "Frame.h"
#include "Square.h"

using namespace std;

Frame drawFrame;

int main() {
	const char * cmd =
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         "
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               "
		"-i -                "
		"-pix_fmt yuv420p    "
		"-vcodec mpeg4       "
		"-an                 "
		"-q:v 5              "
		"output.mp4          ";

#ifdef _WIN32
	FILE * pipe = _popen(cmd, "wb");
#else
	FILE * pipe = popen(cmd, "w");
#endif
	if (pipe == nullptr) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}

	vector<Square>sqr;

	Square s1(45, 45, 150, 50, 0xff, 0x00, 0xff);
	s1.setSpeed(5, 4);
	Square s2(45, 45, 200, 55, 0xff, 0x00, 0x00);
	s2.setSpeed(2, 7);
	Square s3(45, 45, 5, 150, 0x00, 0x00, 0xff);
	s3.setSpeed(3, 4);
	Square s4(45, 45, 30, 5, 0x00, 0xff, 0x00);
	s4.setSpeed(1, 5);

	sqr.push_back(s1);
	sqr.push_back(s2);
	sqr.push_back(s3);
	sqr.push_back(s4);

	auto num_frames = (duration_in_seconds * frames_per_second);
	for (int i = 0; i < num_frames; ++i) {
		double dt = i / frames_per_second;
		drawFrame.clear();
		for (auto &j : sqr) {
			j.draw(drawFrame);
			j.update(dt);
		}
		drawFrame.write(pipe);
	}

	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif
	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;
	return 0;
}