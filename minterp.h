#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>

#define __stdf___KB 1024

#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif

////////////////////
/* replace commas */
static inline void __stdf___remove_comma(char ** string)
{
	for(int i = 0, j = strlen(*string); i < j; i++){
		if((*string)[i] == ',') (*string)[i] = '.';
	}
}

/////////////////////////////
/* remove char from string */
static inline void scharr(char * string, int numofchars, ...)
{
	
	va_list va;
	va_start(va, numofchars);
	char currentchar;
	
	for(int i = 0; i < numofchars; i++){
		char *read, *write;
		currentchar = va_arg(va, int);
		for(read = write = string; *read != '\0'; ++read)
		{
			if(*read != currentchar)
			{
				*(write++) = *read;
			}
		}
		*write = '\0';
	}
	va_end(va);
}

////////////////////////////////////////////////
/* remove char from string without numofchars */
static inline void scharrs(char * string, char * stringofremv){
	
	int a = strlen(stringofremv);
	for(int i = 0; i < a; i++){
		
		scharr(string, 1, stringofremv[i]);
		
	}
	
}

//////////////////////////////
/* char counter from string */
static inline int charcounter(char * string, char character) { int i = 0, j = 0, x = strlen(string); for( ; i < x; i++) if(string[i] == character) j++; return j; }

////////////////////////////////////////////////////
/* add char from starting point to point+addmount*/
static inline void saddspc(char ** string, int pos, short addmount, char character){
	
	//atexit(report_mem_leak);
	int l = strlen(*string), i;
	char * buffer = calloc(addmount+l+__stdf___KB, sizeof(char));
	
	if(addmount < 0) addmount = 0;
	if(pos < 0) pos = 0;
	else if(pos > l) pos = l;
	
	for(i = 0; i < pos; i++){
		buffer[i] = (*string)[i];
	}
	
	for(i = pos; i < pos+addmount; i++){
		buffer[i] = character;
	}
	
	for(i = pos+addmount; i < l+addmount; i++){
		buffer[i] = (*string)[i-addmount];
	}
	if(*string != NULL) {
		free(*string);
		*string = calloc(strlen(buffer)+2, sizeof(char));
	}
	else *string = calloc(strlen(buffer)+2, sizeof(char));
	strlcpy((*string), buffer, strlen(buffer)+2);
	free(buffer);
	return;
	
}

////////////////////////////////////////////////////
/* add char from starting point to point+addmount*/
static inline void sremvchar(char ** string, int pos, short amount){
	
	//atexit(report_mem_leak);
	int l = strlen(*string), i;
	char * buffer = calloc(amount+l+__stdf___KB, sizeof(char));
	
	if(amount < 0) amount = 0;
	if(pos < 0) pos = 0;
	else if(pos+amount > l) {
		free(buffer);
		return;
	}
	
	for(i = 0; i < pos; i++){
		buffer[i] = (*string)[i];
	}
	
	for(i = pos+amount; i < l; i++){
		buffer[i-amount] = (*string)[i];
	}
	memset(*string, 0, __stdf___KB);
	for(i = 0; i < strlen(buffer); i++){
		(*string)[i] = buffer[i];
	}
	//if(*string != NULL) {
	//	free(*string);
	//	*string = calloc(strlen(buffer)+__stdf___KB, sizeof(char));
	//}
	//else *string = calloc(strlen(buffer)+__stdf___KB, sizeof(char));
	//memcpy((*string), buffer, strlen(buffer)+__stdf___KB);
	free(buffer);
	return;
	
}

static inline void saddstr(char ** string, int pos, char * add){
	
	int l = strlen(*string), i;
	int addmount = strlen(add);
	char * buffer = calloc(addmount+l+__stdf___KB, sizeof(char));
	if(!buffer) return;
	if(addmount < 0) addmount = 0;
	if(pos < 0) pos = 0;
	else if(pos > l) pos = l;
	
	for(i = 0; i < pos; i++){
		buffer[i] = (*string)[i];
	}
	
	for(i = pos; i < pos+addmount; i++){
		buffer[i] = add[i-pos];
	}
	
	for(i = pos+addmount; i < l+addmount; i++){
		buffer[i] = (*string)[i-addmount];
	}
	memset(*string, 0, __stdf___KB);
	for(i = 0; i < strlen(buffer); i++){
		(*string)[i] = buffer[i];
	}
	free(buffer);
	return;
	
}

