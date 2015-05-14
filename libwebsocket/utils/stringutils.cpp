/**
    stringutils.cpp
    Utility funcions for http parser

    @author Bertrand Martel
    @version 1.0
*/
#include "stringutils.h"
#include "sstream"
#include "vector"
#include <cctype>
#include <algorithm>

using namespace std;

/**
 * @brief split
 *      split a string with a character delimiter
 * @param s
 *      string to split
 * @param delim
 *      character delimiter
 * @return
 *      vector of splitted string
 */
vector<string> stringutils::split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

/**
 * @brief split
 *      split a string with a character delimiter
 * @param s
 *      string to split
 * @param delim
 *      character delimiter
 * @param elems
 *      the same as vector list returned
 * @return
 *      vector of splitted string
 */
vector<string> stringutils::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/**
 * @brief isNum
 *      check if char * is numeric data
 * @param s
 *      char * input
 * @return
 *      true if data is numeric
 */
bool stringutils::isNum(char *s) {
    int i = 0,  flag;

    while(s[i]){
            //if there is a letter in a string then string is not a number
        if(isalpha(s[i])){
            flag = 0;
            break;
        }
        else flag = 1;
        i++;
        }
    if (flag == 1) return true;
    else return false;
}

/**
 * @brief stringutils::ltrim
 *      Trim string from start
 * @param s
 *      string to trim
 * @return
 */
string& stringutils::ltrim(string& s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
        return s;
}

/**
 * @brief stringutils::rtrim
 *      Trim string from end
 * @param s
 *      string to trim
 * @return
 */
string& stringutils::rtrim(string& s) {
        s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
        return s;
}

/**
 * @brief stringutils::trim
 *      trim string from both ends
 * @param s
 *      string to trim
 * @return
 */
string& stringutils::trim(string& s) {
        return ltrim(rtrim(s));
}
