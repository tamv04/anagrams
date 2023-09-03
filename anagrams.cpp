//
//  main.cpp
//  New Project 3
//
//  Created by tam vo on 8/2/23.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAXRESULTS = 20; // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


// helper function for the vocab creator
int VC(istream& dictfile, string dict[], int& results)
{
    // base case
    if (results >= MAXDICTWORDS || dictfile.eof())
          return results;
    
    if ((dictfile >> dict[0]).eof())
        // This part reads a word from the dictfile and stores it in the first position (dict[0]) of the dict array.
        // addtioanlly it uses and extration operation to store stuff in dictfile into dict[0]
        // the "eof" part checks if the end of the file has been reached. If the end of the file is reached, it means there are no more words to read.
   
    {
        return (++results); // returns updated value
        
    }
    
    return VC(dictfile, dict + 1, ++results); // calling the magic function
}

//Puts each string in dictfile into the array dict. Returns the number of words
//read into dict. This number should not be larger than MAXDICTWORDS since that is
//the size of the array
int vocabularyCreator(istream &dictfile, string dict[])
{
    int returnThis = 0;
    return VC(dictfile, dict, returnThis); // using the helper function
}


// another helper to count the number of each chracter in any string

int Counter(string word, char k, int count)
{
    //base case
        
    if (word.size() == 1 )
    {
        if (word[0] == k) // checking the first postion if it matches the char k
      
        return count + 1;
        
        if(word [0] != k) // checking if it doesnt then we just return count
            
        return count;
    }
    
    if(word[word.size() -1] == k) // this is checking the last character to see if it matches K
    {
        count++;
    }
    
    return Counter(word.substr(0,word.size() -1),k, count); // calling our magic function onto rest of the string
    
}

// another helper
// going to check work and find to see if they're anagrams of each other
bool IsAnagram(string word, string find, int j)
{
    // no way its an anagram
    if(word.length() != find.length())
    {
        return false;
    }
    
    char CharJ = find[j]; // using j to go thru the string find
    
   // counts how many times CharJ appears in word
    
    int JCountWord = Counter(word, CharJ,0); // counting the string word and how many times the character appears in it
    int JCountFind = Counter(find,CharJ ,0); // doing the same here but for string find
    
    if (JCountFind == JCountWord) // if the counts of chracters match up
    {
        // tar is find and rat is word
        if (find.size() - 1 == j)

        return true;
        
        return IsAnagram(word,find,j+1); // going thru everything in find
        
    }
    else
        return false;
}

//helper to check for duplicates
bool isDuplicate(const string results[], int currentIndex, const string& target)
{
    // Base case
     if (currentIndex < 0)
     {
         return false; // The entire array has been checked no duplicate found
     }

     // Check if the current element is equal to the target
     if (results[currentIndex] == target)
     {
         return true; // Found a duplicate
     }
    
    bool excludeFront = isDuplicate(results, currentIndex - 1, target);
     // using the magic function in this
    return excludeFront;
    
 }



// helper
void PSHelper(string word, const string dict[], int size, string results[], int i, int &resultCounter)
{
    if (i >= size || ( resultCounter >= MAXRESULTS ) || ( size <= 0 ))
        // for the first part it checks if the current index i is greater than or equal to the size of the dictionary (size). The purpose of this check is to ensure that we don't go beyond range of the dictionary when accessing elements
        // for the second part This condition checks if the number of results found so far (resultCounter) has reached or exceeded the maximum number of results allowed (MAXRESULTS).
        // for the third part This condition checks if the size of the dictionary (size) is less than or equal to 0. If size is 0 or negative, it indicates that the dictionary is empty or invalid,
    {
        return;
    }
    
    if (IsAnagram(word, dict[i], 0) && !isDuplicate(results, resultCounter - 1, dict[i]))
    {
        results[resultCounter] = dict[i]; // If the current word is an anagram, it is stored in the results array
        //  is the line of code responsible for storing an anagram found in the dict array into the results array.
        resultCounter++; // then we add
    }

    PSHelper(word, dict, size, results, i + 1, resultCounter); // calling my magic function
}


// Puts all the possibilities of word which are found in dict into results. Returns
//the number of matched words found. This number should not be larger than
//MAXRESULTS since that is the size of the array. The size is the number of words
//inside the dict array.
int potentialSequences(string word, const string dict[], int size, string results[])
{
   // goes thru all words in diction and finds all string that are anagrams of string word and saves them into results array
    // returns how many it finds
    // use helper that takes in everything and also an int i , call it as a magic function of I + 1, and I is gonna be used to access dict , see if word is an anagram with dict [i] update results ,
    //need a counter in parameters of helper functions
    //
    
    if (size == 0) // acount for zero size array
    {
        return 0;
    }
    
    int resultCounter = 0;
    
    PSHelper(word, dict, size, results, 0, resultCounter);
    
    return resultCounter;
    
}



void outcomeDisclosure(const string results[], int size)
{
    if (size <= 0) // checking so the function from going into an infinite recursive loop
        //  is to check if there are no elements left to display in the results
        //When size becomes zero or negative all elements in the results array have been displayed, and there's no need to continue the recursion further.
            return;
        else
        {
            cout << results[0] << endl;
            outcomeDisclosure(results + 1, size - 1);
        }
}


int main()
{
    
//    string results[MAXRESULTS];
//
//        string exampleDict[] = {"kool", "moe", "dee"};
//        int numResults = potentialSequences("kloo", exampleDict,
//        3, results);
//        assert(numResults == 1 && results[0] == "kool");
//
//    string dict[MAXDICTWORDS];
//    ifstream dictfile; // file containing the list of words
//    int nwords; // number of words read from dictionary
//    string word;
//    dictfile.open("/Users/tamvo/Desktop/Project 1_files/New Project 3/New Project 3/words (1).txt");
//    if (!dictfile) {
//    cout << "File not found!" << endl;
//    return (1);
//    }
//    nwords = vocabularyCreator(dictfile, dict);
//    cout << "Please enter a string for an anagram:";
//    cin >> word;
//    int numMatches = potentialSequences(word, dict, nwords, results);
//    if (!numMatches) {
//    cout << "No matches found" << endl;
//    }
//    else {
//    outcomeDisclosure(results, numMatches);
//    }
//    return 0;
    string results[MAXRESULTS] = {"apple", "banana", "cherry", "apple", "date"};
       int numResults = 5;

       // Test case 1: Check if "apple" is a duplicate
       assert(isDuplicate(results, numResults - 1, "apple"));
       cout << "Test case 1 passed." << endl;

       // Test case 2: Check if "banana" is a duplicate
       assert(isDuplicate(results, numResults - 1, "banana"));
       cout << "Test case 2 passed." << endl;

       // Test case 3: Check if "cherry" is a duplicate
       assert(isDuplicate(results, numResults - 1, "cherry"));
       cout << "Test case 3 passed." << endl;

       // Test case 4: Check if "date" is a duplicate
       assert(isDuplicate(results, numResults - 1, "date"));
       cout << "Test case 4 passed." << endl;

       // Test case 5: Check if "grape" is a duplicate (not in the results)
       assert(!isDuplicate(results, numResults - 1, "grape"));
       cout << "Test case 5 passed." << endl;

       return 0;
    
    }