static inline int intlen(int integer){
	
	if (integer < 100000) {
		if (integer < 100){
			if (integer < 10) return 1;
			else return 2;
		} 
		else {
			if (integer < 1000) return 3;
			else {
				if (integer < 10000) return 4;
				else return 5;
			}
		}
	}
	else {
		if (integer < 10000000) {
			if (integer < 1000000) return 6;
			else return 7;
		} 
		else {
			if (integer < 100000000) return 8;
			else {
				if (integer < 1000000000)return 9;
				else return 10;
			}
		}
	}
	
}

static inline int longlonglen(long long longlong){
	
	return (int)abs(log10((long double) longlong))+1;
	
}

static inline int dpow(int base, int exp)
{
	int original = base;
	if      (exp > 64)  exp = 64;
	else if (exp <  0)  exp = 0;
	if      (exp == 0) return 0;
	for(int i = 1; i < exp; i++){
		base *= original;
	}
    return base;
}

static inline long long ldpow(int basel, int exp)
{
	long long base = basel;
	long long original = base;
	if      (exp > 64)  exp = 64;
	else if (exp <  0)  exp = 0;
	if      (exp == 0) return 0;
	for(int i = 1; i < exp; i++){
		base *= original;
	}
    return base;
}

static inline char isposf(double a) { 
	if( a >= 0.0 ) return 1; 
	else return 0; 
}

static inline char isposlld(long long int a) {
	if( a >= 0 ) return 1;
	else return 0;
}

static inline char isposd(int a) { 
	if( a >= 0 ) return 1;
	else return 0; 
}

static inline char isnegf(double a) {
	if( a < 0.0 ) return 1; 
	else return 0; 
}

static inline char isneglld(long long a) { 
	if( a < 0 ) return 1; 
	else return 0; 
}

static inline char isnegd(int a) { 
	if( a < 0 ) return 1;
	else return 0; 
}




static inline char * minterp_getfirstnumber(char * math, int pos, bool searchinfront, int * lastnumb){
	
	int i, j, k, first, end, l = strlen(math); char currchar; bool breakloop = false; char * output = NULL;
	
	if      ( pos < 0 ) pos = 0;
	else if ( pos > l ) pos = l;
	
	if(isdigit(math[pos])){
		end = first = pos;
		for(i = pos; i < l; i++){
			if(isdigit(math[i])){
				end = i;
			}
			else if(math[i] == '.') end = i;
			else break;
		}
		for(i = pos; i >= 0; i--){
			if(isdigit(math[i])){
				first = i;
			}
			else if(math[i] == '.') first = i;
			else break;
		}
		for( ; i >= 0; i--){
			if(isspace(math[i]));
			if(math[i] == '*') break;
			if(math[i] == '/') break;
			if(math[i] == '%') break;
			if(math[i] == '+') {
				first = i;
				break;
			}
			if(math[i] == '-'){
				first = i;
				break;
			}
		}
		if(end-first > 100) return NULL;
		else output = calloc((end-first)+2, sizeof(char));
		
		for( i = first; i <= end; i++){
			output[i-first] = math[i];
		}
		
		return output;
	}
	
	
	if(searchinfront == true){
		if(pos == l) return NULL;
		for( i = pos+1, breakloop = false, j = pos, k = 0; i < l; i++){
			currchar = math[i];
			if(isdigit(currchar)){
				first = i;
				breakloop = true;
			}
			else if(currchar == '.'){
				first = i;
				breakloop = true;
			}
			else if(currchar == '+'){
				k++;
				j = i;
			}
			else if(currchar == '-'){
				k++;
				j = i;
			}
			else;
			if(k > 1) return NULL;
			if( breakloop == true ) break;
		}
		if( breakloop == false) return NULL;
		if(j != pos) first = j;
		for( end = i, breakloop = false; i < l; i++){
			currchar = math[i];
			if(!isdigit(currchar)){
				if(currchar == '.') end = i;
				else breakloop = true;
			}
			else end = i;
			if( breakloop == true ) break;
		}
		if(end-first > 100) return NULL;
		if(output != NULL) free(output);
		output = calloc((end-first)+2, sizeof(char));
		
		for( i = first; i <= end; i++){
			output[i-first] = math[i];
		}
		scharr(output, 1, ' ');
		*lastnumb = end;
	}
	else{
		if(pos == 0) return NULL;
		for( i = pos-1, breakloop = false; i >= 0; i--){
			currchar = math[i];
			if(isdigit(currchar)){
				end = i;
				breakloop = true;
			}
			else if(currchar == '.'){
				end = i;
				breakloop = true;
			}
			else;
			if( breakloop == true ) break;
		}
		if( breakloop == false ) return NULL;
		i = first = end;
		for(breakloop = false; i >= 0; i--){
			currchar = math[i];
			if(!isdigit(currchar)){
				if(currchar == '.') first = i;
				else breakloop = true;
			}
			else first = i;
			if( breakloop == true ) break;
		}
		
		//else first = i;
		for( ; i >= 0; i--){
			if(isspace(math[i]));
			if(math[i] == '*') break;
			if(math[i] == '/') break;
			if(math[i] == '%') break;
			if(math[i] == ')') break;
			if(math[i] == '+') {
				first = i;
				break;
			}
			if(math[i] == '-'){
				first = i;
				break;
			}
		}
		if(end-first > 100) return NULL;
		if(output != NULL) free(output);
		output = calloc((end-first)+2, sizeof(char));
		
		for( i = first; i <= end; i++){
			output[i-first] = math[i];
		}
		scharr(output, 1, ' ');
		*lastnumb = first;
	}
	return output;
	
}

