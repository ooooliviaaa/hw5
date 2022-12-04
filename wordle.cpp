// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helpers(
std::string& in, 
std::string floating, 
const std::set<std::string>& dict, 
int index, 
std::size_t numofdash, 
std::set<std::string>& result, 
std::string vocab);

size_t emptyspace(const std::string& in);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> finalanswer; 
  //define the dashes number here for numofdash
  std::size_t dashnumbers = emptyspace(in);
  std::string inputword = in;
  const std::string floats = floating; 
  std::string vocabs = "";
  helpers(inputword, floats, dict, 0, dashnumbers, finalanswer, vocabs);
  return finalanswer; 
}



void helpers(
  std::string& in, 
  const std::string floating, 
  const std::set<std::string>& dict, 
  int index,
  std::size_t numofdash,
  std::set<std::string>& result,
  std::string vocab)
{
  int sizein = in.size();
  int sizeflo = floating.size();
  std::set<char> floatinset(begin(floating), end(floating));
  //base case
  if(index == sizein)
  {
    //1. if the word in in dict
    if(dict.find(vocab)!=dict.end()){
      //if map is empty
        //convert in to a set 
        result.insert(vocab); 
    }
  }
  //else meaning that the word has dashes inside and needs to be filled in 
  else
  {
    //when it needs to be filled in, which is when there is a dash
    if(in[index] == '-'){
      //when there needs letter to fill 
      if(numofdash > (size_t)sizeflo){
        //loop through all the letters from a to z 
        for(char i = 'a'; i <= 'z'; i++){
          //if the letter is in floating
          if(floatinset.find(i) != floatinset.end()){
            //remove and recurse
            floatinset.erase(floatinset.find(i));
            helpers(in, floating, dict, index+1, numofdash-1, result, vocab+i);
            floatinset.insert(i);
          }
          //if the letter is not in floating
          else{
            //just recurse
            helpers(in, floating, dict, index+1, numofdash-1, result, vocab+i);
          }
        }
      }
      //when the number of floating is enough to fill the dash gap 
      else{
        //loop through all the letters again
        for(char i = 'a'; i <= 'z'; i++){
          //if it is the floating letter 
          if(floatinset.find(i) != floatinset.end()){
            floatinset.erase(floatinset.find(i));
            //recurse
            helpers(in, floating, dict, index+1, numofdash-1, result, vocab+i);
            floatinset.insert(i);
          }
        }
      }
    }
    //when it is not dash, meaning that it is fixed
    else{
      vocab += in[index];
      //recurse
      helpers(in, floating, dict, index+1, numofdash, result, vocab);
    }
  }
}


std::size_t emptyspace(const std::string& in)
{
  int empty = 0; 
  for(unsigned int i = 0; i < in.size(); i++){
    if(in[i]=='-'){
      empty++;
    }
  }
  return empty;
}