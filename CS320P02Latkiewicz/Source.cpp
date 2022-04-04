//Karly Latkiewicz

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Point.h"
#include <vector>
using namespace std;

pair<Point, Point> bruteForce(vector<Point> P, int n) {

	double min = P[0].distance(P[1]);
	pair<Point, Point> points(P[0], P[1]);

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; ++j) {
			if (P[i].distance(P[j]) < min) {
				min = P[i].distance(P[j]);
				points = make_pair(P[i], P[j]);
			}
		}
	}
	return points;
}

pair<Point, Point> stripClosest(vector<Point> strip, pair<Point, Point> closest2) {

	// first gets you the first of a pair, second gives you the second 
	double min = closest2.first.distance(closest2.second);
	pair<Point, Point> Fclosest = closest2;
	int size = strip.size();

	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size && (strip[j].getY() - strip[i].getY()) < min; j++) {
			if (strip[i].distance(strip[j]) < min) {
				min = strip[i].distance(strip[j]);
				Fclosest = make_pair(strip[i], strip[j]);
			}
		}
	}
	return Fclosest;

}


pair<Point, Point> closest(vector<Point> points) {

	auto n = points.size();
	if (n <= 4) {
		return bruteForce(points, n);
	}
	
	auto middle = n / 2;
	Point midPoint = points[middle];
	
	vector<Point> firstHalf(points.begin(), points.begin() + middle);
	vector<Point> secondHalf(points.begin() + middle, points.end());

	
	auto dl = closest(firstHalf);
	auto dr = closest(secondHalf);

	double min1 = dl.first.distance(dl.second);
	double min2 = dr.first.distance(dr.second);

	double minX = (min1 < min2) ? min1 : min2;
	auto d = (min1 < min2) ? dl : dr;


	vector<Point> strip;
	
	for (int i = 0; i < n; i++) {
		if (abs(points[i].getX() - midPoint.getX()) < minX){
			strip.push_back(points[i]);

		}
	}
	return stripClosest(strip, d);

}

template <class T>
void mergeSort(vector<Point> & points, T compare, int n) {

	if (n > 1) {
		int m = n / 2;
		int x = n - m;

		vector<Point> firstHalf(points.begin(), points.begin() + m);
		vector<Point> secondHalf(points.begin() + m, points.end());

		mergeSort(firstHalf, compare, m);
		mergeSort(secondHalf, compare, x);

		merge(m, x, firstHalf, secondHalf, points, compare);
	}
	
}

template <class T>
void merge(int a, int b, vector<Point> c, vector<Point> d, vector<Point> & e, T compare) {
	int x = 0, y = 0, z = 0;

	while (x < a && y < b) {
		if (compare(c[x], d[y])) {
			e[z] = c[x];
			x++;
		}
		else {
			e[z] = d[y];
			y++;
		}
		z++;
	}

	
	while (x < a) {
		if (z < a + b) {
			e[z] = c[x];
			x++;
			
		}
		z++;
	}
	while (y < b) {
		if (z < a + b) {
			e[z] = d[y];
			y++;
		}
		z++;
	}

}





int main() {
	string file;
	//Prompt user for filename
	cout << "Enter Filename: ";
	cin >> file;
	//Open file for reading
	ifstream infile;
	infile.open(file);
	//check if file in there
	if (!infile) {
		cout << "Not in file";
		return 0;
	}
	//use only text files
	if (file.find(".txt") == (file.length()-4)) {
		//read file
		//unsigned numOfPoints = 0;
		// while(infile >> ws && !infile.eof() && numOfPoints < MAX_NUM_POINTS)
		vector<Point> points;
		while (!infile.eof()) {
			Point p;
			infile >> p;
			points.push_back(p);
		}
		infile.close();
		pair<Point, Point> c = closest(points);
		double d = c.first.distance(c.second);
		cout << "Closest points are: (" << c.first << ") and (" << c.second << ") with distance = " << d << endl;
		
	}
	else {
		cout << "File must be a txt file" << endl;
	}

	
}