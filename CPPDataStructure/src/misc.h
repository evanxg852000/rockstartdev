#include <cstdlib>
#include <ctime>

int generate_random(int min, int max){
	srand(static_cast<unsigned int>(time(0)));
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0) ;
	return min + static_cast<int>( (max - min + 1) * (rand() * fraction) );
}
