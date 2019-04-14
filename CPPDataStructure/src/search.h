#include <algorithm>
/*
TODO
  4 chapters
  2 articles [functional, part 3]
  2 videos
*/
template<typename T>
std::vector<std::pair<T, int>> enumerate(T arr[], int len){
	std::vector<std::pair<T, int>> r;
	for(int i = 0; i< len; i++){
		r.push_back(std::make_pair(arr[i], i));
	}
	return r;
}

template<typename T>
int linearSearch(T arr[], int len, T key){
	int rst = -1;
	auto it = enumerate<T>(arr, len);
	std::for_each(it.begin(), it.end(), [&](const std::pair<T, int> v){
		if (v.first == key)
			rst = v.second ;
	});
	return rst;
}


template<typename T>
int binarySearch(T arr[], T key, int start, int end){
	if(start > end)
		return -1;

	int mid = start + (end-start) / 2;
	if(arr[mid] == key)
		return mid;
	if(arr[mid] > key)
		return binarySearch(arr, key, 0, mid-1);
	else
		return binarySearch(arr, key, mid+1, end);
}
