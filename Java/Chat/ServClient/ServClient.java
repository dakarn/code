import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;


public class ServClient extends JFrame {

	static BarLoadFile progress = new BarLoadFile();
	static JButton b , b1, b2 , con , op;
	static JPanel p;
	static JTextField tf , tfname;
	Socket s;
	static JTextArea ta;
	JLabel label;
	static boolean StatusConnect = false;
	static boolean OpStatus = false;
	Font font = new Font("TimesRoman", Font.BOLD,   13);
	static long iduser;
	
	
	public boolean Connect()
	{
		 try
		  { 
			  
			 s = new Socket( Config.getAddres(), Integer.parseInt(Config.getPort()) ); 
				 
			 new Thread( new ReadInet( s ) ).start(  ); 
			 
			
			 
			 return true;
			 
		  } catch(IOException e){ return false; }
		 
	}
	
	
	static void uploadSetting( Socket s )
	{
		
		String data = "usersetting:"+Config.getLoadFile()+"<loadfile>"+Config.getprvmsg()+"<prvmsg>";
		try { s.getOutputStream().write(  data.getBytes()  ); } catch(Exception e){ }
		
	}
	
	
	public ServClient(){
	
	
		
		 super("ClientServer");
		
		      Date date = new Date();
		      iduser = date.getTime();
		      
		  	  
		      
		      
		      
		      this.setTitle("ClientServer - SelfID: "+iduser);
		      
		      p = new JPanel();
		      p.setLayout( null );
		      p.setBackground(Color.GRAY);
			  
		      Insets m = new Insets( 6, 6, 6, 6 );
		      
		      label = new JLabel("<html><b>Онлайн-Чат</b>"); 
			  label.setSize(190, 25); 
			  label.setLocation( 20,90 );
			  p.add( label );
			  	  
			  tfname = new JTextField("Login"); 
			  tfname.setSize(190, 32); 
			  tfname.setLocation( 20,25 );
			  tfname.setMargin( m );
			  p.add( tfname );
			  tf = new JTextField("getUsersID"); 
			  tf.setSize(170, 32); 
			  tf.setLocation( 230,25 );
			  tf.setMargin(m);
			  p.add( tf );

			  JPopupMenu popup = new JPopupMenu();
			  popup.add(" Copy ");
			  popup.add(" Paste ");
			  popup.add(" Cut ");
			  tf.add(popup);
			  tf.setComponentPopupMenu(popup);
			  	  
			  ta = new JTextArea(0, 31);
			  ta.setSize(430, 393); 
			  ta.setText("");
			  ta.setLocation( 20,115 );
			  ta.setEnabled( false );
			  ta.setDisabledTextColor( Color.black );
			  ta.setMargin( m );
			  ta.setFont( font );
			  JScrollPane scroll = new JScrollPane(ta);
			  scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		      scroll.setBounds(20, 115, 430, 393);
			  p.add( scroll );
			  	  
			  b = new JButton("Exit"); 
			  b.setSize(80, 30); 
			  b.setLocation( 20,520 );
			  p.add( b );
			  
			  con = new JButton("Connect"); 
			  con.setSize(110, 30); 
			  con.setLocation( 110,520 );
			  p.add( con );
			  	  
			  op = new JButton("Options"); 
			  op.setSize(110, 30); 
			  op.setLocation( 232,520 );
			  p.add( op );
			    
			  b1 = new JButton("Send"); 
			  b1.setSize(80, 26); 
			  b1.setLocation( 20,57 );
			  p.add( b1 );
			  
			  b.addMouseListener(new MouseAdapter() {
				  
				  public void mouseClicked(MouseEvent event) 
				  {
					     
				    try
				    {
				    	new MediaFile();
				    	
				    	if( StatusConnect != false )
						{ 
				    	 String data1 = "getresultQuery:exit<name>0<value>";  
						
						 s.getOutputStream().write(  data1.getBytes()  );
						
					     s.close();
						}
				    	
					    //System.exit(0);
					    
				    } catch (IOException e) {}
					
				  }
				    
			  });
			  

              con.addMouseListener(new MouseAdapter() {
				  
				  public void mouseClicked(MouseEvent event) 
				  {   
					  
					  
					  
					  if( StatusConnect ){
					    	
					      try { s.getOutputStream().write(  "getresultQuery:exit<name>0<value>".getBytes()  ); s.close(); } catch(Exception e){ }  con.setText("Connect"); StatusConnect = false; 
			              return;
					  }	
				    	
				      boolean res = Connect(); 
				      
				      if( !res ) { 
				    	  
				    	  JOptionPane.showMessageDialog(ServClient.p, "Подключение к серверу\nне удалось.");
				      
				          StatusConnect = false; con.setText( "Reconnect" ); } else { 
				    	  StatusConnect = true; con.setText( "Disconnect" );
				    	  String data = "getresultQuery:hello<name>"+iduser+"<value>";  
						
				          try { s.getOutputStream().write(  data.getBytes()  ); } catch(Exception e){ }    
				    	  
				      }
				    	   
				      
				  }
				    
			  });
              
              op.addMouseListener(new MouseAdapter() {
				  
				  public void mouseClicked(MouseEvent event) 
				  {  
					   if( !OpStatus ){  OpStatus = true; new Options(); }		
				  }
				    
			  });
            
			  b1.addMouseListener(new MouseAdapter() {
				  public void mouseClicked(MouseEvent event) 
				  {
					  try
					  {
						 if( StatusConnect != false )
						 {  
						  
						  String data = iduser+"<tag>"+tfname.getText()+"("+Options.getForamtTime()+"):  <message>"+tf.getText();  
						
						  s.getOutputStream().write(  data.getBytes()  );
						  
						 }
						  
					  } catch (IOException e) {}
				  }   
			  });
			  
			  setLocation(200,100);
			  setMinimumSize(new Dimension(500, 600));
			  setResizable( false );
			  setContentPane( p );
			  setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			  setSize(500 , 600);
			  
			  setVisible( true );
			  
			  
			  
	}

	
	
