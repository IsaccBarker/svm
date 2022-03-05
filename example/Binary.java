public class Binary{
   void Cocktail_Sort(int my_arr[]){
      boolean swapped = true;
      int start = 0;
      int end = my_arr.length;
      while (swapped == true) {
         swapped = false;
         for (int i = start; i < end - 1; ++i) {
            if (my_arr[i] > my_arr[i + 1]) {
               int temp = my_arr[i];
               my_arr[i] = my_arr[i + 1];
               my_arr[i + 1] = temp;
               swapped = true;
            }
         }
         if (swapped == false)
            break;
         swapped = false;
         end = end - 1;
         for (int i = end - 1; i >= start; i--) {
            if (my_arr[i] > my_arr[i + 1]) {
               int temp = my_arr[i];
               my_arr[i] = my_arr[i + 1];
               my_arr[i + 1] = temp;
               swapped = true;
            }
         }
         start = start + 1;
      }
   }
   void print_values(int my_arr[]){
      for (int i = 0; i < my_arr.length; i++)
      System.out.print(my_arr[i] + " ");
      System.out.println();
   }  
   public static void main(String[] args){
      Binary my_object = new Binary();
      int my_arr[] = { 6, 8, 34, 21, 0, 1, 98, 64, 6};
      System.out.println("The array contains ");
      for (int i = 0; i < my_arr.length; i++)
      System.out.print(my_arr[i] + " ");
      System.out.println();
      my_object.Cocktail_Sort(my_arr);
      System.out.println("The array after implementing cocktail sort is : ");
      my_object.print_values(my_arr);
   }
}
