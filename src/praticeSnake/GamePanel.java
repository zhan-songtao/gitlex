package praticeSnake;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.security.Key;
import java.util.Random;
import javax.swing.*;
public class GamePanel extends JPanel implements KeyListener, ActionListener {
       int length;
       int[] snakeX=new int[600];
       int[] snakeY=new int[500];
       String fx="R";
       boolean isStart=false;
      int score;//定义积分

       Timer time=new Timer(100,this);//制作时间帧
       int foodx;int foody;
       Random random=new Random();
        boolean isFail=false;
    public GamePanel(){
             init();
             //获取键盘的监听事件

             this.setFocusable(true);
             this.addKeyListener(this);
             time.start();
         }

       public void init(){
            score=0;
            length=3;//小蛇长度
            snakeX[0]=100;snakeY[0]=100;
            snakeX[1]=75;snakeY[1]=100;
            snakeX[2]=50;snakeY[2]=100;
            foodx=25+25*random.nextInt(34);  //设定边界，确保食物不在区域外面34*25=850
            foody=25+25*random.nextInt(24);
       }

          @Override
     protected void paintComponent(Graphics g){

              super.paintComponent(g);//清屏
               this.setBackground(Color.WHITE);//设置背景颜色
              Data.headder.paintIcon(this,g,25,11);
              if(fx.equals("R")){
                  Data.right.paintIcon(this,g,snakeX[0],snakeY[0]);
               }else if(fx.equals("L")){
                  Data.left.paintIcon(this,g,snakeX[0],snakeY[0]);
              }else if(fx.equals("U")){
                  Data.up.paintIcon(this,g,snakeX[0],snakeY[0]);
              }else if(fx.equals("D")){
                  Data.down.paintIcon(this,g,snakeX[0],snakeY[0]);
              }
              g.fillRect(25,75,850,600);//绘制游戏区域
               //画个积分表
                g.setColor(Color.WHITE);
                g.setFont(new Font("微软雅黑",Font.BOLD,18));
                g.drawString("长度"+length,750,35);
                g.drawString("分数"+score,750,50);


              //画静态小蛇以及初始位置
              Data.right.paintIcon(this,g,snakeX[0],snakeY[0]);
              //Data.body.paintIcon(this,g,snakeX[1],snakeY[1]);
              //Data.body.paintIcon(this,g,snakeX[2],snakeY[2]);

              for(int i=1;i<length;i++){
                  Data.body.paintIcon(this,g,snakeX[i],snakeY[i]);
              }
                Data.food.paintIcon(this,g,foodx,foody);

              if(isStart==false){

                  g.setColor(Color.WHITE);//设置画笔颜色
                  g.setFont(new Font("微软雅黑",Font.BOLD,40));
                  g.drawString("按下空格开始游戏",300,400);

              }
              if(isFail){

                     g.setColor(Color.RED);
                     g.setFont(new Font("微软雅黑",Font.BOLD,40));
                     g.drawString("游戏失败!按下空格重新开始",300,400);
                     isStart=!isStart;

              }
     }

    @Override
    public void keyTyped(KeyEvent e) {
        //键盘按下，弹起
        // 接受键盘输入

    }

    @Override
    public void keyPressed(KeyEvent e) {
        //键盘按下，未释放
        int keyCode=e.getKeyCode();
        if(keyCode==KeyEvent.VK_SPACE) {//空格监听
            if (isFail) {//如果游戏失败，要重新开始:
                isFail = false;
                init();//重新初始化游戏
            }else {
                isStart = !isStart;
            }
            repaint();//重画（刷新）
        }
        if(keyCode==KeyEvent.VK_S){
             isStart=false;
             repaint();
        }


        if(keyCode==KeyEvent.VK_LEFT){
              fx="L";
        }else if(keyCode== KeyEvent.VK_RIGHT){
            fx="R";
        }else if(keyCode==KeyEvent.VK_UP){
            fx="U";
        }else if(keyCode==KeyEvent.VK_DOWN){
            fx="D";
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
         //释放某个键
    }

    @Override
    //执行定时操作
    public void actionPerformed(ActionEvent e) {//事件监听器
            if(isStart) {

                for (int i = length - 1; i > 0; i--) {
                    snakeX[i] = snakeX[i - 1];
                    snakeY[i] = snakeY[i - 1];
                }//这里便于让身体跟着头部运动
                //通过控制方向让头部移动
                if (fx.equals("R")) {
                    snakeX[0] = snakeX[0] + 25;
                    if (snakeX[0] > 850) {
                        snakeX[0] = 50;
                    }
                } else if (fx.equals("L")) {
                    snakeX[0] = snakeX[0] - 25;
                    if (snakeX[0] < 25) {
                        snakeX[0] = 850;
                    }
                } else if (fx.equals("U")) {

                    snakeY[0] = snakeY[0] - 25;

                    if (snakeY[0] < 75) {
                        snakeY[0] = 600;
                    }
                } else if (fx.equals("D")) {
                    snakeY[0] = snakeY[0] + 25;

                    if (snakeY[0] > 600) {
                        snakeY[0] = 75;
                    }
                }
                if (snakeX[0] == foodx && snakeY[0] == foody){
                    length++;//吃到食物 身体变长
                    score=score+10;
                    foodx=25+25*random.nextInt(34);  //随机生成下一个食物；
                    foody=25+25*random.nextInt(24);

            }
                for(int i=1;i<length;i++){
                    if(snakeX[0]==snakeX[i]&&snakeY[0]==snakeY[i]){
                         isFail=true;
                    }
                }
              //snakeX[0]=(snakeX[0]+25)%850;
                 //if(snakeX[0]>850) snakeX[0]=25;
                repaint();//刷新画板
            }
           // time.start();

    }
}
