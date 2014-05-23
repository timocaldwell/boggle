//
//  Header.h
//  boggle_ots
//
//  Created by Timothy Caldwell on 6/18/13.
//  Copyright (c) 2013 Timothy Caldwell. All rights reserved.
//

#ifndef boggle_ots_Boggle_h
#define boggle_ots_Boggle_h


#include "global.h"


class Boggle {
private:
    ifstream words_file;
    string* cube;
    vector<string> dict;
    
    //range of numbers {1, 2, 3, ... } so do not need to calculate each time needed.
    vector<int> dict_range;
    vector<int> roots2_range;
    vector<int> roots3_range;
    
    //map of primitive word roots to dict or roots with more letters containing the roots.
    vector<vector<int>> roots1_map2dict;
    vector<vector<int>> roots1_map2roots2;
    vector<vector<int>> roots1_map2roots3;
    vector<vector<int>> roots2_map2dict;
    vector<vector<int>> roots2_map2roots3;
    vector<vector<int>> roots3_map2dict;
    
    //location of words in dict with all word roots in roots1, roots2, and roots3 that are in cube.
    vector<int> not_weeded;
    
    int cube_count = 0;
    vector<vector<int>> letter_cubies; //cubie location (0 - 63) for each letter.
    vector<vector<int>> neighb_cubies; //neibhoring cubie locations (0 - 63) for each cubie.
    
    struct cubie_t;
    
    void read_dict(ifstream&);
    void find_nieghb_cubies();
    int coords2cubie(int*);    
    void cubie2coords(int, int*);
    int letter2val(char);
    vector<vector<int>> words_map(const vector<string>&, const vector<string>&);
    vector<int> words_weeded(const vector<vector<int>>&, const  vector<int>&);
public:
    Boggle(const char *);
    ~Boggle();
    
    bool test_word(string);
    void set_cube(string*);
    int test_dictionary();
};



#endif
