import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;



public class BarLoadFile extends JFrame {

	JButton b;
	JPanel p;
	JProgressBar pb = new JProgressBar(0,100);
	JLabel label;
	Font font = new Font("TimesRoman", Font.BOLD,   13);
	int currValue = 0;
	String title = "";
   
	
	public void create()
	{
		
		p = new JPanel();
	    p.setLayout( null );
	    p.setBackground( new Color(188,188,188));
		Insets m = new Insets( 6, 6, 6, 6 );
		
		pb.setForeground( new Color(74,64,255) );
		pb.setValue( currValue );
		pb.setStringPainted(true);
		pb.setBorderPainted(true);
		pb.setBounds(20, 45, 250, 25);
		p.add(pb);
		
		label = new JLabel( title ); 
		label.setSize(200, 20); 
		label.setLocation( 20,20 );
		p.add( label );
	
		setLocation(200,100);
		setResizable( false );
		setContentPane( p );
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setSize(300 , 150);
		
	}
	
	public void Title( String title ){
		
		setTitle( title );
		this.title = title;
	}
	
	public BarLoadFile( ) 
	{
		super( "" );
	}
	
	public void closeBar()
	{
		dispose();
	}
	
	public void hideBar()
	{
		try { Thread.sleep(2000); } catch(InterruptedException e){}
		dispose();
	}
	
	public void showBar()
	{
		setVisible( true );
		this.setFocusable(true);
		
	}

	public void editBar( int size , int offset )
	{
		int total = (offset/size)*100;
		
		pb.setValue( total );
		label.setText( title+": "+(offset/1000)+"kb of "+(total)+"kb");
		
	}
	
}