	public static void main(String[] args) {
		
		new ServClient(); 
		
		
	    
	}

}



class ReadInet extends Thread {
	
	Socket s;
	public int countLine = 0;
	static boolean SendFile = false;
	static boolean PutFile = false;
	String[] infostr = new String[]{"LoadingFile","getNextFile","resprvmsg","0","1","2","resloadfile","CommandChat","accessload","3"};
	long FrameFile = 0;
	public static StringBuilder sbfile = new StringBuilder();
	static long filesize;
	static String putfilename;
	static long putfilesize;
	int countPutFile = 0;
	
	
	public void ThreadDialog( ){
		
		new Thread( new Runnable(){ public void run(){	
			int res = JOptionPane.showConfirmDialog(ServClient.p, "Принять файл от пользователя?","Подтверждение",JOptionPane.YES_NO_OPTION);
			String str = "getresultQuery:beginload<name>0<value>";
			if( res == 0 ){ str = "getresultQuery:beginload<name>1<value>"; }
			try {s.getOutputStream().write(str.getBytes());}catch(Exception e){}
		}}).start();
		
	}

	
	
	public boolean setResultQuery( String data )
	{
	  try 
	  {	
        String[] str = data.split( "resultQuery:" );
		
		if( str.length == 2 )
		{
			
			String[] name = str[1].split("<name>"); 
			
			if( name[0].equals(infostr[2]) )
			{
				
			 String[] value = name[1].split("<value>");
			 if( value[0].equals(infostr[3]) )
			 {
				 JOptionPane.showMessageDialog(ServClient.p, "Отпрака приватных сообщений\nэтому пользователя не доступна.");	 
			 }
			
			} else if( name[0].equals(infostr[6]) )
			{
				 String[] value = name[1].split("<value>");
				 if( value[0].equals(infostr[3]) )
				 {   
					 SendFile = false;
					 JOptionPane.showMessageDialog(ServClient.p, "Отпрака файлов не доступна\nэтому пользователю.");
					 
				 } else  if( value[0].equals(infostr[5]) )
				 { 
					 SendFile = true; 
					 ServClient.progress.Title( "Sending File" ); ServClient.progress.create(); ServClient.progress.showBar();
					 FrameFile(); 
				 } else if( value[0].equals(infostr[9]) )
				 {
					 JOptionPane.showMessageDialog(ServClient.p, "Пользователь не хочет получать этот файл.");	 
				 }
			
			} else if( name[0].equals(infostr[8]) ){
				
				 String[] value = name[1].split("<value>");
				 if( value[0].equals(infostr[4]) )
				 {  
					ThreadDialog();
				 }
			}
			
			return true;	  
		}
		
	  } catch( Exception e ){}
		
		return false;
    }

	
	public void FrameFile( )
	{
		ServClient.progress.editBar( (int)putfilesize, countPutFile  );
		
		if( filesize < 7000 ){
			
			try { 
			    String data1 = ReadInet.sbfile.substring( 0 , ReadInet.sbfile.length() );
			    s.getOutputStream().write(  data1.getBytes() );
			    filesize = 0; sbfile.setLength(0);  SendFile = false; FrameFile = 0;
			    JOptionPane.showMessageDialog(ServClient.p, "Пользователь получил файл."); 
			    ServClient.progress.hideBar(); return;
			} catch(Exception e){ } 
		}
		
		if( filesize <= FrameFile )
		{  
			try { 
				
				String info = "EndFile";
				s.getOutputStream().write(  info.getBytes() );
				
			} catch(Exception e){ } 
			 JOptionPane.showMessageDialog(ServClient.p, "Пользователь получил файл.");
			 filesize = 0; sbfile.setLength(0);  SendFile = false; FrameFile = 0; 
			 ServClient.progress.hideBar(); return; 
			
		}
		
		long current = FrameFile;
		FrameFile = FrameFile + 5000;
		
		if( FrameFile > filesize  )
		{ 
			long temp =  FrameFile - filesize;
			FrameFile = FrameFile - temp;
		}
		
		String data = sbfile.substring( (int)current , (int)FrameFile );
	
		try { 
		    s.getOutputStream().write(  data.getBytes() );
		} catch(Exception e){ } 
		
		
		
	}
	
	
   	public ReadInet( Socket s )
   	{
   		
   		this.s = s;
   		
   	}
   	
   	
   	public void writefile( String data )
   	{
   		
   	 File sdFile = new File("A:\\"+putfilename);
     try 
     {
   
      BufferedWriter bw = new BufferedWriter(new FileWriter(sdFile , true ));
      bw.write(data);
      bw.flush();
      bw.close();
     
     } catch (IOException e) { }
     
   	}
   	
