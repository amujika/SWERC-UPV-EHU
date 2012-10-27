import java.util.Scanner;


public class GuessTheNumbers {

	/**
	 * @param args
	 */
	
	public static int[] valores;
	public static int[] lista = new int[30];
	public static char[] caracteres;
	public static int cantidadCaracteres;
	public static int resultado;
	public static boolean encontrado;
	public static arbolbin b;
	private class arbolbin{
		arbolbin izk,der;
		char c;
		
		
		arbolbin(String s){
			int n;
			if (s.length()==1){
				c=s.charAt(0);
				if (lista[c-'a']==0){
					caracteres[cantidadCaracteres++]=c;	
					lista[c-'a']=1;
				}
			}
			else{
				n=dividir(s);
				izk = new arbolbin(s.substring(1,n));
				der = new arbolbin(s.substring(n+1,s.length()-1));
				c = s.charAt(n);			
			}
		}
		
		public int operacion(){
			if (izk==null)
				return getValue(c);
			int n=izk.operacion();
			int m=der.operacion();
			switch(c){
			case '*':
				return n*m;
			case '+':
				return n+m;
			case '-':
				return n-m;
			}			
			return 0;
		}		
	}

	private int getValue(char c) {
		return	lista[c-'a'];
	}
	
	public static int dividir(String s){
		int nivel=1;
		
		for(int i =0;i<s.length();i++){
			switch(s.charAt(i)){
				case '(':
					nivel--;
					break;
				case ')':
					nivel++;
					break;	
				case '*':
				case '+':
				case '-':
					if(nivel==0)
						return i;					
				break;
			}
				
		}
		
		return -1;
	}
	
	public static void swap(int[] a,int x,int y){
		int prov=a[x];
		a[x]=a[y];
		a[y]=prov;
	}
	
    public static void perm2(int[] a) {
        perm2(a, a.length);
     }

     private static void perm2(int[] a, int n) {
         if (n == 1) {
             for (int i=0;i<a.length;i++){
            	 lista[caracteres[i]-'a']=a[i];
             }
             if (resultado==b.operacion()){
            	encontrado=true;
             }
             return;
         }
         for (int i = 0; (i < n)&&!encontrado;i++) {
             swap(a, i, n-1);
             perm2(a, n-1);
             swap(a, i, n-1);
         }
     }
     
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int n= in.nextInt();
		while(n!=0){
			cantidadCaracteres=0;
			encontrado=false;
			lista = new int[30];
			valores = new int[n];
			for (int i=0;i<n;i++)
				valores[i]=in.nextInt();
			caracteres=new char[n];
			resultado=in.nextInt();
			String s=in.next();
			GuessTheNumbers copy= new GuessTheNumbers();
			b=copy.new arbolbin(s);
			perm2(valores);
			if (encontrado)
				 System.out.println("YES");
			else
				 System.out.println("NO");
			n=in.nextInt();
		}
		
	}	

}
