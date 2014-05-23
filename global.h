//
//  global.h
//  boggle_ots
//
//  Created by Timothy Caldwell on 6/18/13.
//  Copyright (c) 2013 Timothy Caldwell. All rights reserved.
//

#ifndef boggle_ots_global_h
#define boggle_ots_global_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;


//Common word roots.  Checking if these are in the cube first can drastically reduce the number of words to be checked. 
//1-letter roots of words
const vector<string> roots1 = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
//2-letter roots of words
const vector<string> roots2 = {"ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "ak", "al", "am", "an", "ap", "ar", "as", "at", "au", "av", "aw", "ax", "ay", "az", "ba", "bb", "be", "bi", "bl", "bo", "br", "bs", "bu", "by", "ca",   "cc", "ce", "ch", "ci", "ck", "cl", "co", "cr", "ct", "cu", "cy", "da", "dd", "de", "dg", "di", "dl", "do", "dr", "ds", "du", "dw", "dy", "ea", "eb", "ec", "ed", "ee", "ef", "eg", "eh", "ei", "el", "em", "en", "eo", "ep", "eq", "er", "es", "et", "eu", "ev", "ew", "ex", "ey", "fa", "fe", "ff", "fi", "fl", "fo", "fr", "ft", "fu", "fy", "ga", "ge", "gg", "gh", "gi", "gl", "gn", "go", "gr", "gu", "gy", "ha", "he", "hi", "hm", "ho", "hr", "ht", "hu", "hy", "ia", "ib", "ic", "id", "ie", "if", "ig", "ik", "il", "im", "in", "io", "ip", "ir", "is", "it", "iu", "iv", "ix", "iz", "ja", "je", "jo", "ju", "ka", "ke", "ki", "kl", "kn", "ko", "ks", "ky", "la", "lb", "lc", "ld", "le", "lf", "lg", "li", "lk", "ll", "lm", "lo", "lp", "ls", "lt", "lu", "lv", "ly", "ma", "mb", "mc", "me", "mi", "mm", "mo", "mp", "mu", "my", "na", "nb", "nc", "nd", "ne", "nf", "ng", "nh", "ni", "nk", "nn", "no", "ns", "nt", "nu", "nv", "ny", "oa", "ob", "oc", "od", "oe", "of", "og", "oi", "ok", "ol", "om", "on", "oo", "op", "or", "os", "ot", "ou", "ov", "ow", "ox", "oy", "pa", "pe", "ph", "pi", "pl", "po", "pp", "pr", "ps", "pt", "pu", "py", "qu", "ra", "rb", "rc", "rd", "re", "rf", "rg", "rh", "ri", "rk", "rl", "rm", "rn", "ro", "rp", "rr", "rs", "rt", "ru", "rv", "ry", "sa", "sc", "se", "sh", "si", "sk", "sl", "sm", "sn", "so", "sp", "sq", "ss", "st", "su", "sw", "sy", "ta", "tc", "te", "th", "ti", "tl", "to", "tr", "ts", "tt", "tu", "tw", "ty", "ua", "ub", "uc", "ud", "ue", "uf", "ug", "ui", "ul", "um", "un", "uo", "up", "ur", "us", "ut", "va", "ve", "vi", "vo", "wa", "we", "wh", "wi", "wn", "wo", "wr", "xi", "xp", "xt", "ya", "yc", "yd", "ye", "yl", "ym", "yn", "yo", "yp", "yr", "ys", "yt", "za", "ze"};
//3-letter roots of words
const vector<string> roots3 = {"abi","abl","abo","acc","ace","ach","aci","ack","act","acy","add","ade","adi","ado","aff","age","agg","agn","ago","ail","ain","air","ake","ala","ald","ale","ali","all","alo","alt","ama","amb","ame","ami","amo","amp","ana","anc","and","ane","ang","ani","ank","ann","ano","ans","ant","ape","aph","app","ara","arb","arc","ard","are","arg","ari","ark","arl","arm","aro","arr","ars","art","ary","ase","ash","asi","ass","ast","ata","ate","ath","ati","ato","atr","att","atu","aus","aut","ave","avi","bac","bal","ban","bar","bas","bat","bea","bel","ben","ber","bet","bil","bin","bit","bla","ble","blo","boa","bol","bon","boo","bor","bou","bra","bre","bri","bro","bul","bur","bus","but","cab","cal","can","cap","car","cas","cat","cel","cen","cep","cer","ces","cha","che","chi","cho","chr","chu","cia","cio","cis","cit","cke","ckl","cla","cle","cli","clo","col","com","con","cop","cor","cou","cra","cre","cri","cro","cta","cti","cto","ctr","ctu","cul","cum","cur","cus","dal","dan","dec","def","del","dem","den","dep","der","des","dge","dia","dic","din","dio","dis","dit","dle","don","dow","dra","dre","dri","dro","duc","ead","eak","eal","ean","ear","eas","eat","ece","eci","eck","eco","ect","ecu","ede","edi","eed","een","eer","ega","eig","ein","ela","eld","ele","eli","ell","elo","ema","emb","eme","emi","emo","emp","ena","enc","end","ene","eni","enn","eno","ens","ent","eou","epi","ept","equ","era","erb","erc","ere","erg","eri","erl","erm","ern","ero","erp","err","ers","ert","erv","ery","esc","ese","esi","esp","ess","est","eta","ete","eth","eti","eto","etr","ett","eur","eve","evi","exc","exp","ext","fer","ffe","ffi","fic","fie","fin","fis","fla","fle","flo","flu","for","fra","fre","gal","gan","gar","gat","gen","ger","ggi","ght","gin","gla","gle","gon","gra","gre","gri","gro","gue","gui","hal","ham","han","har","hat","hea","hel","hem","hen","her","hes","het","hic","hil","hin","his","hol","hom","hon","hoo","hor","hos","hou","hro","ial","ian","iat","ibl","ica","ice","ich","ici","ick","ico","ict","icu","ida","ide","idi","iel","ien","ier","iet","iff","ify","iga","igh","ign","ike","ila","ile","ili","ill","ima","ime","imi","imp","ina","inc","ind","ine","inf","ing","ini","ink","inn","ino","ins","int","inv","ion","iou","ire","isc","ise","ish","isi","ism","iso","iss","ist","ita","ite","ith","iti","ito","itt","itu","ity","ium","iva","ive","ivi","ken","ker","ket","kin","kle","lac","lad","lag","lai","lam","lan","lar","las","lat","lau","lay","lea","lec","led","leg","lem","len","ler","les","let","ley","lia","lic","lie","lig","lim","lin","lio","lis","lit","lla","lle","lli","llo","lly","loc","log","lon","loo","lor","lot","lou","low","lum","lus","lut","lve","mac","mag","mal","man","mar","mas","mat","mbe","med","mel","men","mer","met","mic","mid","mil","min","mis","mit","mma","mme","mol","mon","mor","mot","mou","mpa","mpe","mpl","mpo","mpr","mpt","mul","mus","nal","nan","nar","nat","nce","nch","nci","nco","nda","nde","ndi","ndo","ndr","nel","ner","nes","net","ney","nge","ngl","nia","nic","nis","nit","nne","nni","nom","nor","not","nou","nse","nsi","nso","nst","nta","nte","nth","nti","nto","ntr","nve","oar","oat","oca","och","ock","ode","odi","off","oge","ogr","ogy","oid","oin","oke","ola","old","ole","oli","oll","olo","olu","oly","oma","omb","ome","omi","omm","omo","omp","ona","onc","ond","one","onf","ong","oni","onn","ono","ons","ont","ony","ood","ook","ool","oom","oot","ope","oph","opo","ora","ord","ore","ori","ork","orm","orn","oro","orp","orr","ors","ort","ory","ose","osi","osp","oss","ost","ota","ote","oth","oti","ott","oug","oun","our","ous","out","ove","owe","own","pal","pan","par","pas","pat","pea","pec","pel","pen","per","pet","pha","phe","phi","pho","phy","pic","pin","pit","pla","ple","pli","pol","pon","por","pos","pot","ppe","pre","pri","pro","pti","qua","que","qui","rab","rac","rad","rag","rai","ral","ram","ran","rap","ras","rat","rav","rbo","rce","rch","rdi","rea","rec","red","ree","ref","reg","rel","rem","ren","rep","res","ret","rev","rge","ria","rib","ric","rid","rie","rig","ril","rim","rin","rio","rip","ris","rit","riv","rma","rmi","rna","rne","roa","rob","roc","rog","rol","rom","ron","roo","rop","ros","rot","rou","rov","row","rra","rre","rri","rro","rry","rse","rsi","rso","rte","rth","rti","rum","run","rus","sab","sal","san","sca","sce","sch","sco","scr","sec","sel","sen","ser","sha","she","shi","sho","sia","sib","sic","sid","sil","sin","sio","sis","sit","siv","sma","sol","som","son","sor","spa","spe","spi","spo","squ","ssa","sse","ssi","sso","sta","ste","sti","sto","str","stu","sup","sur","tab","tac","tag","tai","tal","tan","tar","tat","tch","tea","tee","tel","tem","ten","ter","tes","tha","the","thi","tho","thr","thy","tia","tic","til","tim","tin","tio","tis","tit","tiv","tle","tom","ton","top","tor","tra","tre","tri","tro","tru","try","tta","tte","tti","ttl","tua","tud","tur","ual","uar","uck","uct","ude","uff","ugh","uis","uit","ula","ule","ull","ult","umb","ume","ump","unc","und","ung","uni","unt","ura","ure","urg","uri","urn","urr","urs","urt","use","ush","usi","ust","uta","ute","uth","uti","uto","utt","val","van","vel","ven","ver","ves","vil","vin","vis","vol","wal","war","wat","way","wel","whe","whi","wil","win","wit","woo","wor"};

template <typename t>
vector<t> vec_union(const vector<t>& v1, const vector<t>& v2){
    vector<t> v3;
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}

template <typename t>
vector<t> inter(const vector<t>& v1, const vector<t>& v2){
    vector<t> v3;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}

template <typename t>
vector<t> differ(const vector<t>& v1, const vector<t>& v2){
    vector<t> v3;
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}


#endif
