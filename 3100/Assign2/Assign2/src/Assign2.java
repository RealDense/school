/*Assignment 1 for 3100
 * Riley Densley
 */

import java.util.regex.*;
import java.lang.Object;
import java.lang.Runtime;
import java.util.Properties;
import java.text.DecimalFormat;


public class Assign2 {

	public static void help(){
		System.out.println("--- Assign 1 Help ---");
		System.out.println("  -fib [n] : Compute the Fibonacci of [n]; valid range [0, 40]");
		System.out.println("  -fac [n] : Compute the Factorial of [n]; valid range, [0, 2147483647]");
		System.out.println("    -e [n] : compute the value of 'e' using [n] iterations; valid range [1, 2147483647]\n");

	}


	public static void printMem(String type, long mem){
		DecimalFormat formatter = new DecimalFormat("#,###");
		System.out.printf("%s\t: %16s\n", type, formatter.format(mem));
	}

	public static void main( String []args ) {
		for (int i = 0; i < args.length; i+=1){
			if(args[i].equals("-cpu")){
				System.out.printf("Processors\t: ");
				System.out.println(Runtime.getRuntime().availableProcessors());
			}

			else if(args[i].equals("-mem")){
				printMem("Free Memory", Runtime.getRuntime().freeMemory());
				printMem("Total Memory", Runtime.getRuntime().totalMemory());
				printMem("Max Memory", Runtime.getRuntime().maxMemory());

			}

			else if(args[i].equals("-dirs")){
				System.out.printf("Working Directory\t: %s\n", System.getProperty("user.dir"));
				System.out.printf("User Home Directory\t: %s\n", System.getProperty("user.home"));
			}

			else if(args[i].equals("-os")){
				System.out.printf("OS Name\t\t: ");
				System.out.println(System.getProperty("os.name"));
				System.out.printf("OS Version\t: ");
				System.out.println(System.getProperty("os.version"));
				
			}

			else if(args[i].equals("-java")){
				System.out.printf("Java Vendor\t: %s\n", System.getProperty("java.vendor"));
				System.out.printf("Java Runtime\t: %s\n", System.getProperty("java.runtime.name"));
				System.out.printf("Java Version\t: %s\n", System.getProperty("java.version"));
				System.out.printf("Java VM Version\t: %s\n", System.getProperty("java.vm.version"));
				System.out.printf("Java VM Name\t: %s\n", System.getProperty("java.vm.name"));

			}

			else{
				System.out.printf("   Unknown command line argument: %s%n", args[i]);
				help();
			}
				
		}
	}

}
