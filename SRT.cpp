/**
*
*
*
* Vijay K Shah - 12506602 
* Michael Jolley - 
**/


#include<iostream>
#include<deque>
#include<iomanip>
using namespace std;

int delay = 0;
int totalNoOfShifts = 0;
string QUOTIENT, REMAINDER;

string complement (string a);
string shiftOverZeros(string AQ);
string shiftOverOnes(string AQ);
string getA(string AQ);
string addBitStrings( string first, string second );
string substractB(string AQ, string B);
string addB(string AQ, string B);
void printOutput(string AQ);
int checkInvalidInputs(string AQ, string B){
	return 0;
}

int main(){
	deque<int> dividend, divisor;
	string Q , A , B , AQ , comB;
	//string Q , A , B = "01010", AQ = "0000110111" , comB;
	//string Q , A , B = "01111", AQ = "0010100100" , comB;

	//string Q , A , B = "011001", AQ = "000011001100" , comB;
	//string Q , A , B = "01101", AQ = "0010110101" , comB;
	//string Q , A , B = "00011", AQ = "0000010001" , comB;
	int t = 0, T;
	cin>>T;
	while(t < T){
		cin >> AQ >> B;

		delay = 0 , totalNoOfShifts = 0;
		int initAdj = 0, k = 0, BLen = B.length();
		string normB = B;
		//Check if the inputs are valid
		int invalid = checkInvalidInputs(AQ, B) ;
		if(invalid == -1)
		{
			cout <<" Invalid Inputs \n";
		}
		else{
			// STEP 1: normalize B
			for(int i =0 ; i < B.length(); i++){
				if(B[i] == '0'){
					//push 0 to the end
					normB.push_back('0');
					//trim 0 in the front
					normB = normB.substr(1);
					initAdj++;
				}
				else
					break;
			}
			delay = delay + initAdj * 3; // 3 t for each shift required for normalizing B

			cout << setw(30) << "AQ = " << "." << AQ.substr(0, AQ.length()/2) <<"  "<< AQ.substr(AQ.length()/2, AQ.length()) << endl;
			cout << setw(30) << "B = " << "." << B << endl;
			cout << setw(30) <<"Normalized B = " << "." << normB <<endl << endl;
			cout << setw(30) << "Total Delay in normalize B" << delay <<"\n";
			//cout << " Adjusted position: "  << initAdj<< endl;
			// STEP 2: Complement B
			string tempNormB = normB;
			string tempComB = complement(tempNormB.insert(0,"0"));
			delay  = delay + B.length(); // length of operand times t
			cout<<setw(30)<<"Complement of Normalized B = " << tempComB.substr(0,1) <<"." << tempComB.substr(1, tempComB.length()) <<endl;
			cout<<setw(30)<<" Total Delay after complementing B " << delay <<" \n";

			cout<<setw(30)<<"------------------------INITIALIZATION-----------------------" <<endl;
			cout << setw(30) << "."<<AQ.substr(0, AQ.length()/2) <<"  "<<AQ.substr(AQ.length()/2  , AQ.length()) <<endl;
			
			// STEP 3: Adjust AQ

			delay = delay + initAdj * 3; // 3 t for each shift required for adjusting AQ
			cout<<setw(30)<<"Total Delay after adjusting AQ: " << delay<<"\n";
			string adjAQ = AQ;
			for(int i = 0; i < AQ.length() ; i++){
				if(AQ[i] == '0' && initAdj > 0 ){
					adjAQ.push_back('*');
					adjAQ = adjAQ.substr(1);
					initAdj --;
				}
			}
			AQ = adjAQ;
			totalNoOfShifts += initAdj;

			//cout << " Total number of shifts after normalization: " << totalNoOfShifts << endl;
			//cout << " Total delay upto after normalization B: " << delay << endl;

			//print the quotient and remainder
			if(totalNoOfShifts > AQ.length()/2){
				printOutput(AQ);
				//break;
			}
			cout << setw(30) << "Adjusted AQ: " << "." << adjAQ.substr(0, AQ.length()/2) << "  "<< AQ.substr(AQ.length()/2, AQ.length())<<endl;

			//STEP 4: Shift over 0's
			
			adjAQ = shiftOverZeros(AQ);
			//cout << " Total number of shifts here: " << totalNoOfShifts << endl;
			//cout << " Total delay upto adjusting AQ: " << delay << endl;
			// check if the quotient and remainder are generated
			if(totalNoOfShifts > B.length()){
				//end here;
				cout << " End at very beginning" << endl;
			}
			//cout <<" Shifted over 0's " << adjAQ << endl;

			AQ = adjAQ;
			string resAQ;
			char isPositive = '0'; //positive by default
			//keep performing the operation unless total # of shifts is less than the operand bit length
			while( totalNoOfShifts <= B.length() && adjAQ.compare("END")!= 0){
				
				if(isPositive == '0'){
					//STEP 5: Substract B
					resAQ = substractB(AQ , normB);
					cout << setw(30)<<"Negative Result : " << resAQ.substr(0,1)<<"."<<
					resAQ.substr(1, resAQ.length()/2)<<"  "<<resAQ.substr(resAQ.length()/2+1, resAQ.length()) <<endl;
				}
				else{
					resAQ = addB(AQ , normB);
					cout << setw(30)<<"Positive Result : " << resAQ.substr(0,1)<<"."<<
					resAQ.substr(1, resAQ.length()/2)<<"  "<<resAQ.substr(resAQ.length()/2+1, resAQ.length()) <<endl;
				
					//cout << "The result after adding B is: " << resAQ << endl;
				}
				
				isPositive = resAQ[0];

				resAQ = resAQ.substr(1);
				//cout << " After substraction: " << resAQ << endl;
				// STEP 6: If resAQ is a positive or negative value
				//STEP 6.1 : If resAQ is +ve,
				if(isPositive == '0'){
					//cout << endl << "The result is positive: " << endl ;
					// shift AQ left, q0 <- 1
					resAQ.push_back('1');
					resAQ = resAQ.substr(1);

					delay = delay + 3; // 3 t delay for 1 shift
					cout<<"Total Delay in shift AQ left and q0 <- 1" <<delay <<"\n";
					totalNoOfShifts += 1;

					cout <<setw(30)<<"Shift AQ left, q0 <- 1 :  " <<"."
					<<resAQ.substr(0,resAQ.length()/2)<<"  "<<resAQ.substr(resAQ.length()/2,resAQ.length()) << endl;
					
					//cout <<"Shift AQ left, q0 <- 1 :  " << resAQ << endl;
					//cout << " Total number of shifts here: " << totalNoOfShifts << endl;
					//cout << " Total delay upto adjusting AQ: " << delay << endl;
					//print the quotient and remainder
					if(totalNoOfShifts > resAQ.length()/2){
						AQ = resAQ;
						//printOutput(resAQ);
						break;
					}
					// shift over 0's
					resAQ = shiftOverZeros(resAQ);
					if(totalNoOfShifts > resAQ.length()/2){
						AQ = resAQ;
						break;
					}
					//delay += noOfShiftsHere * 3; // 3 t for each shift
					//cout << " Total number of shifts here: " << totalNoOfShifts << endl;
					//cout << " Total delay upto adjusting AQ: " << delay << endl;

					//cout << " After operations when result is positive : " << finalAQ << endl;

					AQ = resAQ;
				}
				
				//STEP 6.1 : If resAQ is -ve,
				else if(isPositive == '1'){
					//cout << endl << "The result is negative: " << endl ;
					// shift AQ left, q0 <- 0
					resAQ.push_back('0');
					resAQ = resAQ.substr(1);

					delay = delay + 3; // 3 t delay for 1 shift
					cout<<"Total Delay in shift AQ left and q0 <- 0" <<delay <<"\n";
					totalNoOfShifts += 1;

					cout <<setw(30)<<"Shift AQ left, q0 <- 0 :  " << "1"<<"."
					<<resAQ.substr(0,resAQ.length()/2)<<"  "<<resAQ.substr(resAQ.length()/2,resAQ.length()) << endl;
					//cout << " Total number of shifts here: " << totalNoOfShifts << endl;
					//cout << " Total delay upto adjusting AQ: " << delay << endl;
					//print the quotient and remainder
					if(totalNoOfShifts > resAQ.length()/2){
						AQ = resAQ;
						//printOutput(resAQ);
						//break;
					}
					// shift over 1's
					resAQ = shiftOverOnes(resAQ);
					if(totalNoOfShifts > B.length()){
						AQ = resAQ;
						break;
					}
					
					//cout << " Total number of shifts here: " << totalNoOfShifts << endl;
					//cout << " Total delay upto adjusting AQ: " << delay << endl;

					AQ = resAQ;
				}
			}
			// correct remainder
			if( isPositive == '1'){
				//cout <<  endl <<"Correction is required since Remainder is negative: " << AQ << endl << endl;
				//cout << "The quotient is: " << AQ.substr(AQ.length()/2 ) << endl;
				string finalQ = AQ.substr(AQ.length()/2 );
				A = getA (AQ.insert(0, "1"));

				//shift right
				string correctA = A;
				correctA = correctA.substr(0, A.length() - 1 );
				delay += (3 * (AQ.length()/2));

				cout<<"After correcting remainder, "<< delay<<"\n";

				cout << setw(30)<<"Correct remainer by  " << "1."<<correctA << endl;
				cout << setw(30)<<"Shifting A and adding B  " <<"."<<normB<<endl;
				cout << setw(38) << "--------"<<endl;
				correctA = addBitStrings(correctA, normB);
				cout << setw(33) << "0." <<correctA << endl;

				cout<<setw(30)<<"------------------------RESULTS-------------------------------"<<endl;
				cout <<setw(30)<<" QUOTIENT: "<< finalQ<<endl;
				cout<<setw(30) <<" REMAINDER: "<<correctA<<endl;
				cout <<setw(30)<< "DELAY: " << delay << " dt" <<endl;
			}
			else{
					printOutput(AQ);
			}
		}
		t++;
	}
}

