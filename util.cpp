#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    
    rawWords = convToLower(rawWords);
    set<string> words;

    if (rawWords.length() == 0){
        return words;
    }

    int begin = 0;
    for (unsigned int i = 0; i < rawWords.length(); i++){
        if (int(rawWords[i])<97 || int(rawWords[i])>122){
            string temp = rawWords.substr(begin, (i-begin));
            if (temp.length() > 1){
                words.insert(temp);
            }
            begin = i+1;
        }
        else if (i==(rawWords.length()-1)){
            if ((rawWords.substr(begin)).length() > 1){
                words.insert(rawWords.substr(begin));
            }
        }
    }

    return words;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
