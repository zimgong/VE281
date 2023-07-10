#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>

using namespace std;

// A point
struct point
{
    int x;
    int y;
};

// ccw
long ccw(point p1, point p2, point p3) {
    return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}

// std_sort implementation
template<typename T, typename Compare>
void std_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    std::sort(vector.begin(), vector.end(), comp);
}

// A compare function with operation override
struct CompareLess {
    point p0;

    bool operator()(point &lvec, point &rvec) const {
        return ccw(p0, lvec, rvec) > 0;
    } 
};

// Graham scan 
vector<point> graham_scan(std::vector<point> &vector) {    
    std::vector<point> stack_vec;

    if (vector.size() <= 1)
    {
        return vector;
    }

    // Locate the point with lowest y, then lowest x
    for (size_t i = 1; i < vector.size(); i++)
    {
        if (vector[i].y < vector[0].y || (vector[i].y == vector[0].y && vector[i].x < vector[0].x))
        {
            swap(vector[0], vector[i]);
        }  
    }
    point p0 = vector[0];
    
    // Remove duplicate p0
    std::vector<point> vec_new;

    for (size_t i = 1; i < vector.size(); i++)
    {
        if (!(vector[i].x == p0.x && vector[i].y == p0.y))
        {
            vec_new.emplace_back(vector[i]);
        }
    }

    // Return for only one point scenario
    if (vec_new.size() <= 0)
    {
        vec_new.emplace_back(p0);
        return vec_new;
    }

    // Sort the points
    std_sort(vec_new, CompareLess{p0});

    // Remove points with same angle with x axis
    std::vector<point> space;
    space.emplace_back(vec_new[0]);

    for (unsigned long i = 1; i < vec_new.size(); i++)
    {
        if (ccw(vec_new[i-1], vec_new[i], p0) == 0)
        {
            if ((vec_new[i].x-p0.x)*(vec_new[i].x-p0.x) > (vec_new[i-1].x-p0.x)*(vec_new[i-1].x-p0.x))
            {
                space.pop_back();
                space.emplace_back(vec_new[i]);
            }
        }  
        else
        {
            space.emplace_back(vec_new[i]);
        }
    }

    // Core of Graham Scan 
    stack_vec.emplace_back(p0);

    for (unsigned long i = 0; i < space.size(); i++)
    {        
        while (stack_vec.size()>1 && ccw(stack_vec[stack_vec.size()-2], stack_vec.back(), space[i])<=0)
        {
            stack_vec.pop_back();
        }
        stack_vec.emplace_back(space[i]);
    }
    return stack_vec;
}

int main() {
    int size;
    int x, y;
    point p;
    std::vector<point> set;

    cin >> size;
    if (size==0)
    {
        return 0;
    }
    
    for (int i = 0; i < size; i++)
    {
        cin >> x >> y;
        p.x = x;
        p.y = y;
        set.emplace_back(p);
    }
    
    std::vector<point> sorted_set = graham_scan(set);

    for (unsigned long i = 0; i < sorted_set.size(); i++)
    {
        p = sorted_set[i];
        x = p.x;
        y = p.y;
        cout << x << " " << y << endl;
    }
    
    return 0;
}