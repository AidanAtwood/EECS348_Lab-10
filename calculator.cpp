#include "calculator.hpp"
#include "iostream"
#include "fstream"
#include "string"

//included for simplicity
using namespace std;

//ascii values can still be compared, so this function determines whether a string character is an integer by ensuring its value is between 0 and 9, returning true/false
bool is_int(char c) {
    //compare our character to 0 and 9, ensuring it is an integer
    return c >= '0' && c <= '9';
}

//declare a function that will create a double-precision number based on out string values. this does not alter the original string.
double parse_number(const string &expression) {
    //variable that will allow us to parse each character in the string
    int i = 0;
    //declare return value
    double result = 0.0;
    //declare a boolean for future use
    bool is_negative = false;

    //check if the first character in our string is a '-', returning negative
    if (expression[0] == '-') {
        //set boolean to true if string is a negative number
        is_negative = true;
        //move to next string character
        i++;
    }
    //check if the first character in our string is a '+', returning positive (optional)
    else if(expression[0] == '+') {
        //move to next string character
        i++;
    }

    //this portion examines our string up until the decimal point
    while (is_int(expression[i])) {
        result = result * 10 + (expression[i] - '0');
        //move to next string character
        i++;
    }

    //check for a decimal within our string
    if (expression[i] == '.') {
        //move to next string character
        i++;
        //declare a variable to help us remember which decimal place are in
        double place = 0.1;
        //ensure our string still contains only integer digits
        while (is_int(expression[i])) {
            //convert our current value into an integer before multiplying by our 'place' variable, adding it to the result
            result += (expression[i] - '0') * place;
            //move our 'place' variable one unit to the right after each eval
            place *= 0.1;
            //move to next string character
            i++;
        }
    }

    //check if our final number is negative
    if (is_negative){
        //if negative, return as a negative value
        return -result;
    }
    //check if our final number is positive
    else {
        //return our number
        return result;
    }
}

/*
    NOTE: ChatGPT was used as reference for the prototyping of this portion, it helped provide the idea of adding our string character by character. Code is a mixture of its output and my own editing and will be commented as such.
*/