   	public void SaveFile( String data )
	{     
   		  countPutFile = countPutFile + data.length();
   		  
   		  ServClient.progress.editBar( (int)putfilesize, countPutFile  );
		  writefile( data );
		  
		  if( putfilesize <= countPutFile )
		  {
			  countPutFile = 0; PutFile = false; SendFile = false; 
			  JOptionPane.showMessageDialog(ServClient.p, "Файл успешно получен."); 
			  ServClient.progress.hideBar(); return;	  
		  }
		  
		  
          
	}
   	
   	
   	public void run(){
   		
   		try
   		{
   			
   		 ServClient.uploadSetting( s );
   			
   		 while( true )
   		 {
   			  
   		  byte buf[] = new byte[64*1024];
          int r = s.getInputStream().read(buf);
          String data = new String(buf, 0, r);
          
         
          if( PutFile ){
        	
        	  SaveFile( data );
        	  continue;
          }
          
          if( SendFile ){
        	  
              if( data.equals( infostr[1] ) ){ FrameFile( ); }
        	  continue;
          }
          
          if( getloadFile( s , data )) continue;
          
          if( setResultQuery( data ) ) continue;
          
          String[] datatag = data.split( "<tag>" );
          
          if( datatag[0].equals( infostr[7] ) ){ new RunCommand(  s, datatag[1] ); continue; }
          
          ServClient.ta.append( datatag[1]+"\n" ); 
          countLine++;
          ServClient.ta.setRows( countLine  );
          
   		 }
   		
   		} catch(Exception e){ }
   		
   	    if( ServClient.StatusConnect ){ try { s.close();  ServClient.con.setText("Reconnect"); ServClient.StatusConnect = false; } catch(Exception e){ } }
   		
   	}
   	
   	
   	public boolean getloadFile( Socket s , String data )
	{
		String[] str = data.split( "filesend:" );
		
		if( str.length == 2 )
		{
			PutFile = true;
			
			String[] name = str[1].split("<filename>"); 
			String[] size = name[1].split("<filesize>");
			String[] idput = size[1].split("<iduserput>");
			putfilename = name[0];
			putfilesize = Integer.parseInt(size[0]);
			
			File sdFile = new File("A:\\"+putfilename);
		    try 
		    {
		     
		       BufferedWriter bw = new BufferedWriter(new FileWriter(sdFile));
		       bw.write("");
		       bw.flush();
		       bw.close();
		       
		       ServClient.progress.Title( "Download File" ); ServClient.progress.create(); ServClient.progress.showBar();
		      
		    } catch (IOException e) { }
			
			return true;	  
		}
		
		return false;
			  
	}
}



