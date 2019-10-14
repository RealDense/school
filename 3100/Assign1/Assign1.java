/*Assignment 1 for 3100
 * Riley Densley
 */

import java.math.BigInteger;
import java.math.RoundingMode;
import java.math.BigDecimal;
import java.util.regex.*;

/*
 * Fibonacci
 * This class takes a number and finds the corresponding value in the Fibonicci sequence
 * @Riley Densley
 */
class Fibonacci {

	Fibonacci() {
		
	}
	
	int findFibonacci(int steps){
		//1 1 2 3 5 8 13
		int num1 = 1;
		int num2 = 1;
		for (int i = 1; i < steps; i++){
			int temp = num2 + num1;
			num1 = num2;
			num2 = temp;
		}
		return num2;

	}

}


/*
 * Factorial 
 * This class takes a number and finds the factorial of that number
 * @Riley Densley
 */
class Factorial {
	BigInteger num;

	Factorial() {
		this.num = BigInteger.valueOf(1);
	}

	BigInteger findFactorial(int steps){
		BigInteger num1 = BigInteger.valueOf(1);
		for (int i = 1; i <= steps; i++){
			num1 = num1.multiply(BigInteger.valueOf(i));
		}
		return num1;	
	}

}

/*
 * E
 * This class iterates through the Taylor series to find e a given number of times.
 * @Riley Densley
 */
class E {
	BigDecimal num;

	E() {
		this.num = BigDecimal.valueOf(1);
	}

	BigDecimal findE(int steps){
		Factorial eFac = new Factorial();
		if(steps == 1){
			return this.num;
		}else{
			for(int i = 1; i < steps; i++){
				//Taylor series devies by the factorial, the factorial class is called for that purpose
				this.num = this.num.add(BigDecimal.ONE.divide(new BigDecimal(eFac.findFactorial(i)), 16, RoundingMode.HALF_UP));
			}
			return this.num;
		}
	}
}

public class Assign1 {

	public static void help(){
		System.out.println("--- Assign 1 Help ---");
		System.out.println("  -fib [n] : Compute the Fibonacci of [n]; valid range [0, 40]");
		System.out.println("  -fac [n] : Compute the Factorial of [n]; valid range, [0, 2147483647]");
		System.out.println("    -e [n] : compute the value of 'e' using [n] iterations; valid range [1, 2147483647]\n");

	}

	public static boolean isInt(String str) {
		//Checks to see if input is actually an integer or not
		try {
			Integer.parseInt(str);
			return true;
		} catch (NumberFormatException e){
			return false;
		}
	}

	public static void main( String []args ) {
		int num;
		//Check to see if there were arguments given and if they are given as pairs
		if (args.length == 0 || (args.length%2) != 0){
			help();	
		}else{

			for (int i = 0; i < args.length; i+=2){
				if(isInt(args[i+1])){

					num = Integer.parseInt(args[i+1]);
					
					if(args[i].equals("-fib")){
						//Is number in a valid range?
						if((0<= num) && (num <= 40)){
							Fibonacci f = new Fibonacci();
							System.out.println("Fibonacci of " + num + " is " + f.findFibonacci(num));
						}else{
							System.out.println("\n   Number outside of acceptable range for -fib");
							help();
						}

					}

					else if(args[i].equals("-e")){
						//Is number in a valid range?
						if((1<= num) && (num <= 2147483647)){
							E e = new E();
							System.out.println("Value of e using " + num + " iterations is " + e.findE(num));
						}else{
							System.out.println("\n   Number outside of acceptable range for -e");
							help();
						}
					}

					else if(args[i].equals("-fac")){
						//Is number in a valid range?
						if((0<= num) && (num <= 2147483647)){
							Factorial fac = new Factorial();
							System.out.println("Factorial of " + num + " is " + fac.findFactorial(num));
						}else{
							System.out.println("\n   Number outside of acceptable range for -fac");
							help();
						}
					}

					else{
						System.out.printf("   Unknown command line argument: %s%n", args[i]);
						help();
					}
				}
				
				else{
					System.out.println("Not an integer: " + args[i] + " " + args[i+1]);
				}
			}
		}
	}

}
