
import java.net.*;
import java.util.*;
import java.io.*;
import java.util.regex.*;

import javax.swing.JOptionPane;


public class SocketA implements Runnable {

	Thread t;
	public static Vector<Socket> vector = new Vector<Socket>();
	public static ServerSocket server;
	public static Vector<String> idusers = new Vector<String>();
	static Vector<Boolean> accessLoad = new Vector<Boolean>();
	static UserSetting useset = new UserSetting();
	static String[] infostr = new String[]{"beginload","1","0","exit","hello"};
	
	public SocketA() 
	{
		
		t = new Thread( this );
		t.start();
	}

	
	public static int setCountClient()
	{
		
		  int count = SocketA.vector.size();
		  ServerMain.count = count;
		  ServerMain.l.setText( "Количество клиентов: "+Integer.toString( count ) );
		  return count;
		
	}
	
	
	public void run()
	{
		try
        {
			server = new ServerSocket(128, 0, InetAddress.getByName("localhost"));
			
			while(true)
            {
                new Thread( new Connect( setCountClient() ,  server.accept()) ).start(); 
            }
           
        } catch(IOException e){ }
	}

}


class Connect extends Thread {

	Socket s;
	public boolean sock = true;
	static boolean FilePut = false;
	static int filesize;
	static String filename;
	int countPutFile;
	static String userput, usersend;
	
	
	
	public Connect( int count , Socket s )
	{
		this.s = s;
		
		ServerMain.l.setText( "Количество клиентов: "+Integer.toString( count ) );
		
		SocketA.vector.add( s );
		
	}
	
	
	public void SendClient( String data )
	{
		try
		{
			
		  for( int i = 0; i < SocketA.vector.size(); ++i )
		  {
			 if( SocketA.accessLoad.elementAt( i ) ) { continue; }
			 SocketA.vector.elementAt(i).getOutputStream().write(data.getBytes());
			
		  }
		 
		} catch(IOException e){ }
	}
	
	
	public void setAccessLoad( boolean status )
	{
		   int index = SocketA.idusers.indexOf( userput );
	       SocketA.accessLoad.set(index , status );
	       int index1 = SocketA.idusers.indexOf( usersend );
	       SocketA.accessLoad.set(index1 , status );
	      
	}
	
	public void SaveFile( Socket s ,  String data)
	{
		try 
	    {  
		 
		  String reg = "EndFile";
		  final int index = SocketA.idusers.indexOf( userput );
		  if( data.equals("EndFile") ){
			 
		    setAccessLoad( false );
			 FilePut = false; return;
	      }
	
	    	
		   SocketA.vector.elementAt(index).getOutputStream().write(data.getBytes());
	     
	       if( filesize < 7000 ){
	    	   setAccessLoad( false );
	    	   FilePut = false; return;	
			}
	       
	       try { Thread.sleep(400); } catch(InterruptedException e){}
           String data1 = "getNextFile";
		
           s.getOutputStream().write(data1.getBytes());
		
	    } catch (IOException e) {}
		
	}
	
	
	public void run()
	{
		
		try
		{
			
			while( sock )
			{
				
				byte buf[] = new byte[50*1024];
				InputStream is = s.getInputStream();
				int r = is.read( buf );
				String data = new String(buf, 0, r); 
				
				if( FilePut ){ SaveFile( s, data ); continue; }
				
				if( getResultQuery( s , data ) ) continue;
				
				if( getloadFile( s , data )) continue;
		        
		        String[] datatag = data.split( "<message>" );
		        
		        if( datatag.length == 2 )
		        {
		          if( getUsersID( s, datatag[1] ) ) continue;
		          if( SendPrivateMessage( datatag[0] , s, datatag[1] ) ) continue;      
		          SendClient( datatag[0]+""+datatag[1] ); continue;
		        }
		       
		        if( SocketA.useset.isSetting(data) ){ SocketA.useset.SaveSetting(); continue;  }
			}
			
		} catch(IOException e){ }
		
		DeleteClient( s ); this.interrupt(); sock = false; 
		
	}
	
	
	public boolean getResultQuery( Socket s , String data )
	{
		
        String[] str = data.split( "getresultQuery:" );
		
		if( str.length == 2 )
		{
			int index = SocketA.idusers.indexOf( userput );  
			int index1 = SocketA.idusers.indexOf( usersend );
			
			String[] name = str[1].split("<name>"); 
			
			if( name[0].equals(SocketA.infostr[0]) )
			{
				
			  String[] value = name[1].split("<value>");
			  if( value[0].equals(SocketA.infostr[1]) )
			  {
				 
				 FilePut = true;
				 SocketA.accessLoad.set(index , true );
		    	 SocketA.accessLoad.set(index1 , true );
		    	 
		    	 try {
		    		 
		    	   SocketA.vector.elementAt(index1).getOutputStream().write("resultQuery:resloadfile<name>2<value>".getBytes());
		    	   
		           String dataset = "filesend:"+filename+"<filename>"+filesize+"<filesize>"+userput+"<iduserput>"+usersend+"<idusersend>";
		           SocketA.vector.elementAt(index).getOutputStream().write(dataset.getBytes());
		           
		    	 } catch(IOException e){ }
		    	 
			  } else if( value[0].equals(SocketA.infostr[2]) ){
				 
				   try { 
				   SocketA.vector.elementAt(index1).getOutputStream().write("resultQuery:resloadfile<name>3<value>".getBytes());    
			       } catch(Exception e){}
			  }
			
			} else if( name[0].equals(SocketA.infostr[3]) )
			{
				DeleteClient( s ); this.interrupt(); sock = false;
				
			} else if( name[0].equals(SocketA.infostr[4]) )
			{ 
				String[] value = name[1].split("<value>"); 
				SocketA.idusers.add( value[0] ); SocketA.accessLoad.add( false );
			}
			
			
			return true;	  
		}
		
		return false;
    }
	
	
	
