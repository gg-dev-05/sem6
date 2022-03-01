// C++ program for implementing Sutherland–Hodgman 
// algorithm for polygon clipping 
#include<bits/stdc++.h>
using namespace std;
#define db double
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)
struct P{
    db x;
    db y;
};
struct Line{
    P p1;
    P p2;
};

// Returns x-value of point of intersectipn of two 
// lines 
db x_intersect(db x1, db y1, db x2, db y2, 
				db x3, db y3, db x4, db y4) 
{ 
	db num = (x1*y2 - y1*x2) * (x3-x4) - 
			(x1-x2) * (x3*y4 - y3*x4); 
	db den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 
	return num/den; 
} 

// Returns y-value of point of intersectipn of 
// two lines 
db y_intersect(db x1, db y1, db x2, db y2, 
				db x3, db y3, db x4, db y4) 
{ 
	db num = (x1*y2 - y1*x2) * (y3-y4) - 
			(y1-y2) * (x3*y4 - y3*x4); 
	db den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 
	return num/den; 
} 

// This functions clips all the edges w.r.t one clip 
// edge of clipping area 
void clip(vector<P> &poly_points, int &poly_size, 
		db x1, db y1, db x2, db y2) 
{ 
	vector<P> new_points;

	// (ix,iy),(kx,ky) are the co-ordinate values of 
	// the points 
	rep(i,poly_size) 
	{ 
		// i and k form a line in polygon 
		int k = (i+1) % poly_size; 
		db ix = poly_points[i].x, iy = poly_points[i].y; 
		db kx = poly_points[k].x, ky = poly_points[k].y; 

		// Calculating position of first point 
		// w.r.t. clipper line 
		db i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1); 

		// Calculating position of second point 
		// w.r.t. clipper line 
		db k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1); 

		// Case 1 : When both points are inside 
		if (i_pos < 0 && k_pos < 0) 
		{ 
			//Only second point is added 
            new_points.pb({kx,ky});
		} 

		// Case 2: When only first point is outside 
		else if (i_pos >= 0 && k_pos < 0) 
		{ 
			// Point of intersection with edge 
			// and the second point is added 
			new_points.pb({x_intersect(x1, 
							y1, x2, y2, ix, iy, kx, ky),y_intersect(x1, 
							y1, x2, y2, ix, iy, kx, ky)});
            new_points.pb({kx,ky});
		} 

		// Case 3: When only second point is outside 
		else if (i_pos < 0 && k_pos >= 0) 
		{ 
			//Only point of intersection with edge is added 
            new_points.pb({x_intersect(x1, 
							y1, x2, y2, ix, iy, kx, ky),y_intersect(x1, 
							y1, x2, y2, ix, iy, kx, ky)});
		} 

		// Case 4: When both points are outside 
		else
		{ 
			//No points are added 
		} 
	} 

	// Copying new points into original array 
	// and changing the no. of vertices 
	poly_size   = new_points.size();
    poly_points = new_points;
} 

// Implements Sutherland–Hodgman algorithm 
void suthHodgClip(vector<P> &poly_points, int &poly_size, 
				vector<P> &clipper_points, int &clipper_size) 
{ 
	//i and k are two consecutive indexes 
	rep(i, clipper_size) 
	{ 
		int k = (i+1) % clipper_size; 

		// We pass the current array of vertices, it's size 
		// and the end points of the selected clipper line 
		clip(poly_points, poly_size, clipper_points[i].x, 
			clipper_points[i].y, clipper_points[k].x, 
			clipper_points[k].y); 
	} 

	// Printing vertices of clipped polygon 
	rep(i,poly_size) 
		cout << '(' << poly_points[i].x << 
				", " << poly_points[i].y << ") ";
    cout<<"\n"; 
} 

//Driver code 
int main() 
{ 
	// Defining polygon vertices in clockwise order 
	int poly_size;
    cout<<"Enter number of vertices in the polygon to be clipped: ";
    cin>>poly_size;
    vector<P> poly_points(poly_size);
    cout<<"Start entering (x,y) points of the polygon to be clipped...\n";
    rep(i,poly_size){
        cin>>poly_points[i].x>>poly_points[i].y;
    }
	// Defining clipper polygon vertices in clockwise order 
	// 1st Example with square clipper 
	int clipper_size;
    cout<<"Enter number of vertices in the clipping window: ";
    cin>>clipper_size;
    vector<P> clipper_points(clipper_size);
    rep(i,clipper_size){
        cin>>clipper_points[i].x>>clipper_points[i].y;
    }

	// 2nd Example with triangle clipper 
	/*int clipper_size = 3; 
	int clipper_points[][2] = {{100,300}, {300,300}, 
								{200,100}};*/

	//Calling the clipping function 
	suthHodgClip(poly_points, poly_size, clipper_points, clipper_size); 

	return 0; 
} 