class RunCommand extends JPopupMenu {
	
	
	String command;
	static boolean openmenu = false;
	String userselect = "";
	Socket s;
	
	
	
	public RunCommand( Socket s, String command ){
		
		
		this.s = s;
		this.command = command;
		
		if( openmenu ) return;
		
		String[] commands = command.split("<(.*)>");
		
		String[] runcomm = new String[]{ "getUserList" };
		
		
		if( commands[0].equals( runcomm[0] ) ){ viewUsersID ( command ); }
		
		
		
	}
	
	
	private void viewUsersID( String data ){
		
		
		  int ytext = 10;
		
		  String users[] = data.split( "<users>" );
		 
		  String[] user = users[1].split( "<user>" );
		
		  openmenu = true;
		  
		  final JFrame frame = new JFrame("ListUser");
		  JPanel pan;
	      
	      pan = new JPanel();
	      pan.setLayout( null );
	      pan.setBackground(Color.GRAY);
	      
	      JButton mess = new JButton("Send Message");
	      JButton filesend = new JButton("Send File");
	      mess.setSize(120,28);  
    	  mess.setLocation( 14 , 230 );
    	  filesend.setSize(100,28);  
    	  filesend.setLocation( 148 , 230 );
    	  pan.add(mess);
    	  pan.add(filesend);
    	  
	      
	        
	      for( int i = 0; i < user.length-1; ++i )
	      {
	    	  
	    	  if( ServClient.iduser ==  Long.parseLong(user[i]) ) continue;
	    	  
	    	  
	    	  final JButton b = new JButton(user[i]);
	    	  b.setSize(130,20);  
	    	  b.setLocation( 14 , ytext );
	    	  b.setBackground(Color.GREEN);
	    	  pan.add(b);
	    	  ytext = ytext + 26;
	    	  
              b.addMouseListener(new MouseAdapter() {
				  
				  public void mouseClicked(MouseEvent event) 
				  {  
					  userselect = b.getText();	b.setBackground(Color.WHITE);
				  }
				    
			  });
	    	 
			  
	      }
	     
	      
	      mess.addMouseListener(new MouseAdapter() {
			  
			  public void mouseClicked(MouseEvent event) 
			  {  
				  if( userselect != "" ){  openmenu = false; frame.dispose(); new SendMessage( s, userselect ); } else {
					  JOptionPane.showMessageDialog(ServClient.p, "Не выбран подьзователь!");
				  }
			  }
			    
		  });
	      
	      filesend.addMouseListener(new MouseAdapter() {
			  
			  public void mouseClicked(MouseEvent event) 
			  {  
				  if( userselect != "" ){ openmenu = false; frame.dispose(); new SendFile( s , userselect ); } else {
					  JOptionPane.showMessageDialog(ServClient.p, "Не выбран подьзователь!");
				  }
			  }
			    
		  });
	      
	      
	      frame.setMinimumSize(new Dimension(360, 300));
		  frame.setResizable( false );
		  frame.setContentPane( pan );
		  frame.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		  frame.setSize(300 , 300);
		  frame.setVisible( true );
		  
		  
		  frame.addWindowListener(new WindowAdapter() {
			    public void windowClosing(java.awt.event.WindowEvent windowEvent) {	openmenu = false;  }	    
		  });
		
	}
	
}


