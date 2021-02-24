package test_pro;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
public class LoginClient {

	public LoginClient() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	
////	备注：必须先运行服务器端，然后运行客户端
////	1.客户端
////	LoginClient.java
//	package pb.socket.LoginStr;

	         try {
	            //1.建立客户端socket连接，指定服务器位置及端口
	            Socket socket =new Socket("localhost",8899);
	            //2.得到socket读写流
	            OutputStream os=socket.getOutputStream();
	            PrintWriter pw=new PrintWriter(os);
	            //输入流
	            InputStream is=socket.getInputStream();
	            BufferedReader br=new BufferedReader(new InputStreamReader(is));
	            //3.利用流按照一定的操作，对socket进行读写操作
//	            String info="用户名：Tom,用户密码：123456";
	            String info="高德地图持续为您导航";
	            pw.write(info);
	            pw.flush();
	            socket.shutdownOutput();
	            //接收服务器的相应
	            String reply=null;
	            while(!((reply=br.readLine())==null)){
	                System.out.println("接收服务器的信息："+reply);
	            }
	            //4.关闭资源
	            br.close();
	            is.close();
	            pw.close();
	            os.close();
	            socket.close();
	        } catch (UnknownHostException e) {
	            e.printStackTrace();
	        } catch (IOException e) {
	            e.printStackTrace();
	        }
	    }
	}



