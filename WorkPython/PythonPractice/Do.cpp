#include <sound_play/sound_play.h>


int main (int argc, char **argv)
{
sound_play::SoundClient sc;
sound_play::Sound s1 = sc.waveSound("Bike_Bell.wav");
s1.repeat();
sleepok(1, _nh);
s1.stop();
}