string complement (string a)
{

 	int l, i, c=0;
 	char b[24];
 	l=a.length();
 	for (i=l-1; i>=0; i--)
 	{
  		if (a[i]=='0')
  			b[i]='1';
  		else
  			b[i]='0';
 	}
 	for(i=l-1; i>=0; i--)
 	{
 		if(i==l-1)
 		{
  			if (b[i]=='0')
  				b[i]='1';
  			else
  			{
   				b[i]='0';
   				c=1;
  			}
 		}
 		else
 		{
  			if(c==1 && b[i]=='0')
  			{
   				b[i]='1';
   				c=0;
  			}
 			else if (c==1 && b[i]=='1')
 			{
  				b[i]='0';
  				c=1;
 			}
		}
	}
	b[l]='\0';

	return b;
}

string shiftOverZeros(string AQ){
	string adjAQ = AQ;
	int noOfShiftsHere = 0;
	for( int i = 0 ; i < AQ.length() ; i ++){
		if(totalNoOfShifts > adjAQ.length()/2){
				//cout << "Shifted over 0's : " << adjAQ << endl;
				QUOTIENT = adjAQ.substr(0, adjAQ.length()/2);
				REMAINDER = adjAQ.substr(adjAQ.length()/2+1 , adjAQ.length());
				//cout << "we are done here";
				//printOutput(adjAQ);
				break;
		}
		else if(AQ[i] == '0'){
			adjAQ.push_back('0');
			adjAQ = adjAQ.substr(1);
			noOfShiftsHere ++;
			totalNoOfShifts ++;

		}
		else
			break;
	}
	if(noOfShiftsHere >0)
		cout<< setw(30)<<"Shift Over 0's: " <<"."<< adjAQ.substr(0, adjAQ.length()/2) <<"  "<<adjAQ.substr(adjAQ.length()/2, adjAQ.length())<<endl;
	
	//cout << "Shifted over 0's : " << adjAQ << endl;
	delay = delay + 3 * noOfShiftsHere; // each shift takes 3 * t
	cout<<"Total Delay After shifting over 0's " << delay << "\n";
	return adjAQ;
}

