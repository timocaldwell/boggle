//
//  boggle.cpp
//  boggle_ots
//
//  Created by Timothy Caldwell on 6/18/13.
//  Copyright (c) 2013 Timothy Caldwell. All rights reserved.
//

#include "boggle.h"

//Stack type for testing if a word is in the cube.  Each stack entry holds candidate cubies which are neighboring cubie locations of the correct letter.  Each stack entry also keeps track of the cubies locations already used so that they are not used again.
struct Boggle::cubie_t {
    stack<int,vector<int>> cand_cubies; //candidate cubies
    vector<int> used_cubies; //used cubies
};

Boggle::Boggle(const char words_file_name[]){
    words_file.open(words_file_name);
    
    read_dict(words_file);
    find_nieghb_cubies();
    
    roots1_map2dict = words_map(roots1,dict);
    
    roots2_map2dict = words_map(roots2,dict);
    roots1_map2roots2 = words_map(roots1,roots2);
    
    roots1_map2roots3 = words_map(roots1,roots3);
    roots2_map2roots3 = words_map(roots2,roots3);
    roots3_map2dict = words_map(roots3,dict);
    
    for(unsigned ii = 0; ii != dict.size(); ++ii)
        dict_range.push_back(ii);
    for(unsigned ii = 0; ii != roots2.size(); ++ii)
        roots2_range.push_back(ii);
    for(unsigned ii = 0; ii != roots3.size(); ++ii)
        roots3_range.push_back(ii);
}

Boggle::~Boggle(){
    words_file.close();
}

void Boggle::read_dict(ifstream& words_file) {
    string word;
    unsigned iter = 0;
    locale loc;
    bool skip_word = false;
    
    while(words_file.is_open() && words_file.good()) {
        skip_word = false;
        getline(words_file,word);
        for (size_t ii=0; ii<word.length(); ++ii) {
            if (!isalpha(word[ii])) {
                skip_word = true; //Do not include non-alphabet words
                continue;
            }
            word[ii] = tolower(word[ii],loc); //Upper case -> lower case
        }
        if(!skip_word && word.length()!=0){
            dict.push_back(word);
            iter++;
        }
    }
    words_file.close();
}

// Calculates the cubie neighbors to each cubie.
void Boggle::find_nieghb_cubies(){
    int coords_cur[3], coords_neighb[3];
    int n_cubie;
    
    cout << endl;
    for(unsigned iter=0; iter<64; ++iter){
        vector<int> n_cubies_iter;
        cubie2coords(iter,coords_cur);
        for(int ii=coords_cur[0]-1; ii<=coords_cur[0]+1; ++ii){
            for(int jj=coords_cur[1]-1; jj<=coords_cur[1]+1; ++jj){
                for(int kk=coords_cur[2]-1; kk<=coords_cur[2]+1; ++kk){
                    if(ii>=0 && jj>=0 && kk>=0 && ii<=3 && jj<=3 && kk<=3){
                        coords_neighb[0] = ii;
                        coords_neighb[1] = jj;
                        coords_neighb[2] = kk;
                        n_cubie = coords2cubie(coords_neighb);
                        if(n_cubie!=iter)
                            n_cubies_iter.push_back(n_cubie);
                    }
                }
            }
        }
        neighb_cubies.push_back(n_cubies_iter);
    }
}

//cubie has value 0-63, coords has value {0-3,0-3,0-3}
int Boggle::coords2cubie(int coords[3]){
    return 16*coords[0] + 4*coords[1] + coords[2];
}

void Boggle::cubie2coords(int cubie, int coords[]){
    div_t  divresult;
    divresult = div(cubie,16);
    coords[0] = divresult.quot;
    divresult = div(cubie-coords[0]*16,4);
    coords[1] = divresult.quot;
    coords[2] = cubie-coords[1]*4-coords[0]*16;
}

//transforms 'a'-'z'-> 0-25
int Boggle::letter2val(char letter){
    return int(letter-97); //97 is 'a'
}

//Finds which words contain which roots and returns the mapping.
vector<vector<int>> Boggle::words_map(const vector<string>& roots, const vector<string>& words){
    vector<int> vec;
    vector<vector<int>> map;
    for(vector<string>::const_iterator roots_it = roots.begin(); roots_it!=roots.end(); ++roots_it){
        vec.clear();
        for(unsigned jj = 0; jj<words.size(); ++jj){
            if(words[jj].find(*roots_it)!=-1)
                vec.push_back(jj);
        }
        map.push_back(vec);
    }
    return map;
}

//Given primitive roots not in cube and the mapping of primitive roots to words or primary roots containing the primitive roots, returns location of words or primary roots not in cube.
vector<int> Boggle::words_weeded(const vector<vector<int>>& roots_map,const  vector<int>& roots_nin_cube){
    vector<int> weeded;
    for(vector<int>::const_iterator it = roots_nin_cube.begin(); it != roots_nin_cube.end(); ++it){
        weeded = vec_union(weeded,roots_map.at(*it));
    }
    return weeded;
}

