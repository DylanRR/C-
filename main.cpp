
#include <iostream>
#include <string>
#include <algorithm>
#include <regex> 

using namespace std;


int main(){
    string rna[10] =           {"AUG","UUU","UUC","AUU","AUC","AUA","GUU","GUU","GUC","GUA"}; //Array of posible mRNA combinations
    string rnaCorrespond[10] = {"MET","PHE","PHE","ILE","ILE","ILE","VAL","VAL","VAL","VAL"}; //Simplified Codon List inline with rna array
    string end = "UGA"; //Three letter combo to signify the end of an mRNA sequence
    string final =""; //Instantiate final Simplified Codon List string
    std::string mrnaInput; //mRNA Input
    string userExit = "EXIT"; //Signify exit keyword
    //Main regular expression to check user input starts with 'AUG' Ends with 'UGA'
    //Only contains 'A', 'U', 'G', 'C' characters
    regex mainMatch("^[A][U][G][ACGU]+[$U][G][A]$");
    //Secondary regular expression that catches input that the mainMatch cant catch
    //Catches no middle sequence example. 'AUGUGA'
    regex secondaryMatch("^[A][U][G][ACGU]?[$U][G][A]$");
    
    
    cout<< "Welcome to the Bioinformatics Lab" << endl;
    cout<< "Please enter a mRNA sequence" << endl;
    getline (cin, mrnaInput); //Sets mrnaInput from user input
    
    bool firstTime = true; //True if you are putting in 1st mRNA input after program starts otherwise false
	bool start = true; //Used to loop entire program if False program ends ie. 'EXIT'
	while (start){
	    if(!firstTime){ //Prompts user for input if not the first mRNA input
                cout<< "Please enter a mRNA sequence" << endl;
                getline (cin, mrnaInput);
        	}
        firstTime = false;
            //Takes user input and makes all characters uppercase 
            std::for_each(mrnaInput.begin(), mrnaInput.end(), [](char & c){
    	    c = ::toupper(c);});
    	    
    	if(mrnaInput.compare(userExit)){ //Checks if 'EXIT' keyword is used
    	    bool initalDash = true; //Used to properly format Simplified Codon List of mRNA Inputs
    	        if(regex_match(mrnaInput, mainMatch) || regex_match(mrnaInput, secondaryMatch)){ //Uses regex to check user input. See above for more info
    	            int a = mrnaInput.length(); //Sets a to the length of userInput
    	            if(mrnaInput.length() % 3 == 0) //Checks to make sure input is a multipe of 3
    	                for(int i=0; i<=mrnaInput.length()-3; i=i+3){ //Iterates through the mrnaInput setting x to every 3rd letter
    	                    string str = mrnaInput.substr(i,3); //Substrings mrnaInput into 3 letter string
    	                    bool noMatch = true; //Used if a 3 letter substring is not found in the rna Array
    	                    if(str.compare(end)){ //Checks if the current 3 letter string is the end ("UGA") of the sequence
        	                    for(int x=0; x<=10; x++) //Iterates through rna Array 'Used to scan the rna array against the substring'
        	                        if(!rna[x].compare(str)) //Checks if substring matches current element in array
        	                        
        	                            //If true add the Simplified Codon to the final keyword
        	                            //Sets noMatch to false due to the fact that final will no longer be blank
        	                            //Breaks out of loop that searches through rna Array because match is found
        	                            //Needed beacuse we dont want the Simplified Codon to start with a dash
        	                            if(initalDash){
        	                                final = final + rnaCorrespond[x];
        	                                initalDash = false;
        	                                noMatch = false;
        	                                break;
        	                            }
        	                            //Used if the final Simplified Codon list is not blank
        	                            //Adds a dash and the next Simplified Codon to the final Simplified Codon list
        	                            else{
        	                                final = final + "-" + rnaCorrespond[x];
        	                                noMatch = false;
        	                                break;
        	                            }
        	                }
        	                else  //Sets noMatch to false when the end of a sequence is found inorder to not trigger the noMatch statement
        	                   noMatch = false;
        	                if(noMatch) //If no match is found in the rna array we add "-ALA" as (Other) in the final Simplified Codon list
        	                   final = final + "-ALA";
    	                }
    	            
    	            //The following iterates though the mRNA sequence and counts each letter
    	            int aCount=0, cCount=0, gCount=0, uCount=0;
    	            for(int a=0; a<mrnaInput.length(); a++)
    	                if(mrnaInput.at(a) == 'A')
    	                    aCount++;
    	                else if(mrnaInput.at(a) == 'C')
    	                    cCount++;
    	                else if(mrnaInput.at(a) == 'G')
    	                    gCount++;
    	                else if(mrnaInput.at(a) == 'U')
    	                    uCount++;
    	                    
    	            //Outputs the count of each basess and the Final Simplified Codon sequence
    	            cout<<"Number of 'A' Bases: "<< aCount <<endl;
    	            cout<<"Number of 'C' Bases: "<< cCount <<endl;
    	            cout<<"Number of 'G' Bases: "<< gCount <<endl;
    	            cout<<"Number of 'U' Bases: "<< uCount <<endl;
    	            cout<<final<<endl;
    	            cout<<"------------------------------"<<endl;
    	            final = "";
    	        }
    	        else //Used if neither of the regular expressions recognize the inputed mRNA sequence
    	            cout<< "Invalid mRNA, please cheack to make sure your mRNA start with \"AUG\" and ends with \"UGA\""<< endl;
        }
        else //Sets start to false which will end program when the keyword "EXIT" is inputed
            start = false;
	}
}
