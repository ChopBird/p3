#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
#include<cassert>
#include <map>
#include<regex>
#include <fstream>
class pirateSpeak{
public:

std::string tolower(std::string s) const{                                   
    for (int i = 0; i < s.length();i++){                                        
        s[i] = std::tolower(s[i]);                                              
    }                                                                           
    return s;                                                                   
}

std::string getWord(std::string str, int &start) const{
    std::string ret;
    while(isspace(str[start])) start++;
    while(start < str.size() && !isspace(str[start])&&!ispunct(str[start])){
        ret.push_back(str[start]);
        start++;
    }

    //eats spaces between words
    
    return ret; 
}

//returns str with words with pirate translations replaced by those translations
std::string translate(std::string str) const{
    int index = 0;
    int wordstart = 0;
    std::string ret = str;
    while (ret[index] != '\0'){
        if (isspace(ret[index]) || ispunct(ret[index])){
            index++;
            wordstart++;
            continue;
        }
        std::string gotWord = getWord(ret,index);
        auto lookUp = dict.find(tolower(gotWord));
        auto word = lookUp!=dict.end()?lookUp->second:tolower(gotWord);
        
        //std::cout << word->first << " " << word->second << std::endl;
       // if (lookUp!=dict.end()){
            
            ret.replace(ret.begin()+wordstart, ret.begin()+index,word);
        wordstart = index;
    }

    return ret;
    
}
// initalized the dictionary from piratedict.txt
void initDict(){
    std::ifstream f;
    std::string buff;
    std::string en,pr;
    char* entry[40];
    f.open("piratedict.txt");
    while(getline(f,buff)){
        int index = 0;
        std::cout << buff<<std::endl;
        //loops through the english entry chars
        while(!isspace(buff[index])){
            en.push_back(std::tolower(buff[index]));
            index++;
        }
        
        // eats the whitespace between
        while(isspace(buff[index])) index++;
        // reads until end line
        while(buff[index] != '\0'){
            pr.push_back(std::tolower(buff[index]));
            index++;
        }
        //std::cout << pr <<std::endl<< en << std::endl;
        dict.insert(std::pair<std::string, std::string>(en,pr));
        en = std::string();
        pr = std::string();
    }
    std::cout << "dictionary initialized\n";
}

std::map<std::string,std::string> dict;


};

int main(){
    auto p = pirateSpeak();
    p.initDict();
    int i = 0;
    assert(p.translate("Hello")=="ahoy");
    assert((p.getWord("hello there you only see the first word",i) == "hello"));
    assert(p.tolower("ToKi a JAN ale O") == "toki a jan ale o");
    assert(p.translate("Hello friend have you seen that madame? She was in front of the restroom by the officer") == "ahoy mate have ye seen that proud beauty? she was in front of th' head by th' foul blaggart");
    auto punctMess = "@#(!%#$#@)";
    assert(p.translate(punctMess) == punctMess);
}