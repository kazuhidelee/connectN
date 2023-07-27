#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "input_validation.h"

/**
* Check whether the input was valid
* @param numArgsRead: the number of arguments user entered
* @param numArgsNeed: the number of arguments needed
*/
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); 
		if(!isspace(character)){ 
			formatIsGood = false;
		}
	}while(character != '\n'); 
  return formatIsGood;
}
