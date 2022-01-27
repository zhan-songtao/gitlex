package praticeSnake;
import javax.swing.*;
import java.net.URL;
public class Data {

      //头部图片  用到URL类
       public static URL headerurl=Data.class.getResource("/sourseSnake/header.png");
       public static ImageIcon headder=new ImageIcon(headerurl);

      public static URL downurl=Data.class.getResource("/sourseSnake/down.png");
      public static URL bodyurl=Data.class.getResource("/sourseSnake/body.png");
      public static URL lefturl=Data.class.getResource("/sourseSnake/left.png");
      public static URL righturl=Data.class.getResource("/sourseSnake/right.png");
      public static URL upurl=Data.class.getResource("/sourseSnake/up.png");
      public  static  URL foodurl=Data.class.getResource("/sourseSnake/food.png");

      public static ImageIcon down=new ImageIcon(downurl);
      public static ImageIcon up=new ImageIcon(upurl);
      public static ImageIcon right=new ImageIcon(righturl);
      public static ImageIcon left=new ImageIcon(lefturl);
      public static ImageIcon body=new ImageIcon(bodyurl);
      public static  ImageIcon food=new ImageIcon(foodurl);

}
