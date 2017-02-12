
import java.io.*;
import java.net.*;
import javax.swing.JFileChooser;


public class SendFile {

	
	JFileChooser fsch = new JFileChooser();
	long filesize;
	
	
	public SendFile( Socket s , String iduser )
	{
		
	    try 
	    {
	    	  
	       fsch.setCurrentDirectory(new File("A:\\workspace"));
           int ret = fsch.showDialog(null, "OpenDialog");
           
           if( ret != JFileChooser.APPROVE_OPTION ){ return; }
           
           
		   File file = fsch.getSelectedFile();
		   
		   String name = file.getName();
		   filesize = file.length();
		   ReadInet.filesize = filesize;
		   
		   
		   
		   BufferedReader is =  new BufferedReader(new FileReader(file));
		   int line;
		   
		   
		 
		   while( (line = is.read()) != -1 )
		   {
		    ReadInet.sbfile.append( (char)line );
		   }
		   
		   is.close();
		   
		
		   if( ServClient.StatusConnect )
           {	  
	         String data = "filesend:"+name+"<filename>"+filesize+"<filesize>"+iduser+"<iduserput>"+ServClient.iduser+"<idusersend>";
	         
	         
             try { s.getOutputStream().write(  data.getBytes()  ); } catch(Exception e){ } 
           }   
		
	    } catch(IOException e){}
		
	
		
	}

}
