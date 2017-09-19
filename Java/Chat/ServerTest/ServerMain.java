import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class ServerMain extends JFrame {

	static int count = 0;
	static int SetupWindow = 0;
	JButton b , off;
	JPanel p;
	JMenuBar menu;
	static JLabel l , countclient;
	static boolean StatusServer = false;
	
	
	private void CreateUI()
	{
		
		  menu = new JMenuBar();
		  JMenu fileMenu = new JMenu("�����");
		  fileMenu.add(new JMenuItem("���������"));
		  fileMenu.add(new JMenuItem("�����"));
		  fileMenu.setBackground( Color.RED );
		  menu.add(fileMenu);
		  
		  p = new JPanel();
		  p.setLayout( null );
		  p.setBackground(Color.GRAY);
		  
		  l = new JLabel( "���������� ��������: 0" ); l.setSize(200, 10); l.setLocation(20, 20);
		  p.add( l );
		  
		  b = new JButton("�����"); 
		  b.setSize(80, 30); 
		  b.setLocation( 20,400 );
		  p.add( b );
		  
		  off = new JButton("�������� ������"); 
		  off.setSize(140, 30); 
		  off.setLocation( 120,400 );
		  p.add( off );
		  
		  setResizable( false );
		  setLocation(100,100);
		  setContentPane( p );
		  setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		  setSize(500 , 500);
		  setVisible( true );
		
	}
	
	public ServerMain() {
		
		
	  super( "ServerTest" );
	  
	  CreateUI();
	  
	  b.addMouseListener(new MouseAdapter() {
		  public void mouseClicked(MouseEvent event) 
		  {
		   try{ SocketA.server.close(); } catch(Exception e){ } System.exit(0);
		  }   
	  });
	  
	  off.addMouseListener(new MouseAdapter() {
		  public void mouseClicked(MouseEvent event) 
		  {
		    if( StatusServer == false){ 
		    	
		    	off.setSize(150,30); off.setText( "��������� ������" ); StatusServer = true; new SocketA();
		    	
		    }
		  }   
	  });
	  
	  
	}
	
	
	public static void main(String[] args) {
		 
		new ServerMain();
		
		
	}

}