string shiftOverOnes(string AQ){
	string adjAQ = AQ;
	int noOfShiftsHere = 0;
	for( int i = 0 ; i < AQ.length() ; i ++){
		if(totalNoOfShifts > adjAQ.length()/2){
				//cout << "Shifted over 1's : " << adjAQ << endl;
				QUOTIENT = adjAQ.substr(0, adjAQ.length()/2);
				REMAINDER = adjAQ.substr(adjAQ.length()/2+1 , adjAQ.length());
				//cout << "we are done here";
				//printOutput(adjAQ);
				//adjAQ = "END";
				break;
		}
		else if(AQ[i] == '1'){
			adjAQ.push_back('1');
			adjAQ = adjAQ.substr(1);
			noOfShiftsHere ++;
			totalNoOfShifts ++;

		}
		else
			break;
	}
	if(noOfShiftsHere >0)
		cout<< setw(30)<<"Shift Over 1's: " <<"."<< adjAQ.substr(0, adjAQ.length()/2) <<"  "<<adjAQ.substr(adjAQ.length()/2, adjAQ.length())<<endl;
	
	//cout << "Shifted over 1's : " << adjAQ << endl;
	delay = delay + 3 * noOfShiftsHere; // each shift takes 3 * t
	cout<<"Total Delay After shifting over 1's "<<delay<<"\n";
	return adjAQ;
}

