#include <iostream>
#include<string>
#include<map>

std::map<char,int> romanTable{
    {'I',1},
    {'V',5},
    {'X',10},
    {'L',50},
    {'C',100},
    {'D',500},
    {'M',1000}
};

int romanToDecimal(const std::string & str){
    int ret = 0;
    char cur;
    char next;
    for (int i = 0; i < str.size(); i++){
        cur = str[i];
        next = i+1>str.size()?0:str[i+1];

        if(romanTable[cur]<romanTable[next]){
            ret-= romanTable[cur];
        }else{
            ret+= romanTable[cur];
        }
    }
    return ret;
}
/*
int main(){
    std::cout << romanToDecimal("MCMXVIII") << std::endl;
    
}*/