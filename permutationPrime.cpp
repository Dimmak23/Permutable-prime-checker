/*
Code for solving "Permutable Prime" challenge.

Permutable Prime.

A permutable prime is a prime number of two or more digits
that remains prime with every possible rearrangement
of the digits.

For example:
Input: 79
Output: true (79 and 97 are both primes)

Input: 127
Output: false

Input: 337
Output: true (337, 373 and 733 are primes)

Write a program to check if the user input is a permutable
prime or not.

Bonus: Print all the permutable primes in a given range.
______________________________________________________________

Input instructions.

For getting code work you should:

1) Press character (s/S)-for single number checker
or (r/R)-for range searcher and after that press ENTER button.

2) Enter int number if you choose (s/S) and than SUBMIT
or enter first number in the range and that ENTER
and last number in the range and than SUBMIT.
*/
#include <iostream>
#include <algorithm> 
#include <vector>

/*
Base class provides to derrived class protectedly:
for getting digits from number,
setting digits to vector container,
permutating digits in the number,
setting all permutations to vector container,
checking if every permutation number is prime,
setting result of checking to bool container.
Base class provides to main program publicly:
dialog for getting mode of research,
bool containers with mode and approved statuses,
dialog for sending error in case of incorrect input,
destructor with "bye" message.
*/
class researchPrime
{
	// Answer from user keeping in the private
	private:
	// char container
	char answer;

	// protected containers and methods
	// shared with derrived classes
	protected:
	// container with digits from number
	std::vector<int> digits;
	// container with permutations
	std::vector<int> permutations;
	// container with status of number,
	// true - number is prime
	bool result = true;

	// Method for erasing containers
	void releaseContainers(){
		digits.erase (digits.begin(),digits.end());
		permutations.erase (permutations.begin(),permutations.end());
		// result always keeps as "true"
		result = true;
	}

	// Method for getting all digits from original number setting
	// them to vector and sorting after. It is nescessary
	// to pass number by value to method, because while loop
	// erase it, also digits should be sorted for correct
	// work of std::next_permutation in the next method -
	// getPermutations();
	void getDigits(int copy){
		// initilizing iterator for pointing starting position where
		// next digit should be placed
		std::vector<int>::iterator start;
		// while-loop provide checking non-empty copy of number 
		while (copy){
			// set iterator to begin of the vector
			start = digits.begin();
			// pass last digit to vector
			start = digits.insert(start, copy%10);
			// cutting copy of the number
			copy /= 10;
		}
		// sorting vector with digits
		std::sort(digits.begin(), digits.end());
	}

	// Method collect all possible permutations of digits from number
	// to the vector.
	void getPermutations(){
		// temporary variable for keeping permutation before passing it
		int temp = 0;
		// initilizing iterator for pointing starting position where
		// next permutation should be placed
		std::vector<int>::iterator start;
		// using do-while loop provide placing at least one original number
		// if the is no other possible permutation of digits
		do {
			// iterator provide digits that stored to temp
			for (std::vector<int>::iterator it = digits.begin();
			     it != digits.end(); ++it)
					temp = temp*10 + *it;
			// set iterator to begin of the vector
			start = permutations.begin();
			// pass new permutation to vector
			start = permutations.insert(start, temp);
			// erase temp
			temp = 0;
		// check if there is another possible permutation
		} while ( std::next_permutation(digits.begin(), digits.end()) );
	}
	
	// Method check every single possible permutation and return false
	// to result container when find at least one not prime variant.
	// It mean that number not prime in all permutations.
	void checkPrime(){
		// iterator in for-loop provide permutation that will be checked
		for (std::vector<int>::iterator it = permutations.begin();
		     it != permutations.end(); ++it){
			// for-loop look for number that could divisor to researched
			// number
			for (int i=2;i<=(*it/2+1);i++)
				// if find divisor and researched number consist more
				// than 1 digit return false to prime status
				// and break loop
				if ( !(*it % i) && (digits.size() != 1) ){
					// result always "true", it change only if permutation
					// not prime
					result = false;
					// point of return from method
					return;
				}
		}		
	}

	public:
	// true - for number, false - for range
	bool mode = true;
	// approved = true - correct input, false - incorrect
	bool approved = true;
	
	// Method that show to user options of the program
	void openDialog(){
		// message to user
		std::cout << "\nChoose your goal of research:"
				  << "\n\n(s/S) - for varifing single number"
				  << " being permutate prime,"
				  << "\n(r/R) - for showing all permutate primes "
				  << "in the given range.\n\n";
		// answer from user
		std::cin >> answer;
	}

	// Method that interpreted answer from user
	void scanDialog(){
		// Setting single number search mode
		if ( (answer == 's') || (answer == 'S') ) mode = true;
		// Setting range-search mode
		else if ( (answer == 'r') || (answer == 'R') ) mode = false;
		// Not allow to program work when input invalid
		else approved = false;
	}

