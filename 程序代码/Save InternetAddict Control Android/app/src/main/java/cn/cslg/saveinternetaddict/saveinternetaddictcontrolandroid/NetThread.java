package cn.cslg.saveinternetaddict.saveinternetaddictcontrolandroid;

import java.io.PrintWriter;
import java.net.Socket;

public class NetThread extends Thread{
    public static int state = 0;
    private String ip;
    private String messageInfo;

    public NetThread(String ip, String messageInfo){
        NetThread.state = 0;
        this.ip = ip;
        this.messageInfo = messageInfo;
    }

    @Override
    public void run() {
        NetThread.state = 1;
        try {
            Socket socket = new Socket(ip, 5000);
            PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
            printWriter.println(messageInfo);
            printWriter.flush();
            printWriter.close();
            socket.close();
            NetThread.state = 0;
        } catch (Exception e) {
            e.printStackTrace();
            NetThread.state = -1;
        }

    }
}