bool Boggle::test_word(string word)
{
    stack<cubie_t,vector<cubie_t>> test_stack;
    vector<int> vec1;
    vector<int>* p_vec;
    int next_cubie;
    size_t word_len = word.length();
    cubie_t cubie_info;
    
    //Checking the reverse word may require fewer iterations of the loop if there are fewer letters in the cube of the word's last letter than the word's first letter.
    if(letter_cubies[letter2val(word[0])].size()>letter_cubies[letter2val(word[word.size()-1])].size())
        word = string(word.rbegin(), word.rend()); // reverse letters in word.
    
    //initial candidate cubies are all cubies with first letter of word
    p_vec = &letter_cubies[letter2val(word[0])];
    for(vector<int>::const_iterator it = p_vec->begin() ; it != p_vec->end(); ++it)
        cubie_info.cand_cubies.push(*it);
    
    test_stack.push(cubie_info);
    
    while(test_stack.empty()!=true){
        if(test_stack.top().cand_cubies.size()!=0){
            if(test_stack.size()>=word_len)// Full word is in cube -- SUCCESS!!
                return true;
            
            // take step in new path
            next_cubie = test_stack.top().cand_cubies.top();
            test_stack.top().cand_cubies.pop();
            
            // clear cubie_info
            cubie_info.used_cubies.clear();
            while(!cubie_info.cand_cubies.empty())
                cubie_info.cand_cubies.pop();
            
            // next "used cubies" are previous cubie's "used cubies" and next_cubie
            cubie_info.used_cubies = test_stack.top().used_cubies;
            cubie_info.used_cubies.push_back(next_cubie);
            sort(cubie_info.used_cubies.begin(),cubie_info.used_cubies.end()); //used cubies might not already be sorted.
            
            // next "candidate cubies" are neighboring cubies to next_cubie of correct letter that have not been used
            vec1 = inter(letter_cubies[letter2val(word[test_stack.size()])], neighb_cubies[next_cubie]);
            vec1 = differ(vec1,cubie_info.used_cubies);
            for(vector<int>::const_iterator it = vec1.begin(); it != vec1.end(); ++it)
                cubie_info.cand_cubies.push(*it);
            
            test_stack.push(cubie_info);
        }
        else{ //word not found in this path
            test_stack.pop();
        }
    }
    return false;
}

//Initializes boggle game for new cube.
void Boggle::set_cube(string* cube_in){
    cube = cube_in;
    vector<int> empty_vec;
    
    // to keep track of roots not in cube.
    vector<int> unused_roots1;
    vector<int> unused_roots2;
    vector<int> unused_roots3;
    
    // to keep track of roots not already removed by checking if roots of less size are in cube.
    vector<int> roots2_not_weeded;
    vector<int> roots3_not_weeded;
    
    // Sets cubie location (0-63) for each letter
    letter_cubies.assign(26,empty_vec);
    for(unsigned ii = 0; ii<64; ++ii){
        letter_cubies[letter2val(cube->at(ii))].push_back(ii);
    }
    
    // keep track of 1-letter roots not in cube.
    for(unsigned ii = 0; ii<letter_cubies.size(); ++ii){
        if(letter_cubies[ii].size()==0)
            unused_roots1.push_back(ii);
    }
    
    // keep track of 2-letter roots not in cube.
    roots2_not_weeded = roots2_range;
    roots2_not_weeded = differ(roots2_not_weeded, words_weeded(roots1_map2roots2, unused_roots1)); // don't check 2-letter roots already removed by 1-letter roots.
    for(vector<int>::const_iterator it = roots2_not_weeded.begin(); it != roots2_not_weeded.end(); ++it){
        if(!test_word(roots2[*it]))
            unused_roots2.push_back(*it);
    }
    
    // keep track of 3-letter roots not in cube.
    roots3_not_weeded = roots3_range;
    roots3_not_weeded = differ(roots3_not_weeded, words_weeded(roots1_map2roots3, unused_roots1)); // don't check 3-letter roots already removed by 1-letter roots.
    roots3_not_weeded = differ(roots3_not_weeded, words_weeded(roots2_map2roots3, unused_roots2)); // don't check 3-letter roots already removed by 2-letter roots.
    for(vector<int>::const_iterator it = roots3_not_weeded.begin(); it != roots3_not_weeded.end(); ++it){
        if(!test_word(roots3[*it]))
            unused_roots3.push_back(*it);
    }
    
    // keep the word locations of words whose roots in cube (i.e. words which haven't been weeded).
    not_weeded = dict_range;
    not_weeded = differ(not_weeded,words_weeded(roots1_map2dict, unused_roots1));
    not_weeded = differ(not_weeded,words_weeded(roots2_map2dict, unused_roots2));
    not_weeded = differ(not_weeded,words_weeded(roots3_map2dict, unused_roots3));
}

int Boggle::test_dictionary(){
    int count = 0;
    for(vector<int>::const_iterator it = not_weeded.begin(); it!=not_weeded.end(); ++it){
        if(test_word(dict[*it])) // only test words not weeded
            count++;
    }
    return count;
}

