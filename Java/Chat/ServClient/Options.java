import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.util.*;

import javax.swing.*;


public class Options extends JFrame {

	JPanel p;
	JTextField ip , addr , dir , load, prvmsg;
	JButton save;
	Insets m = new Insets( 6, 6, 6, 6 );
	JLabel l1 , l2 , l3 , l4 , l5;

	
	public Options() {
		
		 super("ClientServer - Options");
		
		  
		 
	      p = new JPanel();
	      p.setLayout( null );
	      p.setBackground(Color.GRAY);
	      
	      addr = new JTextField( Config.getAddres() ); 
		  addr.setSize(190, 32); 
		  addr.setLocation( 20,50 );
		  addr.setMargin( m );
		  p.add(  addr );
		  ip = new JTextField(  Config.getPort() ); 
		  ip.setSize(170, 32); 
		  ip.setLocation( 230,50 );
		  ip.setMargin(m);
		  p.add( ip );
		  
		  
		  l3= new JLabel("<html><b>Папка для файлов</b>"); 
		  l3.setSize(190, 25); 
		  l3.setLocation( 20,104 );
		  p.add(l3);
		  
		  dir = new JTextField(  Config.getPathSave() ); 
		  dir.setSize(110, 32); 
		  dir.setLocation( 20,130 );
		  dir.setMargin(m);
		  p.add( dir );
		  
		  
		  l4= new JLabel("<html><b>Получ. файлов</b>"); 
		  l4.setSize(190, 25); 
		  l4.setLocation( 170,104 );
		  p.add(l4);
		  
		  load = new JTextField(  Integer.toString(Config.getLoadFile() ) ); 
		  load.setSize(90, 32); 
		  load.setLocation( 170,130 );
		  load.setMargin(m);
		  p.add( load );
		  
		  l5= new JLabel("<html><b>Получать прив. сообщения</b>"); 
		  l5.setSize(220, 25); 
		  l5.setLocation( 300,104 );
		  p.add(l5);
		  
		  prvmsg = new JTextField( Config.getprvmsg() ); 
		  prvmsg.setSize(150, 32); 
		  prvmsg.setLocation( 300,130 );
		  prvmsg.setMargin(m);
		  p.add( prvmsg );
		  
		  save = new JButton("Save"); 
		  save.setSize(80, 30); 
		  save.setLocation( 20,220 );
		  p.add( save );
		  
		  l1= new JLabel("<html><b>Адрес сервера</b>"); 
		  l1.setSize(190, 25); 
		  l1.setLocation( 20,24 );
		  p.add( l1 );
		  
		  l2= new JLabel("<html><b>Порт сервера</b>"); 
		  l2.setSize(190, 25); 
		  l2.setLocation( 230,24 );
		  p.add( l2 );
		  
		  save.addMouseListener(new MouseAdapter() {
			  
			  public void mouseClicked(MouseEvent event) 
			  { 
			    		Config.setAddres( addr.getText() ); Config.setPort( ip.getText() );
			    		Config.setPrvMsg( prvmsg.getText() ); Config.setLoadFile( Integer.parseInt(load.getText()) );
			    		Config.setPathSave( dir.getText() );
			    		ServClient.OpStatus = false;
			    		dispose();
			  }
			    
		  });
		  
		  this.addWindowListener(new WindowAdapter() {
			   
			    public void windowClosing(java.awt.event.WindowEvent windowEvent)
			    {
			        
			    	ServClient.OpStatus = false;
			    	Config.setAddres( addr.getText() ); Config.setPort( ip.getText() );
			    	Config.setPrvMsg( prvmsg.getText() ); Config.setLoadFile( Integer.parseInt(load.getText()) );
			    	Config.setPathSave( dir.getText() );
			    	
			    }
			    
			});
	      
	      setMinimumSize(new Dimension(500, 300));
		  setResizable( false );
		  setContentPane( p );
		  setDefaultCloseOperation( JFrame.HIDE_ON_CLOSE);
		  setSize(500 , 300);
		  
		  setVisible( true );
	}
	
	
	public static String getForamtTime()
	{
		
        Calendar date = Calendar.getInstance();
		
		int hours = date.get( Calendar.HOUR); int minute = date.get( Calendar.MINUTE); int sec = date.get( Calendar.SECOND );
		
		String ch = "", ch1 = "", ch2 = "";
		
		if( hours < 10 ){  ch = "0"; } 
		
		if( minute < 10 ){  ch1 = "0"; } 
		
		if( sec < 10 ){  ch2 = "0"; } 
		
		String time = ch+Integer.toString( hours )+" : "+ch1+Integer.toString( minute )+" : "+ch2+Integer.toString( sec );
		
		return time;
		
	}



}