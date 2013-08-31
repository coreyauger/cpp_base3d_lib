
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "NetworkManager.h"


namespace Affine{

	Socket::Socket( const std::string hostname, const int port )
	: mHostName( hostname ),
	mSocketFd( socket( AF_INET, SOCK_STREAM, TCP ) ) 
	{
		bzero( (char*)&mServerAddr, sizeof( mServerAddr) );     // zero our memory
		// cant have structs in an init list ... ?for some unknown reason?
		mServerAddr.sin_family = AF_INET; 
		mServerAddr.sin_port = htons( port );
		mServerAddr.sin_addr.s_addr = INADDR_ANY;	
		if( mSocketFd < 0 ){                                      // error getting socket
			perror("socket failed");
			exit( 1 );
		}	
		int on=1;
		if( setsockopt( socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(int) ) == -1 )
		{
			perror( "setsockopt error" );
			exit( 1 );	
		}
		if( bind( mSocketFd, (struct sockaddr*)&mServerAddr, sizeof(mServerAddr) ) < 0 ) // assign a name to the socket
		{
			perror( "bind error" );
			exit( 1 );	
		}
		if( listen( mSocketFd, MAX_CONNECTIONS ) < 0)                // listen for connectionsions
		{
			perror( "listen fail" );
			exit( 1 );
		}
	}
	
	bool Socket::send( const void* data ) const
	{
		return true;	
	}
	
	int Socket::recieve( void *data ) const 
	{
		return 0;	
	}

	NetworkManager::NetworkManager( )
	: mHost( new Socket( "localhost", PORT ) )
	{
		init( );
	}
	
	void NetworkManager::init( )
	{
		/* Put this shit in the Host class with overloaded << ops *****************************/
		
		// construct a posix thread to listen on our socket now.	
	}
	
	/*	
	void NetworkManager::pthreadAcceptState( )
	{
	//	struct sockaddr clientAddr;
	//	int addrLen = sizeof( struct sockaddr );
		for( ;; )
		{
			//conn_fd = accept( mSocketFd, (struct sockaddr*)&clientAddr, &addrLen );	
			
		}	
	}
	*/	
	void NetworkManager::addSocket( const Socket socket )
	{
		
		
	}
	
	
	void NetworkManager::sendFile( const void* data, const std::string hostname="all" )
	{
			
	}
	
}

