#include "socket.hpp"
#include <sstd/sstd.hpp>


bool sstd::sockSSL::open(){
	struct addrinfo info;
	info.ai_flags    = 0;
	info.ai_family   = AF_UNSPEC;   // allow IPv4 or IPv6
	info.ai_socktype = SOCK_STREAM; // SOCK_STREAM: TCP, SOCK_DGRAM: UDP
	info.ai_protocol = 0;
	
	struct addrinfo *pInfo;
	int ret = getaddrinfo(this->hostNameOrAddress.c_str(), this->service.c_str(), &info, &pInfo );
	if(ret!=0){ sstd::pdbg("ERROR: getaddrinfo() was failed: %s\n",gai_strerror(ret)); return false; }
	
	struct addrinfo *rp; // for repeat
	
	for(rp=pInfo; rp!=NULL; rp=rp->ai_next){
		this->sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if(this->sock!=-1){
			if(::connect(this->sock, rp->ai_addr, rp->ai_addrlen)==0){ break; }
			sstd::pdbg("ERROR: connect() was failed.\n");
			::close(this->sock);
		}else{
			sstd::pdbg("ERROR: socket() was failed.\n");
		}
	}

	if(rp==NULL){
		sstd::pdbg("ERROR: All connection was failed.\n");
		freeaddrinfo(pInfo);
		return false;
	}
	freeaddrinfo(pInfo);
	
	// - init OpenSSL ------------------------------------------
		// init
	SSL_load_error_strings();
	SSL_library_init();

		// settings
//	this->ctx = SSL_CTX_new( SSLv2_client_method());	// SSLver2だけを使用する
//	this->ctx = SSL_CTX_new( SSLv3_client_method());	// SSLver3だけを使用する
//	this->ctx = SSL_CTX_new( TLSv1_client_method());	// TLSver1だけを使用する
	this->ctx = SSL_CTX_new(SSLv23_client_method());	// SSLv2,SSLv3,TLSv1すべてだけを使用する

	this->ssl = SSL_new(this->ctx);

		// beginning of the SSL connection
	SSL_set_fd(this->ssl, this->sock); // throwing socket to OpenSSL
	SSL_connect(this->ssl);
	// ----------------------------------- end of init OpenSSL -
	
	return true;
}

int sstd::sockSSL::send(const std::string& msg){
	return SSL_write(this->ssl, msg.c_str(), msg.length());
}
int sstd::sockSSL::send_withPrint(const std::string& msg){
	printf("Sending Data >> %s", msg.c_str());
	return send(msg);
}

std::string sstd::sockSSL::recv(bool& result){
	result=true;
	
	std::string recvMsg;
	char buf[1024*1024];
	for(int previous_readSize=0, readSize=1;
			previous_readSize != readSize;
			previous_readSize  = readSize	)
	{
		memset(buf, 0, sizeof(buf));
		readSize = SSL_read(this->ssl, buf, sizeof(buf)-1);
		if(readSize<=0){ break; }
		buf[readSize] = '\0';
		
		recvMsg += buf;
	}
	if(recvMsg.size()==0){ result=false; }
	return recvMsg;
}

void sstd::sockSSL::close(){
	
	// finalize of OpenSSL
	SSL_shutdown(this->ssl); // correspond to SSL_connect()
	SSL_free    (this->ssl); // correspond to SSL_new()
	SSL_CTX_free(this->ctx); // correspond to SSL_CTX_new()
	
	// disconnection of the line
	::close(this->sock);
}
