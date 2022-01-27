package praticeSnake;

import javax.swing.*;
import java.awt.*;

public class Section1 {
    public static void main(String[] args) {
           //绘制静态窗口
        JFrame jFrame=new JFrame("Java：贪吃蛇小游戏");
        jFrame.setBounds(200,50,900,720);
        jFrame.setVisible(true);
        jFrame.setResizable(false);
        jFrame.setDefaultCloseOperation(jFrame.EXIT_ON_CLOSE);
        jFrame.add(new GamePanel());

    }
}