//declare a function that will format the lengths of our integer and decimal portions of our double, adding them character by character
string add_string(string &s, string &s2){
    //declare a variable that is used to traverse the integer portion of our first string
    int i = 0;
    //declare a variable that is used to traverse the integer portion of our second string
    int i2 = 0;
    //declare a variable that is used to traverse the decimal portion of our first string
    int d = 0;
    //declare a variable that is used to traverse the decimal portion of our second string
    int d2 = 0;
    //declare a substring for the first string integer portion
    string intsub; 
    //declare a substring for the second string integer portion
    string intsub2;
    //declare a substring for the first string decimal portion
    string decsub;
    //declare a substring for the second string decimal portion
    string decsub2;
    //declare a variable that will record the sign for the first string
    char sign1;
    //declare a variable that will record the sign for the second string
    char sign2;

    //check our string to ensure the first digit isn't a +/-
    if(is_int(s[0])) {
        //declare our number positive if no sign is present
        sign1 = '+';
        //move to next character within the string
        i++;
        //append a + to the beginning of our string, making sure no indexing issues arise when negatives are present
        s = '+' + s;
    }
    //check our string to ensure the first digit isn't a +/-
    if(is_int(s2[0])) {
        //declare our number positive if no sign is present
        sign2 = '+';
        //move to next character within the string
        i2++;
        //append a + to the beginning of our string, making sure no indexing issues arise when negatives are present
        s2 = '+' + s2;
    }
    //skip the +/- character if it is present
    if(s[0] == '+' || s[0] == '-') {
        //save our sign
        sign1 = s[0];
        //move to next character within the string
        i++;
    }
    //skip the +/- character if it is present
    if(s2[0] == '+' || s2[0] == '-') {
        //save our sign
        sign2 = s2[0];
        //move to next character within the string
        i2++;
    }
    
    //ensure our characters are between 0 and 9
    while(is_int(s[i])) {
        //move to next character within the string
        i++;
    }
    //ensure our characters are between 0 and 9
    while(is_int(s2[i2])) {
        //move to next character within the string
        i2++;
    } 
    
    //make sure our indexing starts at index 1, ignoring the +/- 
    intsub = s.substr(1, i - 1);
    //make sure our indexing starts at index 1, ignoring the +/- 
    intsub2 = s2.substr(1, i2 - 1);

    /* 
        This block is used to make sure we dont subtract values in different 10s. We check the difference between the places our characters occupy and alter them 
        zeroes in order to maintain the value.
    */
    if (i > i2) {
        int diff = i - i2;
        intsub2 = string(diff, '0') + intsub2;
    } 
    /* Simple repeat of the last if statement but for string 2 */
    if (i2 > i) {
        int diff = i2 - i;
        intsub = string(diff, '0') + intsub;
    }

    //check if a decimal is present
    if(s[i] == '.') {
        //skip the decimal if yes 
        i++;
    }
    //repeat above statement for string 2
    if(s2[i2] == '.') {
        //skip the decimal 
        i2++;
    }
    //declare a variable that will remember where we are within the decimal portion of our first string
    d = i;
    //declare a variable that will remember where we are within the decimal portion of our second string
    d2 = i2;
    //ensure our character is between 0 and 9
    while(is_int(s[d])) {
        //move to the next character within our string
        d++;
    }
    //ensure our character is between 0 and 9
    while(is_int(s2[d2])) {
        //move to the next character within our string
        d2++;
    }

    //declare a substring for our decimal portion
    decsub = s.substr(i, d - i);
    //declare a substring for the decimal portion of our second string 
    decsub2 = s2.substr(i2, d2 - i2);

    //if our first substring is longer than the second, adjust the second substring
    if ((d - i) > (d2 - i2)) { 
        //check for the difference
        int diff = (d - i) - (d2 - i2);
        //remove the difference by adding the correct number of zeroes
        decsub2 += string(diff, '0'); 
    }
    //if our second string is longer than the first, adjust the first substring
    else if ((d2 - i2) > (d - i)) {
        //check for the difference
        int diff = (d2 - i2) - (d - i);
        //remove the difference by adding the correct number of zeroes
        decsub += string(diff, '0');
    }

    //declare our full first number
    string first = intsub + decsub;
    //declare our full second number
    string second = intsub2 + decsub2;
    //this will hold our final number
    string result;
    //declare a variable that will keep track of where we are within our strings
    int carry = 0; 

    //check if both numbers are positive
    if (sign1 == sign2) {
        //start with the smallest available value, moving up
        for (int j = first.length() - 1; j >= 0; j--) {
            //use zero to convert the ascii value to binary and add the values
            int sum = (first[j] - '0') + (second[j] - '0') + carry;
            //any additional value that we need to carry over due to addition will be saved as 'carry'
            carry = sum / 10;
            //return the sum to a character and add it to the result
            result = char((sum % 10) + '0') + result;
        }
        //check if there's any value left in our carry-over variable
        if (carry) {
            //add our carry value to our result
            result = '1' + result;
        } 
        
        //find where our decimal needs to be
        int decimal_position = result.length() - decsub.length();
        //check if there are any leading zeroes before our result
        if (decimal_position < 0) {
            //add the appropriate number of leading zeroes 
            result = string(-decimal_position, '0') + result;
            //set position to zero
            decimal_position = 0;
        }
        //insert our decimal point within the result
        result.insert(decimal_position, 1, '.');
        
        //check if we added with negatives
        if (sign1 == '-') {
            //make our result negative
            result = '-' + result;
        }
    } 

    //if our signs are different, subtract instead
    else {
        //decide which value is bigger
        bool bigger_first = first >= second;
        //create variables that will hold our two values
        string a;
        string b;

        //check if the first value is bigger
        if (bigger_first) {
            //if yes, save it as 'a'
            a = first;
            //then, save 'b' as the smaller value
            b = second;
        } 

        //run if the second value is bigger
        else {
            //save the bigger value as 'a'
            a = second;
            //then, save 'b' as the smaller value
            b = first;
        }

        //start at the smallest available value and move up
        for (int j = a.length() - 1; j >= 0; j--) {
            //make the digits of 'a' and 'b' integers
            int digitA = a[j] - '0';
            int digitB = b[j] - '0' + carry;
            /*
                The below block 'takes' a ten from the value in front of it in order to subtract accordingly if the lower value is too big
            */
            if (digitA < digitB) {
                //add the extra ten to our value so we don't produce negatives
                digitA += 10;
                //account for the carry-over
                carry = 1;
            }
            else {
                //if digitA is bigger than digitB, no carry is needed, so leave it as zero
                carry = 0;
            }
            //return our value to a character and add it back into our result
            result = char((digitA - digitB) + '0') + result;
        }
        //create a variable that will help us remove leading zeroes
        int pos = 0;
        //ensure we stay within our index
        while (pos < result.size() - 1 && result[pos] == '0') {
            pos++;
        } 
        //save the result of our substrings after removing leading zeroes
        result = result.substr(pos);
        //we use sign2 if our second value is bigger than our first
        if (!bigger_first) {
            //make our signs equal
            sign1 = sign2;
        }
        //find where the decimal should go
        int decimal_position = result.length() - decsub.length();
        //check if there are any leading zeroes before our result
        if (decimal_position < 0) {
            //add our leading zeroes back into the result 
            result = string(-decimal_position, '0') + result;
            //set position to zero
            decimal_position = 0;
        }
        //insert our decimal back into the result
        result.insert(decimal_position, 1, '.');
        
        //check if our result is not zero AND negative
        if (result != "0" && sign1 == '-') {
            //if so, make our result negative
            result = '-' + result;
        }
    }

    //check if our output is only zeroes
    bool only_zero = true;
    //loop through every character within our result
    for (char c : result) {
        //if we ever find a character that isn't a zero or the decimal, we know our result is NOT all zeroes
        if (c != '0' && c != '.') {
            //return falst
            only_zero = false;
            //break the loop
            break;
        }
    }
    //confirm our output is only zeroes
    if (only_zero) {
        //return zero 
        return "0";
    }
    //if our result is short and starts with a decimal (example: .0689), we need to add a zero in front of the decimal for readability
    if (result.length() >= 2 && result[0] == '+' && result[1] == '.') {
        //add zero to the front of our result
        result = "0" + result.substr(1);
    }
    //if our result is short and starts with a decimal (example: .0689), we need to add a zero in front of the decimal for readability
    else if (result.length() >= 2 && result[0] == '-' && result[1] == '.') {
        //add zero to the front of our result
        result = "-0" + result.substr(1);
    }

    //return
    return result;
}

//ensure our value is a valid double
bool is_valid_double(const string& s) {
    
    //check if our input is empty
    if(s.empty()) {
        //return false if our input is empty
        return false;
    }
    
    //declare a variable that will help us iterate through the string
    int i = 0;
    //declare a variable that will help us check our bounds
    int n = s.length();
    //declare a variable that will ensure there's a valid integer before the decimal point
    bool hasDigits = false;

    //check for signs, skip if they are present
    if(s[0] == '+' || s[0] == '-') {
        i++;
    }

    //check if there's an integer before our decimal point
    while(i < n && is_int(s[i])) {
        //return true if our number is like 9.0048, false will be returned if its something like -.9380
        hasDigits = true;
        //move to next character in our string
        i++; 
    }

    //check our bounds and find our decimal point
    if(i < n && s[i] == '.') {
        //move past our decimal point
        i++;
        //ensure the last character of our value isn't a decimal point
        if (i == n) {
            //return false, ending function and declaring our string as an invalid double
            return false;
        }
        //ensure all values within our decimal portion are digits
        while (i < n && is_int(s[i])) {
            //move to next character within string
            i++;
        }
    }

    //return
    return hasDigits && i == n;
}