static inline int minterp_getfurthestnumbpos(char * math, int pos, bool searchfront){
	
	int i, j, k, l = strlen(math);
	
	if(searchfront == true){
		for(i = pos; i < l; i++){
			if(isdigit(math[i]))
				break;
			else if(math[i] == '.')
				break;
		}
		for(i = i; i < l; i++){
			if(!isdigit(math[i])) {
				if(math[i] == '.');
				else return i-1;
			}
		}
		return i;
	}
	else {
		for(i = pos; i >= 0; i--){
			if(isdigit(math[i]))
				break;
			else if(math[i] == '.') 
				break;
		}
		for(i = i; i >= 0; i--){
			if(!isdigit(math[i])) {
				if(math[i] == '.');
				else return i+1;
			}
		}
		return i;
	}
	
}

static inline int minterp_bracketcounter(char * math){
	
	int l_bracketcount = charcounter(math, '(');
	int r_bracketcount = charcounter(math, ')');;
	
	if(l_bracketcount != r_bracketcount) return -1;
	else return l_bracketcount;

}

static inline char * minterp_solver(char * math, char ** output, bool usefloat){
	
	
	int i, j, l = strlen(math);
	char currchar;
	
	int startpoint;
	int endpoint;
	int removemount;
	int skipmount;
	
	double    firstnumberfloat;
	double    secondnumberfloat;
	long long firstnumberint;
	long long secondnumberint;
	double    floatresult;
	long long intresult;
	
	char * result     = calloc(__stdf___KB * 5, sizeof(char));
	char * firstnumb ;
	char * secondnumb;
	char * nullby     = calloc(__stdf___KB * 5, sizeof(char));
	
	if(usefloat == true){
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0 + skipmount; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '^'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberfloat  = atof(firstnumb);
					secondnumberfloat = atof(secondnumb);
					
					floatresult = pow(firstnumberfloat, secondnumberfloat);
					
					if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
					else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
				if(currchar == '$'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberfloat  = atof(firstnumb);
					secondnumberfloat = atof(secondnumb);
					
					floatresult = pow(secondnumberfloat, 1/firstnumberfloat);
					
					if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
					else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
			}

			if(j == 0) break;
			
		}
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0 + skipmount; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '*'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberfloat  = atof(firstnumb);
					secondnumberfloat = atof(secondnumb);
					
					floatresult = firstnumberfloat * secondnumberfloat;
					
					if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
					else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
				if(currchar == '/'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					firstnumberfloat  = atof(firstnumb);
					secondnumberfloat = atof(secondnumb);
					floatresult = firstnumberfloat / secondnumberfloat;
					
					if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
					else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);
					saddstr(&math, startpoint, result);
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
				if(currchar == '%'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberfloat  = atof(firstnumb);
					secondnumberfloat = atof(secondnumb);
					
					floatresult = fmod(firstnumberfloat, secondnumberfloat);
					
					if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
					else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
			}

			if(j == 0) break;
			
		}
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0 + skipmount; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '+') {
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					if(!firstnumb);
					else {
						j++;
						secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
						if(firstnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						if(secondnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						
						firstnumberfloat  = atof(firstnumb);
						secondnumberfloat = atof(secondnumb);
						
						floatresult = firstnumberfloat + secondnumberfloat;
						
						if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
						else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
						
						removemount = endpoint-startpoint;
						if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
						sremvchar(&math, startpoint, removemount);
	
						saddstr(&math, startpoint, result);
						
						l = strlen(math);
						skipmount = startpoint + strlen(result);
						
						free(firstnumb);
						free(secondnumb);
						break;
					}
				}
			
				if(currchar == '-'){
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					if(!firstnumb);
					else {
						j++;
						secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
						if(firstnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						if(secondnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						
						firstnumberfloat  = atof(firstnumb);
						secondnumberfloat = atof(secondnumb);
						
						floatresult = firstnumberfloat - secondnumberfloat;
						
						if(isposf(floatresult)) snprintf(result, __stdf___KB*5-5, "+%lf", floatresult);
						else snprintf(result, __stdf___KB*5-5, "%lf", floatresult);
						
						removemount = endpoint-startpoint;
						if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
						sremvchar(&math, startpoint, removemount);
	
						saddstr(&math, startpoint, result);
						
						l = strlen(math);
						skipmount = startpoint + strlen(result);
						
						free(firstnumb);
						free(secondnumb);
						break;
					}
				}
				
			}

			if(j == 0) break;
			
		}
			
	}
		
	else{
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0 + skipmount; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '^'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;					
					}
					
					firstnumberint  = atoll(firstnumb);
					secondnumberint = atoll(secondnumb);
					
					intresult = ldpow(firstnumberint, secondnumberint);
					
					if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
					else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);

					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
			}

			if(j == 0) break;
			
		}
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '*'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;					
					}
					
					firstnumberint  = atoll(firstnumb);
					secondnumberint = atoll(secondnumb);
					
					intresult = firstnumberint * secondnumberint;
					
					if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
					else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);

					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
				if(currchar == '/'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberint  = atoll(firstnumb);
					secondnumberint = atoll(secondnumb);
					
					intresult = firstnumberint / secondnumberint;
					
					if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
					else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
				if(currchar == '%'){
					j++;
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
					if(firstnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					if(secondnumb == NULL) {
						free(result);
						free(firstnumb);
						free(secondnumb);
						free(nullby);
						free(math);
						return NULL;
					}
					
					firstnumberint  = atoll(firstnumb);
					secondnumberint = atoll(secondnumb);
					
					intresult = firstnumberint % secondnumberint;
					
					if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
					else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
					
					removemount = endpoint-startpoint;
					if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
					sremvchar(&math, startpoint, removemount);

					saddstr(&math, startpoint, result);
					
					l = strlen(math);
					skipmount = startpoint + strlen(result);
					
					free(firstnumb);
					free(secondnumb);
					break;
					
				}
				
			}

			if(j == 0) break;
			
		}
		skipmount = 0;
		for( ; ; ){
			j = 0;
			for(i = 0; i < l; i++){

				currchar = math[i];
				
				memset(result, 0, __stdf___KB*5);
				
				if(currchar == '+') {
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					if(!firstnumb);
					else {
						j++;
						secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
						if(firstnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						if(secondnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						
						firstnumberint  = atoll(firstnumb);
						secondnumberint = atoll(secondnumb);

						intresult = firstnumberint + secondnumberint;

						if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
						else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
						
						removemount = endpoint-startpoint;
						if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
						sremvchar(&math, startpoint, removemount);
	
						saddstr(&math, startpoint, result);
						
						l = strlen(math);
						skipmount = startpoint + strlen(result);
						
						free(firstnumb);
						free(secondnumb);
						break;
					}
					
				}
		
				if(currchar == '-'){
					firstnumb  = minterp_getfirstnumber(math, i, false, &startpoint);
					if(!firstnumb);
					else {
						j++;
						secondnumb = minterp_getfirstnumber(math, i, true,  &endpoint);
						if(firstnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						if(secondnumb == NULL) {
							free(result);
							free(firstnumb);
							free(secondnumb);
							free(nullby);
							free(math);
							return NULL;
						}
						
						firstnumberint  = atoll(firstnumb);
						secondnumberint = atoll(secondnumb);
						
						intresult = firstnumberint - secondnumberint;
						
						if(isposlld(intresult)) snprintf(result, __stdf___KB*5-5, "+%lld", intresult);
						else snprintf(result, __stdf___KB*5-5, "%lld", intresult);
						
						removemount = endpoint-startpoint;
						if(removemount != -1) if(!(removemount + startpoint >= l)) removemount++;
						sremvchar(&math, startpoint, removemount);
	
						saddstr(&math, startpoint, result);
						skipmount = startpoint + strlen(result);
						
						l = strlen(math);
						
						free(firstnumb);
						free(secondnumb);
						break;
					}
						
				}
				
			}

			if(j == 0) break;
			
		}
			
	}
		
	free(result);
	free(nullby);
	
	for( i = 0, l = strlen(math); i < l; i++){
		(*output)[i] = math[i];
	}
	
	free(math);
		
}

static inline char minterp_solvedeepestbracket(char ** math, bool usefloat){
	
	int i, j, k, l = strlen(*math);
	
	int bracketopenpos, bracketclosepos;
	bool containopenbracket, containclosebracket;
	char currchar;
	
	char * mathbuff = calloc(__stdf___KB*5, sizeof(char));
	char * mathout = calloc(__stdf___KB*5, sizeof(char));
	containopenbracket  = false;
	containclosebracket = false;
	for(i = 0, bracketopenpos = 0, bracketclosepos = 0; i < l; i++){
		
		currchar = (*math)[i];
		if(currchar == '('){
			bracketopenpos = i;
			containopenbracket = true;
		}
		if(currchar == ')') {
			bracketclosepos = i;
			if(containopenbracket != true) {
				free(mathbuff);
				free(mathout);
				return 0;
			}
			break;
		}
		
	}
	if(containopenbracket == false && containclosebracket == false){
		bracketopenpos = 0;
		bracketclosepos = l;
	}
	else {
		if(bracketopenpos == 0 && bracketclosepos == 0)  {
			free(mathbuff);
			free(mathout);
			return  0;
		}
		if(bracketopenpos != 0) if(bracketclosepos == 0) {
			free(mathbuff);
			free(mathout);
			return 0;
		}
		if(bracketopenpos+1 == bracketclosepos) {
			sremvchar(math, bracketopenpos, (bracketclosepos-bracketopenpos)+1);
			free(mathbuff);
			free(mathout);
			return 1;
		}
	}
	
	
	if(containopenbracket == false && containclosebracket == false){
		for(i = 0; i < l; i++){
			
			mathbuff[i] = (*math)[i];
			
		}
	}
	else{
		for(i = bracketopenpos+1; i < bracketclosepos; i++){
			
			mathbuff[i-(bracketopenpos+1)] = (*math)[i];
			
		}
	}
	
	
	char * pointer = minterp_solver(mathbuff, &mathout, usefloat);
	
	if(pointer == NULL){
		free(mathbuff);
		free(mathout);
		return 0;
	}
	if(!mathbuff) {
		free(mathbuff);
		free(mathout);
		return 0;
	}
	if(!mathout) {
		free(mathbuff);
		free(mathout);
		return 0;
	}
	if(containopenbracket == false && containclosebracket == false) sremvchar(math, bracketopenpos, (bracketclosepos-bracketopenpos));
	else sremvchar(math, bracketopenpos, (bracketclosepos-bracketopenpos)+1);
	saddstr(math, bracketopenpos, mathout);
	free(mathbuff);
	free(mathout);
	if(containopenbracket == false && containclosebracket == false) return 0;
	return 1;
	
	
}

// minterp steps:
// - check if string contains float
// - convert the %d, %ld and %f numbers to their real float/decimal counterpart passed through stdarg
// - solve every deepest bracket and replace the bracket with the solved bracket.
// - after solving every deepest bracket solve the whole math func


char minterp(char * mathformat, char ** output, ...){
	
	char * math = calloc(__stdf___KB, sizeof(char));
	memcpy(math, mathformat, __stdf___KB);
	
	bool stringhasfloat;
	char currchar;
	int  len = strlen(math);
	int  i, j, l, n, b; 
	
	int        argint;
	double     argfloat;
	long long  arglonglong;
	int    lengof;
	char * value                  = calloc(__stdf___KB, sizeof(char));
	char * numbgetbuff;
	char * bracketholder                 ;
	bool   bracketholderallocated = false;

	va_list va;
	
	if(minterp_bracketcounter(math) == -1) {
		free(value);
		return 0;
	}
	else __stdf___remove_comma(&math);
	
	for(i = 0, stringhasfloat = false; i < len; i++){
		
		currchar = math[i];
		if(currchar == '%') {
			
			if(i+1 != len) {
				
				switch(math[i+1]){
					
					default:
					break;
					
					case 'd':
					i++;
					break;
					
					
					case 'f':
					stringhasfloat = true;
					break;
					
					
					case 'l':
					if (math[i+2] == 'd') i += 2     ;
					else;
					break;
					
				}
				
			}
			
		}
		
		if(currchar == '&') {
			
			if(i+1 != len) {
				
				switch(math[i+1]){
					
					default:
					break;
					
					case 'f':
					stringhasfloat = true;
					break;
					
					
					case 'l':
					if (math[i+2] == 'd') i += 2;
					else;
					break;
					
				}
				
			} 
			
		}
		if(currchar == '.') stringhasfloat = true;
		if(currchar == '/') stringhasfloat = true;
		if(currchar == '$') stringhasfloat = true;
		if(stringhasfloat == true) break;
		
	}
	
	va_start(va, output);

	for(i = 0; i < len; i++){
		currchar = math[i];
		if(currchar == '%'){
			
			if     (math[i+1] == 'd' || math[i+1] == 'D'){
				
				argint = va_arg(va, int);
				snprintf(value, __stdf___KB-5, "%d", argint);
				l = intlen(argint)-1;
				value[l+1] = '\0';
				sremvchar(&math, i, 2);
				saddstr(&math, i, value);
				i += l;
				len = strlen(math);
				
			}
			
			else if(math[i+1] == 'f' || math[i+1] == 'F'){
				
				argfloat = va_arg(va, double);
				snprintf(value, __stdf___KB-5, "%f", argfloat);
				l = strlen(value)-1;
				value[l+1] = '\0';
				sremvchar(&math, i, 2);
				saddstr(&math, i, value);
				i += l;
				len = strlen(math);
				
			}
			
			else if(math[i+1] == 'l' || math[i+1] == 'L' ){

				if(math[i+2] == 'd' || math[i+2] == 'D'){
					
					arglonglong = va_arg(va, long long);
					snprintf(value, __stdf___KB-5, "%lld", arglonglong);
					l = strlen(value)-1;
					value[l+1] = '\0';
					sremvchar(&math, i, 3);
					saddstr(&math, i, value);
					i += l;
					len = strlen(math);
					
				}
				
			}
			
		}
		
	}
	
	va_end(va);
	
	for(i = 0; i < len; i++){
		currchar = math[i];
		if(currchar == '&'){
			if(math[i+1] == 'f' || math[i+1] == 'F'){
				
				numbgetbuff = minterp_getfirstnumber(math, i, true, &b);
				n = atoi(numbgetbuff);
				va_start(va, output);
				for(j = 1; j < n; j++){
					va_arg(va, double);
				}
				argfloat = va_arg(va, double);
				va_end(va);
				snprintf(value, __stdf___KB-5, "%f", argfloat);
				l = strlen(value);
				value[l+1] = '\0';
				sremvchar(&math, i, 2+intlen(n));
				saddstr(&math, i, value);
				i += l;
				len = strlen(math);
				free(numbgetbuff);
				
			}
			
			else if(math[i+1] == 'l' || math[i+1] == 'L' ){

				if(math[i+2] == 'd' || math[i+2] == 'D'){
					
					numbgetbuff = minterp_getfirstnumber(math, i, true, &b);
					n = atoi(numbgetbuff);
					free(numbgetbuff);
					va_start(va, output);
					for(j = 1; j < n; j++){
						va_arg(va, long long);
					}
					arglonglong = va_arg(va, long long);
					va_end(va);
					snprintf(value, __stdf___KB-5, "%lld", arglonglong);
					l = longlonglen(arglonglong);
					value[l+1] = '\0';
					sremvchar(&math, i, 3+intlen(n));
					saddstr(&math, i, value);
					i += l;
					len = strlen(math);
					
				}
				
			}
			
		}
		
	}

	while(minterp_solvedeepestbracket(&math, stringhasfloat));
	
	l = strlen(math);
	if(*output == NULL);
	else free(*output);
	*output = calloc(l+1, sizeof(char));
	
	if(math == NULL) *output = "---";
	else{
		for(i = 0; i < l; i++){
			
			(*output)[i] = math[i];
			
		}
	}
	
	free(math);
	free(value);
	return 1;
	
}