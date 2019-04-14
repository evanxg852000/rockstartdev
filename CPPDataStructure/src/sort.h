#include <algorithm>

template<typename T>
void bubleSort(T arr[], int len){
	for(int i=0; i<len; i++){
		for(int j=0; j<i; j++){
			if(arr[i] < arr[j]){
				std::swap(arr[i], arr[j]);
			}
		}
	}
}

template<typename T>
void insertionSort(T arr[], int len){
	for(int i=1; i < len; i++){
		auto tmp = arr[i];
		int j;
		for(j=i-1; j>=0 && arr[j] > tmp; j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = tmp;
	}
}

template<typename T>
void selectionSort(T arr[], int len){
	int min;
	for(int i=0; i< len; i++){
		min = i;
		for(int j= i+1; j < len ; j++){
			if(arr[j]< arr[min])
				min = j;
		}
		std::swap(arr[i], arr[min]);
	}
}

template<typename T>
void mergeSort(T arr[], int len){

}


template<typename T>
void quickSort(T arr[], int len){

}







