

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool valid(
  const AvailabilityMatrix& avail, 
  const size_t dailyNeed, 
  const size_t maxShifts,
  DailySchedule& sched,
  int days, 
  vector<size_t>& shiftnumber
  );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    int days = 0;
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //passing in availability, dailyneed, maxshift, and then sched 
    //initialize sched since it is supposed to be empty first 
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
            sched[i][j]=-1;
      }
    }
    vector<size_t> shiftnumber;
    for(size_t i = 0; i < avail[0].size(); i++){
      shiftnumber.push_back(0);
    }
    // initialize to 0 
    return valid(avail, dailyNeed, maxShifts, sched, days, shiftnumber);
}

bool valid(
  const AvailabilityMatrix& avail, 
  const size_t dailyNeed, 
  const size_t maxShifts,
  DailySchedule& sched,
  int days, 
  vector<size_t>& shiftnumber
  )
{ 
  if(sched.size()==avail.size()){
    return false;
  }
  //base case 
  //situation 1: when the day needed is perectly matching 
  else if(sched[days].size()==dailyNeed){
    //recurse
    if(valid(avail, dailyNeed, maxShifts, sched, days+1, shiftnumber)){
      return true;
    }
  }
  //backtracking, starting from day 1 
  for(size_t i = 0; i < avail[0].size(); i++){
    //when the worker is able to work that day 
    if(avail[days][i] == true){
      //also if the worker hasn't reach the maxshift required 
      if(maxShifts > shiftnumber[i]){
        sched[days].push_back(i);
        //update worker's shift amount 
        shiftnumber[i] = shiftnumber[i]+1;
        bool b = valid(avail, dailyNeed, maxShifts, sched, days, shiftnumber);
        // if it is not valid then we have to take the person out of the shift 
        if(b){
          return true;
        }
        else{
          sched[days].erase(std::find(sched[days].begin(),sched[days].end(),i));
          shiftnumber[i] = shiftnumber[i]-1;
          //recurse 
          return valid(avail, dailyNeed, maxShifts, sched, days, shiftnumber);
        }
      }
    }
  }
    return false;
}
    
    



    