	public void DeleteClient( Socket s )
	{
		try
		{	
		  int index = SocketA.vector.indexOf(s);
		   
		  String iduser = SocketA.idusers.elementAt( index );
		  s.close(); SocketA.vector.remove(index); SocketA.idusers.remove(index);
		  SocketA.accessLoad.remove( index );
		  
		  SocketA.useset.ClearSetting( index );
	
		  SocketA.setCountClient();
		  if( SocketA.idusers.size() > 0 ){ SendClient("1<tag>CHATBOT: The User("+iduser+") left the chat"); }
		
		} catch(Exception e){ }
		
	}
	
	
	public boolean getUsersID( Socket s , String data )
	{
		try{
			
		 String eq = "getUsersID";
		
	     if( data.equals(eq) )
	     { 
	    	 String[] listuser = SocketA.idusers.toArray( new String[ SocketA.idusers.size() ]);
	 		
	 		 String data1 = "CommandChat<tag>getUserList<users>"+String.join( "<user>" , listuser)+"<user>end";
	 		 
	    	 OutputStream os = s.getOutputStream();
			 os.write(data1.getBytes());
			 return true;
	     } 
	     
		} catch(Exception e){  }
		
		return false;
	}
	
	
	public boolean getloadFile( Socket s , String data )
	{
		String[] str = data.split( "filesend:" );
		
		if( str.length == 2 )
		{
			String[] name = str[1].split("<filename>"); 
			String[] size = name[1].split("<filesize>");
			String[] idput = size[1].split("<iduserput>");
			String[] idsend = idput[1].split("<idusersend>");
			filename = name[0];
			filesize = Integer.parseInt(size[0]);
			userput = idput[0];
			usersend = idsend[0];
			
		    try 
		    {
		       int index = SocketA.idusers.indexOf( userput );  
			   int index1 = SocketA.idusers.indexOf( usersend );
			   
		       int res = SocketA.useset.getloadFile( index );
		       if( res == 0 )
		       {
		    	   s.getOutputStream().write("resultQuery:resloadfile<name>0<value>".getBytes());
		    	   
		       } else if( res == 1 ){
		    	   
		    	   SocketA.vector.elementAt(index).getOutputStream().write("resultQuery:accessload<name>1<value>".getBytes());
		    	   
		       } else if( res == 2 )
		       { 
		    	   SocketA.accessLoad.set(index , true );
		    	   SocketA.accessLoad.set(index1 , true );
		    	   
		    	   s.getOutputStream().write("resultQuery:resloadfile<name>2<value>".getBytes()); 
		       
		    	   FilePut = true;
		       
		           String dataset = "filesend:"+filename+"<filename>"+filesize+"<filesize>"+userput+"<iduserput>"+usersend+"<idusersend>";
		       
		           SocketA.vector.elementAt(index).getOutputStream().write(dataset.getBytes());
		       }
		       
		    } catch (IOException e) { }
			
			return true;	  
		}
		
		return false;
			  
	}
	
	
	public boolean SendPrivateMessage( String tag , Socket s, String data )
	{
		String[] str = data.split( "<privatemessage>" );
		
		if( str.length == 2 ){
			
		  int index = SocketA.idusers.indexOf( str[1] );	
		  
		  try {
			 
		   String data1 = tag+""+str[0];
		   boolean res = SocketA.useset.getPrvMsg( index );
		   
		   if( res )
		   {
		    OutputStream os = SocketA.vector.elementAt(index).getOutputStream();
		    os.write(data1.getBytes());
		   
		    s.getOutputStream().write(data1.getBytes());
		    
		    return true;
		   }
		   	
		   s.getOutputStream().write("resultQuery:resprvmsg<name>0<value>".getBytes());
		   
		   return true;
		  
		  } catch(Exception e){  }
		 
		}
		
		return false;
	}
	
}
