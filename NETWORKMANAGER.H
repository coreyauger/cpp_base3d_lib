


#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H


#include <map>
#include <string>
#include <memory>
#include <netinet/in.h>
//#include <pthread.h>

const int  TCP 			= 0;
const int  PORT			= 7676;
const int  MAX_CONNECTIONS 	= 5;

namespace Affine{


	class Socket
	{
	private:
		const std::string	mHostName;
		int			mSocketFd;
		struct sockaddr_in 	mServerAddr;
	public:
		Socket( const std::string hostname, const int port );
		inline const std::string* getHostName() { return &mHostName; };
		bool accept( Socket &socket ) const;
		
		bool send( const void* data ) const;
		int recieve( void* data ) const;
	};


	class NetworkManager
	{
	private:
		std::auto_ptr< Socket >		mHost;
		NetworkManager 			*mInstance;
		std::map<std::string, Socket> 	mHostsMap; 
		
		
		void init( );
	protected:
		NetworkManager( );	
		
	public:	
		virtual ~NetworkManager() {};
		void addSocket( const Socket socket );
		void sendFile( const void* data, const std::string hostname );
	
	};


}
#endif

