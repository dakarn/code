import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import java.net.*;
import java.io.*;
import javax.sound.sampled.*;
import com.mysql.jdbc.Driver;
import java.sql.*;


public class MediaFile extends JFrame {

	JPanel p;
	Connection conndb;
	private static Statement stmt;
    private static ResultSet rs;
	
	public MediaFile() {
		
		  super("Player");
		  
		  try {
				 
				conndb = (Connection) DriverManager.getConnection("jdbc:mysql://localhost:3306/site","root","234679"); 
				
				stmt = conndb.createStatement();
	            rs = stmt.executeQuery("SELECT * FROM films LIMIT 0, 10");
	            
	            while (rs.next()) {
	                String count = rs.getString("screen");
	                System.out.println(count);
	            }
				
			} catch(Exception e){  } finally {
				
				try { conndb.close(); } catch(SQLException se) { }
	            try { stmt.close(); } catch(SQLException se) {  }
	            try { rs.close(); } catch(SQLException se) { }
			}
		  
		  try{ 
			  
			  
			  final AudioInputStream audioStream = AudioSystem.getAudioInputStream(new File("A://1.wav"));
			  AudioFormat format = audioStream.getFormat();
			  
	            DataLine.Info info = new DataLine.Info(Clip.class, format);
	 
	            final Clip audioClip = (Clip) AudioSystem.getLine(info);
	 
	            audioClip.addLineListener(new LineListener(){
					public void update(LineEvent ln) {
						
					}}
	            );
	 
	            audioClip.open(audioStream);
	             
	            audioClip.start();
		  
	            addWindowListener(new WindowAdapter() {
				public void windowClosing(java.awt.event.WindowEvent windowEvent) {	
					try { audioStream.close(); audioClip.close(); } catch (IOException e) {}
					}
	            });
		  
		  
		  } catch(Exception e){ e.printStackTrace(); }
		  
	      p = new JPanel();
	      p.setLayout( null );
	      p.setBackground(Color.GRAY);
	      
	      setLocation(100,100);
		  setMinimumSize(new Dimension(340, 330));
		  setResizable( false );
		  setContentPane( p );
		  setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		  setSize(440 , 430);
		  
		  setVisible( true );
		  
	}

}
