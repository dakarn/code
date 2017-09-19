import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;


public class SendMessage extends JFrame {

	
	 JPanel p;
	 JTextArea ta;
	 JButton but = new JButton("Send");
	 public String iduser;
	 public Socket s;
	 
	public SendMessage( final Socket s , final String iduser ) {
		
		
		super("Send Message - "+iduser);
		
	      this.iduser = iduser;
	      this.s = s;
	      
	      JLabel lab = new JLabel("Enter Text");
	      
	      p = new JPanel();
	      p.setLayout( null );
	      p.setBackground(Color.GRAY);
	      
	      ta = new JTextArea(6, 31);
		  ta.setSize(270, 203); 
		  ta.setText("");
		  ta.setLocation( 30,45 );
		  ta.setMargin(new Insets(5,5,5,5));
		  ta.setEnabled( true );
		  ta.setDisabledTextColor( Color.black );
		  p.add( ta );
		  
		  lab.setLocation( 30,18 );
		  lab.setSize(143,20);
		  p.add(lab);
		  
		  but.setLocation( 30,260 );
		  but.setSize(143,30);
		  p.add(but);
		  
		  setMinimumSize(new Dimension(340, 330));
		  setResizable( false );
		  setContentPane( p );
		  setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		  setSize(340 , 330);
		  
		  setVisible( true );
		  
          but.addMouseListener(new MouseAdapter() {
			  
			  public void mouseClicked(MouseEvent event) 
			  {  
		  
	         	   if( ServClient.StatusConnect )
		           {	  
			          String data = ServClient.iduser+"<tag>"+ServClient.tfname.getText()+"("+Options.getForamtTime()+"):  <message>"+ta.getText()
			        		  +"<privatemessage>"+iduser;  
				
	                 try { s.getOutputStream().write(  data.getBytes()  ); dispose(); } catch(Exception e){ dispose(); } 
		           }   
			  }
			  
          });
		  
		
	}

}
