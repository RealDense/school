public class TrueFalse{
	public static void main (String[] args){
		if(false || false || false && false || false){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
		if(true || false || false && false || false){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
		if(false || true || false && false || false){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
		if(false || false || true && false || false){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
		if(false || false || true && false || false){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
		if(false || false || false && false || true){
			System.out.println("true");
		}else{
			System.out.println("false");
		}
	
	}
}
