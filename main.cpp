//
//  main.cpp
//  boggle_ots
//
//  Created by Timothy Caldwell on 5/20/13.
//  Copyright (c) 2013 Timothy Caldwell. All rights reserved.
//

#include <ctime>


#include "boggle.h"
#include "global.h"


bool next_cube_line(ifstream& cubes_file, string* cubies) {
    if (cubes_file.is_open() && cubes_file.good()) {
        getline(cubes_file,*cubies);
        if(cubies->size()!=64) // check size: 4x4x4 = 64
            return false;
    }
    else {
        cubes_file.close();
        return false;
    }
    return true;
}

int main(int argc, const char * argv[])
{
    clock_t t_start = clock();
    ifstream cubes_file;
    string cube[64];
    int cube_count = 0;
    vector<int> num_in_cube;
    
    if (argc!=3) {
        cout << "Needs exactly 2 arguments" << endl;
        return 0;
    }
    
    Boggle boggle(argv[2]); 
    cubes_file.open(argv[1]);
    
    //tests dictionary on each cube.
    while(next_cube_line(cubes_file, cube)){
        cube_count++;
        boggle.set_cube(cube);
        num_in_cube.push_back(boggle.test_dictionary());
    }
    for(vector<int>::const_iterator it = num_in_cube.begin(); it != num_in_cube.end(); ++it)
        cout << *it << endl;
    
    cout << "scored " << cube_count << " cubes with dimension 4 in " << ((float)(clock()-t_start))/CLOCKS_PER_SEC << " seconds." << endl;
 
    return 0;
}