string getA(string AQ){
	return AQ.substr(0, AQ.length()/2 + 1);
}

string addBitStrings( string first, string second )
{
	//cout<< " the A and B are : " << first << "  "<< second << endl;
    string result;  // To store the sum bits
 
    int carry = 0;  // Initialize carry
 
    // Add all bits one by one
    for (int i = first.length()-1 ; i >= 0 ; i--)
    {
    	if(first.at(i) == '*' || second.at(i) == '*')
    	{
    		result = result + '*';
    		carry = 0; // CORRECT THIS
    	}
    	else{
    		int firstBit = first.at(i) - '0';
       		int secondBit = second.at(i) - '0';
 
        	// boolean expression for sum of 3 bits
        	int sum = (firstBit ^ secondBit ^ carry)+'0';
 
        	result = (char)sum + result;
 
        	// boolean expression for 3-bit addition
        	carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    	}
    }
 
    // if overflow, then add a leading 1
    //if (carry)
      //  result = '1' + result;
 	


	/**
	* For carry select adder with 2 bit adder block
	* Tdelay = (n/m -1) * Ts + mTc
	* where
	* n = number of total operand bits
	* m = number of bits in full bit adder(we consider 2 bit adder)
	* Ts = delay for multiplexer ( 2t)
	* Tc = delay for m full bit ripple adder 
	**/
	delay = delay + ((first.length()/2 - 1) * 2 + 6); // 6 t for 2 bit ripple adder 
	cout<<"Total Delay in addition: "<<delay<<"\n";
    return result;
}
string substractB(string AQ, string B){
	string A = getA(AQ.insert(0,"0"));
	//cout << " A is : " << A << endl;
	
	string comB = complement(B.insert(0, "0"));
	cout<<setw(30)<<"Substract B: "<<comB.substr(0,1)<<"."<<comB.substr(1, comB.length())<<endl;
	cout << setw(40) <<" ---------"<<endl;
	//cout << "Complement of B: " << comB << endl;
	A = addBitStrings( A, comB);
	//cout << " A after substraction: " << A << endl;
	A = A.append(AQ.substr(AQ.length()/2 + 1   , AQ.length()));
	return A;
}

string addB(string AQ, string B){
	string A = getA(AQ.insert(0, "1"));
	//cout << " A is : " << A << endl;
	A = addBitStrings(A , B.insert(0,"0"));
	cout<<setw(30)<<"Add B: "<<"."<<B.substr(1, B.length())<<endl;
	cout << setw(40) <<" ---------"<<endl;
	//cout<<" A after addition: " << A << endl;
	A = A.append(AQ.substr(AQ.length()/2 + 1   , AQ.length()));
	return A;
}
void printOutput(string AQ){
	REMAINDER = AQ.substr(0, AQ.length()/2);
	QUOTIENT = AQ.substr(AQ.length()/2 , AQ.length());

	cout<<setw(30)<<"------------------------RESULTS-------------------------------"<<endl;
	cout <<setw(30)<<" QUOTIENT: "<< QUOTIENT<<endl;
	cout<<setw(30) <<" REMAINDER: "<<REMAINDER<<endl;
	cout <<setw(30)<< "DELAY: " << delay << " dt" <<endl;
}