	// Method sending "error" message to user,
	// inputed option was incorrect
	void validateDialog(){
		// Invalid input
		if (!approved)
			std::cout << "\nYou enter \"" << answer
					  << "\" for research mode."
					  << " It's invalid input.\n";
	}
	// Destructor of base class provide closing message
	~researchPrime() {
		std::cout << "\nThank you, run program again!\n";
	};	
};

/*
Class for researching single number given by user, which
protectedly inhirit methods and containers from researchPrime
class, so it can only start methods and print result
when it needed.
*/
class researchNumber : protected researchPrime
{
	// accessible to derrived range researcher class
	protected:
	// container with researched number 
	int number;

	// public methods shared with derrived class and main program
	public:
	// Method that ask user about wanted number to research
	void openDialog(){
		// response stored in the container
		std::cout << "\nEnter number for research here: ";
		std::cin >> number;
	}

	// Method runs in order inherited researching methods from
	// base class
	void runSingle(){
		// 1 - erase containers
		releaseContainers();
		// 2 - store digits from number
		getDigits(number);
		// 3 - store all permutations for number
		getPermutations();
		// 4 - check if every permutation is prime
		checkPrime();
	};

	// Method show result of research to user
	void closeDialog(){
		if (result) std::cout << "\n\nThe number " << number
							  << " is a prime in all permutations.\n";
		else std::cout << "\n\nThe number " << number
					   << " is not a prime in all permutations.\n";
	};	
};

/*
Class for researching all numbers in the given range by user.
This class protectedly inherit methods and containers from
researchNumber class, so it can only start methods and print
result when it needed.
*/
class researchRange : protected researchNumber
{
	// there is no need to share this containers with main program,
	// so they keeps private
	private:
	// container with begin point of the range
	int lRange;
	// container with end point of the range
	int rRange;
	// container with permutated primes
	std::vector<int> permutatePrimes;

	// public methods shared with main program
	public:

	// Method ask user about range of reserches
	void openDialog(){
		std::cout << "\nEnter first number of range here: ";
		std::cin >> lRange;
		std::cout << "\nEnter last number of range here: ";
		std::cin >> rRange;
	}

	// Method research number from user range (begin to end)
	// by calling runSingle() from researchNumber base class,
	// storing permutating primes into container
	void runRange(){
		std::vector<int>::iterator start;
		for (number = lRange; number <= rRange; number++){
			start = permutatePrimes.begin();
			runSingle();
			// next number wont get to container if it all permutations
			// are not prime
			if (result) start = permutatePrimes.insert(start, number);
		}
	};

	// Method show to user result of reserches
	void closeDialog(){
		int i = 5;
		// Show message in case of not a single permutated prime
		// appear in the given range
		if ( permutatePrimes.empty() )
			std::cout << "\n\nUnfortunatly, there is not a single permutable"
					  << "\nprime number in the given range." << '\n';
		// Show message if there is some permutated primes in the
		// given range
		else {
			std::cout << "\n\nThere are " << permutatePrimes.size()
					  << " permutate primes in the range ["
					  << lRange << ',' << ' ' << rRange << ']' << ":\n";
			for (std::vector<int>::iterator it = permutatePrimes.begin(); it != permutatePrimes.end(); ++it)
			{
				if (++i == 6){
					std::cout << '\n' << ' ';
					i = 0;
				}
				// permutated prime printed here
				std::cout << *it;
				if (it == (permutatePrimes.end()-1) )
					std::cout << '.' << '\n';
				else std::cout << ',' << '\t';
			}
		}
	};	
};

// Main program starting point
int main()
{
	// Start program by initilizing base class pointer
	researchPrime* arrow = new researchPrime;
	// Ask user about mode
	arrow -> openDialog();
	// What recieved from user?
	arrow -> scanDialog();
	// Show error message if it needed
	arrow -> validateDialog();

	// Start number research if mode require
	if ( arrow -> mode && arrow -> approved )
	{
		// Start number research by initilizing derrived
		// class pointer
		researchNumber* check = new researchNumber;
		// Ask user about number
		check -> openDialog();
		// Run research for single number
		check -> runSingle();
		// Show result
		check -> closeDialog();
	}
	
	// Start range research if mode require
	else if ( !(arrow -> mode)  && arrow -> approved )
	{
		// Start number research by initilizing derrived
		// class pointer
		researchRange* check = new researchRange;
		// Ask user about range
		check -> openDialog();
		// Run research for range
		check -> runRange();
		// Show result
		check -> closeDialog();
	}

	// For the end delete base class pointer
	// User will recieved closing "bye"
	delete arrow;
	return 0;
}
