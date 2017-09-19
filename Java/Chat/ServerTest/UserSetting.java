import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;


public class UserSetting {

	
	public Vector<Integer> loadfile = new Vector<Integer>(); 
	public Vector<Boolean> prvmsg = new Vector<Boolean>();
	private String savestr = new String();
	
	public UserSetting() {
		
	}

	
	public boolean isSetting( String data )
	{
		
        String[] str = data.split( "usersetting:" );
       
		if( str.length == 2 )
		{
			savestr = str[1];
			return true;
		}
		
		return false;
		
	}
	
	public void SaveSetting( )
	{  
		String[] loadfiles = savestr.split("<loadfile>"); 
		String[] prvmsga = loadfiles[1].split("<prvmsg>");
		
		loadfile.addElement( Integer.parseInt(loadfiles[0]) );
		prvmsg.addElement( Boolean.parseBoolean( prvmsga[0] ) );
	}
	
	
	public void ClearSetting( int index )
	{
		loadfile.remove( index );
		prvmsg.remove(index);
		
	}
	
	public int getloadFile( int index )
	{
		return loadfile.elementAt(index);
	}
	
	public boolean getPrvMsg( int index )
	{
		return prvmsg.elementAt( index );
	}
	
	public String getSettings( String index )
	{
		return "";
	}
	
}
