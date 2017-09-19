
public class Config {

	static String port = "128";
	static String pathsave = "A:\\";
	static String addr = "localhost";
	static String pathget = "A:\\workspace";
	static int loadfile = 1;
	static String prvmsg = "false";
	
	
	public Config() {
		
		
	}
	
	static int getLoadFile()
	{
		return loadfile;
	}
	
	static String getprvmsg()
	{
		return prvmsg;
	}
	
	static String getAddres()
	{
		return addr;
	}
	
	
	static String getPathSave()
	{
		return pathsave;
	}
	
	
	static void setPathSave( String path)
	{
		pathsave = path;
	}
	
	
	static String getPort()
	{
		return port;
	}
	
	
	static void setPort( String data)
	{
		port = data;
	}
	
	
	static void setAddres( String data)
	{
		addr = data;
	}

	static void setPrvMsg( String data )
	{
		prvmsg = data;
	}
	
	
	static void setLoadFile( int data)
	{
		loadfile = data;
	}

}
